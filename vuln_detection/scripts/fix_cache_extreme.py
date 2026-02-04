#!/usr/bin/env python3
"""
fix_cache_extreme.py - Fix extreme values (and NaN/Inf) in cached .pt files

The Word2Vec embeddings contain astronomically large values (10^37 - 10^38)
that cause numerical overflow during training. This script:
1. Replaces NaN/Inf with zeros
2. Clips extreme values to a reasonable range (default: [-100, 100])

Usage:
    # Preview what will be fixed
    python fix_cache_extreme.py \
        --cache-dir "/path/to/cache" \
        --dry-run
    
    # Actually fix files
    python fix_cache_extreme.py \
        --cache-dir "/path/to/cache"
    
    # Custom clip range
    python fix_cache_extreme.py \
        --cache-dir "/path/to/cache" \
        --clip-min -50 --clip-max 50
"""

import argparse
import sys
from pathlib import Path
import torch
import numpy as np
from typing import Tuple


def analyze_tensor(tensor: torch.Tensor) -> dict:
    """Analyze a tensor for issues."""
    stats = {
        "nan_count": int(torch.isnan(tensor).sum()),
        "inf_count": int(torch.isinf(tensor).sum()),
        "extreme_count": 0,
        "min": None,
        "max": None,
    }
    
    # Get finite values for stats
    finite_mask = torch.isfinite(tensor)
    if finite_mask.any():
        finite_vals = tensor[finite_mask]
        stats["min"] = float(finite_vals.min())
        stats["max"] = float(finite_vals.max())
    
    return stats


def fix_tensor(tensor: torch.Tensor, clip_min: float, clip_max: float) -> Tuple[torch.Tensor, dict]:
    """
    Fix NaN, Inf, and extreme values in a tensor.
    
    Returns:
        (fixed_tensor, stats_dict)
    """
    stats = {
        "nan_fixed": 0,
        "inf_fixed": 0,
        "clipped_low": 0,
        "clipped_high": 0,
    }
    
    # Count issues before fixing
    nan_mask = torch.isnan(tensor)
    inf_mask = torch.isinf(tensor)
    stats["nan_fixed"] = int(nan_mask.sum())
    stats["inf_fixed"] = int(inf_mask.sum())
    
    # Replace NaN/Inf with 0 first
    tensor = torch.where(nan_mask | inf_mask, torch.zeros_like(tensor), tensor)
    
    # Count and clip extreme values
    low_mask = tensor < clip_min
    high_mask = tensor > clip_max
    stats["clipped_low"] = int(low_mask.sum())
    stats["clipped_high"] = int(high_mask.sum())
    
    # Clip to range
    tensor = torch.clamp(tensor, min=clip_min, max=clip_max)
    
    return tensor, stats


def fix_pt_file(pt_path: Path, clip_min: float, clip_max: float, dry_run: bool = False) -> dict:
    """Fix a single .pt file."""
    result = {
        "path": str(pt_path.name),
        "nan_fixed": 0,
        "inf_fixed": 0,
        "clipped_low": 0,
        "clipped_high": 0,
        "modified": False,
        "error": None,
        "original_range": None,
    }
    
    try:
        data = torch.load(pt_path, map_location="cpu", weights_only=False)
    except Exception as e:
        result["error"] = str(e)
        return result
    
    # Check and fix x (node features)
    if hasattr(data, "x") and data.x is not None:
        # Analyze before fix
        pre_stats = analyze_tensor(data.x)
        result["original_range"] = (pre_stats["min"], pre_stats["max"])
        
        # Fix
        data.x, fix_stats = fix_tensor(data.x.float(), clip_min, clip_max)
        
        result["nan_fixed"] += fix_stats["nan_fixed"]
        result["inf_fixed"] += fix_stats["inf_fixed"]
        result["clipped_low"] += fix_stats["clipped_low"]
        result["clipped_high"] += fix_stats["clipped_high"]
        
        if any(v > 0 for v in fix_stats.values()):
            result["modified"] = True
    
    # Save if modified
    if result["modified"] and not dry_run:
        torch.save(data, pt_path)
    
    return result


