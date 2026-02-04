#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
inspect_raw_data.py - Inspect raw CPG data and embeddings

Shows actual text being extracted from nodes and embeddings applied.

Usage:
    python inspect_raw_data.py \
        --graphson-path /path/to/export.json \
        --embedding-db /path/to/embeddings.sqlite \
        --num-nodes 20
"""

import argparse
import json
import sqlite3
import sys
import hashlib
import re
from pathlib import Path
from typing import Dict, List, Optional, Any

import numpy as np


# =============================================================================
# TEXT NORMALIZATION (mirror of shared_text_norm.py)
# =============================================================================

IGNORED_TOKENS = {
    "->", "::", "==", "!=", ">=", "<=", "&&", "||", "++", "--", 
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
    "...", "::", "->*", ".*", "=", "+", "-", "*", "/", "%",
    "&", "|", "^", "!", "~", "?", ":", ",", ";", "{", "}", "(", ")", "[", "]"
}
PLACEHOLDER_SET = {"<empty>", "<global>", "<includes>", "<unknown>", "ANY"}


def normalize_for_embedding(s: str) -> str:
    """Normalize text for embedding lookup."""
    if not s or not isinstance(s, str):
        return ""
    
    s = s.replace("\r", " ").replace("\n", " ")
    s = re.sub(r'\s+', ' ', s).strip()
    
    if not s:
        return ""
    
    if s in IGNORED_TOKENS:
        return ""
    
    if s in PLACEHOLDER_SET:
        return ""
    
    if re.match(r"^<.*?>$", s):
        return ""
    
    if len(s) > 2000:
        return ""
    
    if len(s) < 2 and not s.isalnum():
        return ""
    
    return s.strip()


def sha256_normalized(s: str) -> str:
    n = normalize_for_embedding(s)
    return hashlib.sha256(n.encode("utf-8", errors="ignore")).hexdigest()


# =============================================================================
# GRAPHSON PARSING
# =============================================================================

def unwrap_graphson(val):
    """Unwrap GraphSON v3 type wrappers."""
    if isinstance(val, dict):
        if "@value" in val:
            return unwrap_graphson(val["@value"])
        return {k: unwrap_graphson(v) for k, v in val.items()}
    elif isinstance(val, list):
        return [unwrap_graphson(x) for x in val]
    return val


def load_graphson(path: Path) -> Optional[Dict]:
    """Load and parse GraphSON file."""
    try:
        with open(path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        return unwrap_graphson(data)
    except Exception as e:
        print(f"Error loading {path}: {e}")
        return None


# Property extraction priority by label
LABEL_TO_PROPERTY_KEYS = {
    "CALL": ("CODE", "NAME", "METHOD_FULL_NAME", "SIGNATURE"),
    "IDENTIFIER": ("CODE", "NAME", "TYPE_FULL_NAME"),
    "LITERAL": ("CODE", "TYPE_FULL_NAME"),
    "FIELD_IDENTIFIER": ("CODE", "CANONICAL_NAME"),
    "METHOD": ("CODE", "NAME", "FULL_NAME", "SIGNATURE"),
    "METHOD_REF": ("CODE", "METHOD_FULL_NAME", "TYPE_FULL_NAME"),
    "CONTROL_STRUCTURE": ("CODE", "CONTROL_STRUCTURE_TYPE"),
    "BLOCK": ("CODE", "TYPE_FULL_NAME"),
    "RETURN": ("CODE",),
    "LOCAL": ("CODE", "NAME", "TYPE_FULL_NAME"),
    "JUMP_TARGET": ("CODE", "NAME"),
    "TYPE_DECL": ("CODE", "NAME", "FULL_NAME"),
}

SEMANTIC_NODES = {
    "CALL", "IDENTIFIER", "BLOCK", "METHOD", "LITERAL",
    "FIELD_IDENTIFIER", "TYPE_DECL", "LOCAL", "CONTROL_STRUCTURE",
    "JUMP_TARGET", "RETURN", "METHOD_REF", "UNKNOWN", "MEMBER",
    "IMPORT", "DEPENDENCY"
}


def extract_property_value(prop):
    """Extract string value from property."""
    if isinstance(prop, str):
        return prop
    if isinstance(prop, dict):
        if "@value" in prop:
            return extract_property_value(prop["@value"])
        if "value" in prop:
            return extract_property_value(prop["value"])
    if isinstance(prop, list) and prop:
        first = prop[0]
        if isinstance(first, dict):
            return extract_property_value(first.get("@value") or first.get("value", ""))
        return str(first)
    return str(prop) if prop else ""


def get_node_text(vertex: Dict) -> tuple:
    """Extract text from vertex and return (raw_text, normalized_text, source_key)."""
    label = vertex.get("label", "")
    props = vertex.get("properties", {})
    
    keys = LABEL_TO_PROPERTY_KEYS.get(label, ("CODE", "NAME"))
    
    for key in keys:
        if key not in props:
            continue
        
        raw_text = extract_property_value(props[key])
        if raw_text:
            normalized = normalize_for_embedding(raw_text)
            return (raw_text, normalized, key)
    
    return (None, None, None)


# =============================================================================
# EMBEDDING DATABASE
# =============================================================================

class EmbeddingDB:
    def __init__(self, db_path: str):
        self.conn = sqlite3.connect(db_path)
        self.conn.row_factory = sqlite3.Row
        
        # Get embedding dimension
        row = self.conn.execute("SELECT dim FROM embeddings LIMIT 1").fetchone()
        self.dim = row["dim"] if row else 0
        
        # Get model info
        config_row = self.conn.execute(
            "SELECT value FROM emb_config WHERE key = 'model'"
        ).fetchone()
        self.model = config_row["value"] if config_row else "unknown"
        
        # Get total count
        count_row = self.conn.execute("SELECT COUNT(*) as cnt FROM embeddings").fetchone()
        self.total_count = count_row["cnt"]
        
        print(f"Embedding DB: {self.model}, dim={self.dim}, entries={self.total_count}")
    
    def lookup(self, text: str) -> Optional[np.ndarray]:
        """Look up embedding by normalized text."""
        if not text:
            return None
        
        text_hash = sha256_normalized(text)
        
        row = self.conn.execute(
            "SELECT vec, dim FROM embeddings WHERE sha256 = ?",
            (text_hash,)
        ).fetchone()
        
        if row:
            return np.frombuffer(row["vec"], dtype=np.float32).reshape(row["dim"])
        return None
    
    def close(self):
        self.conn.close()


# =============================================================================
# MAIN INSPECTION
# =============================================================================

def inspect_graphson(graphson_path: str, embedding_db: Optional[EmbeddingDB], 
                     num_nodes: int = 20, show_all: bool = False):
    """Inspect a GraphSON file and show node text + embeddings."""
    
    path = Path(graphson_path)
    doc = load_graphson(path)
    
    if not doc:
        print("Failed to load GraphSON")
        return
    
    vertices = doc.get("vertices", [])
    edges = doc.get("edges", [])
    
    print(f"\n{'='*80}")
    print(f"GRAPHSON FILE: {path.name}")
    print(f"{'='*80}")
    print(f"Total vertices: {len(vertices)}")
    print(f"Total edges: {len(edges)}")
    
    # Count by label
    label_counts = {}
    for v in vertices:
        label = v.get("label", "UNKNOWN")
        label_counts[label] = label_counts.get(label, 0) + 1
    
    print(f"\nNode type distribution:")
    for label, count in sorted(label_counts.items(), key=lambda x: -x[1]):
        marker = "✓" if label in SEMANTIC_NODES else "✗"
        print(f"  {marker} {label}: {count}")
    
    # Show semantic nodes with text
    print(f"\n{'='*80}")
    print(f"SEMANTIC NODES (first {num_nodes})")
    print(f"{'='*80}")
    
    shown = 0
    call_nodes = []
    emb_hits = 0
    emb_misses = 0
    
    for v in vertices:
        label = v.get("label", "")
        
        if not show_all and label not in SEMANTIC_NODES:
            continue
        
        raw_text, norm_text, source_key = get_node_text(v)
        
        if label == "CALL":
            call_nodes.append({
                "raw": raw_text,
                "norm": norm_text,
                "key": source_key,
            })
        
        if shown >= num_nodes:
            continue
        
        shown += 1
        
        print(f"\n--- Node {shown} ---")
        print(f"Label: {label}")
        print(f"Property key: {source_key}")
        print(f"Raw text: {repr(raw_text)[:100]}")
        print(f"Normalized: {repr(norm_text)[:100]}")
        
        if embedding_db and norm_text:
            emb = embedding_db.lookup(norm_text)
            if emb is not None:
                emb_hits += 1
                print(f"Embedding: ✓ FOUND (norm={np.linalg.norm(emb):.4f}, mean={emb.mean():.4f})")
                print(f"           First 5 dims: {emb[:5].tolist()}")
            else:
                emb_misses += 1
                print(f"Embedding: ✗ NOT FOUND")
                print(f"           Hash: {sha256_normalized(norm_text)[:16]}...")
    
    # Special analysis of CALL nodes
    if call_nodes:
        print(f"\n{'='*80}")
        print(f"CALL NODE ANALYSIS ({len(call_nodes)} nodes)")
        print(f"{'='*80}")
        
        call_with_emb = 0
        call_texts = []
        
        for cn in call_nodes:
            if cn["norm"]:
                call_texts.append(cn["norm"])
                if embedding_db:
                    emb = embedding_db.lookup(cn["norm"])
                    if emb is not None:
                        call_with_emb += 1
        
        print(f"\nCALL nodes with text: {len(call_texts)}/{len(call_nodes)}")
        
        if embedding_db:
            print(f"CALL nodes with embeddings: {call_with_emb}/{len(call_texts)}")
        
        # Show unique CALL texts
        unique_calls = list(set(call_texts))
        print(f"\nUnique CALL texts ({len(unique_calls)} unique):")
        for ct in unique_calls[:15]:
            marker = "✓" if (embedding_db and embedding_db.lookup(ct)) else "✗"
            print(f"  {marker} {repr(ct)[:60]}")
        
        # Look for security-sensitive APIs
        sensitive_apis = [
            "strcpy", "strcat", "sprintf", "gets", "scanf",
            "malloc", "free", "realloc", "calloc",
            "memcpy", "memmove", "memset",
            "system", "exec", "popen",
            "read", "write", "open", "close",
            "recv", "send", "socket",
        ]
        
        found_sensitive = []
        for ct in unique_calls:
            ct_lower = ct.lower()
            for api in sensitive_apis:
                if api in ct_lower:
                    found_sensitive.append((api, ct))
                    break
        
        if found_sensitive:
            print(f"\n⚠️  SECURITY-SENSITIVE APIS FOUND:")
            for api, text in found_sensitive[:10]:
                print(f"  {api}: {repr(text)[:50]}")
    
    # Summary
    if embedding_db:
        total = emb_hits + emb_misses
        coverage = emb_hits / total if total > 0 else 0
        print(f"\n{'='*80}")
        print(f"EMBEDDING COVERAGE SUMMARY")
        print(f"{'='*80}")
        print(f"Hits: {emb_hits}, Misses: {emb_misses}, Coverage: {coverage*100:.1f}%")


def main():
    parser = argparse.ArgumentParser(description="Inspect raw CPG data")
    parser.add_argument("--graphson-path", type=str, required=True,
                       help="Path to export.json GraphSON file")
    parser.add_argument("--embedding-db", type=str, default=None,
                       help="Path to embeddings.sqlite (optional)")
    parser.add_argument("--num-nodes", type=int, default=20,
                       help="Number of nodes to show")
    parser.add_argument("--show-all", action="store_true",
                       help="Show all nodes, not just semantic")
    args = parser.parse_args()
    
    embedding_db = None
    if args.embedding_db:
        embedding_db = EmbeddingDB(args.embedding_db)
    
    inspect_graphson(
        args.graphson_path,
        embedding_db,
        args.num_nodes,
        args.show_all,
    )
    
    if embedding_db:
        embedding_db.close()


if __name__ == "__main__":
    main()


"""


python inspect_raw_data.py \
    --graphson-path ./CPGs/original_devign_functions/test/exports/test_func_0000001/export_all/export.json \
    --embedding-db ./Clean_exports/cache_devign_v2/graphcodebert_256d_full.sqlite \
    --num-nodes 30

"""