#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
hypergraph_models.py - Dual-Attention Graph Neural Network for Vulnerability Detection

This model combines two complementary attention mechanisms:
  - Local Attention (GATv2): Focuses on immediate neighbors with edge-type awareness
  - Global Attention (Transformer): Captures longer-range dependencies

The two branches are fused using a learnable gating mechanism.

Note: Originally designed to use HypergraphConv, but standard edge_index format
doesn't properly represent hyperedges. This version uses a more appropriate
dual-attention architecture that achieves similar expressive power.

Key Features:
  - Edge-type-aware attention in both branches
  - Learnable gated fusion (not just sum)
  - Pre-activation residuals for deep networks
  - Proper normalization and dropout
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import GATv2Conv, TransformerConv
from torch_geometric.utils import to_dense_batch
from typing import Dict, Optional
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


class DualAttentionBlock(nn.Module):
    """
    Dual-branch attention block combining local and global attention.
    
    Branch 1 (Local): GATv2 - focuses on immediate neighbors
    Branch 2 (Global): TransformerConv - captures longer-range dependencies
    
    The branches are combined using a learnable gating mechanism that
    allows the model to dynamically weight local vs global information.
    
    Features:
    - Edge-type embeddings in both branches
    - Learnable gated fusion (not just sum)
    - Pre-activation residuals
    - FFN with residual
    - Residual scaling for deep networks
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
        
        # Ensure heads divides hidden_dim evenly
        # Minimum 16 dims per head for stable attention
        effective_heads = min(heads, hidden_dim // 16)
        effective_heads = max(1, effective_heads)
        if effective_heads != heads:
            import warnings
            warnings.warn(f"Reduced heads from {heads} to {effective_heads} (need >=16 dims/head)")
        self.heads = effective_heads
        
        # Pre-norms
        self.norm_local = nn.LayerNorm(hidden_dim)
        self.norm_global = nn.LayerNorm(hidden_dim)
        
        # Branch 1: Local attention (GATv2)
        self.local_attn = GATv2Conv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            heads=effective_heads,
            concat=False,
            dropout=dropout,
            edge_dim=hidden_dim,
            add_self_loops=True,
        )
        
        # Branch 2: Global attention (Transformer)
        self.global_attn = TransformerConv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            heads=effective_heads,
            concat=False,
            dropout=dropout,
            edge_dim=hidden_dim,
        )
        
        # Learnable gated fusion with better initialization
        # Initialize gate bias to 0.5 for equal initial weighting
        self.gate_linear = nn.Linear(hidden_dim * 2, hidden_dim)
        nn.init.zeros_(self.gate_linear.weight)
        nn.init.zeros_(self.gate_linear.bias)  # sigmoid(0) = 0.5
        
        # Post-fusion norm
        self.norm_fusion = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
        
        # Feed-forward network with smaller expansion for stability
        self.norm_ffn = nn.LayerNorm(hidden_dim)
        self.ffn = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim * 2),  # Reduced from 4x to 2x
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.Dropout(dropout),
        )
        
        # Initialize FFN to near-identity
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
        """
        Args:
            x: Node features [N, hidden_dim]
            edge_index: Edge connectivity [2, E]
            edge_attr: Edge embeddings [E, hidden_dim]
            
        Returns:
            Updated node features [N, hidden_dim]
        """
        # Save for residual
        x_res = x
        
        # Branch 1: Local attention (pre-norm)
        h_local = self.norm_local(x)
        h_local = self.local_attn(h_local, edge_index, edge_attr=edge_attr)
        h_local = F.gelu(h_local)  # Changed from elu to gelu for smoother gradients
        
        # Branch 2: Global attention (pre-norm)
        h_global = self.norm_global(x)
        h_global = self.global_attn(h_global, edge_index, edge_attr=edge_attr)
        h_global = F.gelu(h_global)
        
        # Gated fusion with gradient-friendly implementation
        gate_input = torch.cat([h_local, h_global], dim=-1)
        gate = torch.sigmoid(self.gate_linear(gate_input))  # [N, hidden_dim]
        
        # Use soft gating: (1-α)*local + α*global instead of hard switching
        h_fused = (1 - gate) * h_local + gate * h_global
        h_fused = self.norm_fusion(h_fused)
        h_fused = self.dropout(h_fused)
        
        # Scaled residual connection (helps with deep networks)
        x = x_res + self.residual_scale * h_fused
        
        # FFN with pre-norm and scaled residual
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
    
    Note: Named "Hyper" for compatibility with existing code, but uses
    dual-attention instead of misapplied HypergraphConv.
    
    Architecture:
        Input -> Projection -> [DualAttention Block × N] -> Readout -> Classifier
    
    Args:
        in_dim: Input feature dimension
        hidden_dim: Hidden dimension for all layers
        num_relations: Number of edge types (for edge embedding)
        num_layers: Number of dual-attention blocks
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
        
        # Validate heads vs hidden_dim
        # Need at least 16 dims per head for stable attention
        effective_heads = min(heads, hidden_dim // 16)
        effective_heads = max(1, effective_heads)
        if effective_heads != heads:
            import warnings
            warnings.warn(
                f"Adjusted heads from {heads} to {effective_heads} "
                f"(hidden_dim={hidden_dim} needs >=16 dims/head for stability)"
            )
        self.heads = effective_heads
        
        # Input projection with gain-controlled init
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Edge type embedding with small init
        self.edge_embedding = nn.Embedding(num_relations, hidden_dim)
        nn.init.normal_(self.edge_embedding.weight, mean=0.0, std=0.02)
        
        # Dual-attention blocks with depth-scaled residuals
        # Scale residuals by 1/sqrt(2*num_layers) for deep networks
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
        
        # Final normalization
        self.final_norm = nn.LayerNorm(hidden_dim)
        
        # Readout
        self.readout = DevignConvHead(hidden_dim, dropout)
        
        # Classifier with careful initialization
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
                # Use smaller init for stability
                nn.init.trunc_normal_(module.weight, std=0.02)
                if module.bias is not None:
                    nn.init.zeros_(module.bias)
            elif isinstance(module, nn.LayerNorm):
                nn.init.ones_(module.weight)
                nn.init.zeros_(module.bias)
        
        # Special init for final classifier - start near zero output
        # This prevents initial predictions from being too confident
        if hasattr(self.classifier[-1], 'weight'):
            nn.init.normal_(self.classifier[-1].weight, std=0.01)
            nn.init.zeros_(self.classifier[-1].bias)
    
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
        h = h0
        
        # Get edge embeddings (computed once, used in all layers)
        edge_attr = self.edge_embedding(edge_type)
        
        # Dual-attention blocks
        for block in self.blocks:
            h = block(h, edge_index, edge_attr)
        
        # Final normalization
        h = self.final_norm(h)
        
        # Readout
        graph_emb = self.readout(h_input=h0, h_final=h, batch=batch)
        
        # Classification
        logits = self.classifier(graph_emb)
        
        if return_embeddings:
            return {"logits": logits, "graph_emb": graph_emb}
        return {"logits": logits}
