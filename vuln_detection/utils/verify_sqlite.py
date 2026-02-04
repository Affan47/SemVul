#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
verify_sqlite_caches.py - Verify all SQLite embedding caches are valid

This script checks:
1. Database structure (embeddings table, emb_config table)
2. Embedding dimensions match expected
3. No corruption (can read all embeddings)
4. Consistency between emb_config and actual BLOB size
"""

import sqlite3
import sys
from pathlib import Path
from typing import Dict, Any, Optional
import numpy as np


def verify_sqlite_cache(db_path: Path, expected_dim: Optional[int] = None) -> Dict[str, Any]:
    """
    Verify SQLite embedding cache.
    
    Returns dict with verification results.
    """
    results = {
        "path": str(db_path),
        "exists": db_path.exists(),
        "valid": False,
        "errors": [],
        "warnings": [],
        "stats": {},
    }
    
    if not db_path.exists():
        results["errors"].append(f"File not found: {db_path}")
        return results
    
    try:
        con = sqlite3.connect(str(db_path), timeout=30.0)
        cur = con.cursor()
        
        # 1. Check embeddings table exists
        cur.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='embeddings'")
        if not cur.fetchone():
            results["errors"].append("Missing 'embeddings' table")
            con.close()
            return results
        
        # 2. Count rows
        cur.execute("SELECT COUNT(*) FROM embeddings")
        row_count = cur.fetchone()[0]
        results["stats"]["total_rows"] = row_count
        
        if row_count == 0:
            results["errors"].append("embeddings table is empty")
            con.close()
            return results
        
        # 3. Get dimension from emb_config
        emb_config = {}
        try:
            cur.execute("SELECT key, value FROM emb_config")
            emb_config = {k: v for k, v in cur.fetchall()}
            results["stats"]["emb_config"] = emb_config
        except sqlite3.OperationalError:
            results["warnings"].append("emb_config table not found")
        
        config_dim = int(emb_config.get("dim", 0)) if emb_config.get("dim") else None
        
        # 4. Get dimension from embeddings.dim column
        dim_from_column = None
        try:
            cur.execute("SELECT dim FROM embeddings LIMIT 1")
            row = cur.fetchone()
            if row and row[0]:
                dim_from_column = int(row[0])
        except sqlite3.OperationalError:
            results["warnings"].append("'dim' column not found in embeddings table")
        
        # 5. Get dimension from BLOB size
        cur.execute("SELECT vec FROM embeddings LIMIT 1")
        blob = cur.fetchone()[0]
        blob_dim = len(np.frombuffer(blob, dtype=np.float32))
        
        results["stats"]["dim_from_config"] = config_dim
        results["stats"]["dim_from_column"] = dim_from_column
        results["stats"]["dim_from_blob"] = blob_dim
        
        # 6. Verify consistency
        actual_dim = blob_dim
        
        if config_dim and config_dim != blob_dim:
            results["errors"].append(
                f"Dimension mismatch: emb_config={config_dim}, blob={blob_dim}"
            )
        
        if dim_from_column and dim_from_column != blob_dim:
            results["errors"].append(
                f"Dimension mismatch: column={dim_from_column}, blob={blob_dim}"
            )
        
        if expected_dim and actual_dim != expected_dim:
            results["errors"].append(
                f"Dimension mismatch: expected={expected_dim}, actual={actual_dim}"
            )
        
        results["stats"]["actual_dim"] = actual_dim
        
        # 7. Check a sample of embeddings
        cur.execute("SELECT sha256, vec FROM embeddings LIMIT 100")
        sample_rows = cur.fetchall()
        
        corrupt_count = 0
        nan_count = 0
        for sha, vec_blob in sample_rows:
            try:
                vec = np.frombuffer(vec_blob, dtype=np.float32)
                if len(vec) != actual_dim:
                    corrupt_count += 1
                if np.isnan(vec).any():
                    nan_count += 1
            except Exception as e:
                corrupt_count += 1
        
        if corrupt_count > 0:
            results["errors"].append(f"{corrupt_count}/100 sample rows have wrong dimension")
        
        if nan_count > 0:
            results["warnings"].append(f"{nan_count}/100 sample rows contain NaN values")
        
        results["stats"]["sample_size"] = len(sample_rows)
        results["stats"]["corrupt_in_sample"] = corrupt_count
        results["stats"]["nan_in_sample"] = nan_count
        
        # 8. Check model info
        model_name = emb_config.get("model", "unknown")
        results["stats"]["model"] = model_name
        
        con.close()
        
        # Final verdict
        if not results["errors"]:
            results["valid"] = True
        
    except Exception as e:
        results["errors"].append(f"Database error: {str(e)}")
    
    return results


def print_verification_report(results: Dict[str, Any], name: str):
    """Print formatted verification report."""
    print(f"\n{'='*70}")
    print(f"📦 {name}")
    print(f"{'='*70}")
    print(f"Path: {results['path']}")
    
    if not results["exists"]:
        print("❌ FILE NOT FOUND")
        return
    
    stats = results.get("stats", {})
    
    # Status
    if results["valid"]:
        print("✅ VALID")
    else:
        print("❌ INVALID")
    
    # Dimensions
    print(f"\n📐 Dimensions:")
    print(f"   From emb_config: {stats.get('dim_from_config', 'N/A')}")
    print(f"   From column:     {stats.get('dim_from_column', 'N/A')}")
    print(f"   From BLOB:       {stats.get('dim_from_blob', 'N/A')}")
    print(f"   Actual:          {stats.get('actual_dim', 'N/A')}")
    
    # Stats
    print(f"\n📊 Statistics:")
    print(f"   Total rows: {stats.get('total_rows', 0):,}")
    print(f"   Model: {stats.get('model', 'unknown')}")
    
    # Config
    if stats.get("emb_config"):
        print(f"\n⚙️ Config:")
        for k, v in stats["emb_config"].items():
            print(f"   {k}: {v}")
    
    # Errors
    if results["errors"]:
        print(f"\n❌ Errors:")
        for err in results["errors"]:
            print(f"   • {err}")
    
    # Warnings
    if results["warnings"]:
        print(f"\n⚠️ Warnings:")
        for warn in results["warnings"]:
            print(f"   • {warn}")
    
    # Expected dimensions for cache_manager
    dim = stats.get("actual_dim", 768)
    onehot = 28  # Typical for Devign
    print(f"\n📝 For cache_manager.py (early_concat mode):")
    print(f"   One-hot dim: {onehot}")
    print(f"   Embedding dim: {dim}")
    print(f"   Final x_dim: {onehot + dim}")


def main():
    import argparse
    
    parser = argparse.ArgumentParser(description="Verify SQLite embedding caches")
    parser.add_argument("sqlite_files", nargs="+", type=Path, 
                       help="SQLite files to verify")
    parser.add_argument("--expected-dim", type=int, default=None,
                       help="Expected embedding dimension")
    
    args = parser.parse_args()
    
    print("="*70)
    print("🔍 SQLite Embedding Cache Verification")
    print("="*70)
    
    all_valid = True
    
    for db_path in args.sqlite_files:
        results = verify_sqlite_cache(db_path, args.expected_dim)
        print_verification_report(results, db_path.name)
        
        if not results["valid"]:
            all_valid = False
    
    # Summary
    print(f"\n{'='*70}")
    print("📋 SUMMARY")
    print(f"{'='*70}")
    
    if all_valid:
        print("✅ All SQLite caches are valid and ready for cache_manager.py")
    else:
        print("❌ Some caches have issues. Review errors above.")
    
    # Usage hint
    print(f"\n💡 Usage with cache_manager.py:")
    print("""
    # For each SQLite, run with appropriate cache-tag:
    
    # CodeBERT 128d
    python cache_manager.py \\
        --codebert-sqlite /path/to/codebert_128d.sqlite \\
        --cache-tag codebert_128d \\
        --fusion-mode early_concat ...
    
    # CodeT5+ 256d
    python cache_manager.py \\
        --codebert-sqlite /path/to/T5_256d.sqlite \\
        --cache-tag codet5p_256d \\
        --fusion-mode early_concat ...
    
    # UniXcoder 768d
    python cache_manager.py \\
        --codebert-sqlite /path/to/unixcoder_768d.sqlite \\
        --cache-tag unixcoder_768d \\
        --fusion-mode early_concat ...
    """)
    
    return 0 if all_valid else 1


if __name__ == "__main__":
    sys.exit(main())
