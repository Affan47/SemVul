#!/usr/bin/env python3
"""
deep_debug_pipeline.py - Comprehensive Pipeline Debugger

This script performs an EXHAUSTIVE analysis of the entire vulnerability detection
pipeline to identify why the model is not learning (precision ~50% = random guessing).

Checks performed:
1. SQLite Embedding Database Analysis
2. Vocabulary Analysis  
3. Embedding Coverage & Quality
4. Cached .pt File Analysis
5. Label Distribution Analysis
6. Graph Structure Analysis
7. Feature Distribution Analysis
8. End-to-End Sample Tracing
9. Cross-validation of SHA256 matching
10. Embedding Similarity Analysis (are embeddings discriminative?)

Usage:
    python deep_debug_pipeline.py \
        --embedding-db /path/to/word2vec_embeddings.sqlite \
        --cache-dir /path/to/cache/word2vec128/train/signature \
        --vocab-dir /path/to/vocab \
        --strings-csv /path/to/strings_to_embed.csv \
        --output-report debug_report.txt
"""

import argparse
import csv
import hashlib
import json
import os
import sqlite3
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple, Any
import struct

import numpy as np

# Try to import optional dependencies
try:
    import torch
    HAS_TORCH = True
except ImportError:
    HAS_TORCH = False
    print("WARNING: torch not available, some checks will be skipped")

try:
    from scipy import stats
    from scipy.spatial.distance import cosine
    HAS_SCIPY = True
except ImportError:
    HAS_SCIPY = False


