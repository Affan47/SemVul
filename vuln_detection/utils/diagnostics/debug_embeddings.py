#!/usr/bin/env python3
"""
debug_embeddings.py - Trace why embeddings aren't being loaded
"""

import sqlite3
import hashlib
import json
from pathlib import Path
import sys

def normalize_for_embedding_v1(text):
    """Version 1: Simple normalization."""
    import re
    if not isinstance(text, str):
        return ""
    return re.sub(r'\s+', ' ', text.strip())

def sha256_hash(text):
    """Compute SHA256 hash."""
    return hashlib.sha256(text.encode('utf-8', errors='ignore')).hexdigest()

def debug_embedding_lookup(sqlite_path: str, graphson_path: str):
    """Debug embedding lookup for a single GraphSON file."""
    
    # Load SQLite
    conn = sqlite3.connect(sqlite_path)
    conn.row_factory = sqlite3.Row
    
    # Check total embeddings
    count = conn.execute("SELECT COUNT(*) FROM embeddings").fetchone()[0]
    print(f"\n📊 Embedding cache has {count:,} entries")
    
    # Get sample hashes from SQLite
    sample_hashes = [r['sha256'] for r in conn.execute("SELECT sha256 FROM embeddings LIMIT 5").fetchall()]
    print(f"\n📝 Sample hashes in SQLite:")
    for h in sample_hashes:
        print(f"   {h[:32]}...")
    
    # Load GraphSON and extract texts
    print(f"\n📂 Loading GraphSON: {graphson_path}")
    with open(graphson_path, 'r') as f:
        doc = json.load(f)
    
    # Unwrap GraphSON
    def unwrap(obj):
        if isinstance(obj, dict):
            if "@value" in obj:
                return unwrap(obj["@value"])
            return {k: unwrap(v) for k, v in obj.items()}
        elif isinstance(obj, list):
            return [unwrap(item) for item in obj]
        return obj
    
    doc = unwrap(doc)
    vertices = doc.get("vertices", [])
    print(f"   Found {len(vertices)} vertices")
    
    # Property keys by node type (from cpg_config)
    PROPERTY_KEYS = {
        "CALL": ("CODE", "NAME"),
        "IDENTIFIER": ("NAME", "CODE"),
        "LITERAL": ("CODE",),
        "METHOD": ("NAME", "FULL_NAME"),
        "LOCAL": ("NAME", "CODE"),
        "FIELD_IDENTIFIER": ("CODE", "NAME"),
        "BLOCK": ("CODE",),
        "CONTROL_STRUCTURE": ("CODE", "CONTROL_STRUCTURE_TYPE"),
        "RETURN": ("CODE",),
        "METHOD_PARAMETER_IN": ("NAME", "CODE"),
        "UNKNOWN": ("CODE",),
    }
    
    # Extract texts and check lookups
    found = 0
    not_found = 0
    texts_tried = []
    
    for v in vertices[:20]:  # Check first 20 vertices
        label = v.get("label", "UNKNOWN")
        props = v.get("properties", {})
        
        keys = PROPERTY_KEYS.get(label, ("CODE", "NAME"))
        
        for key in keys:
            if key not in props:
                continue
            
            prop_val = unwrap(props[key])
            if isinstance(prop_val, list) and prop_val:
                text = prop_val[0]
            elif isinstance(prop_val, str):
                text = prop_val
            else:
                continue
            
            if not text or not text.strip():
                continue
            
            # Normalize and hash
            normalized = normalize_for_embedding_v1(text)
            text_hash = sha256_hash(normalized)
            
            # Check if in SQLite
            row = conn.execute("SELECT dim FROM embeddings WHERE sha256 = ?", (text_hash,)).fetchone()
            
            status = "✅ FOUND" if row else "❌ NOT FOUND"
            if row:
                found += 1
            else:
                not_found += 1
            
            texts_tried.append({
                "label": label,
                "key": key,
                "text": text[:50] + "..." if len(text) > 50 else text,
                "normalized": normalized[:50] + "..." if len(normalized) > 50 else normalized,
                "hash": text_hash[:16] + "...",
                "status": status
            })
            
            break  # Only first matching key
    
    print(f"\n🔍 Embedding lookup results (first 20 vertices):")
    print(f"   Found: {found}")
    print(f"   Not found: {not_found}")
    
    print(f"\n📋 Details:")
    for t in texts_tried[:10]:
        print(f"   {t['label']:20s} | {t['key']:8s} | {t['status']}")
        print(f"      Text: {t['text']}")
        print(f"      Hash: {t['hash']}")
    
    # Check if ANY hash from GraphSON exists in SQLite
    print(f"\n🔬 Searching for any matching hash...")
    all_hashes_from_graph = set()
    for v in vertices:
        props = v.get("properties", {})
        for key, val in props.items():
            val = unwrap(val)
            if isinstance(val, list) and val:
                text = val[0]
            elif isinstance(val, str):
                text = val
            else:
                continue
            if text:
                all_hashes_from_graph.add(sha256_hash(normalize_for_embedding_v1(text)))
    
    print(f"   Unique hashes from GraphSON: {len(all_hashes_from_graph)}")
    
    # Check overlap
    matches = 0
    for h in list(all_hashes_from_graph)[:1000]:
        if conn.execute("SELECT 1 FROM embeddings WHERE sha256 = ?", (h,)).fetchone():
            matches += 1
    
    print(f"   Matches found (first 1000): {matches}")
    
    if matches == 0:
        print(f"\n⚠️ PROBLEM: No hashes match!")
        print(f"   This suggests a normalization mismatch between:")
        print(f"   - multi_extractor.py (when creating embeddings)")
        print(f"   - cache_manager.py (when looking up embeddings)")
        print(f"\n   Check shared_text_norm.py is used consistently!")
    
    conn.close()


if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser()
    parser.add_argument("--sqlite", required=True, help="Path to embedding SQLite")
    parser.add_argument("--graphson", required=True, help="Path to a sample GraphSON file")
    
    args = parser.parse_args()
    debug_embedding_lookup(args.sqlite, args.graphson)


"""

# Find a sample GraphSON file
SAMPLE_JSON=$(find ./CPGs/original_devign_functions/train -name "export.json" | head -1)

python debug_embeddings.py \
    --sqlite "./Clean_exports/cache_devign_v2/graphcodebert_256d_full_filtered.sqlite" \
    --graphson "$SAMPLE_JSON"
"""    