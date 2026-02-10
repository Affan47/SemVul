#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
download_devign_full.py
Downloads complete Devign dataset with all columns/features and saves in multiple formats.
Displays full dataset structure and column information.
"""

import os
import sys
import json
import argparse
from pathlib import Path
from typing import Dict, Any, List, Optional

# Install required package if not present
try:
    from datasets import load_dataset, DatasetDict, Dataset
except ImportError:
    print("Installing required package: datasets")
    os.system("pip install datasets")
    from datasets import load_dataset, DatasetDict, Dataset


def inspect_dataset_structure(ds: DatasetDict) -> Dict[str, Any]:
    """
    Inspect and return detailed information about dataset structure.
    """
    info = {
        "splits": list(ds.keys()),
        "total_size": sum(len(ds[s]) for s in ds),
        "features": {},
        "statistics": {}
    }
    
    print("\n" + "=" * 60)
    print("DATASET STRUCTURE ANALYSIS")
    print("=" * 60)
    
    for split_name in ds:
        split = ds[split_name]
        print(f"\n{split_name.upper()} SPLIT:")
        print(f"  Size: {len(split):,} examples")
        
        # Get column names and types
        features = split.features
        print(f"\n  Columns ({len(features)}):")
        for col_name, col_type in features.items():
            print(f"    - {col_name}: {col_type}")
        
        info["features"][split_name] = {k: str(v) for k, v in features.items()}
        
        # Calculate statistics
        if "target" in features:
            vulnerable_count = sum(split["target"])
            info["statistics"][split_name] = {
                "total": len(split),
                "vulnerable": int(vulnerable_count),
                "non_vulnerable": int(len(split) - vulnerable_count),
                "vulnerable_percentage": float(vulnerable_count / len(split) * 100)
            }
            
            print(f"\n  Statistics:")
            print(f"    - Vulnerable: {vulnerable_count:,} ({vulnerable_count/len(split):.1%})")
            print(f"    - Non-vulnerable: {len(split) - vulnerable_count:,} ({1 - vulnerable_count/len(split):.1%})")
        
        # Show first example with all columns
        print(f"\n  First Example (all columns):")
        first_example = split[0]
        for col, value in first_example.items():
            preview = str(value)[:100] + "..." if len(str(value)) > 100 else str(value)
            print(f"    {col}: {preview}")
    
    return info


def save_json_full(ds: DatasetDict, output_dir: Path) -> None:
    """
    Save dataset in JSON Lines format with all columns/features.
    """
    print(f"\nSaving JSON format to {output_dir}...")
    
    for split_name in ds:
        split_data = ds[split_name]
        json_file = output_dir / f"{split_name}.jsonl"
        
        # Save each example as a JSON line with ALL columns
        with open(json_file, "w", encoding="utf-8") as f:
            for idx in range(len(split_data)):
                example = {col: split_data[idx][col] for col in split_data.features}
                f.write(json.dumps(example) + "\n")
        
        print(f"  ✓ {split_name}.jsonl ({len(split_data):,} functions)")
    
    print("✓ JSON format saved")


def save_csv_full(ds: DatasetDict, output_dir: Path) -> None:
    """
    Save dataset in CSV format with all columns/features.
    """
    print(f"\nSaving CSV format to {output_dir}...")
    
    for split_name in ds:
        csv_file = output_dir / f"{split_name}.csv"
        ds[split_name].to_csv(csv_file)
        size_mb = csv_file.stat().st_size / (1024**2)
        print(f"  ✓ {split_name}.csv ({len(ds[split_name]):,} functions, {size_mb:.2f} MB)")
    
    print("✓ CSV format saved")


def download_and_save(output_dir: str = "./devign_full",
                     formats: List[str] = ["arrow", "json", "csv"]) -> DatasetDict:
    """
    Download and save Devign dataset with all columns in multiple formats.
    
    Args:
        output_dir: Base output directory
        formats: List of formats to save: 'arrow', 'json', 'csv'
    
    Returns:
        DatasetDict
    """
    base_path = Path(output_dir)
    base_path.mkdir(parents=True, exist_ok=True)
    
    print("=" * 70)
    print("DOWNLOADING FULL DEVIGN DATASET")
    print("Dataset: DetectVul/devign")
    print(f"Output: {base_path}")
    print(f"Formats: {', '.join(formats)}")
    print("=" * 70)
    
    # Download dataset
    print("\n[1/3] Downloading from Hugging Face Hub...")
    ds = load_dataset("DetectVul/devign", trust_remote_code=True)
    
    # Inspect structure
    info = inspect_dataset_structure(ds)
    
    # Save metadata
    with open(base_path / "dataset_info.json", "w") as f:
        json.dump(info, f, indent=2)
    
    # Save in requested formats
    if "arrow" in formats:
        print(f"\n[2a/4] Saving Arrow format...")
        ds.save_to_disk(str(base_path / "arrow"))
        print("✓ Arrow format saved")
    
    if "json" in formats:
        json_dir = base_path / "json"
        json_dir.mkdir(exist_ok=True)
        save_json_full(ds, json_dir)
    
    if "csv" in formats:
        csv_dir = base_path / "csv"
        csv_dir.mkdir(exist_ok=True)
        save_csv_full(ds, csv_dir)
    
    print("\n" + "=" * 70)
    print("✓ DOWNLOAD COMPLETE!")
    print("=" * 70)
    print(f"\nDataset saved with all columns to: {base_path}")
    print("\nAvailable formats:")
    for fmt in formats:
        print(f"  - {fmt.upper()}: {base_path}/{fmt}")
    
    return ds


def main():
    parser = argparse.ArgumentParser(
        description="Download full Devign dataset with all columns in multiple formats"
    )
    parser.add_argument(
        "--output",
        default="./devign_full",
        help="Output directory for downloaded dataset"
    )
    parser.add_argument(
        "--formats",
        nargs="+",
        choices=["arrow", "json", "csv"],
        default=["arrow", "json"],
        help="Formats to save (default: arrow json)"
    )
    
    args = parser.parse_args()
    
    # Download and save
    ds = download_and_save(
        output_dir=args.output,
        formats=args.formats
    )
    
    # Show usage examples
    print("\n" + "=" * 70)
    print("USAGE EXAMPLES")
    print("=" * 70)
    
    if "arrow" in args.formats:
        print("\nLoad Arrow format:")
        print("  from datasets import load_from_disk")
        print(f"  ds = load_from_disk('{args.output}/arrow')")
        print("  train = ds['train']")
    
    if "json" in args.formats:
        print("\nLoad JSON Lines format:")
        print("  import json")
        print(f"  with open('{args.output}/json/train.jsonl') as f:")
        print("      for line in f:")
        print("          data = json.loads(line)")
        print("          # data has all columns: func, target, etc.")
    
    if "csv" in args.formats:
        print("\nLoad CSV format:")
        print("  import pandas as pd")
        print(f"  df = pd.read_csv('{args.output}/csv/train.csv')")
        print("  # Access columns: df['func'], df['target']")


if __name__ == "__main__":
    main()


"""
python download_devign.py --output ./devign_full --formats  json csv

"""    