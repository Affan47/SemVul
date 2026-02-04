#!/usr/bin/env python3
"""
diagnose_cache_v2.py - Check cached data for NaN/Inf issues
Handles both .pt files and .zip cache formats

Usage:
    python diagnose_cache_v2.py \
        --cache-dir /path/to/cache \
        --dataset-name word2vec_128d_full \
        --signature 18ffa5e949d8d68c
"""

import argparse
import torch
import numpy as np
from pathlib import Path
import sys
import zipfile
import tempfile
import os


def analyze_tensor(name: str, tensor: torch.Tensor) -> dict:
    """Analyze a tensor for issues."""
    stats = {
        'name': name,
        'shape': tuple(tensor.shape),
        'dtype': str(tensor.dtype),
    }
    
    # Integer tensor
    if tensor.dtype in [torch.long, torch.int, torch.int32, torch.int64]:
        stats['type'] = 'integer'
        stats['min'] = tensor.min().item()
        stats['max'] = tensor.max().item()
        stats['unique'] = len(torch.unique(tensor))
        return stats
    
    # Float tensor analysis
    stats['type'] = 'float'
    stats['has_nan'] = torch.isnan(tensor).any().item()
    stats['has_inf'] = torch.isinf(tensor).any().item()
    stats['nan_count'] = torch.isnan(tensor).sum().item()
    stats['inf_count'] = torch.isinf(tensor).sum().item()
    
    # Mask out NaN/Inf for statistics
    valid = tensor[~torch.isnan(tensor) & ~torch.isinf(tensor)]
    if len(valid) > 0:
        stats['min'] = valid.min().item()
        stats['max'] = valid.max().item()
        stats['mean'] = valid.mean().item()
        stats['std'] = valid.std().item()
        stats['abs_max'] = valid.abs().max().item()
    else:
        stats['min'] = stats['max'] = stats['mean'] = stats['std'] = float('nan')
    
    return stats


def check_data_object(data, idx: int) -> dict:
    """Check a single PyG Data object."""
    issues = []
    stats = {}
    
    # Check node features (x)
    if hasattr(data, 'x') and data.x is not None:
        x_stats = analyze_tensor('x (node features)', data.x)
        stats['x'] = x_stats
        
        if x_stats.get('has_nan'):
            issues.append(f"NaN in node features: {x_stats['nan_count']} values")
        if x_stats.get('has_inf'):
            issues.append(f"Inf in node features: {x_stats['inf_count']} values")
        if x_stats.get('abs_max', 0) > 1000:
            issues.append(f"Large values in node features: max={x_stats['abs_max']:.2f}")
    
    # Check edge_index
    if hasattr(data, 'edge_index') and data.edge_index is not None:
        ei_stats = analyze_tensor('edge_index', data.edge_index)
        stats['edge_index'] = ei_stats
        
        num_nodes = data.x.shape[0] if hasattr(data, 'x') and data.x is not None else 0
        if ei_stats['max'] >= num_nodes:
            issues.append(f"Invalid edge index: max={ei_stats['max']} >= num_nodes={num_nodes}")
    
    # Check edge_type / edge_attr
    if hasattr(data, 'edge_type') and data.edge_type is not None:
        et_stats = analyze_tensor('edge_type', data.edge_type)
        stats['edge_type'] = et_stats
    elif hasattr(data, 'edge_attr') and data.edge_attr is not None:
        et_stats = analyze_tensor('edge_attr', data.edge_attr)
        stats['edge_attr'] = et_stats

    # Check edge text embeddings (optional)
    if hasattr(data, 'edge_text_emb') and data.edge_text_emb is not None:
        etext_stats = analyze_tensor('edge_text_emb', data.edge_text_emb)
        stats['edge_text_emb'] = etext_stats
        if etext_stats.get('has_nan'):
            issues.append(f"NaN in edge_text_emb: {etext_stats['nan_count']} values")
        if etext_stats.get('has_inf'):
            issues.append(f"Inf in edge_text_emb: {etext_stats['inf_count']} values")
        if etext_stats.get('abs_max', 0) > 1000:
            issues.append(f"Large values in edge_text_emb: max={etext_stats['abs_max']:.2f}")
    
    # Check label
    if hasattr(data, 'y') and data.y is not None:
        y_stats = analyze_tensor('y (label)', data.y)
        stats['y'] = y_stats
    
    return {'idx': idx, 'issues': issues, 'stats': stats}


def load_data_from_zip(zip_path: Path, num_samples: int = 100):
    """Load data objects from a zip file."""
    data_objects = []
    
    with zipfile.ZipFile(zip_path, 'r') as zf:
        pt_files = [f for f in zf.namelist() if f.endswith('.pt')]
        print(f"  Found {len(pt_files)} .pt files in zip")
        
        # Create temp directory
        with tempfile.TemporaryDirectory() as tmpdir:
            for i, pt_file in enumerate(pt_files[:num_samples]):
                try:
                    # Extract to temp
                    zf.extract(pt_file, tmpdir)
                    extracted_path = Path(tmpdir) / pt_file
                    
                    # Load data
                    data = torch.load(extracted_path, map_location='cpu', weights_only=False)
                    data_objects.append((pt_file, data))
                    
                except Exception as e:
                    print(f"  Error loading {pt_file}: {e}")
    
    return data_objects


