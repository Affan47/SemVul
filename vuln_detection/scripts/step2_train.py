#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
step2_train.py - Comprehensive vulnerability detection training script

Matches the Devign_baseline.py interface exactly.

Supports Edge Type Modes:
  - 'full_filtered': 13 edge types (RECOMMENDED)
  - 'simplified':    5 edge types (Original Devign)
  - 'full':         15 edge types (includes metadata edges)

Supported Models:
  - 'mlp':         Graph-Level MLP (Best performance, no GNN)
  - 'devign':      Original Devign GGNN
  - 'gcn':         Standard GCN
  - 'gat':         GATv2 
  - 'transformer': Graph Transformer
  - 'attention':   Attention pooling model
  - 'edge_type':   Edge-type aware GNN (RGCN)
  - 'shallow':     Shallow GNN (1-2 layers)

Usage:
    python step2_train.py \
        --model-type mlp \
        --cache-dir /path/to/cache \
        --dataset-name devign_normfunc_v2 \
        --cache-signature YOUR_SIGNATURE \
        --vocab-dir /path/to/vocab \
        --train-manifest /path/to/manifest_train.csv \
        --val-manifest /path/to/manifest_validation.csv \
        --test-manifest /path/to/manifest_test.csv \
        --hidden-dim 128 \
        --epochs 100 \
        --batch-size 64 \
        --output-dir results
