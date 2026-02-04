#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_data_integrity.py - Verify data pipeline correctness

Checks:
1. Are labels in cached data consistent with manifest?
2. Do different graphs actually have different features?
3. Is there ANY signal in the data?
4. Sample verification - print actual samples to inspect
"""

import argparse
import json
import sys
import random
import io
import zipfile
import csv
from pathlib import Path
from collections import Counter, defaultdict

import numpy as np
import torch
import torch.nn.functional as F
from torch_geometric.data import Data

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_manifest(manifest_path):
    """Load manifest CSV and return dict of {key: label}."""
    manifest = {}
    with open(manifest_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            # Try different column names
            key = row.get('key') or row.get('function_id') or row.get('fid') or row.get('id') or row.get('name')
            label = row.get('label') or row.get('target') or row.get('vulnerable') or row.get('y')
            
            if key and label is not None:
                # Handle different label formats
                if isinstance(label, str):
                    label = label.strip().lower()
                    if label in ['1', 'true', 'yes', 'vulnerable']:
                        label = 1
                    elif label in ['0', 'false', 'no', 'safe']:
                        label = 0
                    else:
                        try:
                            label = int(float(label))
                        except:
                            continue
                else:
                    label = int(label)
                
                # Normalize key (remove .c extension if present) to match cache keys
                key = key.replace('.c', '')
                manifest[key] = int(label)
    
    return manifest


def load_cached_data(cache_dir, dataset_name, cache_sig, split, max_samples=None):
    """Load cached PyG data with filenames, handling multiple path structures."""
    cache_dir = Path(cache_dir)
    
    # 1. New V6 Structure: dataset/signature/split/cache_split.zip
    path_v6 = cache_dir / dataset_name / cache_sig / split / f"cache_{split}.zip"
    
    # 2. Original Structure: dataset/split/signature/cache_split.zip
    path_orig = cache_dir / dataset_name / split / cache_sig / f"cache_{split}.zip"
    
    # 3. Legacy Sliced: dataset/split/sig[:16]/cache_split.zip
    path_sliced = cache_dir / dataset_name / split / cache_sig[:16] / f"cache_{split}.zip"

    if path_v6.exists():
        zip_path = path_v6
    elif path_orig.exists():
        zip_path = path_orig
    elif path_sliced.exists():
        zip_path = path_sliced
    else:
        print(f"  ❌ Cache file not found!")
        print(f"     Checked 1: {path_v6}")
        print(f"     Checked 2: {path_orig}")
        return []

    print(f"  Found cache: {zip_path}")
    
    samples = []
    with zipfile.ZipFile(zip_path, 'r') as zf:
        pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
        
        if max_samples:
            random.shuffle(pt_files)
            pt_files = pt_files[:max_samples]
        
        for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
            try:
                with zf.open(pt_name) as f:
                    data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                    
                    # SAFETY: Replace NaN/Inf in features immediately
                    if hasattr(data, 'x') and data.x is not None:
                        if torch.isnan(data.x).any() or torch.isinf(data.x).any():
                            data.x = torch.where(
                                torch.isnan(data.x) | torch.isinf(data.x), 
                                torch.zeros_like(data.x), 
                                data.x
                            )
                    
                    if hasattr(data, 'y') and data.y is not None:
                        # Extract key from filename and normalize
                        key = pt_name.replace('.pt', '').replace('/', '_')
                        samples.append((key, data))
            except Exception as e:
                # print(f"  Error loading {pt_name}: {e}")
                continue
    
    return samples


def check_label_distribution(samples):
    """Check label distribution in cached data."""
    print("\n" + "=" * 60)
    print("LABEL DISTRIBUTION IN CACHED DATA")
    print("=" * 60)
    
    labels = [s[1].y.item() if s[1].y.numel() == 1 else s[1].y[0].item() for s in samples]
    counter = Counter(labels)
    
    print(f"Total samples: {len(samples)}")
    for label, count in sorted(counter.items()):
        print(f"  Label {label}: {count} ({count/len(samples)*100:.1f}%)")
    
    # Check for unusual labels
    unusual = [l for l in labels if l not in [0, 1]]
    if unusual:
        print(f"  ⚠️ UNUSUAL LABELS FOUND: {set(unusual)}")
    
    return labels


def check_feature_uniqueness(samples, num_check=100):
    """Check if different graphs have different features."""
    print("\n" + "=" * 60)
    print("FEATURE UNIQUENESS CHECK")
    print("=" * 60)
    
    # Get graph-level representations (mean of node features)
    graph_means = []
    valid_samples = 0
    
    for key, data in samples[:num_check]:
        if not hasattr(data, 'x') or data.x is None:
            continue
        x = data.x.float()
        # Skip if all zeros
        if (x == 0).all():
            continue
            
        graph_mean = x.mean(dim=0)  # [feat_dim]
        graph_means.append(graph_mean)
        valid_samples += 1
    
    if not graph_means:
        print("  ❌ No valid features found (all missing or zero)!")
        return
        
    graph_means = torch.stack(graph_means)  # [num_graphs, feat_dim]
    
    # Check pairwise similarity
    # Normalize
    graph_means_norm = F.normalize(graph_means, dim=1)
    similarity_matrix = torch.mm(graph_means_norm, graph_means_norm.t())
    
    # Get upper triangle (excluding diagonal)
    mask = torch.triu(torch.ones_like(similarity_matrix), diagonal=1).bool()
    similarities = similarity_matrix[mask]
    
    print(f"Checked {valid_samples} non-zero graphs")
    print(f"Mean cosine similarity: {similarities.mean():.4f}")
    print(f"Std cosine similarity: {similarities.std():.4f}")
    print(f"Min similarity: {similarities.min():.4f}")
    print(f"Max similarity: {similarities.max():.4f}")
    
    # Count highly similar pairs
    high_sim_threshold = 0.99
    high_sim_count = (similarities > high_sim_threshold).sum().item()
    total_pairs = len(similarities)
    
    if high_sim_count > total_pairs * 0.5:
        print(f"  🚨 CRITICAL: {high_sim_count}/{total_pairs} pairs are nearly IDENTICAL!")
        print(f"     Your embeddings are collapsed. Check normalization or Word2Vec training.")
    elif high_sim_count > total_pairs * 0.1:
        print(f"  ⚠️ WARNING: {high_sim_count}/{total_pairs} pairs have very high similarity.")
    else:
        print(f"  ✅ Features look distinct (only {high_sim_count} high sim pairs)")
    
    return similarities


def check_label_feature_correlation(samples, num_check=500):
    """Check if there's ANY correlation between features and labels."""
    print("\n" + "=" * 60)
    print("FEATURE-LABEL CORRELATION CHECK")
    print("=" * 60)
    
    safe_means = []
    vuln_means = []
    
    for key, data in samples[:num_check]:
        if not hasattr(data, 'x') or data.x is None: continue
        
        x = data.x.float()
        label = data.y.item() if data.y.numel() == 1 else data.y[0].item()
        graph_mean = x.mean(dim=0)
        
        if label == 0:
            safe_means.append(graph_mean)
        else:
            vuln_means.append(graph_mean)
    
    if not safe_means or not vuln_means:
        print("  ❌ Not enough samples of both classes to compare!")
        return
    
    safe_means = torch.stack(safe_means)
    vuln_means = torch.stack(vuln_means)
    
    # Overall statistics
    safe_overall = safe_means.mean(dim=0)
    vuln_overall = vuln_means.mean(dim=0)
    
    # Difference between classes
    diff = (vuln_overall - safe_overall).abs()
    
    print(f"Safe samples: {len(safe_means)}, Vuln samples: {len(vuln_means)}")
    
    # Check per-dimension differences
    significant_dims = (diff > 0.01).sum().item()
    print(f"Dimensions with >0.01 mean difference: {significant_dims}/{len(diff)}")
    
    # Top differing dimensions
    top_diff_dims = diff.topk(min(10, len(diff)))
    print(f"\nTop 5 discriminative dimensions:")
    for idx, val in zip(top_diff_dims.indices.tolist()[:5], top_diff_dims.values.tolist()[:5]):
        print(f"  Dim {idx}: diff={val:.4f}")
    
    # Simple linear separability test
    from sklearn.linear_model import LogisticRegression
    from sklearn.metrics import roc_auc_score
    
    X = torch.cat([safe_means, vuln_means], dim=0).numpy()
    y = np.array([0] * len(safe_means) + [1] * len(vuln_means))
    
    # Shuffle
    perm = np.random.permutation(len(y))
    X, y = X[perm], y[perm]
    
    # Train/test split
    split = int(0.8 * len(y))
    if split < 10:
        print("  Not enough data for Logistic Regression test")
        return

    X_train, X_test = X[:split], X[split:]
    y_train, y_test = y[:split], y[split:]
    
    try:
        clf = LogisticRegression(max_iter=1000, random_state=42)
        clf.fit(X_train, y_train)
        probs = clf.predict_proba(X_test)[:, 1]
        auc = roc_auc_score(y_test, probs)
        
        print(f"\nLogistic Regression on Mean Features:")
        print(f"  Test AUC: {auc:.4f}")
        
        if auc > 0.55:
            print(f"  ✅ Signal detected! (AUC > 0.55)")
        else:
            print(f"  ❌ NO SIGNAL detected in mean features (AUC ~0.50).")
            print(f"     The embeddings might be irrelevant to the label.")
    except Exception as e:
        print(f"  Error in LogisticRegression: {e}")


