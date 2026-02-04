#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
verify_labels.py - Verify that cached labels match manifest labels

The cached keys look like: objects_96_96_train_func_0001176.c__export__d8c26b9b
The manifest keys look like: train_func_0000001.c

This script extracts the function key and verifies alignment.
"""

import argparse
import re
import csv
import io
import zipfile
from pathlib import Path
from collections import Counter

import torch

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def extract_function_key(cached_key):
    """Extract function key from cached filename.
    
    Examples:
        objects_96_96_train_func_0001176.c__export__d8c26b9b -> train_func_0001176.c
        objects_96_8b_train_func_0016362.c__export__d4ecc965 -> train_func_0016362.c
    """
    # Try to find pattern: train_func_XXXXXXX.c
    match = re.search(r'(train_func_\d+\.c)', cached_key)
    if match:
        return match.group(1)
    
    # Try validation/test patterns
    match = re.search(r'(val_func_\d+\.c|test_func_\d+\.c)', cached_key)
    if match:
        return match.group(1)
    
    return None


def load_manifest(manifest_path):
    """Load manifest and return {function_id: label}."""
    manifest = {}
    with open(manifest_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            func_id = row.get('function_id', '').strip()
            label = row.get('label', '').strip()
            
            if func_id and label:
                manifest[func_id] = int(label)
    
    return manifest


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--split", type=str, default="train")
    parser.add_argument("--max-samples", type=int, default=500)
    args = parser.parse_args()
    
    print("=" * 60)
    print("LABEL VERIFICATION")
    print("=" * 60)
    
    # Load manifest
    manifest = load_manifest(args.manifest)
    print(f"Loaded {len(manifest)} entries from manifest")
    
    manifest_labels = list(manifest.values())
    print(f"Manifest label distribution: {Counter(manifest_labels)}")
    
    # Load cached data
    split_dir = Path(args.cache_dir) / args.dataset_name / args.split / args.cache_signature[:16]
    zip_path = split_dir / f"cache_{args.split}.zip"
    
    if not zip_path.exists():
        print(f"Cache not found: {zip_path}")
        return
    
    matches = 0
    mismatches = 0
    not_found = 0
    mismatch_examples = []
    
    with zipfile.ZipFile(zip_path, 'r') as zf:
        pt_files = [n for n in zf.namelist() if n.endswith('.pt')][:args.max_samples]
        
        for pt_name in tqdm(pt_files, desc="Checking"):
            try:
                with zf.open(pt_name) as f:
                    data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                    cached_label = data.y.item() if data.y.numel() == 1 else data.y[0].item()
            except:
                continue
            
            # Extract function key
            func_key = extract_function_key(pt_name)
            
            if func_key is None:
                not_found += 1
                continue
            
            if func_key in manifest:
                manifest_label = manifest[func_key]
                
                if manifest_label == cached_label:
                    matches += 1
                else:
                    mismatches += 1
                    if len(mismatch_examples) < 10:
                        mismatch_examples.append({
                            'file': pt_name,
                            'func_key': func_key,
                            'cached': cached_label,
                            'manifest': manifest_label,
                        })
            else:
                not_found += 1
    
    print(f"\n" + "=" * 60)
    print("RESULTS")
    print("=" * 60)
    print(f"Checked: {args.max_samples}")
    print(f"Matches: {matches} ({matches/args.max_samples*100:.1f}%)")
    print(f"Mismatches: {mismatches} ({mismatches/args.max_samples*100:.1f}%)")
    print(f"Not found: {not_found} ({not_found/args.max_samples*100:.1f}%)")
    
    if mismatches > 0:
        print(f"\n🚨 LABEL MISMATCHES FOUND!")
        print("\nExamples of mismatches:")
        for ex in mismatch_examples:
            print(f"  {ex['func_key']}: cached={ex['cached']}, manifest={ex['manifest']}")
        
        print("\n⚠️ Labels in cache do NOT match manifest!")
        print("   The caching pipeline has a bug in label assignment.")
    
    elif matches > args.max_samples * 0.8:
        print(f"\n✅ Labels are correctly aligned!")
        print("   The issue is NOT in label alignment.")
    
    else:
        print(f"\n⚠️ Many keys not found in manifest.")
        print("   Key format may differ, or manifest is incomplete.")


if __name__ == "__main__":
    main()
