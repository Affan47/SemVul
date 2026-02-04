#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
step1_build_caches.py - Build PyG caches for all embedding types

Usage:
    python step1_build_caches.py
    
    # Or with custom paths:
    python step1_build_caches.py \
        --cache-root /path/to/cache \
        --vocab-dir /path/to/vocab \
        --only codebert_128d  # Build only one
"""

import argparse
import subprocess
import sys
from pathlib import Path


# ============================================================================
# CONFIGURATION - UPDATE THESE PATHS
# ============================================================================

DEFAULT_CONFIG = {
    "cache_root": "./Clean_exports/cache_devign_v2",
    "vocab_dir": "./Clean_exports/devign_vocab_normfunc_v2",
    "train_manifest": "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv",
    "val_manifest": "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv",
    "test_manifest": "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv",
    "train_json": "./CPGs/normalized_devign_functions/train",
    "val_json": "./CPGs/normalized_devign_functions/validation",
    "test_json": "./CPGs/normalized_devign_functions/test",
}

# Embedding configurations
EMBEDDING_CONFIGS = {
    "codebert_128d": {
        "sqlite": "codebert_128d.sqlite",
        "cache_tag": "codebert_128d",
        "expected_dim": 156,  # 28 + 128
    },
    "codet5p_256d": {
        "sqlite": "T5_256d.sqlite",
        "cache_tag": "codet5p_256d",
        "expected_dim": 284,  # 28 + 256
    },
    "unixcoder_768d": {
        "sqlite": "unixcoder_768d.sqlite",
        "cache_tag": "unixcoder_768d",
        "expected_dim": 796,  # 28 + 768
    },
}


def build_cache(config: dict, embedding_name: str, embedding_config: dict):
    """Build cache for a single embedding type."""
    
    cache_root = Path(config["cache_root"])
    sqlite_path = cache_root / embedding_config["sqlite"]
    
    if not sqlite_path.exists():
        print(f"❌ SQLite not found: {sqlite_path}")
        return False
    
    print(f"\n{'='*70}")
    print(f"Building cache: {embedding_name}")
    print(f"SQLite: {sqlite_path}")
    print(f"Expected x_dim: {embedding_config['expected_dim']}")
    print(f"{'='*70}\n")
    
    # Build command
    cmd = [
        sys.executable, "cache_manager.py",
        "--cache-root", str(cache_root),
        "--vocab-dir", config["vocab_dir"],
        "--codebert-sqlite", str(sqlite_path),
        "--dataset-name", "devign_normfunc_v2",
        "--cache-tag", embedding_config["cache_tag"],
        "--use-code-embeddings", "--one-hot",
        "--fusion-mode", "early_concat",
        "--embedding-fallback", "zero",
        "--min-nodes", "1",
        "--merge-to-zip", "--delete-shards-after-merge",
        "--train-manifest", config["train_manifest"],
        "--train-json-root", config["train_json"],
        "--val-manifest", config["val_manifest"],
        "--val-json-root", config["val_json"],
        "--test-manifest", config["test_manifest"],
        "--test-json-root", config["test_json"],
    ]
    
    try:
        result = subprocess.run(cmd, check=True)
        print(f"\n✅ Successfully built cache: {embedding_name}")
        return True
    except subprocess.CalledProcessError as e:
        print(f"\n❌ Failed to build cache: {embedding_name}")
        print(f"   Error: {e}")
        return False


def main():
    parser = argparse.ArgumentParser(description="Build PyG caches for all embeddings")
    parser.add_argument("--cache-root", type=str, default=DEFAULT_CONFIG["cache_root"])
    parser.add_argument("--vocab-dir", type=str, default=DEFAULT_CONFIG["vocab_dir"])
    parser.add_argument("--only", type=str, choices=list(EMBEDDING_CONFIGS.keys()),
                       help="Build only this embedding type")
    args = parser.parse_args()
    
    config = DEFAULT_CONFIG.copy()
    config["cache_root"] = args.cache_root
    config["vocab_dir"] = args.vocab_dir
    
    print("="*70)
    print("STEP 1: Building PyG Caches")
    print("="*70)
    print(f"Cache root: {config['cache_root']}")
    print(f"Vocab dir: {config['vocab_dir']}")
    
    # Determine which to build
    if args.only:
        to_build = {args.only: EMBEDDING_CONFIGS[args.only]}
    else:
        to_build = EMBEDDING_CONFIGS
    
    # Build each
    results = {}
    for name, emb_config in to_build.items():
        success = build_cache(config, name, emb_config)
        results[name] = success
    
    # Summary
    print("\n" + "="*70)
    print("BUILD SUMMARY")
    print("="*70)
    
    for name, success in results.items():
        status = "✅ Success" if success else "❌ Failed"
        print(f"  {name}: {status}")
    
    # Show how to find signatures
    print("\n" + "="*70)
    print("NEXT STEPS")
    print("="*70)
    print("\nFind your cache signatures:")
    print(f"  ls -la {config['cache_root']}/devign_normfunc_v2/train/")
    print("\nThen update the SIGNATURES in step2_train.py")


if __name__ == "__main__":
    main()