def inspect_samples(samples, num_inspect=3):
    """Print details of a few samples for manual inspection."""
    print("\n" + "=" * 60)
    print("SAMPLE INSPECTION")
    print("=" * 60)
    
    # Get some safe and some vulnerable
    safe_samples = [(k, d) for k, d in samples if (d.y.item() if d.y.numel() == 1 else d.y[0].item()) == 0]
    vuln_samples = [(k, d) for k, d in samples if (d.y.item() if d.y.numel() == 1 else d.y[0].item()) == 1]
    
    def print_sample(name, k, d):
        x = d.x
        print(f"\n--- {name} ---")
        print(f"Key: {k}")
        print(f"  Nodes: {x.size(0)}, Features: {x.size(1)}")
        print(f"  Edges: {d.edge_index.size(1)}")
        print(f"  Feature stats: mean={x.float().mean():.4f}, std={x.float().std():.4f}")
        # Check for zeros
        zero_rows = (x.abs().sum(dim=1) == 0).sum().item()
        print(f"  Nodes with zero features: {zero_rows}/{x.size(0)}")

    for i in range(min(num_inspect, len(safe_samples))):
        print_sample("SAFE", safe_samples[i][0], safe_samples[i][1])
        
    for i in range(min(num_inspect, len(vuln_samples))):
        print_sample("VULN", vuln_samples[i][0], vuln_samples[i][1])


