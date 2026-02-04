#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_pipeline.py - Comprehensive Pipeline Diagnostics

Analyzes:
1. Raw CPG data quality
2. Embedding coverage and quality
3. Feature concatenation correctness
4. Node text extraction
5. Class distribution analysis

Run from project root:
    python diagnose_pipeline.py \
        --cache-dir /path/to/cache_devign_v2 \
        --dataset-name word2vec_256d_full \
        --cache-signature c95a4168d5a65be0 \
        --num-samples 100
"""

import argparse
import io
import json
import zipfile
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import numpy as np
import torch
from torch_geometric.data import Data

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_samples(cache_dir: str, dataset_name: str, cache_signature: str, 
                 split: str = "train", max_samples: int = 100) -> List[Data]:
    """Load samples from cache."""
    cache_dir = Path(cache_dir)
    
    # Try different path structures
    paths_to_try = [
        cache_dir / dataset_name / cache_signature / split / f"cache_{split}.zip",
        cache_dir / dataset_name / cache_signature[:16] / split / f"cache_{split}.zip",
        cache_dir / dataset_name / split / cache_signature / f"cache_{split}.zip",
    ]
    
    zip_path = None
    for p in paths_to_try:
        if p.exists():
            zip_path = p
            break
    
    if zip_path is None:
        raise FileNotFoundError(f"Cache not found. Tried: {paths_to_try}")
    
    print(f"Loading from: {zip_path}")
    
    samples = []
    with zipfile.ZipFile(zip_path, 'r') as zf:
        pt_files = sorted([n for n in zf.namelist() if n.endswith('.pt')])[:max_samples]
        
        for pt_name in tqdm(pt_files, desc="Loading samples"):
            try:
                with zf.open(pt_name) as f:
                    data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                    if hasattr(data, 'y') and data.y is not None:
                        samples.append(data)
            except Exception as e:
                print(f"Failed: {pt_name}: {e}")
    
    return samples


def analyze_features(samples: List[Data]) -> Dict:
    """Analyze feature matrix structure and statistics."""
    print("\n" + "=" * 70)
    print("FEATURE ANALYSIS")
    print("=" * 70)
    
    if not samples:
        return {}
    
    sample = samples[0]
    x = sample.x
    feature_dim = x.size(1)
    
    print(f"\n1. FEATURE DIMENSIONS")
    print(f"   Total feature dimension: {feature_dim}")
    
    # Analyze structure
    # Assume: [one_hot (N) | embedding (256)]
    # Try to detect one-hot portion
    
    all_x = torch.cat([s.x for s in samples[:50]], dim=0)  # Sample of all nodes
    
    # For each dimension, check if it looks like one-hot (only 0 or 1)
    one_hot_dims = 0
    for d in range(min(32, feature_dim)):  # Check first 32 dims
        unique_vals = torch.unique(all_x[:, d])
        if len(unique_vals) <= 2 and all(v in [0, 1] for v in unique_vals.tolist()):
            one_hot_dims += 1
        else:
            break
    
    embedding_dims = feature_dim - one_hot_dims
    
    print(f"   Detected one-hot dimensions: {one_hot_dims}")
    print(f"   Detected embedding dimensions: {embedding_dims}")
    
    print(f"\n2. ONE-HOT ENCODING ANALYSIS (first {one_hot_dims} dims)")
    
    if one_hot_dims > 0:
        one_hot_part = all_x[:, :one_hot_dims]
        
        # Check if valid one-hot (exactly one 1 per row)
        row_sums = one_hot_part.sum(dim=1)
        valid_one_hot = (row_sums == 1).float().mean().item()
        print(f"   Valid one-hot encoding: {valid_one_hot*100:.1f}% of nodes")
        
        # Distribution of node types
        node_type_indices = one_hot_part.argmax(dim=1)
        type_counts = Counter(node_type_indices.tolist())
        print(f"   Node type distribution (top 10):")
        for idx, count in sorted(type_counts.items(), key=lambda x: -x[1])[:10]:
            print(f"      Type {idx}: {count} ({100*count/len(node_type_indices):.1f}%)")
    
    print(f"\n3. EMBEDDING ANALYSIS (dims {one_hot_dims}:{feature_dim})")
    
    if embedding_dims > 0:
        emb_part = all_x[:, one_hot_dims:]
        
        # Check for zero embeddings
        zero_rows = (emb_part.abs().sum(dim=1) == 0).float().mean().item()
        print(f"   Zero embeddings: {zero_rows*100:.1f}% of nodes")
        
        # Embedding statistics
        non_zero_emb = emb_part[emb_part.abs().sum(dim=1) > 0]
        if len(non_zero_emb) > 0:
            print(f"   Non-zero embedding stats:")
            print(f"      Mean: {non_zero_emb.mean().item():.4f}")
            print(f"      Std:  {non_zero_emb.std().item():.4f}")
            print(f"      Min:  {non_zero_emb.min().item():.4f}")
            print(f"      Max:  {non_zero_emb.max().item():.4f}")
            
            # Check for embedding diversity
            norms = non_zero_emb.norm(dim=1)
            print(f"      L2 norm mean: {norms.mean().item():.4f}")
            print(f"      L2 norm std:  {norms.std().item():.4f}")
            
            # Sample similarity check (are embeddings diverse?)
            if len(non_zero_emb) >= 100:
                sample_emb = non_zero_emb[:100]
                sample_emb_norm = sample_emb / sample_emb.norm(dim=1, keepdim=True).clamp(min=1e-8)
                sim_matrix = torch.mm(sample_emb_norm, sample_emb_norm.T)
                # Exclude diagonal
                mask = ~torch.eye(100, dtype=torch.bool)
                avg_sim = sim_matrix[mask].mean().item()
                print(f"      Avg pairwise cosine similarity: {avg_sim:.4f}")
                print(f"      (0.0 = diverse, 1.0 = identical)")
    
    return {
        "feature_dim": feature_dim,
        "one_hot_dims": one_hot_dims,
        "embedding_dims": embedding_dims,
        "zero_embedding_ratio": zero_rows if embedding_dims > 0 else 0,
    }


def analyze_by_node_type(samples: List[Data], one_hot_dims: int) -> Dict:
    """Analyze embeddings by node type."""
    print("\n" + "=" * 70)
    print("NODE TYPE EMBEDDING COVERAGE")
    print("=" * 70)
    
    if one_hot_dims == 0:
        print("Cannot analyze - no one-hot encoding detected")
        return {}
    
    all_x = torch.cat([s.x for s in samples[:50]], dim=0)
    
    node_types = all_x[:, :one_hot_dims].argmax(dim=1)
    embeddings = all_x[:, one_hot_dims:]
    
    # For each node type, check embedding coverage
    type_stats = {}
    for node_type in node_types.unique().tolist():
        mask = node_types == node_type
        type_emb = embeddings[mask]
        
        zero_count = (type_emb.abs().sum(dim=1) == 0).sum().item()
        total_count = mask.sum().item()
        coverage = 1 - (zero_count / total_count) if total_count > 0 else 0
        
        type_stats[node_type] = {
            "total": total_count,
            "with_embedding": total_count - zero_count,
            "coverage": coverage,
        }
    
    print(f"\nNode Type | Total | With Emb | Coverage")
    print("-" * 45)
    for node_type in sorted(type_stats.keys()):
        stats = type_stats[node_type]
        print(f"Type {node_type:2d}   | {stats['total']:5d} | {stats['with_embedding']:5d}    | {stats['coverage']*100:5.1f}%")
    
    return type_stats


def analyze_vulnerability_signal(samples: List[Data], one_hot_dims: int) -> Dict:
    """Analyze if embeddings differ between vulnerable and safe samples."""
    print("\n" + "=" * 70)
    print("VULNERABILITY SIGNAL ANALYSIS")
    print("=" * 70)
    
    vuln_samples = [s for s in samples if s.y.item() == 1]
    safe_samples = [s for s in samples if s.y.item() == 0]
    
    print(f"\nSamples: {len(vuln_samples)} vulnerable, {len(safe_samples)} safe")
    
    if len(vuln_samples) == 0 or len(safe_samples) == 0:
        print("Need both classes for analysis")
        return {}
    
    # Graph-level statistics
    print(f"\n1. GRAPH SIZE COMPARISON")
    vuln_nodes = [s.x.size(0) for s in vuln_samples]
    safe_nodes = [s.x.size(0) for s in safe_samples]
    vuln_edges = [s.edge_index.size(1) for s in vuln_samples]
    safe_edges = [s.edge_index.size(1) for s in safe_samples]
    
    print(f"   Vulnerable: {np.mean(vuln_nodes):.1f} nodes, {np.mean(vuln_edges):.1f} edges")
    print(f"   Safe:       {np.mean(safe_nodes):.1f} nodes, {np.mean(safe_edges):.1f} edges")
    
    # Node type distribution comparison
    if one_hot_dims > 0:
        print(f"\n2. NODE TYPE DISTRIBUTION BY CLASS")
        
        vuln_types = Counter()
        safe_types = Counter()
        
        for s in vuln_samples[:30]:
            types = s.x[:, :one_hot_dims].argmax(dim=1).tolist()
            vuln_types.update(types)
        
        for s in safe_samples[:30]:
            types = s.x[:, :one_hot_dims].argmax(dim=1).tolist()
            safe_types.update(types)
        
        all_types = set(vuln_types.keys()) | set(safe_types.keys())
        
        print(f"\n   Type | Vuln % | Safe % | Diff")
        print("   " + "-" * 35)
        
        vuln_total = sum(vuln_types.values())
        safe_total = sum(safe_types.values())
        
        diffs = []
        for t in sorted(all_types):
            v_pct = 100 * vuln_types.get(t, 0) / vuln_total if vuln_total > 0 else 0
            s_pct = 100 * safe_types.get(t, 0) / safe_total if safe_total > 0 else 0
            diff = v_pct - s_pct
            diffs.append((t, diff))
            if abs(diff) > 0.5:  # Only show significant differences
                print(f"   {t:4d} | {v_pct:5.1f}% | {s_pct:5.1f}% | {diff:+5.1f}%")
        
        # Find most discriminative node type
        diffs.sort(key=lambda x: abs(x[1]), reverse=True)
        print(f"\n   Most discriminative node type: Type {diffs[0][0]} ({diffs[0][1]:+.1f}%)")
    
    # Embedding comparison
    print(f"\n3. EMBEDDING SPACE SEPARATION")
    
    # Compute mean embedding for each class
    def get_mean_embedding(samples_list):
        all_emb = []
        for s in samples_list[:30]:
            emb = s.x[:, one_hot_dims:] if one_hot_dims > 0 else s.x
            # Only non-zero embeddings
            non_zero_mask = emb.abs().sum(dim=1) > 0
            if non_zero_mask.sum() > 0:
                all_emb.append(emb[non_zero_mask].mean(dim=0))
        if all_emb:
            return torch.stack(all_emb).mean(dim=0)
        return None
    
    vuln_mean = get_mean_embedding(vuln_samples)
    safe_mean = get_mean_embedding(safe_samples)
    
    if vuln_mean is not None and safe_mean is not None:
        # Cosine similarity between class centroids
        cos_sim = torch.nn.functional.cosine_similarity(
            vuln_mean.unsqueeze(0), safe_mean.unsqueeze(0)
        ).item()
        
        # L2 distance
        l2_dist = (vuln_mean - safe_mean).norm().item()
        
        print(f"   Class centroid cosine similarity: {cos_sim:.4f}")
        print(f"   Class centroid L2 distance: {l2_dist:.4f}")
        print(f"\n   Interpretation:")
        if cos_sim > 0.95:
            print(f"   ⚠️  HIGH SIMILARITY ({cos_sim:.3f}) - Embeddings may not discriminate well!")
        elif cos_sim > 0.8:
            print(f"   ⚡ MODERATE SIMILARITY ({cos_sim:.3f}) - Some discrimination possible")
        else:
            print(f"   ✓  LOW SIMILARITY ({cos_sim:.3f}) - Good embedding separation!")
    
    return {
        "vuln_mean_nodes": np.mean(vuln_nodes),
        "safe_mean_nodes": np.mean(safe_nodes),
        "centroid_cosine_sim": cos_sim if vuln_mean is not None else None,
    }


def analyze_call_nodes(samples: List[Data], one_hot_dims: int, call_node_idx: int = 2) -> Dict:
    """Specifically analyze CALL nodes since they contain vulnerability signal."""
    print("\n" + "=" * 70)
    print(f"CALL NODE ANALYSIS (index={call_node_idx})")
    print("=" * 70)
    
    if one_hot_dims == 0:
        print("Cannot analyze - no one-hot encoding detected")
        return {}
    
    vuln_call_emb = []
    safe_call_emb = []
    vuln_call_count = 0
    safe_call_count = 0
    
    for s in samples[:50]:
        node_types = s.x[:, :one_hot_dims].argmax(dim=1)
        call_mask = node_types == call_node_idx
        
        if call_mask.sum() == 0:
            continue
        
        call_emb = s.x[call_mask, one_hot_dims:]
        
        # Filter zero embeddings
        non_zero_mask = call_emb.abs().sum(dim=1) > 0
        if non_zero_mask.sum() > 0:
            non_zero_emb = call_emb[non_zero_mask]
            
            if s.y.item() == 1:
                vuln_call_emb.append(non_zero_emb)
                vuln_call_count += non_zero_mask.sum().item()
            else:
                safe_call_emb.append(non_zero_emb)
                safe_call_count += non_zero_mask.sum().item()
    
    print(f"\n1. CALL NODE STATISTICS")
    print(f"   Vulnerable samples: {vuln_call_count} CALL nodes with embeddings")
    print(f"   Safe samples: {safe_call_count} CALL nodes with embeddings")
    
    if vuln_call_emb and safe_call_emb:
        vuln_all = torch.cat(vuln_call_emb, dim=0)
        safe_all = torch.cat(safe_call_emb, dim=0)
        
        vuln_mean = vuln_all.mean(dim=0)
        safe_mean = safe_all.mean(dim=0)
        
        cos_sim = torch.nn.functional.cosine_similarity(
            vuln_mean.unsqueeze(0), safe_mean.unsqueeze(0)
        ).item()
        
        print(f"\n2. CALL NODE EMBEDDING COMPARISON")
        print(f"   Vuln CALL centroid vs Safe CALL centroid:")
        print(f"   Cosine similarity: {cos_sim:.4f}")
        
        if cos_sim > 0.95:
            print(f"   ⚠️  CALL embeddings are nearly IDENTICAL between classes!")
            print(f"   → This explains the performance ceiling!")
        elif cos_sim > 0.8:
            print(f"   ⚡ CALL embeddings have MODERATE differentiation")
        else:
            print(f"   ✓  CALL embeddings show GOOD differentiation")
    
    return {}


def analyze_edge_types(samples: List[Data]) -> Dict:
    """Analyze edge type distribution."""
    print("\n" + "=" * 70)
    print("EDGE TYPE ANALYSIS")
    print("=" * 70)
    
    edge_type_counts = Counter()
    edge_type_by_class = {0: Counter(), 1: Counter()}
    
    for s in samples[:50]:
        if hasattr(s, 'edge_type') and s.edge_type is not None:
            edge_types = s.edge_type.tolist()
        elif hasattr(s, 'edge_attr') and s.edge_attr is not None:
            if s.edge_attr.dim() == 1:
                edge_types = s.edge_attr.tolist()
            else:
                edge_types = s.edge_attr.argmax(dim=1).tolist()
        else:
            continue
        
        edge_type_counts.update(edge_types)
        edge_type_by_class[s.y.item()].update(edge_types)
    
    print(f"\nEdge Type | Count | Vuln% | Safe%")
    print("-" * 40)
    
    for etype, count in sorted(edge_type_counts.items()):
        vuln_count = edge_type_by_class[1].get(etype, 0)
        safe_count = edge_type_by_class[0].get(etype, 0)
        total = vuln_count + safe_count
        if total > 0:
            vuln_pct = 100 * vuln_count / total
            safe_pct = 100 * safe_count / total
            print(f"Type {etype:2d}   | {count:6d} | {vuln_pct:5.1f} | {safe_pct:5.1f}")
    
    return {"edge_type_counts": dict(edge_type_counts)}


def main():
    parser = argparse.ArgumentParser(description="Pipeline Diagnostics")
    parser.add_argument("--cache-dir", type=str, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--num-samples", type=int, default=100)
    parser.add_argument("--call-node-idx", type=int, default=2, 
                       help="Index of CALL node type in one-hot encoding")
    args = parser.parse_args()
    
    print("=" * 70)
    print("PIPELINE DIAGNOSTICS")
    print("=" * 70)
    print(f"Dataset: {args.dataset_name}")
    print(f"Signature: {args.cache_signature}")
    print(f"Samples: {args.num_samples}")
    
    # Load samples
    samples = load_samples(
        args.cache_dir, args.dataset_name, args.cache_signature,
        max_samples=args.num_samples
    )
    
    print(f"\nLoaded {len(samples)} samples")
    
    # Run analyses
    feature_stats = analyze_features(samples)
    one_hot_dims = feature_stats.get("one_hot_dims", 0)
    
    type_stats = analyze_by_node_type(samples, one_hot_dims)
    vuln_stats = analyze_vulnerability_signal(samples, one_hot_dims)
    call_stats = analyze_call_nodes(samples, one_hot_dims, args.call_node_idx)
    edge_stats = analyze_edge_types(samples)
    
    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY & RECOMMENDATIONS")
    print("=" * 70)
    
    zero_emb_ratio = feature_stats.get("zero_embedding_ratio", 0)
    centroid_sim = vuln_stats.get("centroid_cosine_sim")
    
    issues = []
    
    if zero_emb_ratio > 0.3:
        issues.append(f"HIGH ({zero_emb_ratio*100:.0f}%) zero embeddings - check text extraction")
    
    if centroid_sim and centroid_sim > 0.9:
        issues.append(f"HIGH class centroid similarity ({centroid_sim:.3f}) - embeddings not discriminative")
    
    if not issues:
        print("\n✓ No major issues detected")
    else:
        print("\n⚠️  ISSUES DETECTED:")
        for issue in issues:
            print(f"   - {issue}")
    
    print("\n" + "=" * 70)


if __name__ == "__main__":
    main()


"""

python diagnose_pipeline.py \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_256d_full" \
    --cache-signature "c95a4168d5a65be0" \
    --num-samples 200 \
    --call-node-idx 2



"""    