#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
vocab_builder.py - V7 for Original (Non-Normalized) CPGs

Updates in V7:
  - Robust TinkerPop GraphSON v3 parsing with @type/@value unwrapping
  - Support for nested property structures (g:VertexProperty, g:List)
  - Handles real function/variable names from original code
  - Improved text extraction for vulnerability-relevant nodes
  - Better statistics and validation

Supports three edge type modes from cpg_config:
  - full_filtered: 14 edge types (recommended for vulnerability detection)
  - full: 16 edge types (includes CONTAINS, SOURCE_FILE)
  - simplified: 5-class Devign scheme (AST, CFG, DFG_READ, DFG_WRITE, NCS)

USAGE:
    python vocab_builder.py --edge-mode full_filtered \\
        --manifests train_manifest.csv val_manifest.csv test_manifest.csv \\
        --json-roots /path/to/train/cpgs /path/to/val/cpgs /path/to/test/cpgs \\
        --out-dir /path/to/vocab_output
"""

import os
import sys
import argparse
import csv
import json
import re
import hashlib
from pathlib import Path
from typing import Any, Dict, Iterable, Iterator, List, Optional, Tuple, Set, Union
from collections import Counter, defaultdict

# ============================================================================
# CONFIGURATION LOADING
# ============================================================================

def load_config():
    """Load dynamic configuration from cpg_config.py and shared_text_norm.py."""
    config = {
        'cpg_config': None,
        'normalize_func': None,
        'sha256_func': None
    }
    
    SCRIPT_DIR = Path(__file__).resolve().parent
    sys.path.insert(0, str(SCRIPT_DIR))
    
    # Try parent directories too
    for parent in [SCRIPT_DIR, SCRIPT_DIR.parent, SCRIPT_DIR.parent.parent]:
        if parent.exists():
            sys.path.insert(0, str(parent))
    
    # Import cpg_config
    try:
        import cpg_config
        config['cpg_config'] = cpg_config
        print(f"[CONFIG] ✅ Loaded cpg_config (default mode: {cpg_config.DEFAULT_EDGE_MODE})")
    except ImportError as e:
        print(f"[CONFIG] ⚠️  cpg_config.py not found: {e}")
        
    # Load text processing functions
    try:
        from shared_text_norm import normalize_for_embedding, sha256_normalized
        config['normalize_func'] = normalize_for_embedding
        config['sha256_func'] = sha256_normalized
        print("[CONFIG] ✅ Loaded shared_text_norm functions")
    except ImportError:
        print("[CONFIG] ⚠️  shared_text_norm.py not found, using fallback")
    
    return config

CONFIG = load_config()
cpg_config = CONFIG['cpg_config']

# ============================================================================
# FALLBACK CONFIGURATION (if cpg_config.py not found)
# ============================================================================

if not cpg_config:
    print("[CONFIG] ⚠️  Using emergency static fallback")

    EDGE_TYPES = ["AST", "CFG", "CDG", "REACHING_DEF", "EVAL_TYPE", "ARGUMENT",
                  "REF", "CALL", "CONDITION", "DOMINATE", "POST_DOMINATE",
                  "PARAMETER_LINK", "BINDS", "ALIAS_OF"]
    
    EDGE_MAP = {
        "AST": "AST", "CFG": "CFG", "CDG": "CDG", "REACHING_DEF": "REACHING_DEF",
        "EVAL_TYPE": "EVAL_TYPE", "ARGUMENT": "ARGUMENT", "REF": "REF",
        "CALL": "CALL", "CONDITION": "CONDITION", "DOMINATE": "DOMINATE",
        "POST_DOMINATE": "POST_DOMINATE", "PARAMETER_LINK": "PARAMETER_LINK",
        "BINDS": "BINDS", "ALIAS_OF": "ALIAS_OF",
        "CONTAINS": None, "SOURCE_FILE": None,
    }

    NODE_LABEL_WHITELIST = {
        "CALL", "IDENTIFIER", "LITERAL", "METHOD", "FIELD_IDENTIFIER",
        "TYPE_DECL", "METHOD_REF", "CONTROL_STRUCTURE", "BLOCK", "RETURN",
        "LOCAL", "JUMP_TARGET",
    }

    LABEL_TO_KEYS = {
        "CALL": ("NAME", "CODE", "METHOD_FULL_NAME"),
        "IDENTIFIER": ("NAME", "CODE"),
        "LITERAL": ("CODE",),
        "METHOD": ("NAME", "FULL_NAME", "SIGNATURE"),
        "FIELD_IDENTIFIER": ("CODE", "CANONICAL_NAME"),
        "TYPE_DECL": ("NAME", "FULL_NAME"),
        "METHOD_REF": ("CODE", "METHOD_FULL_NAME"),
        "CONTROL_STRUCTURE": ("CODE",),
        "BLOCK": ("CODE",),
        "RETURN": ("CODE",),
        "LOCAL": ("NAME", "CODE"),
        "JUMP_TARGET": ("NAME", "CODE"),
    }
    
    _FALLBACK_PROPERTY_KEYS = ("CODE", "NAME", "FULL_NAME")

    def get_edge_types(mode=None): return EDGE_TYPES
    def get_edge_type_to_index(mode=None): return {e: i for i, e in enumerate(EDGE_TYPES)}
    def map_edge_type(label, mode=None): return EDGE_MAP.get(label)
    def should_include_node_type(label): return label in NODE_LABEL_WHITELIST
    def get_property_keys_for_label(label): return LABEL_TO_KEYS.get(label, _FALLBACK_PROPERTY_KEYS)
    def configure_cpg(*args, **kwargs): pass
    def get_discovery_report(): return {}
    
    class EdgeTypeMode:
        FULL = "full"
        SIMPLIFIED = "simplified"
        FULL_FILTERED = "full_filtered"
    
else:
    from cpg_config import (
        get_edge_types,
        get_edge_type_to_index,
        map_edge_type,
        should_include_node_type,
        get_property_keys_for_label,
        configure_cpg,
        get_discovery_report,
        EdgeTypeMode,
        LABEL_TO_PROPERTY_KEYS as LABEL_TO_KEYS,
    )
    
    _FALLBACK_PROPERTY_KEYS = ("CODE", "NAME", "FULL_NAME")

# Global edge mode (set by CLI)
CURRENT_EDGE_MODE = None

def set_edge_mode(mode: str):
    """Set the global edge mode."""
    global CURRENT_EDGE_MODE
    CURRENT_EDGE_MODE = mode
    if cpg_config:
        cpg_config.configure_cpg(edge_mode=mode)
    print(f"[CONFIG] Edge mode set to: {mode}")
    print(f"[CONFIG] Edge types ({len(get_edge_types(mode))}): {get_edge_types(mode)}")

# ============================================================================
# TEXT NORMALIZATION (with fallback)
# ============================================================================

def fallback_normalize(text: str) -> str:
    """Fallback normalization if shared_text_norm not available."""
    if not isinstance(text, str):
        return ""
    text = text.strip()
    text = re.sub(r'\s+', ' ', text)
    # Filter placeholders
    if text in {"<empty>", "<global>", "<unknown>", "RET", "VOID"}:
        return ""
    if "<global>" in text or "<unknown>" in text or "<empty>" in text:
        return ""
    if text.startswith("<") and text.endswith(">"):
        return ""
    return text

def fallback_sha256(text: str) -> str:
    """Fallback SHA256 if shared_text_norm not available."""
    return hashlib.sha256(text.encode('utf-8', errors='ignore')).hexdigest()

normalize_for_embedding = CONFIG['normalize_func'] or fallback_normalize
sha256_normalized = CONFIG['sha256_func'] or fallback_sha256

# TQDM (graceful fallback)
try:
    from tqdm import tqdm
except Exception:
    def tqdm(iterable=None, *a, **k):
        return iterable if iterable is not None else range(0)

# ============================================================================
# TEXT EXTRACTION CONFIG
# ============================================================================

EDGE_TEXT_KEYS: Optional[Set[str]] = {"EdgeProperty"}
MIN_LEN = 1
MAX_LEN = 4000
DROP_IF_ANGLE_BRACKETED = True
JOERN_OPERATOR_PREFIXES = ("<operator>.", "<operators>.")

PLACEHOLDER_SET: Set[str] = {
    "<empty>", "<global>", "<includes>", "<unknown>", "ANY",
    "RET", "VOID", "void",
}

FILTER_PATTERNS = ["<unknown>", "<unreachable>", "<global>", "<includes>"]

# ============================================================================
# GRAPHSON V3 PARSING (TinkerPop format)
# ============================================================================

def unwrap_graphson(obj: Any) -> Any:
    """
    Recursively unwrap TinkerPop GraphSON v3+ typed structures.
    
    Handles formats like:
      - {"@type": "g:Int64", "@value": 123}
      - {"@type": "g:List", "@value": [...]}
      - {"@type": "g:VertexProperty", "@value": {"@type": "g:List", "@value": [...]}}
    """
    try:
        if isinstance(obj, dict):
            if "@value" in obj:
                # Unwrap the @value recursively
                return unwrap_graphson(obj["@value"])
            # Regular dict - unwrap all values
            return {k: unwrap_graphson(v) for k, v in obj.items()}
        elif isinstance(obj, list):
            return [unwrap_graphson(item) for item in obj]
        else:
            return obj
    except (TypeError, KeyError, AttributeError):
        return obj


def extract_property_value(prop_data: Any) -> Any:
    """
    Extract the actual value from a GraphSON property structure.
    
    Handles nested structures like:
      {
        "@type": "g:VertexProperty",
        "@value": {
          "@type": "g:List",
          "@value": ["actual_value"]
        }
      }
    """
    unwrapped = unwrap_graphson(prop_data)
    
    # Handle nested structures
    if isinstance(unwrapped, dict):
        # Look for value key
        if "value" in unwrapped:
            return extract_property_value(unwrapped["value"])
        # Return as-is if no value key
        return unwrapped
    
    elif isinstance(unwrapped, list):
        # If single element list, return the element
        if len(unwrapped) == 1:
            return unwrapped[0]
        # Filter None values
        unwrapped = [x for x in unwrapped if x is not None]
        if len(unwrapped) == 1:
            return unwrapped[0]
        return unwrapped
    
    return unwrapped


def get_vertices_edges(doc: Dict[str, Any]) -> Tuple[List[Dict], List[Dict]]:
    """Extract vertices and edges from unwrapped GraphSON document."""
    if not isinstance(doc, dict):
        return [], []
    vertices = doc.get("vertices", [])
    edges = doc.get("edges", [])
    if not isinstance(vertices, list):
        vertices = []
    if not isinstance(edges, list):
        edges = []
    return vertices, edges


# ============================================================================
# TEXT EXTRACTION
# ============================================================================

def normalize_text(s: str) -> str:
    """Normalize text for embedding."""
    return normalize_for_embedding(s)


def is_placeholder(s: str) -> bool:
    """Check if string is a placeholder."""
    if not isinstance(s, str):
        return True
    s_stripped = s.strip()
    if s_stripped in PLACEHOLDER_SET:
        return True
    if DROP_IF_ANGLE_BRACKETED and s_stripped.startswith("<") and s_stripped.endswith(">"):
        return True
    for pattern in FILTER_PATTERNS:
        if pattern in s:
            return True
    return False


def looks_like_codey(s: str) -> bool:
    """Check if string looks like code content."""
    if not isinstance(s, str):
        return False
    L = len(s)
    if L < MIN_LEN or L > MAX_LEN:
        return False
    if L < 2 and not s.isalnum():
        return False
    return True


def extract_node_texts(vertex: Dict[str, Any]) -> Iterator[str]:
    """
    Extract text from node properties using configured property keys.
    
    Yields the first valid normalized text string by priority.
    """
    if not isinstance(vertex, dict):
        return
    
    props = vertex.get("properties", {})
    if not isinstance(props, dict):
        return
    
    label = vertex.get("label", "")
    if not label:
        return
    
    # Check if node type should be included
    if not should_include_node_type(label):
        return

    # Get property keys for this node type (priority order)
    keys = get_property_keys_for_label(label)

    # Skip operator-only CALL nodes to avoid polluting the vocab.
    if label == "CALL":
        name_prop = props.get("NAME")
        if isinstance(name_prop, list):
            for item in name_prop:
                if isinstance(item, str) and item.startswith(JOERN_OPERATOR_PREFIXES):
                    return
        elif isinstance(name_prop, str) and name_prop.startswith(JOERN_OPERATOR_PREFIXES):
            return
    
    for key in keys:
        if key not in props:
            continue
        
        try:
            prop_value = extract_property_value(props[key])
            
            candidates = []
            if isinstance(prop_value, list):
                candidates = [item for item in prop_value if isinstance(item, str)]
            elif isinstance(prop_value, str):
                candidates = [prop_value]

            for raw in candidates:
                normalized = normalize_text(raw)
                if normalized and not is_placeholder(normalized) and looks_like_codey(normalized):
                    yield normalized
                    return
        except Exception:
            continue


def extract_edge_texts(edge: Dict[str, Any]) -> Iterator[str]:
    """Extract text from edge properties."""
    if not isinstance(edge, dict):
        return
    
    props = edge.get("properties", {})
    if not isinstance(props, dict) or not props:
        return

    keys_to_check = EDGE_TEXT_KEYS if EDGE_TEXT_KEYS else set(props.keys())

    for key in keys_to_check:
        if key not in props:
            continue
        try:
            prop_value = extract_property_value(props[key])
            
            if isinstance(prop_value, str):
                normalized = normalize_text(prop_value)
                if normalized and not is_placeholder(normalized) and looks_like_codey(normalized):
                    yield normalized
            elif isinstance(prop_value, dict) and "value" in prop_value:
                v = prop_value["value"]
                if isinstance(v, str):
                    normalized = normalize_text(v)
                    if normalized and not is_placeholder(normalized) and looks_like_codey(normalized):
                        yield normalized
        except Exception:
            continue


# ============================================================================
# I/O HELPERS
# ============================================================================

def sha256_text(s: str) -> str:
    """Compute SHA256 hash of text."""
    return sha256_normalized(s)


def load_json(path: Path) -> Optional[Dict[str, Any]]:
    """Load and unwrap a GraphSON JSON file."""
    try:
        with path.open("r", encoding="utf-8") as f:
            raw = json.load(f)
        return unwrap_graphson(raw)
    except Exception as e:
        print(f"[ERROR] Failed to load {path}: {e}")
        return None


def resolve_json_path(row: Dict[str, str], root: Path) -> Optional[Path]:
    """Resolve graph JSON path from manifest row."""
    # Try explicit path first
    rel = (row.get("graph_json_path") or row.get("json_path") or "").strip()
    if rel:
        candidates = [rel] if rel.endswith(".json") else [rel + ".json", rel]
        for cand in candidates:
            cand_path = Path(cand)
            if cand_path.is_absolute():
                if cand_path.exists():
                    return cand_path
            else:
                p = root / cand_path
                if p.exists():
                    return p

    # Try function_id based paths
    func_id = (row.get("function_id") or row.get("fid") or "").strip()
    if not func_id:
        return None

    base = func_id.rsplit(".", 1)[0]
    candidates = [
        root / "exports" / base / "export_all" / "export.json",
        root / "exports" / base / "export.json",
        root / base / "export_all" / "export.json",
        root / base / "export.json",
        root / f"{base}.json",
    ]
    for cand in candidates:
        if cand.exists():
            return cand
    return None


def write_json(path: Path, obj: Any) -> None:
    """Write JSON file."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        json.dump(obj, f, ensure_ascii=False, indent=2)