def check_manifest_alignment(samples, manifest_path, num_check=100):
    """Check if manifest labels match cached data labels."""
    print("\n" + "=" * 60)
    print("MANIFEST ALIGNMENT CHECK")
    print("=" * 60)
    
    if not manifest_path or not Path(manifest_path).exists():
        print("  ⚠️ No manifest path provided or file not found")
        return
    
    manifest = load_manifest(manifest_path)
    print(f"Loaded {len(manifest)} entries from manifest")
    
    # Show manifest label distribution
    manifest_labels = list(manifest.values())
    print(f"Manifest labels: {Counter(manifest_labels)}")
    
    # Try to match cached data keys to manifest
    matches = 0
    mismatches = 0
    not_found = 0
    
    for key, data in samples[:num_check]:
        cached_label = data.y.item() if data.y.numel() == 1 else data.y[0].item()
        
        # Try different key formats
        manifest_label = None
        
        # 1. Direct match
        if key in manifest:
            manifest_label = manifest[key]
        else:
            # 2. Try removing/adding .c
            key_no_ext = key.replace('.c', '')
            if key_no_ext in manifest:
                manifest_label = manifest[key_no_ext]
            else:
                # 3. Try parsing function ID from key (e.g. valid_func_0001)
                import re
                match = re.search(r'(train|valid|test)_func_\d+', key)
                if match and match.group(0) in manifest:
                    manifest_label = manifest[match.group(0)]

        if manifest_label is not None:
            if manifest_label == cached_label:
                matches += 1
            else:
                mismatches += 1
                if mismatches <= 5:
                    print(f"  MISMATCH: {key} - cached={cached_label}, manifest={manifest_label}")
        else:
            not_found += 1
    
    print(f"\nChecked {num_check} samples:")
    print(f"  Matches: {matches}")
    print(f"  Mismatches: {mismatches}")
    print(f"  Not found in manifest: {not_found}")
    
    if mismatches > 0:
        print(f"  🚨 LABEL MISMATCH DETECTED!")
    elif not_found > num_check * 0.5:
        print(f"  ⚠️ Many keys not found - manifest format may differ from cache keys")


