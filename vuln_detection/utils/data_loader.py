#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
data_loader.py - Data loading utilities for vulnerability detection

Handles loading from:
- Cached PyG data (zip files)
- Raw CPG data
- Devign dataset format
"""

import io
import random
import zipfile
from pathlib import Path
from typing import List, Optional, Tuple, Dict, Any

import torch
from torch_geometric.data import Data
from torch_geometric.loader import DataLoader

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_from_cache(
    cache_dir: Path,
    dataset_name: str,
    cache_signature: str,
    split: str,
    max_samples: Optional[int] = None,
    shuffle: bool = False,
) -> List[Data]:
    """
    Load cached PyG data from zip file.
    
    Args:
        cache_dir: Base cache directory
        dataset_name: Dataset name (e.g., "devign_normfunc_v2")
        cache_signature: Cache signature hash or tag
        split: "train", "valid", or "test"
        max_samples: Maximum samples to load (None = all)
        shuffle: Whether to shuffle before taking max_samples
    
    Returns:
        List of PyG Data objects
    """
    cache_dir = Path(cache_dir)
    
    # Try different path structures to find the cache
    
    # 1. Cache Manager V6 Structure: dataset/signature/split/cache_split.zip
    path_v6 = cache_dir / dataset_name / cache_signature / split / f"cache_{split}.zip"
    
    # 2. Original Structure: dataset/split/signature/cache_split.zip
    path_orig = cache_dir / dataset_name / split / cache_signature / f"cache_{split}.zip"
    
    # 3. Sliced Signature (Legacy): dataset/split/sig[:16]/cache_split.zip
    path_sliced = cache_dir / dataset_name / split / cache_signature[:16] / f"cache_{split}.zip"

    if path_v6.exists():
        zip_path = path_v6
    elif path_orig.exists():
        zip_path = path_orig
    elif path_sliced.exists():
        zip_path = path_sliced
    else:
        # Debugging info
        raise FileNotFoundError(
            f"Cache not found for split '{split}'.\n"
            f"Checked the following paths:\n"
            f"  1. {path_v6}\n"
            f"  2. {path_orig}\n"
            f"  3. {path_sliced}\n"
            f"Please verify your --dataset-name and --cache-signature arguments."
        )
    
    print(f"[DataLoader] Loading {split} from: {zip_path}")
    
    samples = []
    
    with zipfile.ZipFile(zip_path, 'r') as zf:
        pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
        
        if shuffle:
            random.shuffle(pt_files)
        
        if max_samples:
            pt_files = pt_files[:max_samples]
        
        for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
            try:
                with zf.open(pt_name) as f:
                    data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                    if hasattr(data, 'y') and data.y is not None:
                        samples.append(data)
            except Exception as e:
                print(f"[WARNING] Failed to load {pt_name}: {e}")
                continue
    
    return samples


def load_dataset(
    cache_dir: str,
    dataset_name: str,
    cache_signature: str,
    max_train: Optional[int] = None,
    max_val: Optional[int] = None,
    max_test: Optional[int] = None,
) -> Tuple[List[Data], List[Data], List[Data]]:
    """
    Load train/val/test splits.
    
    Returns:
        (train_data, val_data, test_data)
    """
    cache_dir = Path(cache_dir)
    
    train_data = load_from_cache(
        cache_dir, dataset_name, cache_signature, "train", max_train, shuffle=True
    )
    val_data = load_from_cache(
        cache_dir, dataset_name, cache_signature, "valid", max_val
    )
    test_data = load_from_cache(
        cache_dir, dataset_name, cache_signature, "test", max_test
    )
    
    return train_data, val_data, test_data


def create_data_loaders(
    train_data: List[Data],
    val_data: List[Data],
    test_data: List[Data],
    batch_size: int = 32,
    num_workers: int = 0,
) -> Tuple[DataLoader, DataLoader, DataLoader]:
    """
    Create PyG DataLoaders.
    
    Returns:
        (train_loader, val_loader, test_loader)
    """
    train_loader = DataLoader(
        train_data,
        batch_size=batch_size,
        shuffle=True,
        num_workers=num_workers,
    )
    val_loader = DataLoader(
        val_data,
        batch_size=batch_size,
        shuffle=False,
        num_workers=num_workers,
    )
    test_loader = DataLoader(
        test_data,
        batch_size=batch_size,
        shuffle=False,
        num_workers=num_workers,
    )
    
    return train_loader, val_loader, test_loader


def get_class_weights(data_list: List[Data], device: str = "cpu") -> torch.Tensor:
    """
    Compute class weights for imbalanced dataset.
    
    Returns:
        pos_weight for BCEWithLogitsLoss
    """
    labels = []
    for data in data_list:
        if data.y.numel() == 1:
            labels.append(data.y.item())
        else:
            labels.append(data.y[0].item())
    
    if not labels:
        return torch.tensor([1.0], device=device)

    num_pos = sum(labels)
    num_neg = len(labels) - num_pos
    
    weight = num_neg / max(num_pos, 1)
    return torch.tensor([weight], device=device)


def get_dataset_stats(data_list: List[Data]) -> Dict[str, Any]:
    """
    Compute dataset statistics.
    """
    if not data_list:
        return {}

    labels = []
    num_nodes = []
    num_edges = []
    
    for data in data_list:
        if data.y.numel() == 1:
            labels.append(data.y.item())
        else:
            labels.append(data.y[0].item())
        
        num_nodes.append(data.x.size(0))
        num_edges.append(data.edge_index.size(1))
    
    num_pos = sum(labels)
    num_neg = len(labels) - num_pos
    
    return {
        "total_samples": len(data_list),
        "num_positive": num_pos,
        "num_negative": num_neg,
        "pos_ratio": num_pos / len(data_list) if data_list else 0,
        "avg_nodes": sum(num_nodes) / len(num_nodes) if num_nodes else 0,
        "avg_edges": sum(num_edges) / len(num_edges) if num_edges else 0,
        "input_dim": data_list[0].x.size(1) if data_list else 0,
    }


def print_dataset_stats(
    train_data: List[Data],
    val_data: List[Data],
    test_data: List[Data],
):
    """Print dataset statistics."""
    print("\n" + "=" * 60)
    print("DATASET STATISTICS")
    print("=" * 60)
    
    for name, data in [("Train", train_data), ("Val", val_data), ("Test", test_data)]:
        if not data:
            print(f"\n{name}: [EMPTY]")
            continue
            
        stats = get_dataset_stats(data)
        print(f"\n{name}:")
        print(f"  Samples: {stats['total_samples']}")
        print(f"  Positive: {stats['num_positive']} ({stats['pos_ratio']*100:.1f}%)")
        print(f"  Negative: {stats['num_negative']} ({(1-stats['pos_ratio'])*100:.1f}%)")
        print(f"  Avg nodes: {stats['avg_nodes']:.1f}")
        print(f"  Avg edges: {stats['avg_edges']:.1f}")
        print(f"  Input dim: {stats['input_dim']}")