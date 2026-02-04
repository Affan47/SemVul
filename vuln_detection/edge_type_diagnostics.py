#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
edge_type_diagnostics.py - Comprehensive diagnostic for cached graph data

Checks:
1. Cache directory structure
2. Data file formats (.pt, .zip, etc.)
3. All attributes in Data objects
4. Edge type availability and distribution
5. Compatibility with RGAT and other advanced models
"""

import os
import sys
import zipfile
import tempfile
from pathlib import Path
from collections import Counter

try:
    import torch
    HAS_TORCH = True
except ImportError:
    HAS_TORCH = False
    print("❌ PyTorch not installed!")

try:
    from torch_geometric.data import Data
    HAS_PYG = True
except ImportError:
    HAS_PYG = False
    print("⚠️ PyTorch Geometric not installed")


def print_header(title: str):
    """Print a formatted header."""
    print("\n" + "=" * 60)
    print(f" {title}")
    print("=" * 60)


def explore_directory(path: Path, max_depth: int = 4, current_depth: int = 0) -> dict:
    """Recursively explore directory structure."""
    result = {
        "dirs": [],
        "files": [],
        "pt_files": [],
        "zip_files": [],
        "csv_files": [],
    }
    
    if current_depth > max_depth:
        return result
    
    try:
        for item in path.iterdir():
            if item.is_dir():
                result["dirs"].append(item.name)
            elif item.is_file():
                result["files"].append(item.name)
                if item.suffix == ".pt":
                    result["pt_files"].append(item)
                elif item.suffix == ".zip":
                    result["zip_files"].append(item)
                elif item.suffix == ".csv":
                    result["csv_files"].append(item)
    except PermissionError:
        pass
    
    return result


def find_all_data_files(cache_dir: Path) -> dict:
    """Find all data files recursively."""
    result = {
        "pt_files": list(cache_dir.glob("**/*.pt")),
        "zip_files": list(cache_dir.glob("**/*.zip")),
        "csv_files": list(cache_dir.glob("**/*.csv")),
    }
    return result


def load_from_zip(zip_path: Path, max_samples: int = 3) -> list:
    """Load Data objects from a zip file."""
    samples = []
    
    with zipfile.ZipFile(zip_path, 'r') as zf:
        pt_files = [f for f in zf.namelist() if f.endswith('.pt')]
        
        for pt_file in pt_files[:max_samples]:
            with tempfile.NamedTemporaryFile(suffix='.pt', delete=False) as tmp:
                tmp.write(zf.read(pt_file))
                tmp_path = tmp.name
            
            try:
                data = torch.load(tmp_path, map_location='cpu', weights_only=False)
                samples.append((pt_file, data))
            except Exception as e:
                print(f"  ⚠️ Failed to load {pt_file}: {e}")
            finally:
                os.unlink(tmp_path)
    
    return samples


def analyze_data_object(data, name: str = "Sample"):
    """Analyze a single Data object."""
    print(f"\n📊 {name}")
    print("-" * 50)
    
    # Get all attributes
    if hasattr(data, 'keys'):
        all_keys = list(data.keys())
    else:
        all_keys = [k for k in dir(data) if not k.startswith('_')]
    
    print(f"All attributes: {all_keys}")
    
    # Node features
    if hasattr(data, 'x') and data.x is not None:
        print(f"\n✅ x (node features):")
        print(f"   Shape: {data.x.shape}")
        print(f"   Dtype: {data.x.dtype}")
        print(f"   Range: [{data.x.min():.4f}, {data.x.max():.4f}]")
        
        # Check for NaN/Inf
        nan_count = torch.isnan(data.x).sum().item()
        inf_count = torch.isinf(data.x).sum().item()
        if nan_count > 0 or inf_count > 0:
            print(f"   ⚠️ NaN: {nan_count}, Inf: {inf_count}")
    else:
        print(f"\n❌ x (node features): NOT FOUND")
    
    # Edge index
    if hasattr(data, 'edge_index') and data.edge_index is not None:
        print(f"\n✅ edge_index:")
        print(f"   Shape: {data.edge_index.shape}")
        print(f"   Num edges: {data.edge_index.size(1)}")
        if data.edge_index.numel() > 0:
            print(f"   Node range: [{data.edge_index.min()}, {data.edge_index.max()}]")
    else:
        print(f"\n❌ edge_index: NOT FOUND")
    
    # Edge type - THE CRITICAL CHECK
    edge_type_found = False
    edge_type_attr = None
    
    # Check various possible names for edge type
    possible_edge_type_names = [
        'edge_type', 'edge_types', 'edge_attr', 'edge_label',
        'etype', 'e_type', 'rel_type', 'relation_type'
    ]
    
    for attr_name in possible_edge_type_names:
        if hasattr(data, attr_name):
            attr_val = getattr(data, attr_name)
            if attr_val is not None:
                edge_type_found = True
                edge_type_attr = attr_name
                print(f"\n✅ {attr_name} (edge types):")
                print(f"   Shape: {attr_val.shape}")
                print(f"   Dtype: {attr_val.dtype}")
                if attr_val.numel() > 0:
                    unique_types = attr_val.unique()
                    print(f"   Unique types: {len(unique_types)}")
                    print(f"   Type values: {unique_types.tolist()}")
                    
                    # Distribution
                    type_counts = Counter(attr_val.tolist())
                    print(f"   Distribution:")
                    for t, count in sorted(type_counts.items()):
                        print(f"      Type {t}: {count} edges")
                break
    
    if not edge_type_found:
        print(f"\n❌ edge_type: NOT FOUND")
        print(f"   Searched for: {possible_edge_type_names}")
        print(f"   ⚠️ RGAT will treat ALL edges as same type!")
    
    # Label
    if hasattr(data, 'y') and data.y is not None:
        print(f"\n✅ y (label):")
        print(f"   Value: {data.y}")
    else:
        print(f"\n❌ y (label): NOT FOUND")
    
    # Other potentially useful attributes
    other_attrs = ['num_nodes', 'batch', 'ptr', 'node_type', 'function_id', 'fid']
    for attr in other_attrs:
        if hasattr(data, attr) and getattr(data, attr) is not None:
            val = getattr(data, attr)
            if isinstance(val, torch.Tensor):
                print(f"\n📎 {attr}: shape={val.shape}, dtype={val.dtype}")
            else:
                print(f"\n📎 {attr}: {val}")
    
    return edge_type_found, edge_type_attr


def main():
    # Configuration - UPDATE THESE PATHS
    CACHE_DIR = Path("./Clean_exports/cache_devign_v2")
    DATASET_NAME = "graphcodebert_128d_full_filtered"
    CACHE_SIGNATURE = "806ebd70856b1a10"
    
    print_header("EDGE TYPE DIAGNOSTIC TOOL")
    print(f"Cache Dir: {CACHE_DIR}")
    print(f"Dataset:   {DATASET_NAME}")
    print(f"Signature: {CACHE_SIGNATURE}")
    
    if not HAS_TORCH:
        print("\n❌ Cannot proceed without PyTorch!")
        return
    
    # Check if cache dir exists
    if not CACHE_DIR.exists():
        print(f"\n❌ Cache directory not found: {CACHE_DIR}")
        return
    
    # =========================================================================
    # STEP 1: Explore directory structure
    # =========================================================================
    print_header("STEP 1: Directory Structure")
    
    # Show top-level structure
    print(f"\n📁 {CACHE_DIR}")
    for item in sorted(CACHE_DIR.iterdir()):
        if item.is_dir():
            print(f"   📂 {item.name}/")
            # Show subdirectories
            try:
                for subitem in sorted(item.iterdir())[:5]:
                    if subitem.is_dir():
                        print(f"      📂 {subitem.name}/")
                    else:
                        print(f"      📄 {subitem.name}")
                if len(list(item.iterdir())) > 5:
                    print(f"      ... and {len(list(item.iterdir())) - 5} more")
            except:
                pass
        else:
            print(f"   📄 {item.name}")
    
    # =========================================================================
    # STEP 2: Find all data files
    # =========================================================================
    print_header("STEP 2: Finding Data Files")
    
    all_files = find_all_data_files(CACHE_DIR)
    
    print(f"\n📊 File counts:")
    print(f"   .pt files:  {len(all_files['pt_files'])}")
    print(f"   .zip files: {len(all_files['zip_files'])}")
    print(f"   .csv files: {len(all_files['csv_files'])}")
    
    # Show some paths
    if all_files['pt_files']:
        print(f"\n📍 Sample .pt file paths:")
        for f in all_files['pt_files'][:3]:
            print(f"   {f}")
    
    if all_files['zip_files']:
        print(f"\n📍 Sample .zip file paths:")
        for f in all_files['zip_files'][:5]:
            print(f"   {f}")
    
    # =========================================================================
    # STEP 3: Try specific dataset path
    # =========================================================================
    print_header("STEP 3: Dataset-Specific Path")
    
    dataset_path = CACHE_DIR / DATASET_NAME / CACHE_SIGNATURE
    print(f"\nLooking for: {dataset_path}")
    
    if dataset_path.exists():
        print(f"✅ Dataset path exists!")
        
        # List contents
        print(f"\nContents:")
        for item in sorted(dataset_path.iterdir()):
            if item.is_dir():
                subfiles = list(item.iterdir())
                print(f"   📂 {item.name}/ ({len(subfiles)} items)")
                for sf in subfiles[:3]:
                    print(f"      {sf.name}")
            else:
                print(f"   📄 {item.name} ({item.stat().st_size / 1024:.1f} KB)")
    else:
        print(f"❌ Dataset path not found!")
        
        # Try to find similar paths
        if (CACHE_DIR / DATASET_NAME).exists():
            print(f"\n🔍 Found dataset folder, checking signatures:")
            for sig_dir in (CACHE_DIR / DATASET_NAME).iterdir():
                print(f"   {sig_dir.name}")
    
    # =========================================================================
    # STEP 4: Load and analyze samples
    # =========================================================================
    print_header("STEP 4: Loading Data Samples")
    
    samples_loaded = []
    edge_type_status = {"found": False, "attr_name": None}
    
    # Try 1: Direct .pt files in dataset path
    if dataset_path.exists():
        for split in ['train', 'val', 'test', 'validation']:
            split_path = dataset_path / split
            if split_path.exists():
                pt_files = list(split_path.glob("*.pt"))
                if pt_files:
                    print(f"\n📂 Found {len(pt_files)} .pt files in {split}/")
                    for pt_file in pt_files[:2]:
                        try:
                            data = torch.load(pt_file, map_location='cpu', weights_only=False)
                            found, attr = analyze_data_object(data, f"{split}/{pt_file.name}")
                            if found:
                                edge_type_status["found"] = True
                                edge_type_status["attr_name"] = attr
                            samples_loaded.append(data)
                        except Exception as e:
                            print(f"   ⚠️ Failed to load {pt_file.name}: {e}")
    
    # Try 2: Zip files
    if not samples_loaded:
        print("\n🔍 Looking for zip files...")
        
        # Check various possible locations for zip files
        possible_zip_locations = [
            dataset_path / "train" / "cache_train.zip",
            dataset_path / "cache_train.zip",
            dataset_path / "train.zip",
            CACHE_DIR / DATASET_NAME / "train" / "cache_train.zip",
        ]
        
        # Also find any zip files
        all_zips = list(CACHE_DIR.glob(f"**/*{DATASET_NAME}*/**/*.zip"))
        all_zips.extend(list(CACHE_DIR.glob(f"**/{CACHE_SIGNATURE}/**/*.zip")))
        
        for zip_path in possible_zip_locations + all_zips[:5]:
            if zip_path.exists():
                print(f"\n📦 Found zip: {zip_path}")
                print(f"   Size: {zip_path.stat().st_size / 1024 / 1024:.2f} MB")
                
                # Load samples from zip
                samples = load_from_zip(zip_path, max_samples=2)
                for name, data in samples:
                    found, attr = analyze_data_object(data, name)
                    if found:
                        edge_type_status["found"] = True
                        edge_type_status["attr_name"] = attr
                    samples_loaded.append(data)
                
                if samples_loaded:
                    break
    
    # Try 3: Any .pt file in cache
    if not samples_loaded:
        print("\n🔍 Searching for ANY .pt files in cache...")
        all_pt = list(CACHE_DIR.glob("**/*.pt"))[:5]
        
        for pt_file in all_pt:
            print(f"\n📄 Trying: {pt_file}")
            try:
                data = torch.load(pt_file, map_location='cpu', weights_only=False)
                found, attr = analyze_data_object(data, pt_file.name)
                if found:
                    edge_type_status["found"] = True
                    edge_type_status["attr_name"] = attr
                samples_loaded.append(data)
            except Exception as e:
                print(f"   ⚠️ Failed: {e}")
    
    # =========================================================================
    # STEP 5: Summary and Recommendations
    # =========================================================================
    print_header("SUMMARY & RECOMMENDATIONS")
    
    if not samples_loaded:
        print("\n❌ CRITICAL: Could not load any data samples!")
        print("\nPossible issues:")
        print("  1. Cache directory path is incorrect")
        print("  2. Data hasn't been cached yet")
        print("  3. Different cache format than expected")
        print("\nRecommendation: Run cache_manager.py to regenerate cache")
        return
    
    print(f"\n✅ Loaded {len(samples_loaded)} sample(s)")
    
    if edge_type_status["found"]:
        print(f"\n✅ EDGE TYPES AVAILABLE!")
        print(f"   Attribute name: {edge_type_status['attr_name']}")
        print(f"\n   RGAT and advanced models will work correctly! ✓")
        
        # Check if attribute name matches what train_advanced.py expects
        if edge_type_status['attr_name'] != 'edge_type':
            print(f"\n⚠️ WARNING: Attribute is named '{edge_type_status['attr_name']}' not 'edge_type'")
            print(f"   You may need to modify train_advanced.py to use this name")
    else:
        print(f"\n❌ EDGE TYPES NOT FOUND IN DATA!")
        print(f"\n   Impact:")
        print(f"   - RGAT will treat ALL edges identically")
        print(f"   - MultiView won't be able to separate AST/CFG/DFG")
        print(f"   - HGT won't have relation information")
        print(f"\n   Recommendations:")
        print(f"   1. Update cache_manager.py to include edge_type")
        print(f"   2. Regenerate the cache with edge types")
        print(f"   3. Or use basic models (train.py) which may handle this differently")
    
    # =========================================================================
    # STEP 6: Check cache_manager.py alignment
    # =========================================================================
    print_header("STEP 6: Cache Manager Check")
    
    cache_manager_paths = [
        Path("./cache_manager.py"),
        Path("./Clean_exports/cache_manager.py"),
        CACHE_DIR / "cache_manager.py",
    ]
    
    for cm_path in cache_manager_paths:
        if cm_path.exists():
            print(f"\n📄 Found cache_manager.py at: {cm_path}")
            
            # Read and check for edge_type handling
            with open(cm_path, 'r') as f:
                content = f.read()
            
            if 'edge_type' in content:
                print(f"   ✅ Contains 'edge_type' references")
                
                # Find relevant lines
                lines = content.split('\n')
                for i, line in enumerate(lines):
                    if 'edge_type' in line.lower() and not line.strip().startswith('#'):
                        print(f"   Line {i+1}: {line.strip()[:80]}")
            else:
                print(f"   ❌ No 'edge_type' references found!")
                print(f"   This might be why edge types are missing from cache")
            break
    else:
        print("\n⚠️ cache_manager.py not found in expected locations")


if __name__ == "__main__":
    main()