def write_strings_csv(path: Path, rows: List[Tuple[str, str, str, int]]) -> None:
    """Write strings CSV file."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["sha256", "kind", "string", "count"])
        for sha, kind, text, cnt in rows:
            w.writerow([sha, kind, text, cnt])


def build_index_map_from_counter(ctr: Counter) -> Dict[str, int]:
    """Build index map from counter (most common first)."""
    return {name: idx for idx, (name, _) in enumerate(ctr.most_common())}


# ============================================================================
# GRAPH SCANNING
# ============================================================================

def scan_graph_with_discovery(
    doc: Dict[str, Any],
    node_type_ctr: Counter,
    edge_type_ctr: Counter,
    node_text_ctr: Counter,
    edge_text_ctr: Counter,
    raw_edge_label_ctr: Counter,
    label_stats: Dict[str, Dict[str, int]],
) -> int:
    """Scan a single graph and update counters."""
    vertices, edges = get_vertices_edges(doc)
    string_count = 0

    # Process vertices
    for vertex in vertices:
        if not isinstance(vertex, dict):
            continue
        label = vertex.get("label", "")
        if not label:
            continue
        
        if should_include_node_type(label):
            node_type_ctr[label] += 1
            
            if label not in label_stats:
                label_stats[label] = {"nodes": 0, "texts": 0}
            label_stats[label]["nodes"] += 1
            
            for text in extract_node_texts(vertex):
                node_text_ctr[text] += 1
                label_stats[label]["texts"] += 1
                string_count += 1

    # Process edges with current mode
    for edge in edges:
        if not isinstance(edge, dict):
            continue
        raw_label = edge.get("label", "")
        if not raw_label:
            continue
        
        raw_edge_label_ctr[raw_label] += 1
        
        # Map using current mode
        mapped = map_edge_type(raw_label, CURRENT_EDGE_MODE)
        if mapped:
            edge_type_ctr[mapped] += 1
            for text in extract_edge_texts(edge):
                edge_text_ctr[text] += 1
                string_count += 1

    return string_count


def scan_single_export(
    json_path: Path,
    node_type_ctr: Counter,
    edge_type_ctr: Counter,
    node_text_ctr: Counter,
    edge_text_ctr: Counter,
    raw_edge_label_ctr: Counter,
    label_stats: Dict[str, Dict[str, int]],
) -> Tuple[int, int]:
    """Scan a single export.json file."""
    doc = load_json(json_path)
    if not doc:
        return 0, 0
    
    string_count = scan_graph_with_discovery(
        doc, node_type_ctr, edge_type_ctr,
        node_text_ctr, edge_text_ctr,
        raw_edge_label_ctr, label_stats
    )
    
    return 1, string_count


def scan_manifest_with_discovery(
    manifest_path: Path,
    json_root: Path,
    node_type_ctr: Counter,
    edge_type_ctr: Counter,
    node_text_ctr: Counter,
    edge_text_ctr: Counter,
    raw_edge_label_ctr: Counter,
    label_stats: Dict[str, Dict[str, int]],
    show_progress: bool = True,
) -> Tuple[int, int]:
    """Scan all graphs referenced in a manifest file."""
    rows = []
    with manifest_path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        rows = list(reader)
    
    total_graphs = 0
    total_strings = 0
    missing_files = 0
    
    iterator = tqdm(rows, desc=f"Scanning {manifest_path.name}") if show_progress else rows
    
    for row in iterator:
        json_path = resolve_json_path(row, json_root)
        if not json_path:
            missing_files += 1
            continue
        
        doc = load_json(json_path)
        if not doc:
            continue
        
        string_count = scan_graph_with_discovery(
            doc, node_type_ctr, edge_type_ctr,
            node_text_ctr, edge_text_ctr,
            raw_edge_label_ctr, label_stats
        )
        
        total_graphs += 1
        total_strings += string_count
    
    if missing_files > 0:
        print(f"[WARN] {missing_files} files not found in {manifest_path.name}")
    
    return total_graphs, total_strings


# ============================================================================
# MAIN
# ============================================================================

def main():
    parser = argparse.ArgumentParser(
        description="Build vocabulary from GraphSON CPG exports (V7 - Original CPGs)"
    )
    parser.add_argument(
        "--edge-mode", "-e", type=str, default="full_filtered",
        choices=["full", "simplified", "full_filtered"],
        help="Edge type mode (default: full_filtered)"
    )
    parser.add_argument(
        "--manifests", "-m", nargs="+", type=str, default=[],
        help="Manifest CSV files to process"
    )
    parser.add_argument(
        "--json-roots", "-j", nargs="+", type=str, default=[],
        help="Root directories for JSON files (one per manifest)"
    )
    parser.add_argument(
        "--export-json", type=str, default=None,
        help="Single export.json to analyze"
    )
    parser.add_argument(
        "--out-dir", "-o", type=str, required=True,
        help="Output directory for vocabulary files"
    )
    parser.add_argument(
        "--no-progress", action="store_true",
        help="Disable progress bars"
    )
    parser.add_argument(
        "--save-summary", dest="save_summary", action="store_true", default=True,
        help="Save summary file (default: on)"
    )
    parser.add_argument(
        "--no-save-summary", dest="save_summary", action="store_false",
        help="Disable summary file"
    )
    parser.add_argument(
        "--summary-filename", type=str, default="build_summary.txt",
        help="Summary filename"
    )
    
    args = parser.parse_args()
    
    # Set edge mode
    set_edge_mode(args.edge_mode)
    
    # Get configured edge types
    edge_types = get_edge_types(args.edge_mode)
    edge_type_to_index = get_edge_type_to_index(args.edge_mode)
    
    print(f"\n{'='*70}")
    print(f"VOCAB BUILDER V7 - Original CPGs")
    print(f"{'='*70}")
    print(f"Edge Mode: {args.edge_mode}")
    print(f"Edge Types ({len(edge_types)}): {edge_types}")
    print(f"Output: {args.out_dir}")
    print(f"{'='*70}\n")
    
    # Initialize counters
    node_type_ctr = Counter()
    edge_type_ctr = Counter()
    node_text_ctr = Counter()
    edge_text_ctr = Counter()
    raw_edge_label_ctr = Counter()
    label_stats = {}
    
    total_graphs = 0
    total_strings = 0
    show_progress = not args.no_progress
    
    # Process single export
    if args.export_json:
        g, s = scan_single_export(
            Path(args.export_json),
            node_type_ctr, edge_type_ctr,
            node_text_ctr, edge_text_ctr,
            raw_edge_label_ctr, label_stats
        )
        total_graphs += g
        total_strings += s
        print(f"[INFO] Single export: {g} graphs, {s} strings")
    
    # Process manifests
    if args.manifests:
        if len(args.manifests) != len(args.json_roots):
            raise ValueError("Number of manifests must match json-roots")
        
        for manifest_path, root_path in zip(args.manifests, args.json_roots):
            manifest_file = Path(manifest_path)
            root_dir = Path(root_path)
            
            if not manifest_file.exists():
                print(f"[WARN] Manifest not found: {manifest_file}")
                continue
            if not root_dir.exists():
                print(f"[WARN] Root not found: {root_dir}")
                continue
            
            print(f"\n[INFO] Processing: {manifest_file.name}")
            g, s = scan_manifest_with_discovery(
                manifest_file, root_dir,
                node_type_ctr, edge_type_ctr,
                node_text_ctr, edge_text_ctr,
                raw_edge_label_ctr, label_stats,
                show_progress=show_progress
            )
            total_graphs += g
            total_strings += s
            print(f"[INFO] {manifest_file.name}: {g} graphs, {s} strings")
    
    # Create output directory
    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    
    # Build vocabularies
    print("\n[BUILD] Creating vocabularies...")
    
    # Node type vocab
    node_type_vocab = build_index_map_from_counter(node_type_ctr)
    write_json(out_dir / "node_type_vocab.json", node_type_vocab)
    print(f"  ✅ node_type_vocab.json ({len(node_type_vocab)} types)")
    
    # Edge type vocab - use the configured edge types
    edge_type_vocab = {name: idx for idx, name in enumerate(edge_types)}
    write_json(out_dir / "edge_type_vocab.json", edge_type_vocab)
    print(f"  ✅ edge_type_vocab.json ({len(edge_type_vocab)} types)")
    
    # Devign rel vocab (same as edge_type_vocab for compatibility)
    write_json(out_dir / "devign_rel_vocab.json", edge_type_vocab)
    print(f"  ✅ devign_rel_vocab.json ({len(edge_type_vocab)} types)")
    
    # Node/edge content vocabs
    node_content_vocab = build_index_map_from_counter(node_text_ctr)
    edge_content_vocab = build_index_map_from_counter(edge_text_ctr)
    write_json(out_dir / "node_content_vocab.json", node_content_vocab)
    write_json(out_dir / "edge_content_vocab.json", edge_content_vocab)
    print(f"  ✅ node_content_vocab.json ({len(node_content_vocab)} unique texts)")
    print(f"  ✅ edge_content_vocab.json ({len(edge_content_vocab)} unique texts)")
    
    # Strings to embed
    strings_metadata = []
    for text, count in node_text_ctr.most_common():
        sha = sha256_text(text)
        strings_metadata.append((sha, "node_content", text, count))
    for text, count in edge_text_ctr.most_common():
        sha = sha256_text(text)
        strings_metadata.append((sha, "edge_content", text, count))
    
    write_strings_csv(out_dir / "strings_to_embed.csv", strings_metadata)
    print(f"  ✅ strings_to_embed.csv ({len(strings_metadata)} strings)")
    
    # Parser signature
    parser_info = {
        "version": "7.0-original-cpg",
        "edge_mode": args.edge_mode,
        "edge_types": edge_types,
        "num_edge_types": len(edge_types),
        "devign_order": edge_types,
        "node_types": list(node_type_vocab.keys()),
        "num_node_types": len(node_type_vocab),
        "raw_edge_labels_found": dict(raw_edge_label_ctr.most_common(50)),
        "label_statistics": {
            label: {"nodes": stats["nodes"], "texts": stats["texts"]}
            for label, stats in sorted(label_stats.items(), key=lambda x: -x[1]["nodes"])
        },
        "statistics": {
            "total_graphs": total_graphs,
            "total_strings": len(strings_metadata),
            "node_types_count": len(node_type_vocab),
            "edge_types_count": len(edge_type_vocab),
            "unique_node_texts": len(node_content_vocab),
            "unique_edge_texts": len(edge_content_vocab),
        }
    }
    write_json(out_dir / "parser_sig.json", parser_info)
    print(f"  ✅ parser_sig.json")
    
    # Validation
    print(f"\n[VALIDATION] Edge type coverage:")
    present_edge_types = set(edge_type_ctr.keys())
    for et in edge_types:
        status = "✅" if et in present_edge_types else "⚠️ "
        count = edge_type_ctr.get(et, 0)
        print(f"  {status} {et}: {count:,}")
    
    print(f"\n[RAW] Top 20 raw edge labels from GraphSON:")
    for label, count in raw_edge_label_ctr.most_common(20):
        mapped = map_edge_type(label, args.edge_mode)
        mapped_str = f"→ {mapped}" if mapped else "→ (filtered)"
        print(f"  {label:20}: {count:>10,} {mapped_str}")
    
    print(f"\n[NODES] Node type distribution:")
    for label, count in node_type_ctr.most_common(15):
        texts = label_stats.get(label, {}).get("texts", 0)
        print(f"  {label:25}: {count:>8,} nodes, {texts:>10,} texts")
    
    # Top strings sample
    print(f"\n[SAMPLE] Top 20 node texts (by frequency):")
    for text, count in node_text_ctr.most_common(20):
        display = text[:50] + "..." if len(text) > 50 else text
        print(f"  {count:>6}: {display}")
    
    # Summary
    print(f"\n{'='*70}")
    print(f"VOCAB BUILD COMPLETE")
    print(f"{'='*70}")
    print(f"Edge Mode:        {args.edge_mode}")
    print(f"Edge Types:       {len(edge_types)}")
    print(f"Node Types:       {len(node_type_vocab)}")
    print(f"Graphs Processed: {total_graphs:,}")
    print(f"Unique Strings:   {len(strings_metadata):,}")
    print(f"Output:           {out_dir}")
    print(f"{'='*70}")
    
    # Save summary
    if args.save_summary:
        summary_path = out_dir / args.summary_filename
        with summary_path.open("w") as f:
            f.write(f"Vocab Build Summary (V7 - Original CPGs)\n")
            f.write(f"{'='*50}\n")
            f.write(f"Edge Mode: {args.edge_mode}\n")
            f.write(f"Edge Types ({len(edge_types)}): {edge_types}\n\n")
            f.write(f"Node Types ({len(node_type_vocab)}):\n")
            for label, count in node_type_ctr.most_common():
                f.write(f"  {label}: {count}\n")
            f.write(f"\nGraphs: {total_graphs}\n")
            f.write(f"Unique Strings: {len(strings_metadata)}\n")
        print(f"[INFO] Summary saved to: {summary_path}")


if __name__ == "__main__":
    main()


"""
USAGE EXAMPLES (FULL EDGE MODE):

