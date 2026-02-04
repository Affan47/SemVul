#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
step2_train_advanced.py - Train advanced GNN architectures for vulnerability detection

Uses the EXACT model implementations from:
  - hgt_models.py (HGTDevignModel)
  - hypergraph_models.py (HyperDevignModel - Dual Attention)
  - multiview_models.py (MultiViewGGNN)

Interface matches Devign_baseline.py exactly.

Supported Models:
  - 'multiview': Multi-view GGNN (separate AST/CFG/DFG encoders + attention fusion)
  - 'hgt':       Heterogeneous Graph Transformer
  - 'hypergraph': Dual-Attention Model (GATv2 + Transformer with gated fusion)

Usage:
    python step2_train_advanced.py \
        --model-type multiview \
        --cache-dir /path/to/cache \
        --dataset-name devign_normfunc_v2 \
        --cache-signature YOUR_SIGNATURE \
        --vocab-dir /path/to/vocab \
        --train-manifest /path/to/manifest_train.csv \
        --val-manifest /path/to/manifest_validation.csv \
        --test-manifest /path/to/manifest_test.csv \
        --hidden-dim 200 \
        --layers 4 \
        --epochs 100 \
        --output-dir results_multiview
"""

import argparse
import csv
import json
import random
import time
import warnings
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset as TorchDataset
from torch_geometric.data import Data
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GATv2Conv, TransformerConv, GatedGraphConv, HGTConv
from torch_geometric.utils import to_dense_batch, sort_edge_index

try:
    from sklearn.metrics import roc_auc_score, f1_score, precision_score, recall_score
    HAS_SKLEARN = True
except ImportError:
    HAS_SKLEARN = False


# ============================================================================
# REPRODUCIBILITY
# ============================================================================

def set_seed(seed: int = 42):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


# ============================================================================
# DATASET (matches Devign_baseline.py)
# ============================================================================

class CachedDataset(TorchDataset):
    """Dataset that loads cached .pt graphs from a cache directory."""
    
    def __init__(self, cache_dir: Path, manifest_path: Optional[Path] = None):
        super().__init__()
        self.cache_dir = Path(cache_dir)
        self.pt_paths = []
        self.num_pos = 0
        self.num_neg = 0
        
        index_csv = self.cache_dir / "meta" / "index.csv"
        if not index_csv.is_file():
            raise FileNotFoundError(f"index.csv not found at: {index_csv}")
        
        manifest_keys = None
        if manifest_path and Path(manifest_path).exists():
            manifest_keys = set()
            with Path(manifest_path).open("r", encoding="utf-8") as f:
                reader = csv.DictReader(f)
                for row in reader:
                    fid = row.get("function_id") or row.get("fid")
                    if fid:
                        manifest_keys.add(fid.strip())
        
        with index_csv.open("r", newline="", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            for row in reader:
                rel_path = row.get("rel_path") or row.get("path") or row.get("pt_path")
                if rel_path is None:
                    continue
                
                row_func_id = row.get("function_id", "").strip()
                if manifest_keys is not None:
                    if row_func_id not in manifest_keys:
                        continue
                
                self.pt_paths.append(self.cache_dir / rel_path)
                
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
        
        return data


def ensure_vocabs(vocab_dir: Path) -> int:
    vocab_dir = Path(vocab_dir)
    rel_vocab_path = vocab_dir / "devign_rel_vocab.json"
    
    if not rel_vocab_path.is_file():
        rel_vocab_path = vocab_dir / "edge_type_vocab.json"
    
    if not rel_vocab_path.is_file():
        return 5
    
    with rel_vocab_path.open("r", encoding="utf-8") as f:
        rel_vocab = json.load(f)
    
    return len(rel_vocab)


# ============================================================================
# SHARED: Devign Conv Readout Head
# ============================================================================

class DevignConvHead(nn.Module):
    """
    Devign's Hierarchical Conv Readout Module.
    Compares initial and final node representations through conv layers.
    """
    
    def __init__(self, hidden_dim: int, dropout: float = 0.1):
        super().__init__()
        self.hidden_dim = int(hidden_dim)
        
        # Z path (concatenated initial + final)
        self.conv1_z = nn.Conv1d(hidden_dim * 2, hidden_dim, kernel_size=3, padding=1)
        self.conv2_z = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.mlp_z = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        
        # Y path (final only)
        self.conv1_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=3, padding=1)
        self.conv2_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.mlp_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        
        self.pool = nn.MaxPool1d(kernel_size=2, stride=2)
        self.dropout = nn.Dropout(dropout)
        
        self.bn_z = nn.BatchNorm1d(hidden_dim)
        self.bn_y = nn.BatchNorm1d(hidden_dim)
    
    def forward(
        self,
        h_input: torch.Tensor,
        h_final: torch.Tensor,
        batch: torch.Tensor,
    ) -> torch.Tensor:
        h_cat = torch.cat([h_input, h_final], dim=1)
        
        z_dense, mask = to_dense_batch(h_cat, batch)
        y_dense, _ = to_dense_batch(h_final, batch)
        
        z = z_dense.transpose(1, 2)
        y = y_dense.transpose(1, 2)
        
        # Handle small graphs
        min_size = 4
        if z.size(2) < min_size:
            pad_size = min_size - z.size(2)
            z = F.pad(z, (0, pad_size))
            y = F.pad(y, (0, pad_size))
            mask_float = F.pad(mask.unsqueeze(1).float(), (0, pad_size))
        else:
            mask_float = mask.unsqueeze(1).float()
        
        # Layer 1
        z = self.pool(F.relu(self.conv1_z(z)))
        y = self.pool(F.relu(self.conv1_y(y)))
        mask_pooled = F.max_pool1d(mask_float, kernel_size=2, stride=2)
        
        # Layer 2
        z = self.pool(F.relu(self.conv2_z(z)))
        y = self.pool(F.relu(self.conv2_y(y)))
        mask_pooled = F.max_pool1d(mask_pooled, kernel_size=2, stride=2)
        
        # Batch norm
        z = self.bn_z(z)
        y = self.bn_y(y)
        z = self.dropout(z)
        y = self.dropout(y)
        
        # MLP
        z_prime = self.mlp_z(z)
        y_prime = self.mlp_y(y)
        
        # Interaction
        h_mult = z_prime * y_prime
        
        # Masked mean pooling
        mask_bool = (mask_pooled > 0.5)
        h_mult = h_mult * mask_bool.float()
        sum_h = torch.sum(h_mult, dim=2)
        counts = torch.sum(mask_bool.float(), dim=2).clamp(min=1.0)
        
        return sum_h / counts


# ============================================================================
# MODEL 1: MultiViewGGNN (from multiview_models.py)
# ============================================================================

class ViewEncoder(nn.Module):
    """Processes a single graph view using Gated Graph Neural Network."""
    
    def __init__(self, hidden_dim: int, num_layers: int = 4, dropout: float = 0.2):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.ggnn = GatedGraphConv(out_channels=hidden_dim, num_layers=num_layers)
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor) -> torch.Tensor:
        if edge_index.size(1) == 0:
            return self.norm(x)
        
        edge_index = sort_edge_index(edge_index)
        h = self.ggnn(x, edge_index)
        h = self.norm(h)
        h = self.dropout(h)
        return h + x


class NodeConditionedAttentionFusion(nn.Module):
    """Fuses representations from multiple views using node-conditioned attention."""
    
    def __init__(self, hidden_dim: int, num_views: int = 3):
        super().__init__()
        self.num_views = num_views
        self.hidden_dim = hidden_dim
        
        self.query_net = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.Tanh(),
        )
        self.key_proj = nn.Linear(hidden_dim, hidden_dim)
        self.scale = hidden_dim ** -0.5
    
    def forward(
        self,
        view_embeddings: torch.Tensor,
        node_context: torch.Tensor,
    ) -> Tuple[torch.Tensor, torch.Tensor]:
        query = self.query_net(node_context)
        keys = self.key_proj(view_embeddings)
        
        attn_scores = torch.bmm(query.unsqueeze(1), keys.transpose(1, 2))
        attn_scores = attn_scores.squeeze(1) * self.scale
        attention = F.softmax(attn_scores, dim=-1)
        fused = (view_embeddings * attention.unsqueeze(-1)).sum(dim=1)
        
        return fused, attention


class MultiViewGGNN(nn.Module):
    """
    Multi-View Graph Neural Network for Vulnerability Detection.
    
    Separates CPG into semantic views (AST, CFG, DFG), processes each
    with a dedicated GGNN encoder, and fuses using attention.
    """
    
    DEFAULT_EDGE_CONFIG = {
        'ast': [0],
        'cfg': [1, 4],
        'dfg': [2, 3],
    }
    
    def __init__(
        self,
        in_dim: int,
        hidden_dim: int,
        num_layers: int = 4,
        dropout: float = 0.2,
        edge_type_config: Optional[Dict[str, List[int]]] = None,
        **kwargs
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_layers = num_layers
        self.edge_type_config = edge_type_config or self.DEFAULT_EDGE_CONFIG
        self.num_views = len(self.edge_type_config)
        
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        self.view_encoders = nn.ModuleDict()
        for view_name in self.edge_type_config.keys():
            self.view_encoders[view_name] = ViewEncoder(
                hidden_dim=hidden_dim,
                num_layers=num_layers,
                dropout=dropout,
            )
        
        self.fusion = NodeConditionedAttentionFusion(
            hidden_dim=hidden_dim,
            num_views=self.num_views,
        )
        
        self.readout = DevignConvHead(hidden_dim, dropout)
        
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
        
        self._init_weights()
    
    def _init_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.trunc_normal_(module.weight, std=0.02)
                if module.bias is not None:
                    nn.init.zeros_(module.bias)
    
    def _get_view_mask(self, edge_type: torch.Tensor, view_types: List[int]) -> torch.Tensor:
        mask = torch.zeros_like(edge_type, dtype=torch.bool)
        for t in view_types:
            mask = mask | (edge_type == t)
        return mask
    
    def forward(self, data) -> Dict[str, torch.Tensor]:
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch
        edge_type = getattr(data, "edge_type", None)
        
        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)
        
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        else:
            edge_type = edge_type.long()
        
        h0 = self.input_proj(x)
        
        view_outputs = []
        for view_name, view_types in self.edge_type_config.items():
            mask = self._get_view_mask(edge_type, view_types)
            edge_index_view = edge_index[:, mask]
            h_view = self.view_encoders[view_name](h0, edge_index_view)
            view_outputs.append(h_view)
        
        h_stacked = torch.stack(view_outputs, dim=1)
        h_fused, attention_weights = self.fusion(h_stacked, node_context=h0)
        
        graph_emb = self.readout(h_input=h0, h_final=h_fused, batch=batch)
        logits = self.classifier(graph_emb)
        
        return {"logits": logits}


# ============================================================================
# MODEL 2: HGTDevignModel (from hgt_models.py)
# ============================================================================

class HGTBlock(nn.Module):
    """Heterogeneous Graph Transformer block with proper residuals."""
    
    def __init__(
        self,
        hidden_dim: int,
        metadata: Tuple[List[str], List[Tuple[str, str, str]]],
        heads: int = 4,
        dropout: float = 0.2,
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.norm1 = nn.LayerNorm(hidden_dim)
        
        self.conv = HGTConv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            metadata=metadata,
            heads=heads,
        )
        
        self.dropout1 = nn.Dropout(dropout)
        self.norm2 = nn.LayerNorm(hidden_dim)
        self.ffn = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim * 4),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim * 4, hidden_dim),
            nn.Dropout(dropout),
        )
    
    def forward(
        self,
        x_dict: Dict[str, torch.Tensor],
        edge_index_dict: Dict[Tuple[str, str, str], torch.Tensor],
    ) -> Dict[str, torch.Tensor]:
        x_in = x_dict['0']
        x_normed = self.norm1(x_in)
        x_dict_normed = {'0': x_normed}
        
        out_dict = self.conv(x_dict_normed, edge_index_dict)
        h = out_dict['0']
        h = F.elu(h)
        h = self.dropout1(h)
        x = x_in + h
        
        x_res = x
        h = self.norm2(x)
        h = self.ffn(h)
        x = x_res + h
        
        return {'0': x}


class HGTDevignModel(nn.Module):
    """
    Heterogeneous Graph Transformer for Vulnerability Detection.
    
    Adapts HGT for CPGs by treating edge types as relation types
    in a heterogeneous graph with single node type.
    """
    
    def __init__(
        self,
        in_dim: int,
        hidden_dim: int,
        num_relations: int,
        num_layers: int = 4,
        heads: int = 4,
        dropout: float = 0.2,
        **kwargs
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_layers = num_layers
        self.num_relations = num_relations
        
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        self.node_types = ['0']
        self.edge_types = [('0', str(r), '0') for r in range(num_relations)]
        self.metadata = (self.node_types, self.edge_types)
        
        self.blocks = nn.ModuleList([
            HGTBlock(
                hidden_dim=hidden_dim,
                metadata=self.metadata,
                heads=heads,
                dropout=dropout,
            )
            for _ in range(num_layers)
        ])
        
        self.final_norm = nn.LayerNorm(hidden_dim)
        self.readout = DevignConvHead(hidden_dim, dropout)
        
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
        
        self._init_weights()
    
    def _init_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.trunc_normal_(module.weight, std=0.02)
                if module.bias is not None:
                    nn.init.zeros_(module.bias)
            elif isinstance(module, nn.LayerNorm):
                nn.init.ones_(module.weight)
                nn.init.zeros_(module.bias)
    
    def _build_edge_index_dict(
        self,
        edge_index: torch.Tensor,
        edge_type: torch.Tensor,
    ) -> Dict[Tuple[str, str, str], torch.Tensor]:
        edge_index_dict = {}
        
        for r in range(self.num_relations):
            mask = (edge_type == r)
            edge_key = ('0', str(r), '0')
            
            if mask.any():
                edge_index_dict[edge_key] = edge_index[:, mask]
            else:
                edge_index_dict[edge_key] = torch.empty(
                    (2, 0), dtype=torch.long, device=edge_index.device
                )
        
        return edge_index_dict
    
    def forward(self, data) -> Dict[str, torch.Tensor]:
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch
        edge_type = getattr(data, "edge_type", None)
        
        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)
        
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        else:
            edge_type = edge_type.long().clamp(0, self.num_relations - 1)
        
        h0 = self.input_proj(x)
        
        x_dict = {'0': h0}
        edge_index_dict = self._build_edge_index_dict(edge_index, edge_type)
        
        for block in self.blocks:
            x_dict = block(x_dict, edge_index_dict)
        
        h = x_dict['0']
        h = self.final_norm(h)
        
        graph_emb = self.readout(h_input=h0, h_final=h, batch=batch)
        logits = self.classifier(graph_emb)
        
        return {"logits": logits}


# ============================================================================
# MODEL 3: HyperDevignModel / Dual-Attention (from hypergraph_models.py)
# ============================================================================

class DualAttentionBlock(nn.Module):
    """
    Dual-branch attention block combining local (GATv2) and global (Transformer).
    Uses learnable gated fusion.
    """
    
    def __init__(
        self,
        hidden_dim: int,
        heads: int = 4,
        dropout: float = 0.2,
        residual_scale: float = 1.0,
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.residual_scale = residual_scale
        
        effective_heads = min(heads, hidden_dim // 16)
        effective_heads = max(1, effective_heads)
        if effective_heads != heads:
            warnings.warn(f"Reduced heads from {heads} to {effective_heads}")
        self.heads = effective_heads
        
        self.norm_local = nn.LayerNorm(hidden_dim)
        self.norm_global = nn.LayerNorm(hidden_dim)
        
        self.local_attn = GATv2Conv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            heads=effective_heads,
            concat=False,
            dropout=dropout,
            edge_dim=hidden_dim,
            add_self_loops=True,
        )
        
        self.global_attn = TransformerConv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            heads=effective_heads,
            concat=False,
            dropout=dropout,
            edge_dim=hidden_dim,
        )
        
        self.gate_linear = nn.Linear(hidden_dim * 2, hidden_dim)
        nn.init.zeros_(self.gate_linear.weight)
        nn.init.zeros_(self.gate_linear.bias)
        
        self.norm_fusion = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
        
        self.norm_ffn = nn.LayerNorm(hidden_dim)
        self.ffn = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim * 2),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.Dropout(dropout),
        )
        
        nn.init.xavier_uniform_(self.ffn[0].weight, gain=0.1)
        nn.init.zeros_(self.ffn[0].bias)
        nn.init.xavier_uniform_(self.ffn[3].weight, gain=0.1)
        nn.init.zeros_(self.ffn[3].bias)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_attr: torch.Tensor,
    ) -> torch.Tensor:
        x_res = x
        
        h_local = self.norm_local(x)
        h_local = self.local_attn(h_local, edge_index, edge_attr=edge_attr)
        h_local = F.gelu(h_local)
        
        h_global = self.norm_global(x)
        h_global = self.global_attn(h_global, edge_index, edge_attr=edge_attr)
        h_global = F.gelu(h_global)
        
        gate_input = torch.cat([h_local, h_global], dim=-1)
        gate = torch.sigmoid(self.gate_linear(gate_input))
        
        h_fused = (1 - gate) * h_local + gate * h_global
        h_fused = self.norm_fusion(h_fused)
        h_fused = self.dropout(h_fused)
        
        x = x_res + self.residual_scale * h_fused
        
        x_res = x
        h_ffn = self.norm_ffn(x)
        h_ffn = self.ffn(h_ffn)
        x = x_res + self.residual_scale * h_ffn
        
        return x


class HyperDevignModel(nn.Module):
    """
    Dual-Attention Model for Vulnerability Detection.
    
    Combines local (GATv2) and global (Transformer) attention mechanisms
    with edge-type awareness for processing Code Property Graphs.
    """
    
    def __init__(
        self,
        in_dim: int,
        hidden_dim: int,
        num_relations: int,
        num_layers: int = 4,
        heads: int = 4,
        dropout: float = 0.2,
        **kwargs
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_layers = num_layers
        self.num_relations = num_relations
        
        effective_heads = min(heads, hidden_dim // 16)
        effective_heads = max(1, effective_heads)
        if effective_heads != heads:
            warnings.warn(f"Adjusted heads from {heads} to {effective_heads}")
        self.heads = effective_heads
        
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        self.edge_embedding = nn.Embedding(num_relations, hidden_dim)
        nn.init.normal_(self.edge_embedding.weight, mean=0.0, std=0.02)
        
        residual_scale = 1.0 / (2 * num_layers) ** 0.5
        
        self.blocks = nn.ModuleList([
            DualAttentionBlock(
                hidden_dim=hidden_dim,
                heads=effective_heads,
                dropout=dropout,
                residual_scale=residual_scale,
            )
            for _ in range(num_layers)
        ])
        
        self.final_norm = nn.LayerNorm(hidden_dim)
        self.readout = DevignConvHead(hidden_dim, dropout)
        
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
        
        self._init_weights()
    
    def _init_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.trunc_normal_(module.weight, std=0.02)
                if module.bias is not None:
                    nn.init.zeros_(module.bias)
            elif isinstance(module, nn.LayerNorm):
                nn.init.ones_(module.weight)
                nn.init.zeros_(module.bias)
        
        if hasattr(self.classifier[-1], 'weight'):
            nn.init.normal_(self.classifier[-1].weight, std=0.01)
            nn.init.zeros_(self.classifier[-1].bias)
    
    def forward(self, data) -> Dict[str, torch.Tensor]:
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch
        edge_type = getattr(data, "edge_type", None)
        
        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)
        
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        else:
            edge_type = edge_type.long().clamp(0, self.num_relations - 1)
        
        h0 = self.input_proj(x)
        h = h0
        
        edge_attr = self.edge_embedding(edge_type)
        
        for block in self.blocks:
            h = block(h, edge_index, edge_attr)
        
        h = self.final_norm(h)
        graph_emb = self.readout(h_input=h0, h_final=h, batch=batch)
        logits = self.classifier(graph_emb)
        
        return {"logits": logits}


# ============================================================================
# MODEL FACTORY
# ============================================================================

def create_advanced_model(
    model_type: str,
    in_dim: int,
    hidden_dim: int,
    num_relations: int = 5,
    num_layers: int = 4,
    heads: int = 4,
    dropout: float = 0.2,
) -> nn.Module:
    """Create advanced model by type."""
    if model_type == "multiview":
        return MultiViewGGNN(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_layers=num_layers,
            dropout=dropout,
        )
    elif model_type == "hgt":
        return HGTDevignModel(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_relations=num_relations,
            num_layers=num_layers,
            heads=heads,
            dropout=dropout,
        )
    elif model_type == "hypergraph":
        return HyperDevignModel(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_relations=num_relations,
            num_layers=num_layers,
            heads=heads,
            dropout=dropout,
        )
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
            
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()
            
            total_loss += loss.item() * y.size(0)
            total_samples += y.size(0)
        except RuntimeError as e:
            if "out of memory" in str(e).lower():
                torch.cuda.empty_cache()
                print("  [OOM] Skipping batch")
                continue
            if "nan" in str(e).lower() or "inf" in str(e).lower():
                nan_batches += 1
                continue
            raise
    
    if nan_batches > 0:
        print(f"  [Warning] Skipped {nan_batches} batches due to NaN/Inf")
    
    return total_loss / max(total_samples, 1)


@torch.no_grad()
def eval_epoch(model, loader, device, threshold: float = 0.5):
    model.eval()
    preds, targets = [], []
    
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
    parser = argparse.ArgumentParser(description="Advanced Vulnerability Detection Models")
    
    # Data Config
    parser.add_argument("--cache-dir", type=str, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--vocab-dir", type=str, required=True)
    
    # Manifests
    parser.add_argument("--train-manifest", type=str, required=True)
    parser.add_argument("--val-manifest", type=str, required=True)
    parser.add_argument("--test-manifest", type=str, required=True)
    
    # Model
    parser.add_argument("--model-type", type=str, required=True,
                       choices=["multiview", "hgt", "hypergraph"])
    parser.add_argument("--heads", type=int, default=4)
    
    # Hyperparameters
    parser.add_argument("--hidden-dim", type=int, default=200)
    parser.add_argument("--layers", type=int, default=4)
    parser.add_argument("--lr", type=float, default=2e-4)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--dropout", type=float, default=0.2)
    parser.add_argument("--epochs", type=int, default=100)
    parser.add_argument("--weight-decay", type=float, default=1e-5)
    parser.add_argument("--patience", type=int, default=15)
    
    # Other
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--num-workers", type=int, default=4)
    parser.add_argument("--output-dir", type=str, default="results")
    
    return parser


def make_split_dir(cache_dir: Path, dataset_name: str, cache_sig: str, split: str) -> Path:
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
    
    cache_root = Path(args.cache_dir)
    train_dir = make_split_dir(cache_root, args.dataset_name, args.cache_signature, "train")
    val_dir = make_split_dir(cache_root, args.dataset_name, args.cache_signature, "valid")
    test_dir = make_split_dir(cache_root, args.dataset_name, args.cache_signature, "test")
    
    out_dir = Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    
    sig_path = train_dir / "meta" / "signature.json"
    if not sig_path.exists():
        raise FileNotFoundError(f"Signature not found: {sig_path}")
    
    with sig_path.open("r") as f:
        sig = json.load(f)
    input_dim = sig["features"]["final_x_dim"]
    
    num_rels = ensure_vocabs(args.vocab_dir)
    print(f"[Data] Input dim: {input_dim}, Relations: {num_rels}")
    
    print(f"[Data] Loading datasets...")
    train_ds = CachedDataset(train_dir, args.train_manifest)
    val_ds = CachedDataset(val_dir, args.val_manifest)
    test_ds = CachedDataset(test_dir, args.test_manifest)
    
    pos_weight = train_ds.get_pos_weight()
    print(f"[Data] Train: {len(train_ds)} | Val: {len(val_ds)} | Test: {len(test_ds)}")
    print(f"[Data] Pos weight: {pos_weight:.4f}")
    
    train_loader = DataLoader(train_ds, batch_size=args.batch_size, shuffle=True, num_workers=args.num_workers)
    val_loader = DataLoader(val_ds, batch_size=args.batch_size, shuffle=False, num_workers=args.num_workers)
    test_loader = DataLoader(test_ds, batch_size=args.batch_size, shuffle=False, num_workers=args.num_workers)
    
    model = create_advanced_model(
        args.model_type,
        input_dim,
        args.hidden_dim,
        num_relations=num_rels,
        num_layers=args.layers,
        heads=args.heads,
        dropout=args.dropout,
    ).to(device)
    
    num_params = sum(p.numel() for p in model.parameters())
    print(f"[Model] Parameters: {num_params:,}")
    
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr, weight_decay=args.weight_decay)
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode='max', factor=0.5, patience=5)
    
    best_val_auc = 0
    best_threshold = 0.5
    patience_counter = 0
    
    print(f"\n[Train] Starting training for {args.epochs} epochs...")
    
    for epoch in range(1, args.epochs + 1):
        start_time = time.time()
        
        train_loss = train_epoch(model, train_loader, optimizer, device, pos_weight)
        val_metrics, val_preds, val_targets = eval_epoch(model, val_loader, device)
        
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
        
        if val_metrics["auc"] > best_val_auc:
            best_val_auc = val_metrics["auc"]
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
    
    print(f"\n[Test] Evaluating best model (threshold={best_threshold:.2f})...")
    
    if (out_dir / "best_model.pt").exists():
        model.load_state_dict(torch.load(out_dir / "best_model.pt", weights_only=True))
    
    test_metrics, _, _ = eval_epoch(model, test_loader, device, best_threshold)
    
    print(f"\n{'='*60}")
    print("FINAL TEST RESULTS")
    print(f"{'='*60}")
    print(f"Test Accuracy:  {test_metrics['acc']:.4f}")
    print(f"Test F1 Score:  {test_metrics.get('f1', 0):.4f}")
    print(f"Test Precision: {test_metrics.get('precision', 0):.4f}")
    print(f"Test Recall:    {test_metrics.get('recall', 0):.4f}")
    print(f"Test ROC-AUC:   {test_metrics.get('auc', 0):.4f}")
    print(f"Threshold:      {best_threshold:.2f}")
    
    test_metrics["best_threshold"] = float(best_threshold)
    test_metrics["best_val_auc"] = float(best_val_auc)
    test_metrics["model_type"] = args.model_type
    test_metrics["hidden_dim"] = args.hidden_dim
    test_metrics["num_layers"] = args.layers
    
    with (out_dir / "test_results.json").open("w") as f:
        json.dump(test_metrics, f, indent=2)
    
    print(f"\n[Done] Results saved to: {out_dir}")


if __name__ == "__main__":
    args = build_parser().parse_args()
    run(args)


# ============================================================================
# USAGE EXAMPLES
# ============================================================================

"""
# ============================================================================
# MULTI-VIEW GGNN (Separate AST/CFG/DFG encoders with attention fusion)
# ============================================================================
python step2_train_advanced.py \
  --model-type multiview \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 32 \
  --layers 4 \
  --batch-size 128 \
  --lr 2e-4 \
  --epochs 100 \
  --output-dir "results_multiview_full_filtered_onehotonly"

# ============================================================================
# HGT (Heterogeneous Graph Transformer)
# ============================================================================
python step2_train_advanced.py \
  --model-type hgt \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 32 \
  --layers 4 \
  --heads 4 \
  --batch-size 128 \
  --lr 2e-4 \
  --epochs 100 \
  --output-dir "results_hgt_full_filtered_onehotonly"
# ============================================================================
# HYPERGRAPH / Dual-Attention (GATv2 + Transformer with gated fusion)
# ============================================================================
python step2_train_advanced.py \
  --model-type hypergraph \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_onehotonly_full_filtered" \
  --cache-signature "devign_onehotonly_full_filtered" \
  --vocab-dir "./Clean_exports/devign_vocab_full_filtered_v1" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 512 \
  --layers 2 \
  --heads 2 \
  --batch-size 16 \
  --lr 2e-4 \
  --epochs 100 \
  --output-dir "results_hyper_full_filtered_onehotonly"
"""


# ============================================================================
# USAGE EXAMPLES
# ============================================================================

