#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
pooling.py - Graph pooling strategies for vulnerability detection

Includes:
- Basic pooling (mean, max, sum)
- Attention pooling
- Multi-statistic pooling (mean + max + std) - Optimized & Vectorized
- DevignConvHead (original Devign readout) - Optimized & Vectorized
- Hierarchical attention
"""

from typing import Tuple, Optional, List
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import global_mean_pool, global_max_pool, global_add_pool
from torch_geometric.utils import softmax, to_dense_batch


class MeanPooling(nn.Module):
    """Simple mean pooling."""
    
    def __init__(self, hidden_dim: int):
        super().__init__()
        self.output_dim = hidden_dim
    
    def forward(self, x: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        return global_mean_pool(x, batch)


class MaxPooling(nn.Module):
    """Simple max pooling."""
    
    def __init__(self, hidden_dim: int):
        super().__init__()
        self.output_dim = hidden_dim
    
    def forward(self, x: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        return global_max_pool(x, batch)


class MeanMaxPooling(nn.Module):
    """Concatenate mean and max pooling."""
    
    def __init__(self, hidden_dim: int):
        super().__init__()
        self.output_dim = hidden_dim * 2
    
    def forward(self, x: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        mean_pool = global_mean_pool(x, batch)
        max_pool = global_max_pool(x, batch)
        return torch.cat([mean_pool, max_pool], dim=-1)


class MultiStatPooling(nn.Module):
    """
    Multi-statistic pooling: mean + max + std.
    
    This implementation is fully vectorized and does NOT loop over the batch.
    It uses the identity: Var(X) = E[X^2] - (E[X])^2
    """
    
    def __init__(self, hidden_dim: int, project_output: bool = False):
        super().__init__()
        
        self._hidden_dim = hidden_dim
        self.output_dim = hidden_dim * 3
        
        if project_output:
            self.projection = nn.Sequential(
                nn.Linear(hidden_dim * 3, hidden_dim),
                nn.LayerNorm(hidden_dim),
                nn.GELU(),
            )
            self.output_dim = hidden_dim
        else:
            self.projection = None
    
    def forward(self, x: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        # 1. Mean
        mean_pool = global_mean_pool(x, batch)
        
        # 2. Max
        max_pool = global_max_pool(x, batch)
        
        # 3. Standard Deviation (Vectorized)
        # E[x^2]
        mean_sq_pool = global_mean_pool(x**2, batch)
        # Var(x) = E[x^2] - E[x]^2
        var_pool = mean_sq_pool - (mean_pool ** 2)
        # Relu ensures non-negative (numerical stability), sqrt gives std
        std_pool = torch.sqrt(F.relu(var_pool) + 1e-8)
        
        combined = torch.cat([mean_pool, max_pool, std_pool], dim=-1)
        
        if self.projection is not None:
            return self.projection(combined)
        return combined


class AttentionPooling(nn.Module):
    """
    Attention-based pooling to focus on important nodes.
    Learns which nodes are most relevant for classification.
    """
    
    def __init__(self, hidden_dim: int, dropout: float = 0.1):
        super().__init__()
        self.output_dim = hidden_dim
        
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 4),
            nn.Tanh(),
            nn.Linear(hidden_dim // 4, 1),
        )
        
        self.gate = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.Sigmoid(),
        )
        
        self.dropout = nn.Dropout(dropout)
    
    def forward(
        self, 
        x: torch.Tensor, 
        batch: torch.Tensor,
        return_attention: bool = False,
    ) -> torch.Tensor:
        # Compute attention scores
        attn_scores = self.attention(x).squeeze(-1)
        attn_weights = softmax(attn_scores, batch)
        
        # Apply gating (Node Feature * Sigmoid Gate)
        gated_x = x * self.gate(x)
        gated_x = self.dropout(gated_x)
        
        # Weighted sum
        # global_add_pool sums vectors. Since weights sum to 1 per graph, this is a weighted mean.
        weighted_x = gated_x * attn_weights.unsqueeze(-1)
        pooled = global_add_pool(weighted_x, batch)
        
        if return_attention:
            return pooled, attn_weights
        return pooled


class DevignConvHead(nn.Module):
    """
    Original Devign readout (Conv1D based).
    
    Optimized to use `to_dense_batch` instead of looping over graphs.
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_conv_layers: int = 2,
        kernel_size: int = 3,
    ):
        super().__init__()
        self.output_dim = hidden_dim
        
        layers = []
        for _ in range(num_conv_layers):
            layers.extend([
                nn.Conv1d(hidden_dim, hidden_dim, kernel_size, padding=kernel_size // 2),
                nn.BatchNorm1d(hidden_dim),
                nn.ReLU(),
                nn.MaxPool1d(2, 2),
            ])
        
        self.conv = nn.Sequential(*layers)
        # Global max pool over the sequence dimension (dim 2)
        self.final_pool = nn.AdaptiveMaxPool1d(1)
    
    def forward(self, x: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        # 1. Convert sparse batch to dense: [Batch, MaxNodes, Dim]
        # x_dense will be zero-padded
        x_dense, mask = to_dense_batch(x, batch)
        
        # 2. Transpose for Conv1d: [Batch, Dim, MaxNodes]
        x_dense = x_dense.transpose(1, 2)
        
        # 3. Apply Conv layers
        h = self.conv(x_dense)
        
        # 4. Adaptive Max Pool over the time dimension
        # Output: [Batch, Dim, 1] -> [Batch, Dim]
        out = self.final_pool(h).squeeze(-1)
        
        return out


class CombinedPooling(nn.Module):
    """
    Combine multiple pooling strategies.
    Default: attention + mean + max
    """
    
    def __init__(
        self,
        hidden_dim: int,
        strategies: list = ["attention", "mean", "max"],
        dropout: float = 0.1,
    ):
        super().__init__()
        
        self.strategies = strategies
        total_dim = 0
        
        if "attention" in strategies:
            self.attention_pool = AttentionPooling(hidden_dim, dropout)
            total_dim += hidden_dim
        
        if "mean" in strategies:
            total_dim += hidden_dim
        
        if "max" in strategies:
            total_dim += hidden_dim
        
        if "std" in strategies:
            total_dim += hidden_dim
        
        self.output_dim = total_dim
        
        # Optional projection
        self.projection = nn.Sequential(
            nn.Linear(total_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
        )
        self.output_dim = hidden_dim
    
    def forward(self, x: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        outputs = []
        
        if "attention" in self.strategies:
            outputs.append(self.attention_pool(x, batch))
        
        if "mean" in self.strategies:
            outputs.append(global_mean_pool(x, batch))
        
        if "max" in self.strategies:
            outputs.append(global_max_pool(x, batch))
        
        if "std" in self.strategies:
            # Vectorized std calculation
            mean_pool = global_mean_pool(x, batch)
            mean_sq_pool = global_mean_pool(x**2, batch)
            var_pool = mean_sq_pool - (mean_pool ** 2)
            std_pool = torch.sqrt(F.relu(var_pool) + 1e-8)
            outputs.append(std_pool)
        
        combined = torch.cat(outputs, dim=-1)
        return self.projection(combined)


def create_pooling(
    pooling_type: str,
    hidden_dim: int,
    dropout: float = 0.1,
    **kwargs,
) -> nn.Module:
    """
    Factory function to create pooling by type.
    
    Args:
        pooling_type: "mean", "max", "mean_max", "multi_stat", "attention", 
                      "combined", "devign"
        hidden_dim: Hidden dimension
        dropout: Dropout rate
    
    Returns:
        Pooling module
    """
    if pooling_type == "mean":
        return MeanPooling(hidden_dim)
    elif pooling_type == "max":
        return MaxPooling(hidden_dim)
    elif pooling_type == "mean_max":
        return MeanMaxPooling(hidden_dim)
    elif pooling_type == "multi_stat":
        return MultiStatPooling(hidden_dim, project_output=kwargs.get("project", False))
    elif pooling_type == "attention":
        return AttentionPooling(hidden_dim, dropout)
    elif pooling_type == "combined":
        strategies = kwargs.get("strategies", ["attention", "mean", "max"])
        return CombinedPooling(hidden_dim, strategies, dropout)
    elif pooling_type == "devign":
        return DevignConvHead(hidden_dim)
    else:
        raise ValueError(f"Unknown pooling type: {pooling_type}")