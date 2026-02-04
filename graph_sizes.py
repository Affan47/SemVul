#!/usr/bin/env python3
"""
Graph Size Analysis - Simple Version

Reads num_nodes and num_edges directly from index.csv (no zip loading needed!)

Usage:
    python graph_size_analysis_simple.py \
        --cache-dir /path/to/cache \
        --dataset-name word2vec_256d_full \
        --signature c95a4168d5a65be0
"""

import argparse
import csv
import json
from pathlib import Path
from collections import defaultdict
import numpy as np


def load_index(index_path: Path) -> list:
    """Load index.csv and return list of dicts."""
    samples = []
    with open(index_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            samples.append({
                'function_id': row.get('function_id', ''),
                'label': int(row.get('label', 0)),
                'num_nodes': int(row.get('num_nodes', 0)),
                'num_edges': int(row.get('num_edges', 0)),
            })
    return samples


def compute_stats(arr: np.ndarray) -> dict:
    """Compute statistics for an array."""
    if len(arr) == 0:
        return {}
    return {
        'count': len(arr),
        'min': int(arr.min()),
        'max': int(arr.max()),
        'mean': float(arr.mean()),
        'std': float(arr.std()),
        'median': float(np.median(arr)),
        'p25': float(np.percentile(arr, 25)),
        'p75': float(np.percentile(arr, 75)),
        'p90': float(np.percentile(arr, 90)),
        'p95': float(np.percentile(arr, 95)),
        'p99': float(np.percentile(arr, 99)),
    }


def print_comparison(vuln_arr: np.ndarray, safe_arr: np.ndarray, metric: str):
    """Print side-by-side comparison."""
    if len(vuln_arr) == 0 or len(safe_arr) == 0:
        return
    
    print(f"\n{'─' * 75}")
    print(f"  {metric.upper()} COMPARISON: Vulnerable vs Non-Vulnerable")
    print(f"{'─' * 75}")
    print(f"{'Statistic':<12} {'Vulnerable':>14} {'Non-Vuln':>14} {'Diff':>12} {'Diff %':>10}")
    print(f"{'─' * 75}")
    
    comparisons = [
        ('Count', len(vuln_arr), len(safe_arr)),
        ('Min', vuln_arr.min(), safe_arr.min()),
        ('Max', vuln_arr.max(), safe_arr.max()),
        ('Mean', vuln_arr.mean(), safe_arr.mean()),
        ('Std Dev', vuln_arr.std(), safe_arr.std()),
        ('Median', np.median(vuln_arr), np.median(safe_arr)),
        ('P25', np.percentile(vuln_arr, 25), np.percentile(safe_arr, 25)),
        ('P75', np.percentile(vuln_arr, 75), np.percentile(safe_arr, 75)),
        ('P90', np.percentile(vuln_arr, 90), np.percentile(safe_arr, 90)),
        ('P95', np.percentile(vuln_arr, 95), np.percentile(safe_arr, 95)),
        ('P99', np.percentile(vuln_arr, 99), np.percentile(safe_arr, 99)),
    ]
    
    for name, vuln_val, safe_val in comparisons:
        diff = vuln_val - safe_val
        diff_pct = 100 * diff / safe_val if safe_val != 0 else 0
        print(f"{name:<12} {vuln_val:>14.1f} {safe_val:>14.1f} {diff:>+12.1f} {diff_pct:>+9.1f}%")


def print_threshold_analysis(all_nodes: np.ndarray, vuln_nodes: np.ndarray, safe_nodes: np.ndarray):
    """Analyze retention at different node thresholds."""
    print(f"\n{'═' * 85}")
    print("  NODE THRESHOLD ANALYSIS - What % of samples would be kept?")
    print(f"{'═' * 85}")
    print(f"{'Threshold':<10} {'Total':>18} {'Vulnerable':>18} {'Non-Vuln':>18} {'New Vuln%':>12}")
    print(f"{'─' * 85}")
    
    original_vuln_ratio = len(vuln_nodes) / len(all_nodes) if len(all_nodes) > 0 else 0
    
    thresholds = [100, 200, 300, 400, 500, 600, 750, 1000, 1500, 2000, 3000, 5000]
    
    for thresh in thresholds:
        total_kept = (all_nodes <= thresh).sum()
        vuln_kept = (vuln_nodes <= thresh).sum()
        safe_kept = (safe_nodes <= thresh).sum()
        
        total_pct = 100 * total_kept / len(all_nodes) if len(all_nodes) > 0 else 0
        vuln_pct = 100 * vuln_kept / len(vuln_nodes) if len(vuln_nodes) > 0 else 0
        safe_pct = 100 * safe_kept / len(safe_nodes) if len(safe_nodes) > 0 else 0
        
        # New vulnerable ratio after filtering
        new_vuln_ratio = vuln_kept / total_kept if total_kept > 0 else 0
        
        print(f"{thresh:<10} {total_kept:>8} ({total_pct:>5.1f}%) {vuln_kept:>8} ({vuln_pct:>5.1f}%) {safe_kept:>8} ({safe_pct:>5.1f}%) {100*new_vuln_ratio:>10.1f}%")
    
    print(f"{'─' * 85}")
    print(f"Original vulnerable ratio: {100*original_vuln_ratio:.2f}%")
    print(f"(If 'New Vuln%' differs significantly, truncation causes class imbalance)")


def print_edge_threshold_analysis(all_edges: np.ndarray, vuln_edges: np.ndarray, safe_edges: np.ndarray):
    """Analyze retention at different edge thresholds."""
    print(f"\n{'═' * 85}")
    print("  EDGE THRESHOLD ANALYSIS - What % of samples would be kept?")
    print(f"{'═' * 85}")
    print(f"{'Threshold':<10} {'Total':>18} {'Vulnerable':>18} {'Non-Vuln':>18} {'New Vuln%':>12}")
    print(f"{'─' * 85}")
    
    original_vuln_ratio = len(vuln_edges) / len(all_edges) if len(all_edges) > 0 else 0
    
    thresholds = [500, 1000, 2000, 5000, 10000, 20000, 50000, 100000]
    
    for thresh in thresholds:
        total_kept = (all_edges <= thresh).sum()
        vuln_kept = (vuln_edges <= thresh).sum()
        safe_kept = (safe_edges <= thresh).sum()
        
        total_pct = 100 * total_kept / len(all_edges) if len(all_edges) > 0 else 0
        vuln_pct = 100 * vuln_kept / len(vuln_edges) if len(vuln_edges) > 0 else 0
        safe_pct = 100 * safe_kept / len(safe_edges) if len(safe_edges) > 0 else 0
        
        new_vuln_ratio = vuln_kept / total_kept if total_kept > 0 else 0
        
        print(f"{thresh:<10} {total_kept:>8} ({total_pct:>5.1f}%) {vuln_kept:>8} ({vuln_pct:>5.1f}%) {safe_kept:>8} ({safe_pct:>5.1f}%) {100*new_vuln_ratio:>10.1f}%")
    
    print(f"{'─' * 85}")


def main():
    parser = argparse.ArgumentParser(description="Analyze graph sizes from index.csv")
    parser.add_argument("--cache-dir", required=True, help="Base cache directory")
    parser.add_argument("--dataset-name", required=True, help="Dataset name")
    parser.add_argument("--signature", required=True, help="Cache signature")
    parser.add_argument("--output", default=None, help="Save JSON results to file")
    args = parser.parse_args()
    
    cache_path = Path(args.cache_dir) / args.dataset_name / args.signature
    
    if not cache_path.exists():
        print(f"Error: Cache path not found: {cache_path}")
        return
    
    print("=" * 85)
    print("GRAPH SIZE ANALYSIS")
    print("=" * 85)
    print(f"Dataset: {args.dataset_name}")
    print(f"Signature: {args.signature}")
    print(f"Path: {cache_path}")
    
    # Load all splits
    all_samples = []
    
    for split in ['train', 'valid', 'test']:
        index_path = cache_path / split / "index.csv"
        if index_path.exists():
            samples = load_index(index_path)
            print(f"\n{split.upper()}: {len(samples)} samples")
            all_samples.extend(samples)
        else:
            print(f"\n{split.upper()}: Not found")
    
    if not all_samples:
        print("Error: No samples found!")
        return
    
    # Separate by label
    vuln_samples = [s for s in all_samples if s['label'] == 1]
    safe_samples = [s for s in all_samples if s['label'] == 0]
    
    # Extract arrays
    all_nodes = np.array([s['num_nodes'] for s in all_samples])
    all_edges = np.array([s['num_edges'] for s in all_samples])
    
    vuln_nodes = np.array([s['num_nodes'] for s in vuln_samples])
    vuln_edges = np.array([s['num_edges'] for s in vuln_samples])
    
    safe_nodes = np.array([s['num_nodes'] for s in safe_samples])
    safe_edges = np.array([s['num_edges'] for s in safe_samples])
    
    # Print summary
    print(f"\n{'═' * 85}")
    print("  OVERALL SUMMARY")
    print(f"{'═' * 85}")
    print(f"Total samples:     {len(all_samples):,}")
    print(f"  Vulnerable:      {len(vuln_samples):,} ({100*len(vuln_samples)/len(all_samples):.2f}%)")
    print(f"  Non-vulnerable:  {len(safe_samples):,} ({100*len(safe_samples)/len(all_samples):.2f}%)")
    
    # Node statistics
    print_comparison(vuln_nodes, safe_nodes, "Nodes")
    
    # Edge statistics
    print_comparison(vuln_edges, safe_edges, "Edges")
    
    # Edge density
    print(f"\n{'─' * 75}")
    print(f"  EDGE DENSITY (edges per node)")
    print(f"{'─' * 75}")
    
    vuln_density = vuln_edges / np.maximum(vuln_nodes, 1)
    safe_density = safe_edges / np.maximum(safe_nodes, 1)
    all_density = all_edges / np.maximum(all_nodes, 1)
    
    print(f"{'Category':<20} {'Mean':>12} {'Median':>12} {'P95':>12} {'Max':>12}")
    print(f"{'─' * 75}")
    print(f"{'All':<20} {all_density.mean():>12.2f} {np.median(all_density):>12.2f} {np.percentile(all_density, 95):>12.2f} {all_density.max():>12.2f}")
    print(f"{'Vulnerable':<20} {vuln_density.mean():>12.2f} {np.median(vuln_density):>12.2f} {np.percentile(vuln_density, 95):>12.2f} {vuln_density.max():>12.2f}")
    print(f"{'Non-vulnerable':<20} {safe_density.mean():>12.2f} {np.median(safe_density):>12.2f} {np.percentile(safe_density, 95):>12.2f} {safe_density.max():>12.2f}")
    
    # Threshold analysis
    print_threshold_analysis(all_nodes, vuln_nodes, safe_nodes)
    print_edge_threshold_analysis(all_edges, vuln_edges, safe_edges)
    
    # Recommendations
    print(f"\n{'═' * 85}")
    print("  RECOMMENDATIONS")
    print(f"{'═' * 85}")
    
    p90_nodes = np.percentile(all_nodes, 90)
    p95_nodes = np.percentile(all_nodes, 95)
    p99_nodes = np.percentile(all_nodes, 99)
    
    vuln_mean = vuln_nodes.mean()
    safe_mean = safe_nodes.mean()
    
    print(f"\nNode percentiles (all samples):")
    print(f"  P90: {p90_nodes:.0f} nodes")
    print(f"  P95: {p95_nodes:.0f} nodes")
    print(f"  P99: {p99_nodes:.0f} nodes")
    print(f"  Max: {all_nodes.max()} nodes")
    
    # Check for bias
    if vuln_mean > safe_mean * 1.15:
        bias = 100 * (vuln_mean / safe_mean - 1)
        print(f"\n⚠️  WARNING: Vulnerable samples are {bias:.1f}% LARGER on average!")
        print(f"   Mean nodes - Vuln: {vuln_mean:.1f}, Non-vuln: {safe_mean:.1f}")
        print(f"   Truncation may disproportionately affect vulnerable samples.")
        print(f"   Consider: higher threshold OR importance-based truncation.")
    elif safe_mean > vuln_mean * 1.15:
        bias = 100 * (safe_mean / vuln_mean - 1)
        print(f"\n⚠️  WARNING: Non-vulnerable samples are {bias:.1f}% LARGER on average!")
        print(f"   Mean nodes - Vuln: {vuln_mean:.1f}, Non-vuln: {safe_mean:.1f}")
        print(f"   Truncation will remove more non-vulnerable samples.")
    else:
        print(f"\n✅ Node counts are balanced between classes (within 15%).")
        print(f"   Mean nodes - Vuln: {vuln_mean:.1f}, Non-vuln: {safe_mean:.1f}")
    
    # Suggest threshold
    # Find threshold that keeps ~95% while maintaining class balance
    for thresh in [500, 600, 750, 1000, 1500, 2000]:
        total_pct = 100 * (all_nodes <= thresh).sum() / len(all_nodes)
        vuln_pct = 100 * (vuln_nodes <= thresh).sum() / len(vuln_nodes)
        safe_pct = 100 * (safe_nodes <= thresh).sum() / len(safe_nodes)
        
        if total_pct >= 95 and abs(vuln_pct - safe_pct) < 5:
            suggested = thresh
            break
    else:
        suggested = int(np.ceil(p95_nodes / 100) * 100)
    
    print(f"\n{'─' * 85}")
    print(f"📊 SUGGESTED NODE LIMIT: {suggested}")
    
    # Calculate impact
    kept_total = (all_nodes <= suggested).sum()
    kept_vuln = (vuln_nodes <= suggested).sum()
    kept_safe = (safe_nodes <= suggested).sum()
    
    print(f"   Would keep: {kept_total:,} / {len(all_samples):,} samples ({100*kept_total/len(all_samples):.1f}%)")
    print(f"   Vulnerable: {kept_vuln:,} / {len(vuln_samples):,} ({100*kept_vuln/len(vuln_samples):.1f}%)")
    print(f"   Non-vuln:   {kept_safe:,} / {len(safe_samples):,} ({100*kept_safe/len(safe_samples):.1f}%)")
    
    # Devign comparison
    devign_thresh = 500
    kept_devign = (all_nodes <= devign_thresh).sum()
    print(f"\n   Original Devign (500 nodes): would keep {kept_devign:,} ({100*kept_devign/len(all_samples):.1f}%)")
    
    # Save results
    if args.output:
        results = {
            'dataset': args.dataset_name,
            'signature': args.signature,
            'total_samples': len(all_samples),
            'vulnerable_samples': len(vuln_samples),
            'safe_samples': len(safe_samples),
            'vulnerable_ratio': len(vuln_samples) / len(all_samples),
            'nodes': {
                'all': compute_stats(all_nodes),
                'vulnerable': compute_stats(vuln_nodes),
                'safe': compute_stats(safe_nodes),
            },
            'edges': {
                'all': compute_stats(all_edges),
                'vulnerable': compute_stats(vuln_edges),
                'safe': compute_stats(safe_edges),
            },
            'edge_density': {
                'all_mean': float(all_density.mean()),
                'vuln_mean': float(vuln_density.mean()),
                'safe_mean': float(safe_density.mean()),
            },
            'suggested_node_limit': suggested,
            'devign_500_retention': float(100 * kept_devign / len(all_samples)),
        }
        
        with open(args.output, 'w') as f:
            json.dump(results, f, indent=2)
        print(f"\n📁 Results saved to: {args.output}")
    
    print(f"\n{'═' * 85}")


if __name__ == "__main__":
    main()
"""
python graph_sizes.py \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_256d_full" \
    --signature "c95a4168d5a65be0" \
    --output graph_stats.json
```

### What It Analyzes

| Analysis | Description |
|----------|-------------|
| **Node count distribution** | Min, max, mean, median, percentiles (P25, P75, P90, P95, P99) |
| **Edge count distribution** | Same statistics for edges |
| **Vulnerable vs Non-vulnerable** | Side-by-side comparison to detect structural differences |
| **Threshold impact** | Shows retention % at thresholds (100, 200, 300, 500, 1000, etc.) |
| **Class imbalance check** | Warns if truncation would disproportionately affect one class |
| **Edge density** | Edges per node (indicates graph complexity) |

### Sample Output
```
══════════════════════════════════════════════════════════════════════
  NODES COMPARISON
──────────────────────────────────────────────────────────────────────
Statistic            Vulnerable   Non-Vulnerable      Difference
──────────────────────────────────────────────────────────────────────
Count                   12000            15000        -3000 (-20.0%)
Mean                    342.5            298.2        +44.3 (+14.9%)
Median                  285.0            251.0        +34.0 (+13.5%)
P95                     892.0            745.0       +147.0 (+19.7%)
...

══════════════════════════════════════════════════════════════════════
  NODE THRESHOLD ANALYSIS
──────────────────────────────────────────────────════════════════════
Threshold     Total Kept    Vuln Kept    Safe Kept     Vuln %
──────────────────────────────────────────────────────────────────────
500           24500 (90.7%)  10200 (85.0%)  14300 (95.3%)   41.6%
1000          26800 (99.3%)  11900 (99.2%)  14900 (99.3%)   44.4%
...

📊 SUGGESTED NODE LIMIT: 750
   This would keep ~95% of samples intact.

"""    