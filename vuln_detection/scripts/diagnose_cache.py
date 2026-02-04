#!/usr/bin/env python3
"""
diagnose_cache.py - Check cached .pt files for NaN/Inf values

Usage:
    python diagnose_cache.py --cache-dir /path/to/cache/dataset/split/signature
"""

import argparse
import sys
from pathlib import Path
import torch
import numpy as np

def check_tensor(name: str, tensor: torch.Tensor) -> dict:
    """Check a tensor for issues."""
    stats = {
        "name": name,
        "shape": tuple(tensor.shape),
        "dtype": str(tensor.dtype),
        "has_nan": bool(torch.isnan(tensor).any()),
        "has_inf": bool(torch.isinf(tensor).any()),
        "has_extreme": False,  # Values outside [-100, 100]
        "num_nan": int(torch.isnan(tensor).sum()),
        "num_inf": int(torch.isinf(tensor).sum()),
        "num_extreme": 0,
    }
    
    # Get numeric stats (only for float tensors)
    if tensor.dtype in [torch.float16, torch.float32, torch.float64]:
        finite_mask = torch.isfinite(tensor)
        if finite_mask.any():
            finite_vals = tensor[finite_mask]
            stats["min"] = float(finite_vals.min())
            stats["max"] = float(finite_vals.max())
            stats["mean"] = float(finite_vals.mean())
            stats["std"] = float(finite_vals.std())
            stats["num_zeros"] = int((tensor == 0).sum())
            stats["pct_zeros"] = float((tensor == 0).sum() / tensor.numel() * 100)
            
            # Check for extreme values (outside reasonable range)
            EXTREME_THRESHOLD = 100.0
            extreme_mask = (finite_vals.abs() > EXTREME_THRESHOLD)
            stats["num_extreme"] = int(extreme_mask.sum())
            stats["has_extreme"] = stats["num_extreme"] > 0
    
    return stats

def diagnose_pt_file(pt_path: Path) -> dict:
    """Diagnose a single .pt file."""
    try:
        data = torch.load(pt_path, map_location="cpu", weights_only=False)
    except Exception as e:
        return {"error": str(e), "path": str(pt_path)}
    
    result = {"path": str(pt_path.name)}
    
    # Check x (node features)
    if hasattr(data, "x") and data.x is not None:
        result["x"] = check_tensor("x", data.x)
    
    # Check y (labels)
    if hasattr(data, "y") and data.y is not None:
        result["y"] = check_tensor("y", data.y)
    
    # Check edge_index
    if hasattr(data, "edge_index") and data.edge_index is not None:
        result["edge_index"] = {
            "shape": tuple(data.edge_index.shape),
            "num_edges": data.edge_index.shape[1] if len(data.edge_index.shape) > 1 else 0,
        }
    
    return result