def main():
    parser = argparse.ArgumentParser(description="Fix extreme values in cached .pt files")
    parser.add_argument("--cache-dir", required=True, help="Path to cache directory")
    parser.add_argument("--clip-min", type=float, default=-100.0, help="Minimum value (default: -100)")
    parser.add_argument("--clip-max", type=float, default=100.0, help="Maximum value (default: 100)")
    parser.add_argument("--dry-run", action="store_true", help="Preview without modifying")
    parser.add_argument("--verbose", action="store_true", help="Print details for each file")
    args = parser.parse_args()
    
    cache_dir = Path(args.cache_dir)
    
    if not cache_dir.exists():
        print(f"ERROR: Directory not found: {cache_dir}")
        sys.exit(1)
    
    # Find .pt files
    pt_files = list(cache_dir.rglob("*.pt"))
    
    if not pt_files:
        print(f"No .pt files found in {cache_dir}")
        sys.exit(0)
    
    print(f"Found {len(pt_files)} .pt files")
    print(f"Clip range: [{args.clip_min}, {args.clip_max}]")
    if args.dry_run:
        print("DRY RUN - No files will be modified\n")
    else:
        print("FIXING FILES\n")
    
    # Process files
    totals = {
        "nan_fixed": 0,
        "inf_fixed": 0,
        "clipped_low": 0,
        "clipped_high": 0,
        "files_modified": 0,
        "errors": 0,
    }
    
    extreme_examples = []  # Track files with extreme values
    
    for i, pt_path in enumerate(pt_files):
        result = fix_pt_file(pt_path, args.clip_min, args.clip_max, args.dry_run)
        
        if result["error"]:
            totals["errors"] += 1
            print(f"ERROR: {pt_path.name}: {result['error']}")
            continue
        
        if result["modified"]:
            totals["files_modified"] += 1
            totals["nan_fixed"] += result["nan_fixed"]
            totals["inf_fixed"] += result["inf_fixed"]
            totals["clipped_low"] += result["clipped_low"]
            totals["clipped_high"] += result["clipped_high"]
            
            # Track extreme examples
            if result["original_range"]:
                orig_min, orig_max = result["original_range"]
                if orig_min is not None and (orig_min < -1e6 or orig_max > 1e6):
                    extreme_examples.append({
                        "file": pt_path.name,
                        "min": orig_min,
                        "max": orig_max,
                    })
            
            if args.verbose:
                status = "WOULD_FIX" if args.dry_run else "FIXED"
                print(f"  {status} {pt_path.name}: "
                      f"nan={result['nan_fixed']} inf={result['inf_fixed']} "
                      f"clip_lo={result['clipped_low']} clip_hi={result['clipped_high']}")
        
        # Progress
        if (i + 1) % 2000 == 0:
            print(f"  Processed {i+1}/{len(pt_files)} files... "
                  f"(modified so far: {totals['files_modified']})")
    
    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY")
    print("=" * 70)
    print(f"Total files scanned:    {len(pt_files)}")
    print(f"Files with issues:      {totals['files_modified']}")
    print(f"")
    print(f"Values fixed:")
    print(f"  NaN replaced:         {totals['nan_fixed']:,}")
    print(f"  Inf replaced:         {totals['inf_fixed']:,}")
    print(f"  Clipped (too low):    {totals['clipped_low']:,}")
    print(f"  Clipped (too high):   {totals['clipped_high']:,}")
    print(f"  TOTAL values fixed:   {sum([totals['nan_fixed'], totals['inf_fixed'], totals['clipped_low'], totals['clipped_high']]):,}")
    print(f"")
    print(f"Errors:                 {totals['errors']}")
    
    # Show extreme examples
    if extreme_examples[:5]:
        print(f"\nExamples of extreme values found:")
        for ex in extreme_examples[:5]:
            print(f"  {ex['file']}: min={ex['min']:.2e}, max={ex['max']:.2e}")
    
    if args.dry_run:
        print(f"\n⚠️  DRY RUN: Would fix {totals['files_modified']} files")
        print("Run without --dry-run to apply fixes")
    else:
        print(f"\n✅ Fixed {totals['files_modified']} files!")
        print("You can now run training.")


if __name__ == "__main__":
    main()



"""
# Fix training cache
python fix_cache_extreme.py \
    --cache-dir "./Clean_exports/cache_devign_v2/word2vec128/train/eabf47f3e60df24e"

# Fix validation cache  
python fix_cache_extreme.py \
    --cache-dir "./Clean_exports/cache_devign_v2/word2vec128/valid/eabf47f3e60df24e"

# Fix test cache
python fix_cache_extreme.py \
    --cache-dir "./Clean_exports/cache_devign_v2/word2vec128/test/eabf47f3e60df24e"

"""