# ---------------------------------------------------------------------------
# Dataset roots (adjust once if your folders differ)
# ---------------------------------------------------------------------------
DEVIGN_PF_DIR="./workspace/03_PerFunction_datasets/original_devign_functions"
DEVIGN_CPG_DIR="./CPGs/original_devign_functions"

DRAPER_PF_DIR="./workspace/03_PerFunction_datasets/draper_functions"
DRAPER_CPG_DIR="./CPGs/draper_functions"

REVEAL_PF_DIR="./workspace/03_PerFunction_datasets/normalized_reveal_functions"
REVEAL_CPG_DIR="./CPGs/reveal_functions"

PRIMEVUL_PF_DIR="./workspace/03_PerFunction_datasets/primevul_functions"
PRIMEVUL_CPG_DIR="./CPGs/primevul_functions"

# ---------------------------------------------------------------------------
# DEVIGN
# ---------------------------------------------------------------------------
python vocab_builder.py \
  --edge-mode full \
  --manifests \
    "$DEVIGN_PF_DIR/manifest_train.csv" \
    "$DEVIGN_PF_DIR/manifest_validation.csv" \
    "$DEVIGN_PF_DIR/manifest_test.csv" \
  --json-roots \
    "$DEVIGN_CPG_DIR/train" \
    "$DEVIGN_CPG_DIR/validation" \
    "$DEVIGN_CPG_DIR/test" \
  --out-dir "./Clean_exports/devign_vocab_full"