class DeepPipelineDebugger:
    """Comprehensive pipeline debugger."""
    
    def __init__(self, args):
        self.args = args
        self.report = []
        self.issues_found = []
        self.warnings = []
        self.stats = {}
        
    def log(self, msg: str, level: str = "INFO"):
        """Log a message."""
        prefix = {"INFO": "ℹ️ ", "WARN": "⚠️ ", "ERROR": "❌", "OK": "✅", "DEBUG": "🔍"}
        formatted = f"{prefix.get(level, '')} [{level}] {msg}"
        print(formatted)
        self.report.append(formatted)
        
        if level == "ERROR":
            self.issues_found.append(msg)
        elif level == "WARN":
            self.warnings.append(msg)
    
    def section(self, title: str):
        """Print section header."""
        sep = "=" * 70
        header = f"\n{sep}\n{title}\n{sep}"
        print(header)
        self.report.append(header)
    
    # =========================================================================
    # 1. SQLite Embedding Database Analysis
    # =========================================================================
    
    def analyze_embedding_db(self):
        """Deep analysis of the embedding SQLite database."""
        self.section("1. EMBEDDING DATABASE ANALYSIS")
        
        db_path = Path(self.args.embedding_db)
        if not db_path.exists():
            self.log(f"Embedding DB not found: {db_path}", "ERROR")
            return
        
        self.log(f"Analyzing: {db_path}")
        self.log(f"File size: {db_path.stat().st_size / 1024 / 1024:.2f} MB")
        
        conn = sqlite3.connect(str(db_path))
        cur = conn.cursor()
        
        # Get table schema
        cur.execute("SELECT sql FROM sqlite_master WHERE type='table' AND name='embeddings'")
        schema = cur.fetchone()
        if schema:
            self.log(f"Table schema: {schema[0][:200]}...", "DEBUG")
        
        # Count total embeddings
        cur.execute("SELECT COUNT(*) FROM embeddings")
        total_count = cur.fetchone()[0]
        self.log(f"Total embeddings in DB: {total_count:,}")
        self.stats["db_total_embeddings"] = total_count
        
        if total_count == 0:
            self.log("CRITICAL: Embedding database is EMPTY!", "ERROR")
            conn.close()
            return
        
        # Get column names
        cur.execute("PRAGMA table_info(embeddings)")
        columns = [row[1] for row in cur.fetchall()]
        self.log(f"Columns: {columns}", "DEBUG")
        
        # Determine vector column name
        vec_col = "vec" if "vec" in columns else "vector"
        
        # Sample embeddings for analysis
        self.log("Sampling embeddings for quality analysis...")
        cur.execute(f"SELECT sha256, {vec_col} FROM embeddings ORDER BY RANDOM() LIMIT 1000")
        samples = cur.fetchall()
        
        # Analyze embedding dimensions and values
        dims = []
        all_values = []
        zero_embeddings = 0
        nan_embeddings = 0
        extreme_embeddings = 0
        
        for sha, vec_bytes in samples:
            if vec_bytes is None:
                continue
            
            # Determine dimension from bytes
            dim = len(vec_bytes) // 4  # float32 = 4 bytes
            dims.append(dim)
            
            # Decode embedding
            emb = np.frombuffer(vec_bytes, dtype=np.float32)
            
            # Check for issues
            if np.all(emb == 0):
                zero_embeddings += 1
            if np.any(np.isnan(emb)):
                nan_embeddings += 1
            if np.any(np.abs(emb) > 100):
                extreme_embeddings += 1
            
            all_values.extend(emb[:10].tolist())  # Sample first 10 dims
        
        # Report findings
        if len(set(dims)) == 1:
            self.log(f"Embedding dimension: {dims[0]}", "OK")
            self.stats["embedding_dim"] = dims[0]
        else:
            self.log(f"INCONSISTENT dimensions: {Counter(dims)}", "ERROR")
        
        self.log(f"Zero embeddings: {zero_embeddings}/{len(samples)} ({100*zero_embeddings/len(samples):.1f}%)")
        if zero_embeddings > len(samples) * 0.1:
            self.log("High percentage of zero embeddings!", "WARN")
        
        self.log(f"NaN embeddings: {nan_embeddings}/{len(samples)}")
        if nan_embeddings > 0:
            self.log("Found NaN in embeddings!", "ERROR")
        
        self.log(f"Extreme value embeddings (|x|>100): {extreme_embeddings}/{len(samples)}")
        if extreme_embeddings > len(samples) * 0.01:
            self.log("Significant extreme values in embeddings!", "WARN")
        
        # Value distribution
        if all_values:
            arr = np.array(all_values)
            finite = arr[np.isfinite(arr)]
            if len(finite) > 0:
                self.log(f"Value range: [{finite.min():.4f}, {finite.max():.4f}]")
                self.log(f"Value mean: {finite.mean():.4f}, std: {finite.std():.4f}")
                self.stats["emb_value_mean"] = float(finite.mean())
                self.stats["emb_value_std"] = float(finite.std())
        
        # Check if embeddings are unique or mostly similar
        self.log("\nChecking embedding uniqueness...")
        cur.execute(f"SELECT {vec_col} FROM embeddings ORDER BY RANDOM() LIMIT 100")
        unique_check = cur.fetchall()
        
        if len(unique_check) >= 2:
            emb1 = np.frombuffer(unique_check[0][0], dtype=np.float32)
            similarities = []
            for i in range(1, min(50, len(unique_check))):
                emb2 = np.frombuffer(unique_check[i][0], dtype=np.float32)
                if len(emb1) == len(emb2) and np.linalg.norm(emb1) > 0 and np.linalg.norm(emb2) > 0:
                    sim = np.dot(emb1, emb2) / (np.linalg.norm(emb1) * np.linalg.norm(emb2))
                    similarities.append(sim)
            
            if similarities:
                avg_sim = np.mean(similarities)
                self.log(f"Average cosine similarity between random embeddings: {avg_sim:.4f}")
                self.stats["avg_embedding_similarity"] = float(avg_sim)
                if avg_sim > 0.95:
                    self.log("CRITICAL: Embeddings are almost identical! Model cannot learn from this.", "ERROR")
                elif avg_sim > 0.8:
                    self.log("High similarity between embeddings - may hurt discriminability", "WARN")
                else:
                    self.log("Embedding diversity looks reasonable", "OK")
        
        conn.close()
    
    # =========================================================================
    # 2. Vocabulary Analysis
    # =========================================================================
    
    def analyze_vocabulary(self):
        """Analyze vocabulary files."""
        self.section("2. VOCABULARY ANALYSIS")
        
        vocab_dir = Path(self.args.vocab_dir)
        if not vocab_dir.exists():
            self.log(f"Vocab directory not found: {vocab_dir}", "ERROR")
            return
        
        # Check for vocabulary files
        vocab_files = list(vocab_dir.glob("*.json")) + list(vocab_dir.glob("*.csv"))
        self.log(f"Found {len(vocab_files)} vocab files: {[f.name for f in vocab_files]}")
        
        # Load node type vocab
        node_vocab_path = vocab_dir / "devign_type_vocab.json"
        if not node_vocab_path.exists():
            node_vocab_path = vocab_dir / "node_type_vocab.json"
        
        if node_vocab_path.exists():
            with open(node_vocab_path) as f:
                node_vocab = json.load(f)
            self.log(f"Node types: {len(node_vocab)}")
            self.log(f"Node types: {list(node_vocab.keys())[:10]}...", "DEBUG")
            self.stats["num_node_types"] = len(node_vocab)
        else:
            self.log("Node type vocab not found!", "WARN")
        
        # Load edge type vocab
        edge_vocab_path = vocab_dir / "devign_rel_vocab.json"
        if not edge_vocab_path.exists():
            edge_vocab_path = vocab_dir / "edge_type_vocab.json"
        
        if edge_vocab_path.exists():
            with open(edge_vocab_path) as f:
                edge_vocab = json.load(f)
            self.log(f"Edge types: {len(edge_vocab)}")
            self.log(f"Edge types: {list(edge_vocab.keys())}", "DEBUG")
            self.stats["num_edge_types"] = len(edge_vocab)
        else:
            self.log("Edge type vocab not found!", "WARN")
        
        # Check strings_to_embed.csv
        strings_csv = self.args.strings_csv
        if strings_csv and Path(strings_csv).exists():
            self.log(f"\nAnalyzing strings_to_embed.csv...")
            
            total_strings = 0
            empty_strings = 0
            unique_strings = set()
            string_lengths = []
            
            with open(strings_csv, 'r', encoding='utf-8', errors='ignore') as f:
                reader = csv.DictReader(f)
                for row in reader:
                    total_strings += 1
                    text = row.get('text', '') or row.get('string', '') or ''
                    if not text.strip():
                        empty_strings += 1
                    else:
                        unique_strings.add(text)
                        string_lengths.append(len(text))
                    
                    if total_strings >= 100000:  # Limit for speed
                        break
            
            self.log(f"Total strings (sampled): {total_strings:,}")
            self.log(f"Unique strings: {len(unique_strings):,}")
            self.log(f"Empty strings: {empty_strings} ({100*empty_strings/total_strings:.1f}%)")
            
            if string_lengths:
                self.log(f"String length: min={min(string_lengths)}, max={max(string_lengths)}, "
                        f"mean={np.mean(string_lengths):.1f}")
            
            self.stats["total_vocab_strings"] = total_strings
            self.stats["unique_vocab_strings"] = len(unique_strings)
            
            if empty_strings > total_strings * 0.5:
                self.log("More than 50% empty strings!", "WARN")
    
    # =========================================================================
    # 3. Embedding Coverage Analysis
    # =========================================================================
    
    def analyze_embedding_coverage(self):
        """Check how many vocabulary strings have embeddings."""
        self.section("3. EMBEDDING COVERAGE ANALYSIS")
        
        if not self.args.strings_csv or not Path(self.args.strings_csv).exists():
            self.log("strings_csv not provided, skipping coverage analysis", "WARN")
            return
        
        if not Path(self.args.embedding_db).exists():
            self.log("embedding_db not found, skipping coverage analysis", "WARN")
            return
        
        self.log("Checking SHA256 matching between vocab and embeddings...")
        
        # Load embeddings SHA256s
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        cur.execute("SELECT sha256 FROM embeddings")
        db_hashes = set(row[0] for row in cur.fetchall())
        conn.close()
        
        self.log(f"Unique SHA256s in embedding DB: {len(db_hashes):,}")
        
        # Check coverage of strings_to_embed.csv
        matched = 0
        not_matched = 0
        sample_misses = []
        
        with open(self.args.strings_csv, 'r', encoding='utf-8', errors='ignore') as f:
            reader = csv.DictReader(f)
            for i, row in enumerate(reader):
                text = row.get('text', '') or row.get('string', '') or ''
                if not text.strip():
                    continue
                
                # Compute SHA256 (must match how embeddings were stored)
                # Try different normalization approaches
                sha_raw = hashlib.sha256(text.encode('utf-8', errors='ignore')).hexdigest()
                sha_stripped = hashlib.sha256(text.strip().encode('utf-8', errors='ignore')).hexdigest()
                sha_lower = hashlib.sha256(text.lower().strip().encode('utf-8', errors='ignore')).hexdigest()
                
                if sha_raw in db_hashes or sha_stripped in db_hashes or sha_lower in db_hashes:
                    matched += 1
                else:
                    not_matched += 1
                    if len(sample_misses) < 10:
                        sample_misses.append(text[:50])
                
                if i >= 50000:  # Limit for speed
                    break
        
        total = matched + not_matched
        if total > 0:
            coverage = 100 * matched / total
            self.log(f"Embedding coverage: {matched:,}/{total:,} ({coverage:.1f}%)")
            self.stats["embedding_coverage_pct"] = coverage
            
            if coverage < 50:
                self.log("CRITICAL: Less than 50% embedding coverage!", "ERROR")
                self.log("This means most nodes get ZERO embeddings - model cannot learn!", "ERROR")
            elif coverage < 80:
                self.log("Low embedding coverage - many nodes use fallback", "WARN")
            else:
                self.log("Good embedding coverage", "OK")
            
            if sample_misses:
                self.log(f"Sample strings without embeddings: {sample_misses[:5]}", "DEBUG")
    
    # =========================================================================
    # 4. Cached .pt File Analysis
    # =========================================================================
    
    def analyze_cached_files(self):
        """Deep analysis of cached PyG .pt files."""
        self.section("4. CACHED .PT FILE ANALYSIS")
        
        if not HAS_TORCH:
            self.log("torch not available, skipping .pt analysis", "WARN")
            return
        
        cache_dir = Path(self.args.cache_dir)
        if not cache_dir.exists():
            self.log(f"Cache directory not found: {cache_dir}", "ERROR")
            return
        
        pt_files = list(cache_dir.rglob("*.pt"))
        self.log(f"Found {len(pt_files):,} .pt files")
        
        if not pt_files:
            self.log("No .pt files found!", "ERROR")
            return
        
        # Sample files for analysis
        sample_size = min(500, len(pt_files))
        import random
        random.seed(42)
        sampled_files = random.sample(pt_files, sample_size)
        
        # Collect statistics
        node_counts = []
        edge_counts = []
        feature_dims = []
        labels = []
        
        all_features = []
        zero_feature_graphs = 0
        nan_feature_graphs = 0
        
        feature_means = []
        feature_stds = []
        feature_nonzero_pcts = []
        
        edge_type_counts = Counter()
        
        self.log(f"Analyzing {sample_size} sampled files...")
        
        for pt_path in sampled_files:
            try:
                data = torch.load(pt_path, map_location='cpu', weights_only=False)
            except Exception as e:
                self.log(f"Error loading {pt_path.name}: {e}", "DEBUG")
                continue
            
            # Node features
            if hasattr(data, 'x') and data.x is not None:
                x = data.x.float()
                node_counts.append(x.shape[0])
                feature_dims.append(x.shape[1])
                
                # Feature statistics
                feature_means.append(float(x.mean()))
                feature_stds.append(float(x.std()))
                nonzero_pct = float((x != 0).sum() / x.numel() * 100)
                feature_nonzero_pcts.append(nonzero_pct)
                
                if torch.all(x == 0):
                    zero_feature_graphs += 1
                if torch.any(torch.isnan(x)):
                    nan_feature_graphs += 1
                
                # Sample some feature values
                if len(all_features) < 10000:
                    flat = x.flatten()[:100].tolist()
                    all_features.extend(flat)
            
            # Edges
            if hasattr(data, 'edge_index') and data.edge_index is not None:
                edge_counts.append(data.edge_index.shape[1])
            
            # Edge types
            if hasattr(data, 'edge_type') and data.edge_type is not None:
                for et in data.edge_type.tolist():
                    edge_type_counts[et] += 1
            
            # Labels
            if hasattr(data, 'y') and data.y is not None:
                y = data.y
                if y.dim() == 0:
                    labels.append(int(y.item()))
                else:
                    labels.append(int(y[0].item()))
        
        # Report findings
        self.log(f"\nGraph Statistics ({sample_size} samples):")
        if node_counts:
            self.log(f"  Nodes per graph: min={min(node_counts)}, max={max(node_counts)}, "
                    f"mean={np.mean(node_counts):.1f}, median={np.median(node_counts):.0f}")
            self.stats["avg_nodes_per_graph"] = float(np.mean(node_counts))
        
        if edge_counts:
            self.log(f"  Edges per graph: min={min(edge_counts)}, max={max(edge_counts)}, "
                    f"mean={np.mean(edge_counts):.1f}, median={np.median(edge_counts):.0f}")
            self.stats["avg_edges_per_graph"] = float(np.mean(edge_counts))
        
        if feature_dims:
            unique_dims = set(feature_dims)
            if len(unique_dims) == 1:
                self.log(f"  Feature dimension: {feature_dims[0]}", "OK")
                self.stats["feature_dim"] = feature_dims[0]
            else:
                self.log(f"  INCONSISTENT feature dimensions: {Counter(feature_dims)}", "ERROR")
        
        # Feature quality
        self.log(f"\nFeature Quality:")
        self.log(f"  Zero-feature graphs: {zero_feature_graphs}/{sample_size} ({100*zero_feature_graphs/sample_size:.1f}%)")
        self.log(f"  NaN-feature graphs: {nan_feature_graphs}/{sample_size}")
        
        if feature_means:
            self.log(f"  Feature mean across graphs: {np.mean(feature_means):.4f} (std: {np.std(feature_means):.4f})")
            self.log(f"  Feature std across graphs: {np.mean(feature_stds):.4f}")
            self.log(f"  Non-zero percentage: {np.mean(feature_nonzero_pcts):.1f}%")
            self.stats["avg_feature_mean"] = float(np.mean(feature_means))
            self.stats["avg_feature_std"] = float(np.mean(feature_stds))
            self.stats["avg_nonzero_pct"] = float(np.mean(feature_nonzero_pcts))
        
        if zero_feature_graphs > sample_size * 0.1:
            self.log("CRITICAL: Many graphs have ALL-ZERO features!", "ERROR")
        
        # Check if features are mostly one-hot (first 28 dims) vs embeddings (rest)
        if all_features and feature_dims and feature_dims[0] > 28:
            self.log("\nAnalyzing feature composition (one-hot vs embedding parts):")
            # Load one file to check
            data = torch.load(sampled_files[0], map_location='cpu', weights_only=False)
            if hasattr(data, 'x') and data.x is not None:
                x = data.x.float()
                oh_part = x[:, :28]  # One-hot part
                emb_part = x[:, 28:]  # Embedding part
                
                oh_nonzero = float((oh_part != 0).sum() / oh_part.numel() * 100)
                emb_nonzero = float((emb_part != 0).sum() / emb_part.numel() * 100)
                
                self.log(f"  One-hot part (first 28 dims): {oh_nonzero:.1f}% non-zero")
                self.log(f"  Embedding part (dims 28+): {emb_nonzero:.1f}% non-zero")
                self.stats["onehot_nonzero_pct"] = oh_nonzero
                self.stats["embedding_nonzero_pct"] = emb_nonzero
                
                if emb_nonzero < 10:
                    self.log("CRITICAL: Embedding part is mostly ZEROS! Embeddings not being applied!", "ERROR")
                
                # Check embedding part values
                emb_flat = emb_part.flatten()
                emb_finite = emb_flat[torch.isfinite(emb_flat)]
                if len(emb_finite) > 0:
                    self.log(f"  Embedding values: min={emb_finite.min():.4f}, max={emb_finite.max():.4f}, "
                            f"mean={emb_finite.mean():.4f}")
        
        # Label distribution
        if labels:
            label_counts = Counter(labels)
            self.log(f"\nLabel Distribution:")
            for lbl, cnt in sorted(label_counts.items()):
                pct = 100 * cnt / len(labels)
                self.log(f"  Label {lbl}: {cnt} ({pct:.1f}%)")
            
            self.stats["label_distribution"] = dict(label_counts)
            
            # Check for severe imbalance
            if len(label_counts) == 2:
                counts = list(label_counts.values())
                ratio = max(counts) / min(counts)
                if ratio > 5:
                    self.log(f"Severe class imbalance (ratio {ratio:.1f}:1)", "WARN")
        
        # Edge types
        if edge_type_counts:
            self.log(f"\nEdge Type Distribution:")
            total_edges = sum(edge_type_counts.values())
            for et, cnt in sorted(edge_type_counts.items()):
                self.log(f"  Type {et}: {cnt:,} ({100*cnt/total_edges:.1f}%)")
    
    # =========================================================================
    # 5. End-to-End Sample Trace
    # =========================================================================
    
    def trace_sample_end_to_end(self):
        """Trace a single sample through the entire pipeline."""
        self.section("5. END-TO-END SAMPLE TRACE")
        
        if not HAS_TORCH:
            self.log("torch not available, skipping trace", "WARN")
            return
        
        cache_dir = Path(self.args.cache_dir)
        pt_files = list(cache_dir.rglob("*.pt"))
        
        if not pt_files:
            self.log("No .pt files to trace", "ERROR")
            return
        
        # Pick a sample
        import random
        random.seed(42)
        sample_file = random.choice(pt_files)
        
        self.log(f"Tracing sample: {sample_file.name}")
        
        data = torch.load(sample_file, map_location='cpu', weights_only=False)
        
        self.log(f"\nData object attributes: {[a for a in dir(data) if not a.startswith('_')]}", "DEBUG")
        
        # Node features
        if hasattr(data, 'x') and data.x is not None:
            x = data.x.float()
            self.log(f"Node features (x): shape={tuple(x.shape)}")
            
            # First node
            first_node = x[0]
            self.log(f"  First node features: {first_node[:10].tolist()}...")
            
            # Check structure
            if x.shape[1] > 28:
                oh = first_node[:28]
                emb = first_node[28:]
                
                oh_idx = torch.where(oh > 0)[0]
                self.log(f"  One-hot indices: {oh_idx.tolist()}")
                
                emb_nonzero = torch.sum(emb != 0).item()
                self.log(f"  Embedding non-zeros: {emb_nonzero}/{len(emb)}")
                
                if emb_nonzero > 0:
                    emb_vals = emb[emb != 0]
                    self.log(f"  Embedding values (sample): {emb_vals[:5].tolist()}")
                else:
                    self.log("  WARNING: Embedding part is all zeros for this node!", "WARN")
        
        # Edges
        if hasattr(data, 'edge_index') and data.edge_index is not None:
            ei = data.edge_index
            self.log(f"Edge index: shape={tuple(ei.shape)}, num_edges={ei.shape[1]}")
            
            # Check connectivity
            unique_src = len(torch.unique(ei[0]))
            unique_dst = len(torch.unique(ei[1]))
            self.log(f"  Unique source nodes: {unique_src}")
            self.log(f"  Unique destination nodes: {unique_dst}")
            
            if hasattr(data, 'x'):
                num_nodes = data.x.shape[0]
                connected_ratio = unique_src / num_nodes
                self.log(f"  Node connectivity: {100*connected_ratio:.1f}% nodes have outgoing edges")
                
                if connected_ratio < 0.5:
                    self.log("Low graph connectivity - many isolated nodes", "WARN")
        
        # Edge types
        if hasattr(data, 'edge_type') and data.edge_type is not None:
            et = data.edge_type
            self.log(f"Edge types: {Counter(et.tolist())}")
        
        # Label
        if hasattr(data, 'y') and data.y is not None:
            self.log(f"Label (y): {data.y}")
    
    # =========================================================================
    # 6. Embedding Discriminability Analysis
    # =========================================================================
    
    def analyze_embedding_discriminability(self):
        """Check if embeddings help distinguish vulnerable vs non-vulnerable code."""
        self.section("6. EMBEDDING DISCRIMINABILITY ANALYSIS")
        
        if not HAS_TORCH:
            self.log("torch not available, skipping", "WARN")
            return
        
        cache_dir = Path(self.args.cache_dir)
        pt_files = list(cache_dir.rglob("*.pt"))
        
        if len(pt_files) < 100:
            self.log("Not enough files for discriminability analysis", "WARN")
            return
        
        self.log("Collecting graph-level embeddings by label...")
        
        # Collect graph-level features by label
        features_by_label = defaultdict(list)
        
        import random
        random.seed(42)
        sampled = random.sample(pt_files, min(1000, len(pt_files)))
        
        for pt_path in sampled:
            try:
                data = torch.load(pt_path, map_location='cpu', weights_only=False)
            except:
                continue
            
            if not hasattr(data, 'x') or data.x is None:
                continue
            if not hasattr(data, 'y') or data.y is None:
                continue
            
            x = data.x.float()
            y = int(data.y.item()) if data.y.dim() == 0 else int(data.y[0].item())
            
            # Compute graph-level representation (mean pooling)
            graph_emb = x.mean(dim=0).numpy()
            
            if np.all(np.isfinite(graph_emb)):
                features_by_label[y].append(graph_emb)
        
        self.log(f"Collected: {[(k, len(v)) for k, v in features_by_label.items()]}")
        
        if len(features_by_label) < 2:
            self.log("Need at least 2 classes for discriminability analysis", "WARN")
            return
        
        # Compare distributions
        labels = sorted(features_by_label.keys())
        
        if len(labels) == 2:
            feats_0 = np.array(features_by_label[labels[0]])
            feats_1 = np.array(features_by_label[labels[1]])
            
            self.log(f"\nClass {labels[0]} (non-vuln): {len(feats_0)} samples")
            self.log(f"Class {labels[1]} (vuln): {len(feats_1)} samples")
            
            # Mean vectors
            mean_0 = feats_0.mean(axis=0)
            mean_1 = feats_1.mean(axis=0)
            
            # Cosine similarity between class means
            norm_0 = np.linalg.norm(mean_0)
            norm_1 = np.linalg.norm(mean_1)
            
            if norm_0 > 0 and norm_1 > 0:
                cos_sim = np.dot(mean_0, mean_1) / (norm_0 * norm_1)
                self.log(f"\nCosine similarity between class means: {cos_sim:.4f}")
                self.stats["class_mean_similarity"] = float(cos_sim)
                
                if cos_sim > 0.99:
                    self.log("CRITICAL: Class means are nearly IDENTICAL! Features don't distinguish classes!", "ERROR")
                elif cos_sim > 0.95:
                    self.log("Class means are very similar - features may not be discriminative", "WARN")
                else:
                    self.log("Class means show some difference", "OK")
            
            # Euclidean distance between class means
            eucl_dist = np.linalg.norm(mean_0 - mean_1)
            self.log(f"Euclidean distance between class means: {eucl_dist:.4f}")
            
            # Within-class vs between-class variance
            var_0 = np.var(feats_0, axis=0).mean()
            var_1 = np.var(feats_1, axis=0).mean()
            between_var = np.var([mean_0, mean_1], axis=0).mean()
            
            self.log(f"\nVariance analysis:")
            self.log(f"  Within-class variance (class 0): {var_0:.6f}")
            self.log(f"  Within-class variance (class 1): {var_1:.6f}")
            self.log(f"  Between-class variance: {between_var:.6f}")
            
            # Fisher's criterion (simplified)
            within_var = (var_0 + var_1) / 2
            if within_var > 0:
                fisher_ratio = between_var / within_var
                self.log(f"  Fisher ratio (between/within): {fisher_ratio:.4f}")
                self.stats["fisher_ratio"] = float(fisher_ratio)
                
                if fisher_ratio < 0.01:
                    self.log("CRITICAL: Fisher ratio very low - features not separating classes!", "ERROR")
                elif fisher_ratio < 0.1:
                    self.log("Low Fisher ratio - weak class separation", "WARN")
            
            # Check if embedding part contributes
            if feats_0.shape[1] > 28:
                self.log("\nAnalyzing one-hot vs embedding contribution:")
                
                # One-hot part
                oh_0 = feats_0[:, :28]
                oh_1 = feats_1[:, :28]
                oh_mean_0 = oh_0.mean(axis=0)
                oh_mean_1 = oh_1.mean(axis=0)
                oh_dist = np.linalg.norm(oh_mean_0 - oh_mean_1)
                
                # Embedding part
                emb_0 = feats_0[:, 28:]
                emb_1 = feats_1[:, 28:]
                emb_mean_0 = emb_0.mean(axis=0)
                emb_mean_1 = emb_1.mean(axis=0)
                emb_dist = np.linalg.norm(emb_mean_0 - emb_mean_1)
                
                self.log(f"  One-hot part distance: {oh_dist:.4f}")
                self.log(f"  Embedding part distance: {emb_dist:.4f}")
                
                # Check if embedding part is mostly zeros
                emb_0_nonzero = np.mean(emb_0 != 0) * 100
                emb_1_nonzero = np.mean(emb_1 != 0) * 100
                self.log(f"  Embedding non-zero (class 0): {emb_0_nonzero:.1f}%")
                self.log(f"  Embedding non-zero (class 1): {emb_1_nonzero:.1f}%")
                
                if emb_0_nonzero < 5 and emb_1_nonzero < 5:
                    self.log("CRITICAL: Embeddings are mostly zeros! They're not being used!", "ERROR")
    
    # =========================================================================
    # 7. SHA256 Matching Verification
    # =========================================================================
    
    def verify_sha256_matching(self):
        """Verify SHA256 computation matches between components."""
        self.section("7. SHA256 MATCHING VERIFICATION")
        
        if not self.args.strings_csv or not Path(self.args.strings_csv).exists():
            self.log("strings_csv not provided", "WARN")
            return
        
        if not Path(self.args.embedding_db).exists():
            self.log("embedding_db not found", "WARN")
            return
        
        self.log("Testing SHA256 hash matching...")
        
        # Get a sample string from CSV
        with open(self.args.strings_csv, 'r', encoding='utf-8', errors='ignore') as f:
            reader = csv.DictReader(f)
            sample_row = next(reader)
        
        text = sample_row.get('text', '') or sample_row.get('string', '')
        self.log(f"Sample text: '{text[:50]}...'")
        
        # Try different SHA256 methods
        methods = [
            ("raw", hashlib.sha256(text.encode('utf-8', errors='ignore')).hexdigest()),
            ("strip", hashlib.sha256(text.strip().encode('utf-8', errors='ignore')).hexdigest()),
            ("lower_strip", hashlib.sha256(text.lower().strip().encode('utf-8', errors='ignore')).hexdigest()),
            ("normalize_nfc", hashlib.sha256(text.encode('utf-8', errors='ignore')).hexdigest()),
        ]
        
        self.log("SHA256 computed with different methods:")
        for method, sha in methods:
            self.log(f"  {method}: {sha[:16]}...")
        
        # Check which exists in DB
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        
        found_method = None
        for method, sha in methods:
            cur.execute("SELECT COUNT(*) FROM embeddings WHERE sha256 = ?", (sha,))
            count = cur.fetchone()[0]
            if count > 0:
                self.log(f"  ✓ '{method}' method matches DB!", "OK")
                found_method = method
                break
        
        if not found_method:
            self.log("No SHA256 method matched! Check normalization in vocab_builder vs extractor!", "ERROR")
            
            # Sample some hashes from DB
            cur.execute("SELECT sha256 FROM embeddings LIMIT 5")
            db_samples = [row[0] for row in cur.fetchall()]
            self.log(f"Sample SHA256s in DB: {db_samples}", "DEBUG")
        
        conn.close()
    
    # =========================================================================
    # 8. Word2Vec Specific Checks
    # =========================================================================
    
    def check_word2vec_specific(self):
        """Word2Vec specific quality checks."""
        self.section("8. WORD2VEC SPECIFIC ANALYSIS")
        
        if not Path(self.args.embedding_db).exists():
            return
        
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        
        # Check for common code tokens
        common_tokens = ["int", "return", "if", "else", "for", "while", "void", 
                        "char", "NULL", "sizeof", "malloc", "free", "printf"]
        
        self.log("Checking embeddings for common C/C++ tokens:")
        
        found = 0
        not_found = []
        
        for token in common_tokens:
            sha = hashlib.sha256(token.encode('utf-8')).hexdigest()
            cur.execute("SELECT COUNT(*) FROM embeddings WHERE sha256 = ?", (sha,))
            count = cur.fetchone()[0]
            
            if count > 0:
                found += 1
                self.log(f"  ✓ '{token}' found", "DEBUG")
            else:
                not_found.append(token)
        
        self.log(f"Found {found}/{len(common_tokens)} common tokens")
        
        if not_found:
            self.log(f"Missing: {not_found}", "WARN")
            if len(not_found) > len(common_tokens) / 2:
                self.log("Many common tokens missing - Word2Vec may have different tokenization!", "WARN")
        
        conn.close()
    
    # =========================================================================
    # 9. Model Prediction Analysis (if model available)
    # =========================================================================
    
    def analyze_predictions(self):
        """Analyze if there's a pre-trained model to check predictions."""
        self.section("9. PREDICTION SANITY CHECK")
        
        cache_dir = Path(self.args.cache_dir)
        
        # Look for best_model.pt
        model_paths = list(cache_dir.parent.parent.parent.rglob("best_model.pt"))
        if not model_paths:
            model_paths = list(Path(".").rglob("best_model.pt"))
        
        if model_paths:
            self.log(f"Found model files: {[str(p) for p in model_paths[:3]]}")
            self.log("To analyze predictions, load the model and check output distribution")
        else:
            self.log("No trained model found - run training first")
    
    # =========================================================================
    # 10. Summary and Recommendations
    # =========================================================================
    
    def generate_summary(self):
        """Generate final summary and recommendations."""
        self.section("SUMMARY AND RECOMMENDATIONS")
        
        self.log(f"\nIssues Found: {len(self.issues_found)}")
        for issue in self.issues_found:
            self.log(f"  ❌ {issue}")
        
        self.log(f"\nWarnings: {len(self.warnings)}")
        for warn in self.warnings:
            self.log(f"  ⚠️ {warn}")
        
        # Key stats
        self.log("\nKey Statistics:")
        for key, val in self.stats.items():
            if isinstance(val, float):
                self.log(f"  {key}: {val:.4f}")
            else:
                self.log(f"  {key}: {val}")
        
        # Recommendations
        self.log("\n" + "=" * 70)
        self.log("LIKELY ROOT CAUSES (ranked by probability):")
        self.log("=" * 70)
        
        recommendations = []
        
        # Check embedding coverage
        if self.stats.get("embedding_coverage_pct", 100) < 50:
            recommendations.append((1, "LOW EMBEDDING COVERAGE",
                "Less than 50% of vocabulary has embeddings. "
                "Most nodes get ZERO embeddings, making features uninformative. "
                "FIX: Retrain Word2Vec on larger corpus or fix SHA256 mismatch."))
        
        # Check embedding similarity
        if self.stats.get("avg_embedding_similarity", 0) > 0.9:
            recommendations.append((1, "EMBEDDINGS TOO SIMILAR",
                "Random embeddings are >90% similar (cosine). "
                "Word2Vec collapsed or wasn't trained properly. "
                "FIX: Retrain Word2Vec with proper parameters (min_count, epochs)."))
        
        # Check class separation
        if self.stats.get("class_mean_similarity", 0) > 0.99:
            recommendations.append((1, "NO CLASS SEPARATION",
                "Vulnerable and non-vulnerable code have identical feature means. "
                "Model cannot learn to distinguish them. "
                "FIX: Check label assignment, or features are not informative."))
        
        # Check embedding non-zero
        if self.stats.get("embedding_nonzero_pct", 100) < 10:
            recommendations.append((1, "EMBEDDINGS MOSTLY ZEROS",
                "The embedding part of features is >90% zeros. "
                "Embeddings are not being retrieved/applied. "
                "FIX: Check SHA256 matching, cache building, or embedding DB."))
        
        # Check Fisher ratio
        if self.stats.get("fisher_ratio", 1) < 0.01:
            recommendations.append((2, "LOW FISHER RATIO",
                "Between-class variance is much smaller than within-class. "
                "Features don't help separate classes. "
                "FIX: Use different/better embeddings or add more features."))
        
        # Check embedding values
        if self.stats.get("emb_value_std", 0) > 10:
            recommendations.append((2, "EMBEDDING VALUE INSTABILITY",
                "Embedding values have high variance. "
                "May cause training instability. "
                "FIX: Normalize embeddings or use layer norm in model."))
        
        # Check graph structure
        if self.stats.get("avg_edges_per_graph", 1000) < 10:
            recommendations.append((2, "SPARSE GRAPHS",
                "Graphs have very few edges. "
                "GNN cannot propagate information effectively. "
                "FIX: Check edge construction in cache_manager."))
        
        # Sort and display
        recommendations.sort(key=lambda x: x[0])
        
        for i, (priority, title, desc) in enumerate(recommendations, 1):
            self.log(f"\n{i}. [{title}]")
            self.log(f"   {desc}")
        
        if not recommendations:
            self.log("\nNo obvious issues detected. Consider:")
            self.log("  1. Training hyperparameters (learning rate, batch size)")
            self.log("  2. Model architecture (maybe too simple/complex)")
            self.log("  3. Data quality (label noise, duplicates)")
            self.log("  4. Evaluation protocol (train/test leakage)")
        
        # Save report
        if self.args.output_report:
            with open(self.args.output_report, 'w') as f:
                f.write('\n'.join(self.report))
            self.log(f"\nReport saved to: {self.args.output_report}")
    
    def run_all(self):
        """Run all diagnostic checks."""
        start_time = time.time()
        
        self.log(f"Deep Pipeline Debugger - {time.strftime('%Y-%m-%d %H:%M:%S')}")
        self.log(f"This may take several minutes...\n")
        
        # Run all checks
        self.analyze_embedding_db()
        self.analyze_vocabulary()
        self.analyze_embedding_coverage()
        self.analyze_cached_files()
        self.trace_sample_end_to_end()
        self.analyze_embedding_discriminability()
        self.verify_sha256_matching()
        self.check_word2vec_specific()
        self.analyze_predictions()
        self.generate_summary()
        
        elapsed = time.time() - start_time
        self.log(f"\nTotal time: {elapsed:.1f} seconds")


def main():
    parser = argparse.ArgumentParser(description="Deep Pipeline Debugger")
    parser.add_argument("--embedding-db", required=True, 
                       help="Path to word2vec_embeddings.sqlite")
    parser.add_argument("--cache-dir", required=True,
                       help="Path to cached .pt files (e.g., .../train/signature)")
    parser.add_argument("--vocab-dir", required=True,
                       help="Path to vocabulary directory")
    parser.add_argument("--strings-csv", 
                       help="Path to strings_to_embed.csv")
    parser.add_argument("--output-report", default="debug_report.txt",
                       help="Output report file")
    
    args = parser.parse_args()
    
    debugger = DeepPipelineDebugger(args)
    debugger.run_all()


if __name__ == "__main__":
    main()



"""

python deep_debug_pipeline.py \
    --embedding-db "./Clean_exports/cache_devign_v2/word2vec_embeddings.sqlite" \
    --cache-dir "./Clean_exports/cache_devign_v2/word2vec128/train/eabf47f3e60df24e" \
    --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
    --strings-csv "./Clean_exports/devign_vocab_normfunc_v2/strings_to_embed.csv" \
    --output-report debug_report.txt

"""