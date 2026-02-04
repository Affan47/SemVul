#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
cache_manager.py - V9 ALIGNED VERSION

ALIGNED with:
  - cpg_config.py V7 (14 edge types, 12 semantic nodes)
  - shared_text_norm.py V2 (proper normalization for original code)
  - vocab_builder.py V7 (GraphSON V3 parsing)
  - multi_extractor.py V2 (embedding retrieval)

Creates a SIMPLE, CONSISTENT directory structure:

    cache_root/
      dataset_name/
        train/
          index.csv
          signature.json
          func_0000001.pt
          func_0000002.pt
          ...
          (optionally) shards.zip
        valid/
          ...
        test/
          ...
        cache_meta.json

Updates in V9:
  - Robust GraphSON V3 parsing (handles nested @type/@value)
  - Aligned placeholder filtering with shared_text_norm.py
  - Better property extraction using cpg_config.py V7
  - Improved edge extraction with full unwrapping
  - Statistics tracking for debugging
"""

from __future__ import annotations

import csv
import io
import json
import logging
import os
import sqlite3
import sys
import time
import traceback
import zipfile
import shutil
import errno
from dataclasses import dataclass, field
from hashlib import sha256
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Tuple, Union

import numpy as np
import torch
from torch_geometric.data import Data

# ═══════════════════════════════════════════════════════════════════
# IMPORT CPG CONFIGURATION
# ═══════════════════════════════════════════════════════════════════

def _import_dependencies():
    """Import cpg_config and shared_text_norm."""
    here = Path(__file__).resolve().parent
    scripts_dir = (here / ".." / "workspace" / "Scripts_and_saved_Models" / "Scripts").resolve()
    
    if scripts_dir.exists():
        sys.path.insert(0, str(scripts_dir))
    sys.path.insert(0, str(here))
    
    deps = {}
    
    try:
        import cpg_config
        deps['cpg_config'] = cpg_config
        deps['should_include_node_type'] = cpg_config.should_include_node_type
        deps['get_property_keys_for_label'] = cpg_config.get_property_keys_for_label
        deps['get_edge_types'] = cpg_config.get_edge_types
        deps['get_edge_type_to_index'] = cpg_config.get_edge_type_to_index
        deps['map_edge_type'] = cpg_config.map_edge_type
        deps['configure_cpg'] = cpg_config.configure_cpg
        deps['EdgeTypeMode'] = cpg_config.EdgeTypeMode
        deps['DEFAULT_EDGE_MODE'] = cpg_config.DEFAULT_EDGE_MODE
        print(f"[CACHE_MANAGER] Loaded cpg_config")
    except ImportError as e:
        print(f"[CACHE_MANAGER] Failed to load cpg_config: {e}")
        raise RuntimeError("cpg_config.py is required")
    
    try:
        from shared_text_norm import normalize_for_embedding, sha256_normalized, get_normalization_config
        deps['normalize_for_embedding'] = normalize_for_embedding
        deps['sha256_normalized'] = sha256_normalized
        deps['norm_version'] = get_normalization_config().get("version", "unknown")
        print(f"[CACHE_MANAGER] Loaded shared_text_norm (version={deps['norm_version']})")
    except ImportError:
        import hashlib, re
        deps['normalize_for_embedding'] = lambda t: re.sub(r'\s+', ' ', t.strip()) if isinstance(t, str) else ""
        deps['sha256_normalized'] = lambda t: hashlib.sha256(t.encode('utf-8', errors='ignore')).hexdigest()
        deps['norm_version'] = "fallback"
        print(f"[CACHE_MANAGER] Using fallback text normalization")
    
    return deps

DEPS = _import_dependencies()

cpg_config = DEPS['cpg_config']
should_include_node_type = DEPS['should_include_node_type']
get_property_keys_for_label = DEPS['get_property_keys_for_label']
get_edge_types = DEPS['get_edge_types']
map_edge_type = DEPS['map_edge_type']
configure_cpg = DEPS['configure_cpg']
normalize_for_embedding = DEPS['normalize_for_embedding']
sha256_normalized = DEPS['sha256_normalized']

CURRENT_EDGE_MODE = DEPS['DEFAULT_EDGE_MODE']

def set_edge_mode(mode: str):
    global CURRENT_EDGE_MODE
    CURRENT_EDGE_MODE = mode
    configure_cpg(edge_mode=mode)

def _json_load(path: Path) -> Any:
    with path.open("r", encoding="utf-8") as f:
        return json.load(f)

def _json_dump(path: Path, obj: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8") as f:
        json.dump(obj, f, ensure_ascii=False, indent=2)

def _format_bytes(num_bytes: int) -> str:
    for unit in ("B", "KB", "MB", "GB", "TB"):
        if num_bytes < 1024:
            return f"{num_bytes:.1f}{unit}"
        num_bytes /= 1024
    return f"{num_bytes:.1f}PB"

def _log_disk_usage(path: Path, logger: logging.Logger) -> None:
    try:
        usage = shutil.disk_usage(path)
        logger.warning(
            "Disk usage for %s: total=%s used=%s free=%s",
            path, _format_bytes(usage.total), _format_bytes(usage.used), _format_bytes(usage.free)
        )
    except Exception as e:
        logger.warning("Failed to read disk usage for %s: %s", path, e)

def _safe_torch_save(data: Data, out_path: Path, logger: logging.Logger) -> bool:
    tmp_path = out_path.with_suffix(out_path.suffix + ".tmp")
    try:
        if tmp_path.exists():
            tmp_path.unlink()
        torch.save(data, tmp_path)
        tmp_path.replace(out_path)
        return True
    except Exception as e:
        logger.error("torch.save failed for %s: %s", out_path.name, e)
        try:
            if tmp_path.exists():
                tmp_path.unlink()
        except OSError:
            pass

    # Fallback: legacy serialization can be more robust on some filesystems.
    try:
        torch.save(data, tmp_path, _use_new_zipfile_serialization=False)
        tmp_path.replace(out_path)
        logger.warning("Saved with legacy serialization for %s", out_path.name)
        return True
    except Exception as e:
        logger.error("Legacy torch.save failed for %s: %s", out_path.name, e)
        try:
            if tmp_path.exists():
                tmp_path.unlink()
        except OSError:
            pass

    _log_disk_usage(out_path.parent, logger)
    return False


def compute_signature_hash(config: Dict) -> str:
    """
    Compute a deterministic hash from config for cache validation.
    
    This hash changes when any important config parameter changes,
    allowing the training code to detect stale caches.
    """
    # Select keys that affect cache validity
    sig_keys = [
        "edge_mode",
        "num_edge_types", 
        "num_node_types",
        "fusion_mode",
        "one_hot",
        "use_embeddings",
        "embedding_dim",
        "embedding_cache",
        "embedding_cache_sig",
        "use_edge_content",
        "edge_embedding_dim",
        "edge_embedding_cache",
        "edge_embedding_cache_sig",
        "use_vuln_features",
        "vuln_feature_dim",
        "expected_x_dim",
        "norm_version",
    ]
    
    # Build deterministic string
    parts = []
    for k in sorted(sig_keys):
        if k in config:
            parts.append(f"{k}={config[k]}")
    
    sig_str = "|".join(parts)
    
    # Compute short hash (first 16 chars of SHA256)
    import hashlib
    full_hash = hashlib.sha256(sig_str.encode()).hexdigest()
    return full_hash[:16]

# ═══════════════════════════════════════════════════════════════════
# GRAPHSON V3 PARSING (aligned with vocab_builder.py V7)
# ═══════════════════════════════════════════════════════════════════

def unwrap_graphson(obj: Any) -> Any:
    """
    Recursively unwrap TinkerPop GraphSON v3 typed structures.
    
    Handles:
      - {"@type": "g:Int64", "@value": 123} -> 123
      - {"@type": "g:List", "@value": [...]} -> [...]
      - {"@type": "g:VertexProperty", "@value": {"value": ...}} -> value
      - Nested structures
    """
    try:
        if isinstance(obj, dict):
            if "@type" in obj and "@value" in obj:
                inner = obj["@value"]
                # Handle VertexProperty specially
                if obj.get("@type") == "g:VertexProperty" and isinstance(inner, dict):
                    return unwrap_graphson(inner.get("value", inner))
                return unwrap_graphson(inner)
            return {k: unwrap_graphson(v) for k, v in obj.items()}
        elif isinstance(obj, list):
            return [unwrap_graphson(item) for item in obj]
        return obj
    except Exception:
        return obj


def extract_property_value(prop_data: Any) -> Optional[str]:
    """
    Extract the actual string value from a GraphSON property structure.
    
    Handles various nested formats from Joern/TinkerPop exports.
    """
    unwrapped = unwrap_graphson(prop_data)
    
    # Handle list of values (common in GraphSON)
    if isinstance(unwrapped, list):
        # Filter out None values
        values = [v for v in unwrapped if v is not None]
        if not values:
            return None
        # If single element, return it
        if len(values) == 1:
            unwrapped = values[0]
        else:
            # Multiple values - take first non-empty string
            for v in values:
                if isinstance(v, str) and v.strip():
                    return v.strip()
            return None
    
    # Handle dict with 'value' key (VertexProperty remnant)
    if isinstance(unwrapped, dict):
        if 'value' in unwrapped:
            unwrapped = unwrapped['value']
        else:
            return None
    
    if isinstance(unwrapped, str):
        return unwrapped.strip() if unwrapped.strip() else None
    
    # Convert numbers/booleans to string
    if isinstance(unwrapped, (int, float, bool)):
        return str(unwrapped)
    
    return None


def load_graphson(path: Path) -> Optional[Dict]:
    """Load and unwrap a GraphSON file."""
    try:
        with path.open("r", encoding="utf-8") as f:
            return unwrap_graphson(json.load(f))
    except Exception as e:
        return None


def extract_node_text(vertex: Dict) -> Optional[str]:
    """
    Extract text content from a vertex using cpg_config property keys.
    
    Uses the priority order defined in cpg_config.LABEL_TO_PROPERTY_KEYS:
    - CALL: NAME first, then CODE
    - IDENTIFIER: NAME first, then CODE
    - LITERAL: CODE
    etc.
    """
    if not isinstance(vertex, dict):
        return None
    
    props = vertex.get("properties", {})
    if not isinstance(props, dict):
        return None
    
    label = vertex.get("label", "")
    keys = get_property_keys_for_label(label)
    
    for key in keys:
        if key not in props:
            continue
        
        text = extract_property_value(props[key])
        if text:
            # Use shared_text_norm for normalization
            normalized = normalize_for_embedding(text)
            if normalized:
                return normalized
    
    return None


EDGE_TEXT_KEYS = {"EdgeProperty"}


def extract_edge_text(edge: Dict) -> Optional[str]:
    """Extract normalized text content from an edge (e.g., EdgeProperty)."""
    if not isinstance(edge, dict):
        return None

    props = edge.get("properties", {})
    if not isinstance(props, dict) or not props:
        return None

    keys_to_check = EDGE_TEXT_KEYS if EDGE_TEXT_KEYS else props.keys()
    for key in keys_to_check:
        if key not in props:
            continue

        text = extract_property_value(props[key])
        if text:
            normalized = normalize_for_embedding(text)
            if normalized:
                return normalized

    return None


# ═══════════════════════════════════════════════════════════════════
# VOCABULARY MANAGER
# ═══════════════════════════════════════════════════════════════════

class VocabularyManager:
    """Manages node and edge type vocabularies."""
    
    def __init__(self, vocab_dir: Path, edge_mode: str, logger: logging.Logger):
        self.vocab_dir = Path(vocab_dir)
        self.edge_mode = edge_mode
        self.logger = logger
        self.node_type_vocab: Dict[str, int] = {}
        self.edge_type_vocab: Dict[str, int] = {}
        self._load()
    
    def _load(self):
        # Load node type vocab
        node_path = self.vocab_dir / "node_type_vocab.json"
        if node_path.exists():
            self.node_type_vocab = _json_load(node_path)
            self.logger.info(f"Loaded {len(self.node_type_vocab)} node types from vocab")
        else:
            raise FileNotFoundError(f"Node type vocab not found: {node_path}")
        
        # Load edge type vocab (try multiple names for compatibility)
        for name in ["edge_type_vocab.json", "devign_rel_vocab.json"]:
            p = self.vocab_dir / name
            if p.exists():
                self.edge_type_vocab = _json_load(p)
                self.logger.info(f"Loaded {len(self.edge_type_vocab)} edge types from {name}")
                break
        
        # Fallback: generate from cpg_config
        if not self.edge_type_vocab:
            edge_types = get_edge_types(self.edge_mode)
            self.edge_type_vocab = {et: i for i, et in enumerate(edge_types)}
            self.logger.info(f"Generated {len(self.edge_type_vocab)} edge types from cpg_config")
        
        self.logger.info(f"Vocab summary: {len(self.node_type_vocab)} node types, "
                        f"{len(self.edge_type_vocab)} edge types")
    
    def get_node_type_index(self, node_type: str) -> int:
        """Get index for node type, returns 0 for unknown types."""
        return self.node_type_vocab.get(node_type, 0)
    
    def get_edge_type_index(self, raw_edge: str) -> Optional[int]:
        """Get index for edge type, returns None if edge should be filtered."""
        mapped = map_edge_type(raw_edge, self.edge_mode)
        return self.edge_type_vocab.get(mapped) if mapped else None
    
    @property
    def num_node_types(self) -> int:
        return len(self.node_type_vocab)
    
    @property
    def num_edge_types(self) -> int:
        return len(self.edge_type_vocab)


# ═══════════════════════════════════════════════════════════════════
# EMBEDDING RETRIEVER (aligned with multi_extractor.py V2)
# ═══════════════════════════════════════════════════════════════════

class EmbeddingRetriever:
    """Retrieves pre-computed embeddings from SQLite cache."""
    
    def __init__(self, sqlite_path: Path, logger: logging.Logger):
        self.sqlite_path = sqlite_path
        self.logger = logger
        self.conn = sqlite3.connect(str(sqlite_path))
        self.conn.row_factory = sqlite3.Row
        self.embedding_dim = 0
        self._cache: Dict[str, np.ndarray] = {}  # In-memory cache for frequent lookups
        self._cache_hits = 0
        self._cache_misses = 0
        
        # Get embedding dimension
        row = self.conn.execute("SELECT dim FROM embeddings LIMIT 1").fetchone()
        if row:
            self.embedding_dim = row["dim"]
            logger.info(f"Embedding dim: {self.embedding_dim}")
        
        # Get model info from config
        config_row = self.conn.execute(
            "SELECT value FROM emb_config WHERE key = 'model'"
        ).fetchone()
        if config_row:
            logger.info(f"Embedding model: {config_row['value']}")

    def get_cache_signature(self) -> str:
        """Build a stable signature for the embedding cache contents."""
        parts = []
        try:
            rows = self.conn.execute("SELECT key, value FROM emb_config ORDER BY key").fetchall()
            for row in rows:
                parts.append(f"{row['key']}={row['value']}")
        except Exception:
            pass
        
        parts.append(f"dim={self.embedding_dim}")
        
        try:
            count = self.conn.execute("SELECT COUNT(*) FROM embeddings").fetchone()[0] or 0
        except Exception:
            count = 0
        parts.append(f"count={count}")
        
        try:
            last_added = self.conn.execute("SELECT MAX(added_at) FROM embeddings").fetchone()[0] or 0
        except Exception:
            last_added = 0
        parts.append(f"last_added={last_added}")
        
        sig_str = "|".join(parts)
        return sha256(sig_str.encode()).hexdigest()[:16]
    
    def get_embedding(self, text: str) -> Optional[np.ndarray]:
        """
        Get embedding for normalized text.
        
        Uses sha256_normalized from shared_text_norm.py for consistent hashing.
        """
        if not text:
            return None
        
        text_hash = sha256_normalized(text)
        
        # Check in-memory cache first
        if text_hash in self._cache:
            self._cache_hits += 1
            return self._cache[text_hash]
        
        # Query database
        row = self.conn.execute(
            "SELECT vec, dim FROM embeddings WHERE sha256 = ?", 
            (text_hash,)
        ).fetchone()
        
        if row:
            emb = np.frombuffer(row["vec"], dtype=np.float32).reshape(row["dim"])
            # Cache for future lookups (limit cache size)
            if len(self._cache) < 100000:
                self._cache[text_hash] = emb
            self._cache_misses += 1
            return emb
        
        return None
    
    def get_stats(self) -> Dict[str, int]:
        return {
            "cache_hits": self._cache_hits,
            "cache_misses": self._cache_misses,
            "cache_size": len(self._cache),
        }
    
    def close(self):
        if self.conn:
            self.conn.close()


# ═══════════════════════════════════════════════════════════════════
# CPG TO PYG BUILDER
# ═══════════════════════════════════════════════════════════════════

class CPGToPyGBuilder:
    """Builds PyTorch Geometric Data objects from GraphSON CPGs."""
    
    def __init__(
        self, 
        vocab_manager: VocabularyManager, 
        embedding_retriever: Optional[EmbeddingRetriever],
        edge_embedding_retriever: Optional[EmbeddingRetriever],
        edge_mode: str,
        one_hot: bool = True,
        use_embeddings: bool = True,
        fusion_mode: str = "early_concat",
        logger: logging.Logger = None,
        use_vuln_features: bool = False,
        use_edge_content: bool = False,
    ):
        self.vocab_manager = vocab_manager
        self.embedding_retriever = embedding_retriever
        self.edge_embedding_retriever = edge_embedding_retriever
        self.edge_mode = edge_mode
        self.one_hot = one_hot
        self.use_embeddings = use_embeddings
        self.fusion_mode = fusion_mode
        self.use_vuln_features = use_vuln_features
        self.use_edge_content = use_edge_content
        self.logger = logger or logging.getLogger(__name__)
        
        # Statistics for debugging
        self.stats = {
            "total": 0,
            "success": 0,
            "empty_graph": 0,
            "no_vertices": 0,
            "emb_hits": 0,
            "emb_misses": 0,
            "nodes_with_text": 0,
            "nodes_without_text": 0,
            "edges_with_text": 0,
            "edges_without_text": 0,
            "edge_emb_hits": 0,
            "edge_emb_misses": 0,
        }
        
        # Initialize vulnerability feature extractor
        self.vuln_extractor = None
        if use_vuln_features:
            try:
                from vuln_features import VulnFeatureExtractor
                self.vuln_extractor = VulnFeatureExtractor()
                self.logger.info("Vulnerability feature extractor enabled (20 features)")
            except ImportError:
                self.logger.warning("vuln_features.py not found, disabling vulnerability features")
                self.use_vuln_features = False
    
    def build(self, graphson_path: Path, label: int = 0, metadata: Dict = None) -> Optional[Data]:
        """Build PyG Data object from GraphSON file."""
        self.stats["total"] += 1
        
        doc = load_graphson(graphson_path)
        if not doc:
            return None
        
        vertices = doc.get("vertices", [])
        edges = doc.get("edges", [])
        
        if not vertices:
            self.stats["no_vertices"] += 1
            return None
        
        # Build node features
        x, node_map = self._build_features(vertices)
        if x is None or x.size(0) == 0:
            self.stats["empty_graph"] += 1
            return None
        
        # Build edges
        edge_index, edge_attr, edge_text_emb = self._build_edges(edges, node_map)
        
        # Create PyG Data object
        data = Data(
            x=x,
            edge_index=edge_index,
            edge_attr=edge_attr,
            y=torch.tensor([label], dtype=torch.long)
        )
        if edge_text_emb is not None:
            data.edge_text_emb = edge_text_emb
        
        # Add metadata
        if metadata:
            for k, v in metadata.items():
                setattr(data, k, v)
        
        self.stats["success"] += 1
        return data
    
    def _build_features(self, vertices: List[Dict]) -> Tuple[Optional[torch.Tensor], Dict]:
        """Build node feature matrix."""
        features = []
        node_map = {}
        
        num_types = self.vocab_manager.num_node_types
        emb_dim = self.embedding_retriever.embedding_dim if self.embedding_retriever else 0
        vuln_dim = 20 if self.vuln_extractor else 0
        
        for v in vertices:
            label = v.get("label", "UNKNOWN")
            
            # Filter structural nodes using cpg_config
            if not should_include_node_type(label):
                continue
            
            # Get vertex ID (handle GraphSON V3 wrapping)
            vid = v.get("id")
            if vid is None:
                continue
            vid = unwrap_graphson(vid)  # Ensure ID is unwrapped
            
            node_map[vid] = len(features)
            feat_parts = []
            
            # Extract node text for embeddings and vuln features
            text = extract_node_text(v)
            
            if text:
                self.stats["nodes_with_text"] += 1
            else:
                self.stats["nodes_without_text"] += 1
            
            # One-hot encoding of node type
            if self.one_hot:
                oh = np.zeros(num_types, dtype=np.float32)
                idx = self.vocab_manager.get_node_type_index(label)
                if idx < num_types:
                    oh[idx] = 1.0
                feat_parts.append(oh)
            
            # Code embeddings
            if self.use_embeddings and self.embedding_retriever:
                emb = None
                if text:
                    emb = self.embedding_retriever.get_embedding(text)
                    if emb is not None:
                        self.stats["emb_hits"] += 1
                    else:
                        self.stats["emb_misses"] += 1
                
                if emb is None:
                    emb = np.zeros(emb_dim, dtype=np.float32)
                
                if self.fusion_mode == "early_concat":
                    feat_parts.append(emb)
                elif self.fusion_mode == "early_replace" and text:
                    # Replace one-hot with embedding
                    feat_parts = [emb]
            
            # Vulnerability features
            if self.vuln_extractor:
                vuln_feat = self.vuln_extractor.extract_node_features(text or '', label)
                feat_parts.append(vuln_feat)
            
            # Concatenate all feature parts
            if feat_parts:
                features.append(np.concatenate(feat_parts))
            else:
                # Fallback: zero vector with one-hot size
                features.append(np.zeros(num_types, dtype=np.float32))
        
        if not features:
            return None, {}
        
        return torch.tensor(np.stack(features), dtype=torch.float32), node_map
    
    def _build_edges(
        self,
        edges: List[Dict],
        node_map: Dict
    ) -> Tuple[torch.Tensor, torch.Tensor, Optional[torch.Tensor]]:
        """Build edge index and edge attributes."""
        src, dst, types = [], [], []
        edge_text_embs = []
        edge_emb_dim = 0
        use_edge_text = bool(self.use_edge_content and self.edge_embedding_retriever)
        if use_edge_text:
            edge_emb_dim = self.edge_embedding_retriever.embedding_dim
        
        for e in edges:
            # Handle GraphSON V3 wrapping for edge endpoints
            s = unwrap_graphson(e.get("outV"))
            d = unwrap_graphson(e.get("inV"))
            
            if s not in node_map or d not in node_map:
                continue
            
            # Get edge type index (filters unwanted edge types)
            edge_label = e.get("label", "")
            idx = self.vocab_manager.get_edge_type_index(edge_label)
            if idx is None:
                continue
            
            src.append(node_map[s])
            dst.append(node_map[d])
            types.append(idx)
            
            if use_edge_text:
                text = extract_edge_text(e)
                if text:
                    self.stats["edges_with_text"] += 1
                    emb = self.edge_embedding_retriever.get_embedding(text)
                    if emb is not None:
                        self.stats["edge_emb_hits"] += 1
                    else:
                        self.stats["edge_emb_misses"] += 1
                else:
                    self.stats["edges_without_text"] += 1
                    emb = None
                
                if emb is None:
                    emb = np.zeros(edge_emb_dim, dtype=np.float32)
                edge_text_embs.append(emb)
        
        if not src:
            edge_index = torch.zeros((2, 0), dtype=torch.long)
            edge_attr = torch.zeros(0, dtype=torch.long)
            if use_edge_text and edge_emb_dim > 0:
                edge_text_emb = torch.zeros((0, edge_emb_dim), dtype=torch.float32)
            else:
                edge_text_emb = None
            return edge_index, edge_attr, edge_text_emb
        
        edge_index = torch.tensor([src, dst], dtype=torch.long)
        edge_attr = torch.tensor(types, dtype=torch.long)
        
        edge_text_emb = None
        if use_edge_text and edge_emb_dim > 0:
            edge_text_emb = torch.tensor(np.stack(edge_text_embs), dtype=torch.float32)
        
        return edge_index, edge_attr, edge_text_emb
    
    def get_stats(self) -> Dict:
        return self.stats.copy()


# ═══════════════════════════════════════════════════════════════════
# MANIFEST PROCESSING
# ═══════════════════════════════════════════════════════════════════

def resolve_json_path(row: Dict, root: Path) -> Optional[Path]:
    """Resolve GraphSON file path from manifest row."""
    func_id = row.get("function_id", row.get("fid", ""))
    json_path = row.get("json_path", row.get("graphson_path", ""))
    
    # Try explicit path first
    if json_path:
        p = root / json_path
        if p.exists():
            return p
    
    # Try common patterns
    base = func_id.replace(".c", "")
    for pattern in [
        f"exports/{base}/export_all/export.json",
        f"exports/{func_id}/export_all/export.json",
        f"{base}/export_all/export.json",
        f"{base}/export.json",
        f"{func_id}/export.json",
    ]:
        p = root / pattern
        if p.exists():
            return p
    
    return None


def process_manifest(
    manifest_path: Path,
    root_dir: Path,
    builder: CPGToPyGBuilder,
    output_dir: Path,
    split_name: str,
    merge_to_zip: bool,
    delete_shards: bool,
    logger: logging.Logger,
    config: Dict
) -> Dict:
    """Process manifest and create cache with SIMPLE structure."""
    
    with manifest_path.open("r", encoding="utf-8") as f:
        rows = list(csv.DictReader(f))
    
    logger.info(f"Processing {len(rows)} rows for {split_name}")
    output_dir.mkdir(parents=True, exist_ok=True)
    
    success, failed, skipped = 0, 0, 0
    index_rows = []
    final_x_dim = None
    
    for i, row in enumerate(rows):
        json_path = resolve_json_path(row, root_dir)
        if not json_path or not json_path.exists():
            skipped += 1
            continue
        
        label = int(row.get("label", row.get("target", 0)))
        func_id = row.get("function_id", row.get("fid", f"{split_name}_func_{i:07d}"))
        clean_id = func_id.replace(".c", "").replace("/", "_").replace("\\", "_")
        
        data = builder.build(json_path, label=label, metadata={"func_id": func_id})
        
        if data is not None:
            if final_x_dim is None:
                final_x_dim = data.x.size(1)
            
            filename = f"{clean_id}.pt"
            out_path = output_dir / filename
            if _safe_torch_save(data, out_path, logger):
                index_rows.append({
                    "function_id": func_id,
                    "label": label,
                    "filename": filename,
                    "num_nodes": data.x.size(0),
                    "num_edges": data.edge_index.size(1)
                })
                success += 1
            else:
                failed += 1
        else:
            failed += 1
        
        if (i + 1) % 1000 == 0:
            logger.info(f"  {i+1}/{len(rows)} (success={success}, failed={failed}, skipped={skipped})")
    
    logger.info(f"Done: {success} success, {failed} failed, {skipped} skipped (no JSON)")
    
    # Write index.csv
    with (output_dir / "index.csv").open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["function_id", "label", "filename", "num_nodes", "num_edges"])
        writer.writeheader()
        writer.writerows(index_rows)
    
    # Write signature.json with all config
    sig = config.copy()
    sig.update({
        "split": split_name,
        "total_graphs": success,
        "failed_graphs": failed,
        "skipped_graphs": skipped,
        "final_x_dim": final_x_dim or 0,
        "builder_stats": builder.get_stats(),
    })
    _json_dump(output_dir / "signature.json", sig)
    
    # Optionally zip
    if merge_to_zip:
        pt_files = list(output_dir.glob("*.pt"))
        # Name zip file as cache_{split}.zip to match training script expectations
        zip_path = output_dir / f"cache_{split_name}.zip"
        with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as zf:
            for f in pt_files:
                zf.write(f, arcname=f.name)
        logger.info(f"Created {zip_path} ({len(pt_files)} files)")
        
        if delete_shards:
            for f in pt_files:
                f.unlink()
            logger.info(f"Deleted {len(pt_files)} .pt files")
    
    return {
        "total": len(rows),
        "success": success,
        "failed": failed,
        "skipped": skipped,
        "final_x_dim": final_x_dim
    }


# ═══════════════════════════════════════════════════════════════════
# MAIN
# ═══════════════════════════════════════════════════════════════════

def main():
    import argparse
    
    parser = argparse.ArgumentParser(
        description="Build PyG cache V9 (aligned with vocab_builder V7)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # One-hot only (no embeddings)
    python cache_manager.py \\
        --edge-mode full_filtered \\
        --cache-root ./cache --vocab-dir ./vocab \\
        --dataset-name devign_onehot \\
        --no-code-embeddings --one-hot --fusion-mode none \\
        --train-manifest manifest_train.csv --train-json-root ./CPGs/train

    # Node embeddings only (GraphCodeBERT, node_content)
    python cache_manager.py \\
        --edge-mode full_filtered \\
        --cache-root ./cache --vocab-dir ./vocab \\
        --codebert-sqlite ./graphcodebert_768d.sqlite \\
        --dataset-name devign_gcb768 \\
        --use-code-embeddings --one-hot \\
        --fusion-mode early_concat \\
        --train-manifest manifest_train.csv --train-json-root ./CPGs/train

    # Node + edge content (same sqlite from multi_extractor without --kind)
    python cache_manager.py \\
        --edge-mode full_filtered \\
        --cache-root ./cache --vocab-dir ./vocab \\
        --codebert-sqlite ./graphcodebert_768d.sqlite \\
        --use-edge-content \\
        --dataset-name devign_gcb768_edge \\
        --use-code-embeddings --one-hot \\
        --fusion-mode early_concat \\
        --train-manifest manifest_train.csv --train-json-root ./CPGs/train

    # Node + edge content (separate sqlite caches)
    python cache_manager.py \\
        --edge-mode full_filtered \\
        --cache-root ./cache --vocab-dir ./vocab \\
        --codebert-sqlite ./node_emb.sqlite \\
        --edge-emb-sqlite ./edge_emb.sqlite \\
        --use-edge-content \\
        --dataset-name devign_node_edge_split \\
        --use-code-embeddings --one-hot \\
        --fusion-mode early_concat \\
        --train-manifest manifest_train.csv --train-json-root ./CPGs/train

    # With vulnerability features
    python cache_manager.py \\
        --edge-mode full_filtered \\
        --cache-root ./cache --vocab-dir ./vocab \\
        --codebert-sqlite ./graphcodebert_768d.sqlite \\
        --dataset-name devign_vuln \\
        --use-code-embeddings --one-hot --use-vuln-features \\
        --fusion-mode early_concat \\
        --train-manifest manifest_train.csv --train-json-root ./CPGs/train
"""
    )
    
    parser.add_argument("--cache-root", type=Path, required=True,
                       help="Root directory for cache output")
    parser.add_argument("--vocab-dir", type=Path, required=True,
                       help="Directory containing vocab files from vocab_builder.py")
    parser.add_argument("--edge-mode", choices=["full", "simplified", "full_filtered"],
                       default="full_filtered",
                       help="Edge type mode (default: full_filtered = 14 types)")
    parser.add_argument("--codebert-sqlite", type=Path,
                       help="SQLite embedding cache from multi_extractor.py")
    parser.add_argument("--edge-emb-sqlite", type=Path,
                       help="SQLite edge embedding cache (default: --codebert-sqlite)")
    parser.add_argument("--use-code-embeddings", dest="use_embeddings",
                       action="store_true", default=True,
                       help="Use code embeddings (default: True)")
    parser.add_argument("--no-code-embeddings", dest="use_embeddings",
                       action="store_false",
                       help="Disable code embeddings")
    parser.add_argument("--use-edge-content", action="store_true",
                       help="Attach edge content embeddings to edges")
    parser.add_argument("--one-hot", action="store_true", default=True,
                       help="Include one-hot node type encoding (default: True)")
    parser.add_argument("--no-one-hot", dest="one_hot", action="store_false",
                       help="Disable one-hot encoding")
    parser.add_argument("--fusion-mode", choices=["none", "early_concat", "early_replace"],
                       default="early_concat",
                       help="How to combine embeddings with one-hot")
    parser.add_argument("--merge-to-zip", action="store_true",
                       help="Merge .pt files into shards.zip")
    parser.add_argument("--delete-shards-after-merge", action="store_true",
                       help="Delete .pt files after zipping")
    parser.add_argument("--use-vuln-features", action="store_true",
                       help="Add 20-dim vulnerability features")
    parser.add_argument("--dataset-name", required=True,
                       help="Name for this cache dataset")
    
    # Split arguments
    parser.add_argument("--train-manifest", type=Path)
    parser.add_argument("--train-json-root", type=Path)
    parser.add_argument("--val-manifest", type=Path)
    parser.add_argument("--val-json-root", type=Path)
    parser.add_argument("--test-manifest", type=Path)
    parser.add_argument("--test-json-root", type=Path)
    
    args = parser.parse_args()
    
    # Setup logging
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s"
    )
    logger = logging.getLogger("cache_manager")
    
    # Configure edge mode
    set_edge_mode(args.edge_mode)
    edge_types = get_edge_types(args.edge_mode)
    
    # Load vocabulary
    vocab_manager = VocabularyManager(args.vocab_dir, args.edge_mode, logger)
    
    # Load embeddings
    embedding_retriever = None
    emb_dim = 0
    emb_path = ""
    emb_cache_sig = ""
    if args.use_embeddings and args.codebert_sqlite:
        if args.codebert_sqlite.exists():
            embedding_retriever = EmbeddingRetriever(args.codebert_sqlite, logger)
            emb_dim = embedding_retriever.embedding_dim
            emb_path = str(args.codebert_sqlite.resolve())
            emb_cache_sig = embedding_retriever.get_cache_signature()
        else:
            logger.warning(f"Embedding cache not found: {args.codebert_sqlite}")
            args.use_embeddings = False

    edge_embedding_retriever = None
    edge_emb_dim = 0
    edge_emb_path = ""
    edge_emb_cache_sig = ""
    if args.use_edge_content:
        edge_db = args.edge_emb_sqlite or args.codebert_sqlite
        if edge_db and edge_db.exists():
            edge_emb_path = str(edge_db.resolve())
            if embedding_retriever and edge_db == args.codebert_sqlite:
                edge_embedding_retriever = embedding_retriever
            else:
                edge_embedding_retriever = EmbeddingRetriever(edge_db, logger)
            edge_emb_dim = edge_embedding_retriever.embedding_dim
            if edge_embedding_retriever is embedding_retriever:
                edge_emb_cache_sig = emb_cache_sig
            else:
                edge_emb_cache_sig = edge_embedding_retriever.get_cache_signature()
        else:
            logger.warning("Edge content enabled but embedding cache not found. Disabling edge content.")
            args.use_edge_content = False
    
    # Calculate expected dimensions
    vuln_dim = 20 if args.use_vuln_features else 0
    one_hot_dim = vocab_manager.num_node_types if args.one_hot else 0
    
    if args.fusion_mode == "early_replace" and args.use_embeddings:
        expected_dim = emb_dim + vuln_dim
    else:
        expected_dim = one_hot_dim + (emb_dim if args.use_embeddings else 0) + vuln_dim
    
    # Print configuration
    print(f"\n{'='*60}")
    print(f"CACHE MANAGER V9")
    print(f"{'='*60}")
    print(f"Output: {args.cache_root / args.dataset_name}")
    print(f"Edge mode: {args.edge_mode} ({len(edge_types)} types)")
    print(f"Node types: {vocab_manager.num_node_types}")
    print(f"One-hot: {args.one_hot} (dim={one_hot_dim})")
    print(f"Embeddings: {args.use_embeddings} (dim={emb_dim})")
    print(f"Edge content: {args.use_edge_content} (dim={edge_emb_dim})")
    print(f"Vuln features: {args.use_vuln_features} (dim={vuln_dim})")
    print(f"Fusion mode: {args.fusion_mode}")
    print(f"Expected x_dim: {expected_dim}")
    print(f"{'='*60}\n")
    
    # Build configuration dict
    config = {
        "version": "9.0",
        "edge_mode": args.edge_mode,
        "edge_types": edge_types,
        "num_edge_types": len(edge_types),
        "node_types": list(vocab_manager.node_type_vocab.keys()),
        "num_node_types": vocab_manager.num_node_types,
        "fusion_mode": args.fusion_mode,
        "one_hot": args.one_hot,
        "one_hot_dim": one_hot_dim,
        "use_embeddings": args.use_embeddings,
        "embedding_dim": emb_dim,
        "embedding_cache": emb_path,
        "embedding_cache_sig": emb_cache_sig,
        "use_edge_content": args.use_edge_content,
        "edge_embedding_dim": edge_emb_dim,
        "edge_embedding_cache": edge_emb_path,
        "edge_embedding_cache_sig": edge_emb_cache_sig,
        "use_vuln_features": args.use_vuln_features,
        "vuln_feature_dim": vuln_dim,
        "expected_x_dim": expected_dim,
        "norm_version": DEPS.get('norm_version', 'unknown'),
    }
    
    # Compute signature hash for cache validation
    signature_hash = compute_signature_hash(config)
    config["signature"] = signature_hash
    
    print(f"Signature hash: {signature_hash}")
    
    # Create builder
    builder = CPGToPyGBuilder(
        vocab_manager=vocab_manager,
        embedding_retriever=embedding_retriever,
        edge_embedding_retriever=edge_embedding_retriever,
        edge_mode=args.edge_mode,
        one_hot=args.one_hot,
        use_embeddings=args.use_embeddings,
        fusion_mode=args.fusion_mode,
        logger=logger,
        use_vuln_features=args.use_vuln_features,
        use_edge_content=args.use_edge_content,
    )
    
    # Directory structure: cache_root/dataset_name/signature_hash/split/
    cache_base = args.cache_root / args.dataset_name / signature_hash
    results = {}
    
    print(f"Cache directory: {cache_base}")
    
    # Process each split
    if args.train_manifest and args.train_json_root:
        results["train"] = process_manifest(
            args.train_manifest, args.train_json_root, builder,
            cache_base / "train", "train",
            args.merge_to_zip, args.delete_shards_after_merge, logger, config
        )
    
    if args.val_manifest and args.val_json_root:
        results["valid"] = process_manifest(
            args.val_manifest, args.val_json_root, builder,
            cache_base / "valid", "valid",
            args.merge_to_zip, args.delete_shards_after_merge, logger, config
        )
    
    if args.test_manifest and args.test_json_root:
        results["test"] = process_manifest(
            args.test_manifest, args.test_json_root, builder,
            cache_base / "test", "test",
            args.merge_to_zip, args.delete_shards_after_merge, logger, config
        )
    
    # Write cache metadata
    _json_dump(cache_base / "cache_meta.json", {
        **config,
        "results": results,
        "embedding_retriever_stats": embedding_retriever.get_stats() if embedding_retriever else None,
    })
    
    # Print summary
    print(f"\n{'='*60}")
    print("COMPLETE")
    print(f"{'='*60}")
    print(f"Signature: {signature_hash}")
    for split, res in results.items():
        print(f"{split}: {res['success']}/{res['total']} graphs (x_dim={res.get('final_x_dim')})")
    
    # Print builder stats
    stats = builder.get_stats()
    print(f"\nBuilder stats:")
    print(f"  Total processed: {stats['total']}")
    print(f"  Success: {stats['success']}")
    print(f"  Empty graphs: {stats['empty_graph']}")
    print(f"  Embedding hits: {stats['emb_hits']}")
    print(f"  Embedding misses: {stats['emb_misses']}")
    print(f"  Nodes with text: {stats['nodes_with_text']}")
    print(f"  Nodes without text: {stats['nodes_without_text']}")
    
    if embedding_retriever:
        emb_stats = embedding_retriever.get_stats()
        print(f"\nEmbedding cache stats:")
        print(f"  Cache hits: {emb_stats['cache_hits']}")
        print(f"  DB lookups: {emb_stats['cache_misses']}")
    
    print(f"\nStructure: {cache_base}/")
    print("  cache_meta.json")
    for s in results:
        print(f"  {s}/")
        print(f"    index.csv, signature.json, *.pt" + (f" + cache_{s}.zip" if args.merge_to_zip else ""))
    print(f"{'='*60}")
    
    if embedding_retriever:
        embedding_retriever.close()