def check_graph_structure(samples, num_check=100):
    """Check graph structure integrity."""
    print("\n" + "=" * 60)
    print("GRAPH STRUCTURE CHECK")
    print("=" * 60)
    
    issues = []
    
    for key, data in samples[:num_check]:
        num_nodes = data.x.size(0)
        edge_index = data.edge_index
        
        # Check edge indices are valid
        if edge_index.numel() > 0:
            max_idx = edge_index.max().item()
            min_idx = edge_index.min().item()
            
            if max_idx >= num_nodes:
                issues.append(f"{key}: edge index {max_idx} >= num_nodes {num_nodes}")
            if min_idx < 0:
                issues.append(f"{key}: negative edge index {min_idx}")
        
        # Check for self-loops
        if edge_index.size(1) > 0:
            self_loops = (edge_index[0] == edge_index[1]).sum().item()
            if self_loops > num_nodes * 0.5:
                issues.append(f"{key}: many self-loops ({self_loops}/{edge_index.size(1)})")
    
    if issues:
        print(f"Found {len(issues)} issues:")
        for issue in issues[:10]:
            print(f"  - {issue}")
    else:
        print(f"  ✅ All {num_check} graphs have valid structure")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--manifest", type=Path, default=None,
                        help="Path to manifest CSV for alignment check")
    parser.add_argument("--max-samples", type=int, default=1000)
    parser.add_argument("--split", type=str, default="train")
    args = parser.parse_args()
    
    print("=" * 60)
    print("DATA INTEGRITY DIAGNOSTIC")
    print("=" * 60)
    
    # Load cached data
    samples = load_cached_data(
        args.cache_dir, args.dataset_name, args.cache_signature,
        args.split, args.max_samples
    )
    
    if not samples:
        print("❌ No samples loaded!")
        sys.exit(1)
    
    print(f"\nLoaded {len(samples)} samples")
    
    # Run checks
    check_label_distribution(samples)
    check_feature_uniqueness(samples)
    check_label_feature_correlation(samples)
    check_graph_structure(samples)
    inspect_samples(samples)
    
    if args.manifest:
        check_manifest_alignment(samples, args.manifest)
    
    # Final summary
    print("\n" + "=" * 60)
    print("SUMMARY")
    print("=" * 60)
    print("""
Key questions to investigate:
1. Are the labels correctly aligned with the source code?
2. Does the vulnerability ACTUALLY exist in the code?
3. Is the CPG capturing the vulnerability pattern?
4. Are different functions producing different embeddings?

If LogisticRegression AUC < 0.55 on mean features, the problem is:
- Labels are wrong/misaligned, OR
- GraphCodeBERT embeddings don't capture vulnerability, OR
- Mean pooling destroys the signal

Next steps:
- Manually inspect 10 samples to verify labels
- Check if vulnerability is visible in the source code
- Try a simpler baseline: text classification on raw code
""")


if __name__ == "__main__":
    main()