# ---------------------------------------------------------------------------
# DRAPER
# ---------------------------------------------------------------------------
python vocab_builder.py \
  --edge-mode full \
  --manifests \
    "$DRAPER_PF_DIR/manifest_train.csv" \
    "$DRAPER_PF_DIR/manifest_validation.csv" \
    "$DRAPER_PF_DIR/manifest_test.csv" \
  --json-roots \
    "$DRAPER_CPG_DIR/train" \
    "$DRAPER_CPG_DIR/validation" \
    "$DRAPER_CPG_DIR/test" \
  --out-dir "./Clean_exports/draper_vocab_full"

# ---------------------------------------------------------------------------
# REVEAL
# ---------------------------------------------------------------------------
python vocab_builder.py \
  --edge-mode full \
  --manifests \
    "$REVEAL_PF_DIR/manifest_train.csv" \
    "$REVEAL_PF_DIR/manifest_validation.csv" \
    "$REVEAL_PF_DIR/manifest_test.csv" \
  --json-roots \
    "$REVEAL_CPG_DIR/train" \
    "$REVEAL_CPG_DIR/validation" \
    "$REVEAL_CPG_DIR/test" \
  --out-dir "./Clean_exports/reveal_vocab_full"

# ---------------------------------------------------------------------------
# PRIMEVUL
# ---------------------------------------------------------------------------
python vocab_builder.py \
  --edge-mode full \
  --manifests \
    "$PRIMEVUL_PF_DIR/manifest_train.csv" \
    "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
    "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --json-roots \
    "$PRIMEVUL_CPG_DIR/train" \
    "$PRIMEVUL_CPG_DIR/validation" \
    "$PRIMEVUL_CPG_DIR/test" \
  --out-dir "./Clean_exports/primevul_vocab_full"

# ---------------------------------------------------------------------------
# Single export analysis (quick schema check)
# ---------------------------------------------------------------------------
python vocab_builder.py \
  --edge-mode full \
  --export-json /path/to/export.json \
  --out-dir /path/to/vocab_output
"""