def main():
    parser = argparse.ArgumentParser(description="Diagnose cached .pt files")
    parser.add_argument("--cache-dir", required=True, help="Path to cache directory with .pt files")
    parser.add_argument("--max-files", type=int, default=100, help="Max files to check")
    parser.add_argument("--verbose", action="store_true", help="Print all file stats")
    args = parser.parse_args()
    
    cache_dir = Path(args.cache_dir)
    
    # Find .pt files
    pt_files = list(cache_dir.rglob("*.pt"))
    if not pt_files:
        print(f"ERROR: No .pt files found in {cache_dir}")
        sys.exit(1)
    
    print(f"Found {len(pt_files)} .pt files")
    print(f"Checking first {min(args.max_files, len(pt_files))} files...\n")
    
    # Statistics
    total_files = 0
    files_with_nan = 0
    files_with_inf = 0
    files_with_extreme = 0  # NEW: track extreme values
    files_with_all_zeros = 0
    total_nan_count = 0
    total_inf_count = 0
    total_extreme_count = 0  # NEW
    
    x_stats = {"mins": [], "maxs": [], "means": [], "stds": [], "pct_zeros": []}
    y_values = []
    
    for pt_path in pt_files[:args.max_files]:
        total_files += 1
        result = diagnose_pt_file(pt_path)
        
        if "error" in result:
            print(f"ERROR loading {pt_path}: {result['error']}")
            continue
        
        if "x" in result:
            x = result["x"]
            if x.get("has_nan"):
                files_with_nan += 1
                total_nan_count += x["num_nan"]
                print(f"⚠️  NaN in {pt_path.name}: {x['num_nan']} NaN values in x")
            
            if x.get("has_inf"):
                files_with_inf += 1
                total_inf_count += x["num_inf"]
                print(f"⚠️  Inf in {pt_path.name}: {x['num_inf']} Inf values in x")
            
            # NEW: Check for extreme values
            if x.get("has_extreme"):
                files_with_extreme += 1
                total_extreme_count += x["num_extreme"]
                print(f"⚠️  EXTREME in {pt_path.name}: {x['num_extreme']} values |x| > 100 "
                      f"(min={x.get('min', 0):.2e}, max={x.get('max', 0):.2e})")
            
            if x.get("pct_zeros", 0) > 90:
                files_with_all_zeros += 1
                if args.verbose:
                    print(f"⚠️  High zeros in {pt_path.name}: {x['pct_zeros']:.1f}% zeros")
            
            # Collect stats
            if "min" in x:
                x_stats["mins"].append(x["min"])
                x_stats["maxs"].append(x["max"])
                x_stats["means"].append(x["mean"])
                x_stats["stds"].append(x["std"])
                x_stats["pct_zeros"].append(x.get("pct_zeros", 0))
        
        if "y" in result:
            y = result["y"]
            if y.get("has_nan"):
                print(f"⚠️  NaN in labels {pt_path.name}")
        
        if args.verbose:
            print(f"  {pt_path.name}: x={result.get('x', {}).get('shape')}, "
                  f"y={result.get('y', {}).get('shape')}")
    
    # Print summary
    print("\n" + "=" * 60)
    print("DIAGNOSIS SUMMARY")
    print("=" * 60)
    print(f"Files checked: {total_files}")
    print(f"Files with NaN: {files_with_nan} ({100*files_with_nan/total_files:.1f}%)")
    print(f"Files with Inf: {files_with_inf} ({100*files_with_inf/total_files:.1f}%)")
    print(f"Files with EXTREME values (|x|>100): {files_with_extreme} ({100*files_with_extreme/total_files:.1f}%)")
    print(f"Files with >90% zeros: {files_with_all_zeros} ({100*files_with_all_zeros/total_files:.1f}%)")
    print(f"Total NaN values: {total_nan_count}")
    print(f"Total Inf values: {total_inf_count}")
    print(f"Total EXTREME values: {total_extreme_count}")
    
    if x_stats["mins"]:
        # Filter out inf/-inf for display
        finite_mins = [v for v in x_stats["mins"] if np.isfinite(v)]
        finite_maxs = [v for v in x_stats["maxs"] if np.isfinite(v)]
        finite_means = [v for v in x_stats["means"] if np.isfinite(v)]
        finite_stds = [v for v in x_stats["stds"] if np.isfinite(v)]
        
        print(f"\nFeature (x) statistics across files:")
        if finite_mins:
            print(f"  Min values:  min={min(finite_mins):.4e}, max={max(finite_mins):.4e}")
        if finite_maxs:
            print(f"  Max values:  min={min(finite_maxs):.4e}, max={max(finite_maxs):.4e}")
        if finite_means:
            print(f"  Mean values: min={min(finite_means):.4e}, max={max(finite_means):.4e}, avg={np.mean(finite_means):.4e}")
        if finite_stds:
            print(f"  Std values:  min={min(finite_stds):.4e}, max={max(finite_stds):.4e}, avg={np.mean(finite_stds):.4e}")
        print(f"  Zero %:      min={min(x_stats['pct_zeros']):.1f}%, max={max(x_stats['pct_zeros']):.1f}%, avg={np.mean(x_stats['pct_zeros']):.1f}%")
    
    # Recommendations
    print("\n" + "=" * 60)
    print("RECOMMENDATIONS")
    print("=" * 60)
    
    has_critical_issues = files_with_nan > 0 or files_with_inf > 0 or files_with_extreme > 0
    
    if has_critical_issues:
        print("❌ CRITICAL: Found problematic values in features!")
        if files_with_nan > 0:
            print(f"   - {files_with_nan} files with NaN values")
        if files_with_inf > 0:
            print(f"   - {files_with_inf} files with Inf values")
        if files_with_extreme > 0:
            print(f"   - {files_with_extreme} files with EXTREME values (|x| > 100)")
        print("")
        print("   This WILL cause Loss=nan during training!")
        print("   Fix: Run fix_cache_extreme.py to clip values to [-100, 100]:")
        print(f"   python fix_cache_extreme.py --cache-dir \"{cache_dir}\"")
    elif files_with_all_zeros > total_files * 0.1:
        print("⚠️  WARNING: Many files have >90% zero features")
        print("   This may indicate embedding issues (unknown tokens)")
        print("   Consider: Using a different embedding model or improving tokenization")
    else:
        print("✅ Data looks clean!")
        print("   - No NaN/Inf values")
        print("   - No extreme values (all |x| <= 100)")
        print("   Training should work correctly.")

if __name__ == "__main__":
    main()

"""
python diagnose_cache.py \
  --cache-dir "./Clean_exports/cache_devign_v2/word2vec128/train/eabf47f3e60df24e" \
  --max-files 100 \
  --verbose

"""    