"""

import argparse
import csv
import json
import random
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset as TorchDataset
from torch_geometric.data import Data
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, GATv2Conv, TransformerConv, MessagePassing

try:
    from sklearn.metrics import (
        roc_auc_score, f1_score, precision_score, recall_score,
        accuracy_score, average_precision_score
    )
    HAS_SKLEARN = True
except ImportError:
    HAS_SKLEARN = False


# ============================================================================
# REPRODUCIBILITY
# ============================================================================

def set_seed(seed: int = 42):
    """Set random seeds for reproducibility."""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


# ============================================================================
# DATASET: Cached graphs from .pt files (matches Devign_baseline.py)
# ============================================================================

class CachedDataset(TorchDataset):
    """
    Dataset that loads cached .pt graphs from a cache directory.
    Matches the exact interface of Devign_baseline.py.
    """
    
    def __init__(self, cache_dir: Path, manifest_path: Optional[Path] = None):
        super().__init__()
        self.cache_dir = Path(cache_dir)
        self.pt_paths = []
        self.num_pos = 0
        self.num_neg = 0
        
        # Find index.csv
        index_csv = self.cache_dir / "meta" / "index.csv"
        if not index_csv.is_file():
            raise FileNotFoundError(f"index.csv not found at: {index_csv}")
        
        # Load manifest keys if provided
        manifest_keys = None
        if manifest_path and Path(manifest_path).exists():
            manifest_keys = set()
            with Path(manifest_path).open("r", encoding="utf-8") as f:
                reader = csv.DictReader(f)
                for row in reader:
                    fid = row.get("function_id") or row.get("fid")
                    if fid:
                        manifest_keys.add(fid.strip())
        
        # Load index and filter
        with index_csv.open("r", newline="", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            for row in reader:
                rel_path = row.get("rel_path") or row.get("path") or row.get("pt_path")
                if rel_path is None:
                    continue
                
                # Filter by manifest if provided
                row_func_id = row.get("function_id", "").strip()
                if manifest_keys is not None:
                    if row_func_id not in manifest_keys:
                        continue
                
                self.pt_paths.append(self.cache_dir / rel_path)
                
                # Count labels
                lbl = row.get("label", "")
                try:
                    val = int(float(lbl))
                    if val == 1:
                        self.num_pos += 1
                    elif val == 0:
                        self.num_neg += 1
                except:
                    pass
    
    def get_pos_weight(self) -> float:
        """Calculate positive class weight for imbalanced data."""
        if self.num_pos > 0:
            return self.num_neg / self.num_pos
        return 1.0
    
    def __len__(self):
        return len(self.pt_paths)
    
    def __getitem__(self, idx: int) -> Data:
        path = self.pt_paths[idx]
        try:
            data = torch.load(path, map_location="cpu", weights_only=False)
        except Exception as e:
            print(f"[Error] Failed to load {path}: {e}")
            return Data(x=torch.zeros(1, 1), edge_index=torch.zeros(2, 0, dtype=torch.long), 
                       y=torch.tensor([0]))
        
        if not hasattr(data, "y"):
            data.y = torch.tensor([0])
        
        # CRITICAL: Replace NaN/Inf values with 0 to prevent Loss=nan
        if hasattr(data, "x") and data.x is not None:
            data.x = data.x.float()
            nan_mask = torch.isnan(data.x)
            inf_mask = torch.isinf(data.x)
            if nan_mask.any() or inf_mask.any():
                data.x = torch.where(nan_mask | inf_mask, torch.zeros_like(data.x), data.x)
        
        data.cache_index = idx
        return data


def ensure_vocabs(vocab_dir: Path) -> Tuple[int, List[str]]:
    """Load vocabulary to determine number of edge relations.
    
    Returns:
        Tuple of (num_relations, list_of_edge_type_names)
    """
    vocab_dir = Path(vocab_dir)
    
    # Try edge_type_vocab.json first (new format), then devign_rel_vocab.json (legacy)
    rel_vocab_path = vocab_dir / "edge_type_vocab.json"
    if not rel_vocab_path.is_file():
        rel_vocab_path = vocab_dir / "devign_rel_vocab.json"
    
    if not rel_vocab_path.is_file():
        print("[Vocab] Warning: edge_type_vocab.json not found. Assuming 5 relations (simplified mode).")
        return 5, ["AST", "CFG", "DFG_READ", "DFG_WRITE", "NCS"]
    
    with rel_vocab_path.open("r", encoding="utf-8") as f:
        rel_vocab = json.load(f)
    
    # rel_vocab is {edge_type_name: index}
    edge_types = sorted(rel_vocab.keys(), key=lambda k: rel_vocab[k])
    return len(rel_vocab), edge_types


def load_cache_metadata(cache_dir: Path, dataset_name: str) -> Optional[Dict]:
    """Load cache metadata to verify configuration."""
    meta_path = cache_dir / dataset_name / "cache_meta.json"
    if meta_path.exists():
        with meta_path.open("r") as f:
            return json.load(f)
    return None


def validate_edge_mode_consistency(vocab_dir: Path, cache_dir: Path, dataset_name: str) -> None:
    """Validate that vocab and cache use the same edge mode."""
    num_rels, edge_types = ensure_vocabs(vocab_dir)
    cache_meta = load_cache_metadata(cache_dir, dataset_name)
    
    if cache_meta:
        cache_edge_types = cache_meta.get("edge_types", [])
        cache_num_edge_types = cache_meta.get("num_edge_types", 0)
        cache_edge_mode = cache_meta.get("edge_mode", "unknown")
        
        if cache_num_edge_types != num_rels:
            print(f"[WARNING] Edge type count mismatch!")
            print(f"  Vocab: {num_rels} types ({edge_types})")
            print(f"  Cache: {cache_num_edge_types} types ({cache_edge_mode})")
            print(f"  This may cause index errors during training!")
        else:
            print(f"[Vocab] Edge mode: {cache_edge_mode} ({num_rels} types)")
            print(f"[Vocab] Edge types: {edge_types}")
    else:
        print(f"[Vocab] Edge types ({num_rels}): {edge_types}")
        print(f"[Vocab] Note: cache_meta.json not found, skipping consistency check")


# ============================================================================
# MODELS
# ============================================================================

class GraphLevelMLP(nn.Module):
    """
    Graph-Level MLP - Best performing model.
    Uses multi-stat pooling (mean + max + std) without GNN.
    """
    
    def __init__(self, in_dim: int, hidden_dim: int, dropout: float = 0.3):
        super().__init__()
        # Multi-stat pooling: mean + max + std = 3x features
        self.fc1 = nn.Linear(in_dim * 3, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, hidden_dim)
        self.fc3 = nn.Linear(hidden_dim, 1)
        self.dropout = nn.Dropout(dropout)
        self.norm1 = nn.LayerNorm(hidden_dim)
        self.norm2 = nn.LayerNorm(hidden_dim)
    
    def forward(self, data):
        x, batch = data.x, data.batch
        
        from torch_geometric.nn import global_mean_pool, global_max_pool
        
        mean_pool = global_mean_pool(x, batch)
        max_pool = global_max_pool(x, batch)
        
        # Compute std per graph
        num_graphs = batch.max().item() + 1
        std_list = []
        for i in range(num_graphs):
            mask = (batch == i)
            if mask.sum() > 1:
                std_list.append(x[mask].std(dim=0))
            else:
                std_list.append(torch.zeros(x.size(1), device=x.device))
        std_pool = torch.stack(std_list)
        
        pooled = torch.cat([mean_pool, max_pool, std_pool], dim=1)
        
        h = F.relu(self.norm1(self.fc1(pooled)))
        h = self.dropout(h)
        h = F.relu(self.norm2(self.fc2(h)))
        h = self.dropout(h)
        logits = self.fc3(h)
        
        return {"logits": logits}


class RelGraphConv(MessagePassing):
    """Relational Graph Convolution (matches Devign_baseline.py)."""
    
    def __init__(self, hidden_dim: int, num_relations: int, dropout: float = 0.0):
        super().__init__(aggr="add")
        self.hidden_dim = hidden_dim
        self.num_relations = num_relations
        self.dropout = nn.Dropout(dropout)
        self.norm = nn.LayerNorm(hidden_dim)
        
        self.weight = nn.Parameter(torch.empty(num_relations, hidden_dim, hidden_dim))
        self.root_weight = nn.Parameter(torch.empty(hidden_dim, hidden_dim))
        self.bias = nn.Parameter(torch.zeros(hidden_dim))
        
        self.reset_parameters()
    
    def reset_parameters(self):
        nn.init.xavier_uniform_(self.weight)
        nn.init.xavier_uniform_(self.root_weight)
        nn.init.zeros_(self.bias)
    
    def forward(self, x, edge_index, edge_type):
        out = torch.zeros_like(x)
        
        for r in range(self.num_relations):
            mask = (edge_type == r)
            if mask.sum() == 0:
                continue
            
            edge_r = edge_index[:, mask]
            msg = self.propagate(edge_r, x=x, W=self.weight[r])
            out = out + msg
        
        out = out + x @ self.root_weight
        out = out + self.bias
        out = self.norm(out)
        out = F.relu(out)
        out = self.dropout(out)
        
        return out
    
    def message(self, x_j, W):
        return x_j @ W


class DevignGGNN(nn.Module):
    """Original Devign GGNN model with Conv readout."""
    
    def __init__(self, in_dim: int, hidden_dim: int, num_relations: int = 5,
                 num_layers: int = 4, dropout: float = 0.3):
        super().__init__()
        self.proj = nn.Linear(in_dim, hidden_dim)
        
        self.layers = nn.ModuleList([
            RelGraphConv(hidden_dim, num_relations, dropout)
            for _ in range(num_layers)
        ])
        
        # Conv readout
        self.conv1 = nn.Conv1d(hidden_dim * 2, hidden_dim, kernel_size=3, padding=1)
        self.conv2 = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.fc = nn.Linear(hidden_dim, 1)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data):
        x, edge_index, batch = data.x, data.edge_index, data.batch
        edge_type = data.edge_attr if hasattr(data, 'edge_attr') else None
        
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        h_init = h
        
        for layer in self.layers:
            h = layer(h, edge_index, edge_type)
        
        # Concatenate initial and final
        h_cat = torch.cat([h_init, h], dim=-1)
        
        # Global pooling
        from torch_geometric.nn import global_mean_pool
        pooled = global_mean_pool(h_cat, batch)
        
        # Simple classifier
        pooled = self.dropout(pooled)
        pooled = pooled[:, :pooled.size(1)//2] * pooled[:, pooled.size(1)//2:]
        logits = self.fc(pooled)
        
        return {"logits": logits}


class GCNModel(nn.Module):
    """Standard GCN model."""
    
    def __init__(self, in_dim: int, hidden_dim: int, num_layers: int = 4, dropout: float = 0.3):
        super().__init__()
        self.proj = nn.Linear(in_dim, hidden_dim)
        
        self.convs = nn.ModuleList([
            GCNConv(hidden_dim, hidden_dim) for _ in range(num_layers)
        ])
        self.norms = nn.ModuleList([
            nn.LayerNorm(hidden_dim) for _ in range(num_layers)
        ])
        
        self.fc = nn.Linear(hidden_dim * 3, 1)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data):
        x, edge_index, batch = data.x, data.edge_index, data.batch
        
        h = F.relu(self.proj(x))
        
        for conv, norm in zip(self.convs, self.norms):
            h_new = conv(h, edge_index)
            h_new = norm(h_new)
            h = F.relu(h_new) + h
            h = self.dropout(h)
        
        from torch_geometric.nn import global_mean_pool, global_max_pool
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        num_graphs = batch.max().item() + 1
        std_list = []
        for i in range(num_graphs):
            mask = (batch == i)
            if mask.sum() > 1:
                std_list.append(h[mask].std(dim=0))
            else:
                std_list.append(torch.zeros(h.size(1), device=h.device))
        std_pool = torch.stack(std_list)
        
        pooled = torch.cat([mean_pool, max_pool, std_pool], dim=1)
        logits = self.fc(pooled)
        
        return {"logits": logits}


class GATModel(nn.Module):
    """GATv2 model."""
    
    def __init__(self, in_dim: int, hidden_dim: int, num_layers: int = 4, 
                 heads: int = 4, dropout: float = 0.3):
        super().__init__()
        self.proj = nn.Linear(in_dim, hidden_dim)
        
        self.convs = nn.ModuleList([
            GATv2Conv(hidden_dim, hidden_dim // heads, heads=heads, dropout=dropout, concat=True)
            for _ in range(num_layers)
        ])
        self.norms = nn.ModuleList([
            nn.LayerNorm(hidden_dim) for _ in range(num_layers)
        ])
        
        self.fc = nn.Linear(hidden_dim * 3, 1)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data):
        x, edge_index, batch = data.x, data.edge_index, data.batch
        
        h = F.relu(self.proj(x))
        
        for conv, norm in zip(self.convs, self.norms):
            h_new = conv(h, edge_index)
            h_new = norm(h_new)
            h = F.relu(h_new) + h
            h = self.dropout(h)
        
        from torch_geometric.nn import global_mean_pool, global_max_pool
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        num_graphs = batch.max().item() + 1
        std_list = []
        for i in range(num_graphs):
            mask = (batch == i)
            if mask.sum() > 1:
                std_list.append(h[mask].std(dim=0))
            else:
                std_list.append(torch.zeros(h.size(1), device=h.device))
        std_pool = torch.stack(std_list)
        
        pooled = torch.cat([mean_pool, max_pool, std_pool], dim=1)
        logits = self.fc(pooled)
        
        return {"logits": logits}


class TransformerModel(nn.Module):
    """Graph Transformer model."""
    
    def __init__(self, in_dim: int, hidden_dim: int, num_layers: int = 4,
                 heads: int = 4, dropout: float = 0.3):
        super().__init__()
        self.proj = nn.Linear(in_dim, hidden_dim)
        
        self.convs = nn.ModuleList([
            TransformerConv(hidden_dim, hidden_dim // heads, heads=heads, dropout=dropout, concat=True)
            for _ in range(num_layers)
        ])
        self.norms = nn.ModuleList([
            nn.LayerNorm(hidden_dim) for _ in range(num_layers)
        ])
        
        self.fc = nn.Linear(hidden_dim * 3, 1)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data):
        x, edge_index, batch = data.x, data.edge_index, data.batch
        
        h = F.relu(self.proj(x))
        
        for conv, norm in zip(self.convs, self.norms):
            h_new = conv(h, edge_index)
            h_new = norm(h_new)
            h = F.relu(h_new) + h
            h = self.dropout(h)
        
        from torch_geometric.nn import global_mean_pool, global_max_pool
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        num_graphs = batch.max().item() + 1
        std_list = []
        for i in range(num_graphs):
            mask = (batch == i)
            if mask.sum() > 1:
                std_list.append(h[mask].std(dim=0))
            else:
                std_list.append(torch.zeros(h.size(1), device=h.device))
        std_pool = torch.stack(std_list)
        
        pooled = torch.cat([mean_pool, max_pool, std_pool], dim=1)
        logits = self.fc(pooled)
        
        return {"logits": logits}


class AttentionModel(nn.Module):
    """Attention-based pooling model."""
    
    def __init__(self, in_dim: int, hidden_dim: int, dropout: float = 0.3):
        super().__init__()
        self.proj = nn.Linear(in_dim, hidden_dim)
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.Tanh(),
            nn.Linear(hidden_dim // 2, 1),
        )
        self.fc1 = nn.Linear(hidden_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, 1)
        self.dropout = nn.Dropout(dropout)
        self.norm = nn.LayerNorm(hidden_dim)
    
    def forward(self, data):
        x, batch = data.x, data.batch
        
        h = F.relu(self.proj(x))
        
        attn_scores = self.attention(h)
        from torch_geometric.utils import softmax
        attn_weights = softmax(attn_scores, batch)
        
        from torch_geometric.nn import global_add_pool
        weighted = h * attn_weights
        pooled = global_add_pool(weighted, batch)
        
        h = F.relu(self.norm(self.fc1(pooled)))
        h = self.dropout(h)
        logits = self.fc2(h)
        
        return {"logits": logits}


class EdgeTypeGNN(nn.Module):
    """Edge-type aware GNN using RGCN."""
    
    def __init__(self, in_dim: int, hidden_dim: int, num_relations: int = 5,
                 num_layers: int = 2, dropout: float = 0.3):
        super().__init__()
        from torch_geometric.nn import RGCNConv
        
        self.proj = nn.Linear(in_dim, hidden_dim)
        
        self.convs = nn.ModuleList([
            RGCNConv(hidden_dim, hidden_dim, num_relations=num_relations)
            for _ in range(num_layers)
        ])
        self.norms = nn.ModuleList([
            nn.LayerNorm(hidden_dim) for _ in range(num_layers)
        ])
        
        self.fc = nn.Linear(hidden_dim * 3, 1)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data):
        x, edge_index, batch = data.x, data.edge_index, data.batch
        edge_type = data.edge_attr if hasattr(data, 'edge_attr') else None
        
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        
        for conv, norm in zip(self.convs, self.norms):
            h_new = conv(h, edge_index, edge_type)
            h_new = norm(h_new)
            h = F.relu(h_new) + h
            h = self.dropout(h)
        
        from torch_geometric.nn import global_mean_pool, global_max_pool
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        num_graphs = batch.max().item() + 1
        std_list = []
        for i in range(num_graphs):
            mask = (batch == i)
            if mask.sum() > 1:
                std_list.append(h[mask].std(dim=0))
            else:
                std_list.append(torch.zeros(h.size(1), device=h.device))
        std_pool = torch.stack(std_list)
        
        pooled = torch.cat([mean_pool, max_pool, std_pool], dim=1)
        logits = self.fc(pooled)
        
        return {"logits": logits}


class ShallowGNN(nn.Module):
    """Shallow GNN (1-2 layers) to avoid over-smoothing."""
    
    def __init__(self, in_dim: int, hidden_dim: int, num_layers: int = 1, dropout: float = 0.3):
        super().__init__()
        self.proj = nn.Linear(in_dim, hidden_dim)
        
        self.convs = nn.ModuleList([
            GCNConv(hidden_dim, hidden_dim) for _ in range(num_layers)
        ])
        self.norms = nn.ModuleList([
            nn.LayerNorm(hidden_dim) for _ in range(num_layers)
        ])
        
        self.fc = nn.Linear(hidden_dim * 3, 1)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data):
        x, edge_index, batch = data.x, data.edge_index, data.batch
        
        h = F.relu(self.proj(x))
        
        for conv, norm in zip(self.convs, self.norms):
            h_new = conv(h, edge_index)
            h_new = norm(h_new)
            h = F.relu(h_new) + h
            h = self.dropout(h)
        
        from torch_geometric.nn import global_mean_pool, global_max_pool
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        num_graphs = batch.max().item() + 1
        std_list = []
        for i in range(num_graphs):
            mask = (batch == i)
            if mask.sum() > 1:
                std_list.append(h[mask].std(dim=0))
            else:
                std_list.append(torch.zeros(h.size(1), device=h.device))
        std_pool = torch.stack(std_list)
        
        pooled = torch.cat([mean_pool, max_pool, std_pool], dim=1)
        logits = self.fc(pooled)
        
        return {"logits": logits}


def create_model(model_type: str, in_dim: int, hidden_dim: int, 
                 num_relations: int = 5, num_layers: int = 4,
                 heads: int = 4, dropout: float = 0.3) -> nn.Module:
    """Create model by type."""
    if model_type == "mlp":
        return GraphLevelMLP(in_dim, hidden_dim, dropout)
    elif model_type == "devign" or model_type == "ggnn":
        return DevignGGNN(in_dim, hidden_dim, num_relations, num_layers, dropout)
    elif model_type == "gcn":
        return GCNModel(in_dim, hidden_dim, num_layers, dropout)
    elif model_type == "gat":
        return GATModel(in_dim, hidden_dim, num_layers, heads, dropout)
    elif model_type == "transformer":
        return TransformerModel(in_dim, hidden_dim, num_layers, heads, dropout)
    elif model_type == "attention":
        return AttentionModel(in_dim, hidden_dim, dropout)
    elif model_type == "edge_type":
        return EdgeTypeGNN(in_dim, hidden_dim, num_relations, min(num_layers, 2), dropout)
    elif model_type == "shallow":
        return ShallowGNN(in_dim, hidden_dim, 1, dropout)
    else:
        raise ValueError(f"Unknown model type: {model_type}")


# ============================================================================
# TRAINING
# ============================================================================

def train_epoch(model, loader, optimizer, device, pos_weight: float = 1.0):
    """Train for one epoch with NaN protection."""
    model.train()
    total_loss = 0
    total_samples = 0
    nan_batches = 0
    
    # Clamp pos_weight to reasonable range
    pos_weight = max(0.1, min(pos_weight, 10.0))
    criterion = nn.BCEWithLogitsLoss(pos_weight=torch.tensor([pos_weight], device=device))
    
    for batch in loader:
        batch = batch.to(device)
        
        # Check for NaN/Inf in input features
        if hasattr(batch, "x") and batch.x is not None:
            if torch.isnan(batch.x).any() or torch.isinf(batch.x).any():
                # Replace NaN/Inf with 0
                batch.x = torch.where(
                    torch.isnan(batch.x) | torch.isinf(batch.x),
                    torch.zeros_like(batch.x),
                    batch.x
                )
        
        optimizer.zero_grad()
        
        try:
            out = model(batch)
            logits = out["logits"].view(-1)
            y = batch.y.view(-1).float()
            
            # Handle size mismatch
            if logits.shape != y.shape:
                min_len = min(logits.shape[0], y.shape[0])
                logits = logits[:min_len]
                y = y[:min_len]
            
            # Check for NaN in logits
            if torch.isnan(logits).any() or torch.isinf(logits).any():
                nan_batches += 1
                if nan_batches <= 5:
                    print(f"  [Warning] NaN/Inf in logits (batch {nan_batches}), skipping...")
                continue
            
            loss = criterion(logits, y)
            
            # Check for NaN loss
            if torch.isnan(loss) or torch.isinf(loss):
                nan_batches += 1
                if nan_batches <= 5:
                    print(f"  [Warning] NaN/Inf loss (batch {nan_batches}), skipping...")
                continue
            
            loss.backward()
            
            # Gradient clipping
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()
            
            total_loss += loss.item() * y.size(0)
            total_samples += y.size(0)
            
        except RuntimeError as e:
            if "nan" in str(e).lower() or "inf" in str(e).lower():
                nan_batches += 1
                continue
            raise
    
    if nan_batches > 0:
        print(f"  [Warning] Skipped {nan_batches} batches due to NaN/Inf")
    
    return total_loss / max(total_samples, 1)


@torch.no_grad()
def eval_epoch(model, loader, device, threshold: float = 0.5):
    """Evaluate model."""
    model.eval()
    preds = []
    targets = []
    
    for batch in loader:
        batch = batch.to(device)
        out = model(batch)
        logits = out["logits"].view(-1)
        probs = torch.sigmoid(logits)
        y = batch.y.view(-1)
        
        if probs.shape != y.shape:
            min_len = min(probs.shape[0], y.shape[0])
            probs = probs[:min_len]
            y = y[:min_len]
        
        preds.append(probs.cpu().numpy())
        targets.append(y.cpu().numpy())
    
    if len(preds) == 0:
        return {"acc": 0.0, "f1": 0.0, "auc": 0.0}, np.array([]), np.array([])
    
    preds = np.concatenate(preds)
    targets = np.concatenate(targets)
    
    binary_preds = (preds > threshold).astype(int)
    acc = (binary_preds == targets).mean()
    
    metrics = {"acc": acc}
    
    if HAS_SKLEARN:
        metrics["f1"] = f1_score(targets, binary_preds, zero_division=0)
        metrics["precision"] = precision_score(targets, binary_preds, zero_division=0)
        metrics["recall"] = recall_score(targets, binary_preds, zero_division=0)
        try:
            if len(np.unique(targets)) > 1:
                metrics["auc"] = roc_auc_score(targets, preds)
            else:
                metrics["auc"] = 0.5
        except:
            metrics["auc"] = 0.0
    
    return metrics, preds, targets


def find_optimal_threshold(targets: np.ndarray, preds: np.ndarray) -> Tuple[float, float]:
    """Find threshold that maximizes F1."""
    best_f1 = 0
    best_thresh = 0.5
    
    for thresh in np.arange(0.1, 0.9, 0.05):
        binary = (preds >= thresh).astype(int)
        f1 = f1_score(targets, binary, zero_division=0)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = thresh
    
    return best_thresh, best_f1


# ============================================================================
# ARGUMENT PARSER (matches Devign_baseline.py)
# ============================================================================

def build_parser():
    parser = argparse.ArgumentParser(description="Vulnerability Detection Training")
    
    # Data Config (matches Devign_baseline.py)
    parser.add_argument("--cache-dir", type=str, required=True,
                       help="Path to cache directory")
    parser.add_argument("--dataset-name", type=str, required=True,
                       help="Dataset name (e.g., devign_normfunc_v2)")
    parser.add_argument("--cache-signature", type=str, required=True,
                       help="Cache signature hash")
    parser.add_argument("--vocab-dir", type=str, required=True,
                       help="Path to vocabulary directory")
    
    # Manifests (matches Devign_baseline.py)
    parser.add_argument("--train-manifest", type=str, required=True,
                       help="Path to training manifest CSV")
    parser.add_argument("--val-manifest", type=str, required=True,
                       help="Path to validation manifest CSV")
    parser.add_argument("--test-manifest", type=str, required=True,
                       help="Path to test manifest CSV")
    
    # Model Architecture
    parser.add_argument("--model-type", type=str, default="mlp",
                       choices=["mlp", "devign", "ggnn", "gcn", "gat", "transformer", 
                               "attention", "edge_type", "shallow"],
                       help="Model architecture to use")
    parser.add_argument("--edge-mode", type=str, default=None,
                       choices=["full_filtered", "simplified", "full"],
                       help="Edge type mode (for documentation - auto-detected from vocab)")
    parser.add_argument("--heads", type=int, default=4,
                       help="Number of attention heads (for GAT/Transformer)")
    
    # Hyperparameters (matches Devign_baseline.py)
    parser.add_argument("--hidden-dim", type=int, default=128)
    parser.add_argument("--layers", type=int, default=4)
    parser.add_argument("--lr", type=float, default=1e-3)
    parser.add_argument("--batch-size", type=int, default=64)
    parser.add_argument("--dropout", type=float, default=0.3)
    parser.add_argument("--epochs", type=int, default=100)
    parser.add_argument("--weight-decay", type=float, default=1e-4)
    parser.add_argument("--patience", type=int, default=15)
    
    # Other
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--num-workers", type=int, default=4)
    parser.add_argument("--output-dir", type=str, default="results")
    
    return parser


def make_split_dir(cache_dir: Path, dataset_name: str, cache_sig: str, split: str) -> Path:
    """Construct path to split directory."""
    return cache_dir / dataset_name / split / cache_sig


# ============================================================================
# MAIN
# ============================================================================

def run(args):
    torch.backends.cudnn.benchmark = True
    set_seed(args.seed)
    
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"[Init] Device: {device}")
    print(f"[Init] Model: {args.model_type.upper()} | Layers: {args.layers} | Dim: {args.hidden_dim}")
    
    # 1. Setup paths
    cache_root = Path(args.cache_dir)
    train_dir = make_split_dir(cache_root, args.dataset_name, args.cache_signature, "train")
    val_dir = make_split_dir(cache_root, args.dataset_name, args.cache_signature, "valid")
    test_dir = make_split_dir(cache_root, args.dataset_name, args.cache_signature, "test")
    
    out_dir = Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    
    # 2. Load meta info
    sig_path = train_dir / "meta" / "signature.json"
    if not sig_path.exists():
        raise FileNotFoundError(f"Signature not found: {sig_path}")
    
    with sig_path.open("r") as f:
        sig = json.load(f)
    input_dim = sig["features"]["final_x_dim"]
    
    # Validate edge mode consistency between vocab and cache
    validate_edge_mode_consistency(Path(args.vocab_dir), cache_root, args.dataset_name)
    
    num_rels, edge_types = ensure_vocabs(args.vocab_dir)
    print(f"[Data] Input dim: {input_dim}, Relations: {num_rels}")
    
    # 3. Create datasets
    print(f"[Data] Loading training data from: {train_dir}")
    train_ds = CachedDataset(train_dir, args.train_manifest)
    print(f"[Data] Loading validation data from: {val_dir}")
    val_ds = CachedDataset(val_dir, args.val_manifest)
    print(f"[Data] Loading test data from: {test_dir}")
    test_ds = CachedDataset(test_dir, args.test_manifest)
    
    pos_weight = train_ds.get_pos_weight()
    print(f"[Data] Train: {len(train_ds)} | Val: {len(val_ds)} | Test: {len(test_ds)}")
    print(f"[Data] Pos weight: {pos_weight:.4f}")
    
    # Validate data - check first few samples for NaN/Inf
    print("[Data] Validating data quality...")
    nan_count = 0
    inf_count = 0
    zero_count = 0
    for i in range(min(50, len(train_ds))):
        data = train_ds[i]
        if hasattr(data, "x") and data.x is not None:
            x = data.x
            if torch.isnan(x).any():
                nan_count += 1
            if torch.isinf(x).any():
                inf_count += 1
            if (x == 0).all():
                zero_count += 1
    
    if nan_count > 0 or inf_count > 0:
        print(f"[Data] WARNING: Found {nan_count} samples with NaN, {inf_count} with Inf in first 50 samples!")
        print(f"[Data] NaN/Inf values will be replaced with 0 during training.")
    elif zero_count > 25:
        print(f"[Data] WARNING: {zero_count}/50 samples have all-zero features!")
        print(f"[Data] This may indicate embedding issues (unknown tokens).")
    else:
        print("[Data] Data quality OK - no NaN/Inf detected in sample.")
    
    # 4. Create data loaders
    train_loader = DataLoader(train_ds, batch_size=args.batch_size, shuffle=True, 
                              num_workers=args.num_workers)
    val_loader = DataLoader(val_ds, batch_size=args.batch_size, shuffle=False,
                           num_workers=args.num_workers)
    test_loader = DataLoader(test_ds, batch_size=args.batch_size, shuffle=False,
                            num_workers=args.num_workers)
    
    # 5. Create model
    model = create_model(
        args.model_type, input_dim, args.hidden_dim,
        num_relations=num_rels, num_layers=args.layers,
        heads=args.heads, dropout=args.dropout
    ).to(device)
    
    num_params = sum(p.numel() for p in model.parameters())
    print(f"[Model] Parameters: {num_params:,}")
    
    # 6. Optimizer and scheduler
    optimizer = torch.optim.AdamW(model.parameters(), lr=args.lr, weight_decay=args.weight_decay)
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode='max', factor=0.5, patience=5)
    
    # 7. Training loop
    best_val_auc = 0
    best_val_f1 = 0
    best_threshold = 0.5
    patience_counter = 0
    
    print(f"\n[Train] Starting training for {args.epochs} epochs...")
    
    for epoch in range(1, args.epochs + 1):
        start_time = time.time()
        
        train_loss = train_epoch(model, train_loader, optimizer, device, pos_weight)
        val_metrics, val_preds, val_targets = eval_epoch(model, val_loader, device)
        
        # Find optimal threshold on validation
        curr_thresh, _ = find_optimal_threshold(val_targets, val_preds)
        val_metrics_opt, _, _ = eval_epoch(model, val_loader, device, curr_thresh)
        
        scheduler.step(val_metrics["auc"])
        
        epoch_time = time.time() - start_time
        
        print(f"Epoch {epoch:3d} | "
              f"Loss: {train_loss:.4f} | "
              f"Val AUC: {val_metrics['auc']:.4f} | "
              f"Val F1@0.5: {val_metrics['f1']:.4f} | "
              f"Val F1@{curr_thresh:.2f}: {val_metrics_opt['f1']:.4f} | "
              f"Time: {epoch_time:.1f}s")
        
        # Save best model
        if val_metrics["auc"] > best_val_auc:
            best_val_auc = val_metrics["auc"]
            best_val_f1 = val_metrics_opt["f1"]
            best_threshold = curr_thresh
            patience_counter = 0
            torch.save(model.state_dict(), out_dir / "best_model.pt")
            
            with (out_dir / "best_threshold.txt").open("w") as f:
                f.write(str(best_threshold))
        else:
            patience_counter += 1
            if patience_counter >= args.patience:
                print(f"\n[Train] Early stopping at epoch {epoch}")
                break
    
    # 8. Final test
    print(f"\n[Test] Evaluating best model (threshold={best_threshold:.2f})...")
    
    if (out_dir / "best_model.pt").exists():
        model.load_state_dict(torch.load(out_dir / "best_model.pt", weights_only=True))
    
    test_metrics, test_preds, test_targets = eval_epoch(model, test_loader, device, best_threshold)
    
    print(f"\n{'='*60}")
    print("FINAL TEST RESULTS")
    print(f"{'='*60}")
    print(f"Test Accuracy:  {test_metrics['acc']:.4f}")
    print(f"Test F1 Score:  {test_metrics.get('f1', 0):.4f}")
    print(f"Test Precision: {test_metrics.get('precision', 0):.4f}")
    print(f"Test Recall:    {test_metrics.get('recall', 0):.4f}")
    print(f"Test ROC-AUC:   {test_metrics.get('auc', 0):.4f}")
    print(f"Threshold:      {best_threshold:.2f}")
    
    # Save results
    test_metrics["best_threshold"] = float(best_threshold)
    test_metrics["best_val_auc"] = float(best_val_auc)
    
    with (out_dir / "test_results.json").open("w") as f:
        json.dump(test_metrics, f, indent=2)
    
    print(f"\n[Done] Results saved to: {out_dir}")


if __name__ == "__main__":
    args = build_parser().parse_args()
    run(args)

# ============================================================================
# USAGE EXAMPLES
# ============================================================================

# EDGE MODE REFERENCE:
#   full_filtered: 13 edge types (RECOMMENDED for vulnerability detection)
#   simplified:     5 edge types (Original Devign: AST, CFG, DFG_READ, DFG_WRITE, NCS)
#   full:          15 edge types (includes CONTAINS, SOURCE_FILE)



# ============================================================================
# USAGE EXAMPLES
# ============================================================================

"""
# Graph-Level MLP (Best Model)
python step2_train.py \
  --model-type mlp \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehot" \
  --cache-signature "2f8d034cd97733a8" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 64 \
  --epochs 100 \
  --batch-size 512 \
  --output-dir "results_mlp_only_onehot"