def explore_cache_structure(cache_path: Path):
    """Explore and print the cache directory structure."""
    print("\n--- Cache Structure ---")
    
    for item in sorted(cache_path.iterdir()):
        if item.is_dir():
            print(f"📁 {item.name}/")
            for subitem in sorted(item.iterdir())[:10]:
                size = subitem.stat().st_size / 1024 / 1024  # MB
                print(f"   {'📁' if subitem.is_dir() else '📄'} {subitem.name} ({size:.2f} MB)")
            subcount = len(list(item.iterdir()))
            if subcount > 10:
                print(f"   ... and {subcount - 10} more items")
        else:
            size = item.stat().st_size / 1024 / 1024
            print(f"📄 {item.name} ({size:.2f} MB)")


def main():
    parser = argparse.ArgumentParser(description="Diagnose cache for NaN/Inf issues (v2)")
    parser.add_argument("--cache-dir", required=True, help="Cache directory")
    parser.add_argument("--dataset-name", required=True, help="Dataset name")
    parser.add_argument("--signature", required=True, help="Cache signature")
    parser.add_argument("--num-samples", type=int, default=100, help="Number of samples to check")
    args = parser.parse_args()
    
    cache_path = Path(args.cache_dir) / args.dataset_name / args.signature
    
    print("=" * 70)
    print("CACHE DIAGNOSTIC V2 (Supports Zip Format)")
    print("=" * 70)
    print(f"Cache path: {cache_path}")
    
    if not cache_path.exists():
        print(f"\n❌ ERROR: Cache path does not exist!")
        sys.exit(1)
    
    # Explore structure
    explore_cache_structure(cache_path)
    
    # Global tracking
    global_nan_count = 0
    global_inf_count = 0
    global_min = float('inf')
    global_max = float('-inf')
    all_means = []
    all_stds = []
    
    # Check each split
    for split in ['train', 'valid', 'test']:
        split_path = cache_path / split
        
        if not split_path.exists():
            print(f"\n[{split}] Directory not found, skipping...")
            continue
        
        print(f"\n{'=' * 70}")
        print(f"SPLIT: {split.upper()}")
        print("=" * 70)
        
        # Find data files
        pt_files = list(split_path.glob("*.pt"))
        zip_files = list(split_path.glob("*.zip"))
        
        print(f"Found {len(pt_files)} .pt files, {len(zip_files)} .zip files")
        
        data_objects = []
        
        # Load from .pt files
        if pt_files:
            for i, pt_file in enumerate(pt_files[:args.num_samples]):
                try:
                    data = torch.load(pt_file, map_location='cpu', weights_only=False)
                    data_objects.append((pt_file.name, data))
                except Exception as e:
                    print(f"  Error loading {pt_file.name}: {e}")
        
        # Load from .zip files
        if zip_files and len(data_objects) < args.num_samples:
            remaining = args.num_samples - len(data_objects)
            for zip_file in zip_files:
                print(f"\nLoading from {zip_file.name}...")
                zip_data = load_data_from_zip(zip_file, remaining)
                data_objects.extend(zip_data)
                if len(data_objects) >= args.num_samples:
                    break
        
        if not data_objects:
            print("  No data objects found!")
            continue
        
        print(f"\nAnalyzing {len(data_objects)} samples...")
        
        # Analyze
        all_issues = []
        feature_stats = []
        edge_type_max = 0
        
        for fname, data in data_objects:
            result = check_data_object(data, 0)
            
            if result['issues']:
                all_issues.append((fname, result['issues']))
            
            if 'x' in result['stats']:
                x_stats = result['stats']['x']
                feature_stats.append(x_stats)
                
                global_nan_count += x_stats.get('nan_count', 0)
                global_inf_count += x_stats.get('inf_count', 0)
                
                if 'min' in x_stats and not np.isnan(x_stats['min']):
                    global_min = min(global_min, x_stats['min'])
                if 'max' in x_stats and not np.isnan(x_stats['max']):
                    global_max = max(global_max, x_stats['max'])
                if 'mean' in x_stats and not np.isnan(x_stats['mean']):
                    all_means.append(x_stats['mean'])
                if 'std' in x_stats and not np.isnan(x_stats['std']):
                    all_stds.append(x_stats['std'])
            
            # Track edge types
            if 'edge_type' in result['stats']:
                edge_type_max = max(edge_type_max, result['stats']['edge_type'].get('max', 0))
            elif 'edge_attr' in result['stats']:
                edge_type_max = max(edge_type_max, result['stats']['edge_attr'].get('max', 0))
        
        # Print split summary
        if feature_stats:
            print(f"\n--- Node Feature Statistics ---")
            print(f"Feature shape: {feature_stats[0]['shape']}")
            
            all_mins = [s['min'] for s in feature_stats if 'min' in s and not np.isnan(s['min'])]
            all_maxs = [s['max'] for s in feature_stats if 'max' in s and not np.isnan(s['max'])]
            nan_counts = [s.get('nan_count', 0) for s in feature_stats]
            inf_counts = [s.get('inf_count', 0) for s in feature_stats]
            
            if all_mins and all_maxs:
                print(f"Value range: [{min(all_mins):.4f}, {max(all_maxs):.4f}]")
            print(f"NaN count:   {sum(nan_counts)}")
            print(f"Inf count:   {sum(inf_counts)}")
            
            if sum(nan_counts) > 0:
                print(f"\n🚨 CRITICAL: NaN values detected!")
            if sum(inf_counts) > 0:
                print(f"\n🚨 CRITICAL: Inf values detected!")
        
        print(f"\n--- Edge Type Info ---")
        print(f"Max edge type index: {edge_type_max}")
        print(f"Required --num-edge-types: {edge_type_max + 1}")
        
        if all_issues:
            print(f"\n--- Issues ({len(all_issues)} files) ---")
            for fname, issues in all_issues[:5]:
                print(f"  {fname}: {issues}")
    
    # Global Summary
    print("\n" + "=" * 70)
    print("GLOBAL SUMMARY")
    print("=" * 70)
    print(f"Total NaN values:  {global_nan_count}")
    print(f"Total Inf values:  {global_inf_count}")
    
    if global_min != float('inf') and global_max != float('-inf'):
        print(f"Global value range: [{global_min:.4f}, {global_max:.4f}]")
        if all_means:
            print(f"Mean of means:     {np.mean(all_means):.4f}")
        if all_stds:
            print(f"Mean of stds:      {np.mean(all_stds):.4f}")
    else:
        print("Could not compute value range (no valid data found)")
    
    # Diagnosis
    print("\n" + "=" * 70)
    print("DIAGNOSIS & RECOMMENDATIONS")
    print("=" * 70)
    
    if global_nan_count > 0:
        print("""
🚨 CRITICAL: NaN VALUES DETECTED
================================
Your cache contains NaN values. This WILL cause training to fail.

SOLUTION - Add NaN handling to training:
In train_fixed.py, after loading data, add:

    for data in train_data + val_data + test_data:
        if torch.isnan(data.x).any():
            data.x = torch.nan_to_num(data.x, nan=0.0)
""")
    
    elif global_inf_count > 0:
        print("""
🚨 CRITICAL: INF VALUES DETECTED
================================
SOLUTION - Clamp values:

    data.x = torch.clamp(data.x, min=-100, max=100)
""")
    
    elif global_min != float('inf'):
        if global_max > 50 or global_min < -50:
            print(f"""
⚠️  LARGE VALUE RANGE: [{global_min:.2f}, {global_max:.2f}]
===========================================
This can cause gradient explosion → NaN loss.

SOLUTION 1 - Very low learning rate:
    --lr 0.00005

SOLUTION 2 - Add normalization to train_fixed.py:
    # After loading data
    for data in train_data:
        data.x = (data.x - data.x.mean(dim=0)) / (data.x.std(dim=0) + 1e-8)
""")
        elif global_max > 10 or global_min < -10:
            print(f"""
⚠️  MODERATE VALUE RANGE: [{global_min:.2f}, {global_max:.2f}]
==============================================
Try lower learning rate: --lr 0.0001
""")
        else:
            print(f"""
✅ VALUE RANGE OK: [{global_min:.2f}, {global_max:.2f}]
=========================================
Values look reasonable. If still getting NaN:
    --lr 0.0001
    --batch-size 64
""")
    
    print(f"""
RECOMMENDED COMMAND:
====================
python -m vuln_detection.train \\
    --model-type improved_devign \\
    --embedder-type word2vec \\
    --use-structural-features \\
    --gnn-type edge_type \\
    --gnn-layers 4 \\
    --pooling-type multi_stat \\
    --num-edge-types 15 \\
    --loss-type combined \\
    --optimize-for f1_best \\
    --cache-dir "{args.cache_dir}" \\
    --dataset-name "{args.dataset_name}" \\
    --cache-signature "{args.signature}" \\
    --embedding-dim 128 \\
    --hidden-dim 128 \\
    --dropout 0.2 \\
    --epochs 150 \\
    --patience 30 \\
    --batch-size 64 \\
    --lr 0.0001
""")


if __name__ == "__main__":
    main()


"""
python diagnose_cache.py \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_128d_full" \
    --signature "18ffa5e949d8d68c" \
    --num-samples 200


"""    