if __name__ == "__main__":
    main()

"""
###################################################################################
# Cache build commands (node + edge content aligned)
###################################################################################

# ---------------------------------------------------------------------------
# Shared paths (adjust once if needed)
# ---------------------------------------------------------------------------
DEVIGN_PF_DIR="./workspace/03_PerFunction_datasets/original_devign_functions"
DEVIGN_CPG_DIR="./CPGs/original_devign_functions"
DEVIGN_VOCAB_DIR="./Clean_exports/devign_vocab_full"
DEVIGN_CACHE_ROOT="./Clean_exports/cache_devign_v2"

DRAPER_PF_DIR="./workspace/03_PerFunction_datasets/draper_functions"
DRAPER_CPG_DIR="./CPGs/draper_functions"
DRAPER_VOCAB_DIR="./Clean_exports/draper_vocab_full"
DRAPER_CACHE_ROOT="./Clean_exports/cache_draper_v2"

REVEAL_PF_DIR="./workspace/03_PerFunction_datasets/normalized_reveal_functions"
REVEAL_CPG_DIR="./CPGs/reveal_functions"
REVEAL_VOCAB_DIR="./Clean_exports/reveal_vocab_full"
REVEAL_CACHE_ROOT="./Clean_exports/cache_reveal_v2"

PRIMEVUL_PF_DIR="./workspace/03_PerFunction_datasets/primevul_functions"
PRIMEVUL_CPG_DIR="./CPGs/primevul_functions"
PRIMEVUL_VOCAB_DIR="./Clean_exports/primevul_vocab_full"
PRIMEVUL_CACHE_ROOT="./Clean_exports/cache_primevul_v2"

# ---------------------------------------------------------------------------
# DEVIGN
# ---------------------------------------------------------------------------
python cache_manager.py \
  --edge-mode full \
  --cache-root "$DEVIGN_CACHE_ROOT" \
  --vocab-dir "$DEVIGN_VOCAB_DIR" \
  --codebert-sqlite "$DEVIGN_CACHE_ROOT/graphcodebert_768d_full.sqlite" \
  --use-edge-content \
  --dataset-name "graphcodebert_768d_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DEVIGN_PF_DIR/manifest_train.csv" \
  --train-json-root "$DEVIGN_CPG_DIR/train" \
  --val-manifest "$DEVIGN_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DEVIGN_CPG_DIR/validation" \
  --test-manifest "$DEVIGN_PF_DIR/manifest_test.csv" \
  --test-json-root "$DEVIGN_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DEVIGN_CACHE_ROOT" \
  --vocab-dir "$DEVIGN_VOCAB_DIR" \
  --codebert-sqlite "$DEVIGN_CACHE_ROOT/codet5p_256d_full.sqlite" \
  --use-edge-content \
  --dataset-name "codet5p_256d_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DEVIGN_PF_DIR/manifest_train.csv" \
  --train-json-root "$DEVIGN_CPG_DIR/train" \
  --val-manifest "$DEVIGN_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DEVIGN_CPG_DIR/validation" \
  --test-manifest "$DEVIGN_PF_DIR/manifest_test.csv" \
  --test-json-root "$DEVIGN_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DEVIGN_CACHE_ROOT" \
  --vocab-dir "$DEVIGN_VOCAB_DIR" \
  --codebert-sqlite "$DEVIGN_CACHE_ROOT/unixcoder_768d_full.sqlite" \
  --use-edge-content \
  --dataset-name "unixcoder_768d_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DEVIGN_PF_DIR/manifest_train.csv" \
  --train-json-root "$DEVIGN_CPG_DIR/train" \
  --val-manifest "$DEVIGN_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DEVIGN_CPG_DIR/validation" \
  --test-manifest "$DEVIGN_PF_DIR/manifest_test.csv" \
  --test-json-root "$DEVIGN_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DEVIGN_CACHE_ROOT" \
  --vocab-dir "$DEVIGN_VOCAB_DIR" \
  --codebert-sqlite "$DEVIGN_CACHE_ROOT/word2vec_200d_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_200d_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DEVIGN_PF_DIR/manifest_train.csv" \
  --train-json-root "$DEVIGN_CPG_DIR/train" \
  --val-manifest "$DEVIGN_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DEVIGN_CPG_DIR/validation" \
  --test-manifest "$DEVIGN_PF_DIR/manifest_test.csv" \
  --test-json-root "$DEVIGN_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DEVIGN_CACHE_ROOT" \
  --vocab-dir "$DEVIGN_VOCAB_DIR" \
  --codebert-sqlite "$DEVIGN_CACHE_ROOT/word2vec_100d_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_100d_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DEVIGN_PF_DIR/manifest_train.csv" \
  --train-json-root "$DEVIGN_CPG_DIR/train" \
  --val-manifest "$DEVIGN_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DEVIGN_CPG_DIR/validation" \
  --test-manifest "$DEVIGN_PF_DIR/manifest_test.csv" \
  --test-json-root "$DEVIGN_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DEVIGN_CACHE_ROOT" \
  --vocab-dir "$DEVIGN_VOCAB_DIR" \
  --dataset-name "onehot_devign_full" \
  --no-code-embeddings --one-hot \
  --fusion-mode none \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DEVIGN_PF_DIR/manifest_train.csv" \
  --train-json-root "$DEVIGN_CPG_DIR/train" \
  --val-manifest "$DEVIGN_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DEVIGN_CPG_DIR/validation" \
  --test-manifest "$DEVIGN_PF_DIR/manifest_test.csv" \
  --test-json-root "$DEVIGN_CPG_DIR/test"

# ---------------------------------------------------------------------------
# DRAPER
# ---------------------------------------------------------------------------
python cache_manager.py \
  --edge-mode full \
  --cache-root "$DRAPER_CACHE_ROOT" \
  --vocab-dir "$DRAPER_VOCAB_DIR" \
  --codebert-sqlite "$DRAPER_CACHE_ROOT/graphcodebert_768d_draper_full.sqlite" \
  --use-edge-content \
  --dataset-name "graphcodebert_768d_draper_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DRAPER_PF_DIR/manifest_train.csv" \
  --train-json-root "$DRAPER_CPG_DIR/train" \
  --val-manifest "$DRAPER_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DRAPER_CPG_DIR/validation" \
  --test-manifest "$DRAPER_PF_DIR/manifest_test.csv" \
  --test-json-root "$DRAPER_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DRAPER_CACHE_ROOT" \
  --vocab-dir "$DRAPER_VOCAB_DIR" \
  --codebert-sqlite "$DRAPER_CACHE_ROOT/codet5p_256d_draper_full.sqlite" \
  --use-edge-content \
  --dataset-name "codet5p_256d_draper_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DRAPER_PF_DIR/manifest_train.csv" \
  --train-json-root "$DRAPER_CPG_DIR/train" \
  --val-manifest "$DRAPER_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DRAPER_CPG_DIR/validation" \
  --test-manifest "$DRAPER_PF_DIR/manifest_test.csv" \
  --test-json-root "$DRAPER_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DRAPER_CACHE_ROOT" \
  --vocab-dir "$DRAPER_VOCAB_DIR" \
  --codebert-sqlite "$DRAPER_CACHE_ROOT/unixcoder_768d_draper_full.sqlite" \
  --use-edge-content \
  --dataset-name "unixcoder_768d_draper_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DRAPER_PF_DIR/manifest_train.csv" \
  --train-json-root "$DRAPER_CPG_DIR/train" \
  --val-manifest "$DRAPER_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DRAPER_CPG_DIR/validation" \
  --test-manifest "$DRAPER_PF_DIR/manifest_test.csv" \
  --test-json-root "$DRAPER_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DRAPER_CACHE_ROOT" \
  --vocab-dir "$DRAPER_VOCAB_DIR" \
  --codebert-sqlite "$DRAPER_CACHE_ROOT/word2vec_200d_draper_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_200d_draper_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DRAPER_PF_DIR/manifest_train.csv" \
  --train-json-root "$DRAPER_CPG_DIR/train" \
  --val-manifest "$DRAPER_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DRAPER_CPG_DIR/validation" \
  --test-manifest "$DRAPER_PF_DIR/manifest_test.csv" \
  --test-json-root "$DRAPER_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DRAPER_CACHE_ROOT" \
  --vocab-dir "$DRAPER_VOCAB_DIR" \
  --codebert-sqlite "$DRAPER_CACHE_ROOT/word2vec_100d_draper_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_100d_draper_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DRAPER_PF_DIR/manifest_train.csv" \
  --train-json-root "$DRAPER_CPG_DIR/train" \
  --val-manifest "$DRAPER_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DRAPER_CPG_DIR/validation" \
  --test-manifest "$DRAPER_PF_DIR/manifest_test.csv" \
  --test-json-root "$DRAPER_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$DRAPER_CACHE_ROOT" \
  --vocab-dir "$DRAPER_VOCAB_DIR" \
  --dataset-name "onehot_draper_full" \
  --no-code-embeddings --one-hot \
  --fusion-mode none \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$DRAPER_PF_DIR/manifest_train.csv" \
  --train-json-root "$DRAPER_CPG_DIR/train" \
  --val-manifest "$DRAPER_PF_DIR/manifest_validation.csv" \
  --val-json-root "$DRAPER_CPG_DIR/validation" \
  --test-manifest "$DRAPER_PF_DIR/manifest_test.csv" \
  --test-json-root "$DRAPER_CPG_DIR/test"

# ---------------------------------------------------------------------------
# REVEAL
# ---------------------------------------------------------------------------
python cache_manager.py \
  --edge-mode full \
  --cache-root "$REVEAL_CACHE_ROOT" \
  --vocab-dir "$REVEAL_VOCAB_DIR" \
  --codebert-sqlite "$REVEAL_CACHE_ROOT/graphcodebert_768d_reveal_full.sqlite" \
  --use-edge-content \
  --dataset-name "graphcodebert_768d_reveal_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$REVEAL_PF_DIR/manifest_train.csv" \
  --train-json-root "$REVEAL_CPG_DIR/train" \
  --val-manifest "$REVEAL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$REVEAL_CPG_DIR/validation" \
  --test-manifest "$REVEAL_PF_DIR/manifest_test.csv" \
  --test-json-root "$REVEAL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$REVEAL_CACHE_ROOT" \
  --vocab-dir "$REVEAL_VOCAB_DIR" \
  --codebert-sqlite "$REVEAL_CACHE_ROOT/codet5p_256d_reveal_full.sqlite" \
  --use-edge-content \
  --dataset-name "codet5p_256d_reveal_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$REVEAL_PF_DIR/manifest_train.csv" \
  --train-json-root "$REVEAL_CPG_DIR/train" \
  --val-manifest "$REVEAL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$REVEAL_CPG_DIR/validation" \
  --test-manifest "$REVEAL_PF_DIR/manifest_test.csv" \
  --test-json-root "$REVEAL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$REVEAL_CACHE_ROOT" \
  --vocab-dir "$REVEAL_VOCAB_DIR" \
  --codebert-sqlite "$REVEAL_CACHE_ROOT/unixcoder_768d_reveal_full.sqlite" \
  --use-edge-content \
  --dataset-name "unixcoder_768d_reveal_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$REVEAL_PF_DIR/manifest_train.csv" \
  --train-json-root "$REVEAL_CPG_DIR/train" \
  --val-manifest "$REVEAL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$REVEAL_CPG_DIR/validation" \
  --test-manifest "$REVEAL_PF_DIR/manifest_test.csv" \
  --test-json-root "$REVEAL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$REVEAL_CACHE_ROOT" \
  --vocab-dir "$REVEAL_VOCAB_DIR" \
  --codebert-sqlite "$REVEAL_CACHE_ROOT/word2vec_200d_reveal_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_200d_reveal_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$REVEAL_PF_DIR/manifest_train.csv" \
  --train-json-root "$REVEAL_CPG_DIR/train" \
  --val-manifest "$REVEAL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$REVEAL_CPG_DIR/validation" \
  --test-manifest "$REVEAL_PF_DIR/manifest_test.csv" \
  --test-json-root "$REVEAL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$REVEAL_CACHE_ROOT" \
  --vocab-dir "$REVEAL_VOCAB_DIR" \
  --codebert-sqlite "$REVEAL_CACHE_ROOT/word2vec_100d_reveal_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_100d_reveal_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$REVEAL_PF_DIR/manifest_train.csv" \
  --train-json-root "$REVEAL_CPG_DIR/train" \
  --val-manifest "$REVEAL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$REVEAL_CPG_DIR/validation" \
  --test-manifest "$REVEAL_PF_DIR/manifest_test.csv" \
  --test-json-root "$REVEAL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$REVEAL_CACHE_ROOT" \
  --vocab-dir "$REVEAL_VOCAB_DIR" \
  --dataset-name "onehot_reveal_full" \
  --no-code-embeddings --one-hot \
  --fusion-mode none \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$REVEAL_PF_DIR/manifest_train.csv" \
  --train-json-root "$REVEAL_CPG_DIR/train" \
  --val-manifest "$REVEAL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$REVEAL_CPG_DIR/validation" \
  --test-manifest "$REVEAL_PF_DIR/manifest_test.csv" \
  --test-json-root "$REVEAL_CPG_DIR/test"

# ---------------------------------------------------------------------------
# PRIMEVUL
# ---------------------------------------------------------------------------
python cache_manager.py \
  --edge-mode full \
  --cache-root "$PRIMEVUL_CACHE_ROOT" \
  --vocab-dir "$PRIMEVUL_VOCAB_DIR" \
  --codebert-sqlite "$PRIMEVUL_CACHE_ROOT/graphcodebert_768d_primevul_full.sqlite" \
  --use-edge-content \
  --dataset-name "graphcodebert_768d_primevul_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$PRIMEVUL_PF_DIR/manifest_train.csv" \
  --train-json-root "$PRIMEVUL_CPG_DIR/train" \
  --val-manifest "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$PRIMEVUL_CPG_DIR/validation" \
  --test-manifest "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --test-json-root "$PRIMEVUL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$PRIMEVUL_CACHE_ROOT" \
  --vocab-dir "$PRIMEVUL_VOCAB_DIR" \
  --codebert-sqlite "$PRIMEVUL_CACHE_ROOT/codet5p_256d_primevul_full.sqlite" \
  --use-edge-content \
  --dataset-name "codet5p_256d_primevul_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$PRIMEVUL_PF_DIR/manifest_train.csv" \
  --train-json-root "$PRIMEVUL_CPG_DIR/train" \
  --val-manifest "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$PRIMEVUL_CPG_DIR/validation" \
  --test-manifest "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --test-json-root "$PRIMEVUL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$PRIMEVUL_CACHE_ROOT" \
  --vocab-dir "$PRIMEVUL_VOCAB_DIR" \
  --codebert-sqlite "$PRIMEVUL_CACHE_ROOT/unixcoder_768d_primevul_full.sqlite" \
  --use-edge-content \
  --dataset-name "unixcoder_768d_primevul_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$PRIMEVUL_PF_DIR/manifest_train.csv" \
  --train-json-root "$PRIMEVUL_CPG_DIR/train" \
  --val-manifest "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$PRIMEVUL_CPG_DIR/validation" \
  --test-manifest "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --test-json-root "$PRIMEVUL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$PRIMEVUL_CACHE_ROOT" \
  --vocab-dir "$PRIMEVUL_VOCAB_DIR" \
  --codebert-sqlite "$PRIMEVUL_CACHE_ROOT/word2vec_200d_primevul_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_200d_primevul_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$PRIMEVUL_PF_DIR/manifest_train.csv" \
  --train-json-root "$PRIMEVUL_CPG_DIR/train" \
  --val-manifest "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$PRIMEVUL_CPG_DIR/validation" \
  --test-manifest "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --test-json-root "$PRIMEVUL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$PRIMEVUL_CACHE_ROOT" \
  --vocab-dir "$PRIMEVUL_VOCAB_DIR" \
  --codebert-sqlite "$PRIMEVUL_CACHE_ROOT/word2vec_100d_primevul_full.sqlite" \
  --use-edge-content \
  --dataset-name "word2vec_100d_primevul_full" \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$PRIMEVUL_PF_DIR/manifest_train.csv" \
  --train-json-root "$PRIMEVUL_CPG_DIR/train" \
  --val-manifest "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$PRIMEVUL_CPG_DIR/validation" \
  --test-manifest "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --test-json-root "$PRIMEVUL_CPG_DIR/test"

python cache_manager.py \
  --edge-mode full \
  --cache-root "$PRIMEVUL_CACHE_ROOT" \
  --vocab-dir "$PRIMEVUL_VOCAB_DIR" \
  --dataset-name "onehot_primevul_full" \
  --no-code-embeddings --one-hot \
  --fusion-mode none \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest "$PRIMEVUL_PF_DIR/manifest_train.csv" \
  --train-json-root "$PRIMEVUL_CPG_DIR/train" \
  --val-manifest "$PRIMEVUL_PF_DIR/manifest_validation.csv" \
  --val-json-root "$PRIMEVUL_CPG_DIR/validation" \
  --test-manifest "$PRIMEVUL_PF_DIR/manifest_test.csv" \
  --test-json-root "$PRIMEVUL_CPG_DIR/test"

"""
