#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
hgt_models.py - Heterogeneous Graph Transformer for Vulnerability Detection

This model adapts PyG's HGTConv for Code Property Graphs by treating
different edge types (AST, CFG, DFG) as different relation types in
a heterogeneous graph with a single node type.

Important Note:
    HGT is designed for truly heterogeneous graphs with multiple node types
    (e.g., Author-Paper-Venue). For CPGs with only one node type (code nodes),
    HGT becomes a sophisticated relational attention mechanism. Consider using
    RGAT for this use case, which is more memory efficient.

Key Features:
    - Type-specific transformations per edge type
    - Multi-head attention across relations
    - Pre-activation residuals for deep networks
    - Proper handling of sparse relation types
    
Reference:
    Hu et al., "Heterogeneous Graph Transformer", WWW 2020
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import HGTConv
from torch_geometric.utils import to_dense_batch
from typing import Dict, List, Tuple, Optional
import warnings


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


class HGTBlock(nn.Module):
    """
    Heterogeneous Graph Transformer block with proper residuals.
    
    Wraps HGTConv with:
    - Pre-activation normalization
    - Residual connection
    - FFN with residual
    """
    
    def __init__(
        self,
        hidden_dim: int,
        metadata: Tuple[List[str], List[Tuple[str, str, str]]],
        heads: int = 4,
        dropout: float = 0.2,
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        
        # Pre-norm
        self.norm1 = nn.LayerNorm(hidden_dim)
        
        # HGT convolution
        self.conv = HGTConv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            metadata=metadata,
            heads=heads,
        )
        
        self.dropout1 = nn.Dropout(dropout)
        
        # FFN
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
        """
        Args:
            x_dict: Dict mapping node type to features
            edge_index_dict: Dict mapping edge type tuple to edge indices
            
        Returns:
            Updated x_dict
        """
        # Get input for residual (assuming single node type '0')
        x_in = x_dict['0']
        
        # Pre-norm
        x_normed = self.norm1(x_in)
        x_dict_normed = {'0': x_normed}
        
        # HGT forward
        out_dict = self.conv(x_dict_normed, edge_index_dict)
        h = out_dict['0']
        
        # Activation and dropout
        h = F.elu(h)
        h = self.dropout1(h)
        
        # Residual
        x = x_in + h
        
        # FFN with pre-norm and residual
        x_res = x
        h = self.norm2(x)
        h = self.ffn(h)
        x = x_res + h
        
        return {'0': x}


class HGTDevignModel(nn.Module):
    """
    Heterogeneous Graph Transformer for Vulnerability Detection.
    
    Adapts HGT for Code Property Graphs by treating edge types as
    relation types in a heterogeneous graph with single node type.
    
    Architecture:
        Input -> Projection -> [HGT Block × N] -> Readout -> Classifier
    
    Note:
        Consider using RGAT for single-node-type graphs as it's more
        memory efficient and specifically designed for relational graphs.
    
    Args:
        in_dim: Input feature dimension
        hidden_dim: Hidden dimension for all layers
        num_relations: Number of edge types (AST, CFG, DFG, etc.)
        num_layers: Number of HGT blocks
        heads: Number of attention heads
        dropout: Dropout rate
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
        
        # Input projection
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Define HGT metadata
        # Single node type '0', multiple edge types
        self.node_types = ['0']
        self.edge_types = [('0', str(r), '0') for r in range(num_relations)]
        self.metadata = (self.node_types, self.edge_types)
        
        # HGT blocks
        self.blocks = nn.ModuleList([
            HGTBlock(
                hidden_dim=hidden_dim,
                metadata=self.metadata,
                heads=heads,
                dropout=dropout,
            )
            for _ in range(num_layers)
        ])
        
        # Final normalization
        self.final_norm = nn.LayerNorm(hidden_dim)
        
        # Readout
        self.readout = DevignConvHead(hidden_dim, dropout)
        
        # Classifier
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
        """
        Convert homogeneous edge_index + edge_type to HGT format.
        
        Args:
            edge_index: [2, E] edge connectivity
            edge_type: [E] edge type labels
            
        Returns:
            Dict mapping (src_type, rel_type, dst_type) to edge indices
        """
        edge_index_dict = {}
        
        for r in range(self.num_relations):
            mask = (edge_type == r)
            edge_key = ('0', str(r), '0')
            
            if mask.any():
                edge_index_dict[edge_key] = edge_index[:, mask]
            else:
                # HGT requires all edge types to be present
                # Use empty tensor for missing relations
                edge_index_dict[edge_key] = torch.empty(
                    (2, 0), dtype=torch.long, device=edge_index.device
                )
        
        return edge_index_dict
    
    def forward(self, data, return_embeddings: bool = False) -> Dict[str, torch.Tensor]:
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch
        edge_type = getattr(data, "edge_type", None)
        
        # Handle missing attributes
        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)
        
        if edge_type is None:
            edge_type = torch.zeros(
                edge_index.size(1), dtype=torch.long, device=x.device
            )
        else:
            edge_type = edge_type.long().clamp(0, self.num_relations - 1)
        
        # Input projection
        h0 = self.input_proj(x)
        
        # Convert to HGT format
        x_dict = {'0': h0}
        edge_index_dict = self._build_edge_index_dict(edge_index, edge_type)
        
        # HGT blocks
        for block in self.blocks:
            x_dict = block(x_dict, edge_index_dict)
        
        # Extract final features
        h = x_dict['0']
        h = self.final_norm(h)
        
        # Readout
        graph_emb = self.readout(h_input=h0, h_final=h, batch=batch)
        
        # Classification
        logits = self.classifier(graph_emb)
        
        if return_embeddings:
            return {"logits": logits, "graph_emb": graph_emb}
        return {"logits": logits}