# Devign GGNN (Original)
python step2_train.py \
  --model-type devign \
  --edge-mode full \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full" \
  --cache-signature "devign_onehotonly_full" \
  --vocab-dir "./Clean_exports/devign_vocab_full_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 1400 \
  --layers 2 \
  --epochs 100 \
  --batch-size 32 \
  --output-dir "full_filtered__only_onehot_devign"

# Devign GGNN (Original) Full cache

python step2_train.py \
  --model-type devign \
  --edge-mode full_filtered \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full" \
  --cache-signature "devign_onehotonly_full" \
  --vocab-dir "./Clean_exports/devign_vocab_full_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 32 \
  --layers 32 \
  --epochs 100 \
  --batch-size 32 \
  --output-dir "full_only_onehot_devign"


# GCN Model
python step2_train.py \
  --model-type gcn \
  --edge-mode full_filtered \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 256 \
  --epochs 100 \
  --batch-size 128 \
  --output-dir "full_filtered__only_onehot_results_gcn" 

# GAT Model  
python step2_train.py \
  --model-type gat \
  --edge-mode full_filtered \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 256 \
  --epochs 100 \
  --batch-size 128 \
  --output-dir "full_filtered__only_onehot_results_gat" 

# Transformer Model
python step2_train.py \
  --model-type transformer \
  --heads 16 \
  --edge-mode full_filtered \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full" \
  --cache-signature "devign_onehotonly_full" \
  --vocab-dir "./Clean_exports/devign_vocab_full_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 128 \
  --layers 4 \
  --epochs 100 \
  --batch-size 128 \
  --output-dir "full_only_onehot_devign_transformer"

# Attention Model
python step2_train.py \
  --model-type attention \
  --edge-mode full \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full" \
  --cache-signature "devign_onehotonly_full" \
  --vocab-dir "./Clean_exports/devign_vocab_full_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 128 \
  --layers 4 \
  --epochs 100 \
  --batch-size 128 \
  --output-dir "full_only_onehot_devign_attention"
 

# Edge-Type GNN
python step2_train.py \
  --model-type edge_type \
  --edge-mode full_filtered \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 64 \
  --layers 8 \
  --epochs 100 \
  --batch-size 512 \
  --output-dir "full_filtered__only_onehot_results_edge_type" 

# Shallow GNN
python step2_train.py \
  --model-type shallow \
  --edge-mode full_filtered \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 32 \
  --layers 8 \
  --epochs 100 \
  --batch-size 512 \
  --output-dir "full_filtered__only_onehot_results_shallow" 
"""
