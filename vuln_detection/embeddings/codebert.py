#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
codebert.py - CodeBERT/GraphCodeBERT embeddings with compression options

The problem with raw GraphCodeBERT:
- 768 dimensions produce 97% similar embeddings
- Most dimensions are noise
- GNN message passing destroys the weak signal

Solutions implemented here:
1. Dimension compression (768 -> 64/128)
2. Feature selection (keep only discriminative dims)
3. Learnable projection with normalization
"""

from typing import Optional, List
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data

from .base import BaseEmbedder, EmbedderRegistry


@EmbedderRegistry.register("codebert")
@EmbedderRegistry.register("graphcodebert")
class CodeBERTEmbedder(BaseEmbedder):
    """
    CodeBERT/GraphCodeBERT embeddings with compression.
    
    Assumes input features are already extracted GraphCodeBERT embeddings
    (768 dims from simple_extractor.py).
    """
    
    def __init__(
        self,
        input_dim: int = 768,
        output_dim: int = 128,
        num_node_types: int = 28,
        compression: str = "linear",  # "linear", "bottleneck", "attention", "none"
        use_node_types: bool = True,
        use_structural: bool = True,
        dropout: float = 0.1,
        freeze_input: bool = False,
        **kwargs,  # Added to handle extra args safely
    ):
        """
        Args:
            input_dim: Input embedding dimension (768 for GraphCodeBERT)
            output_dim: Output embedding dimension after compression
            num_node_types: Number of CPG node types (for one-hot)
            compression: Compression method
            use_node_types: Include node type embeddings
            use_structural: Include structural features
            dropout: Dropout rate
            freeze_input: Whether to detach input (no gradients to embeddings)
        """
        super().__init__(output_dim=output_dim)
        
        self.input_dim = input_dim
        self.num_node_types = num_node_types
        self.compression = compression
        self.use_node_types = use_node_types
        self.use_structural = use_structural
        self.freeze_input = freeze_input
        
        # Build compression layers
        if compression == "linear":
            self.compressor = nn.Sequential(
                nn.Linear(input_dim, output_dim),
                nn.LayerNorm(output_dim),
                nn.GELU(),
                nn.Dropout(dropout),
            )
        elif compression == "bottleneck":
            # Compress through bottleneck
            bottleneck_dim = min(64, output_dim // 2)
            self.compressor = nn.Sequential(
                nn.Linear(input_dim, bottleneck_dim),
                nn.LayerNorm(bottleneck_dim),
                nn.GELU(),
                nn.Dropout(dropout),
                nn.Linear(bottleneck_dim, output_dim),
                nn.LayerNorm(output_dim),
                nn.GELU(),
            )
        elif compression == "attention":
            # Attention-based dimension selection
            self.compressor = AttentionCompressor(input_dim, output_dim, dropout)
        elif compression == "none":
            # No compression, just normalize
            self.compressor = nn.LayerNorm(input_dim)
            self._output_dim = input_dim
        else:
            raise ValueError(f"Unknown compression method: {compression}")
        
        # Node type embedding
        if use_node_types:
            type_dim = output_dim // 4
            self.type_embed = nn.Embedding(num_node_types, type_dim)
            combine_dim = output_dim + type_dim
        else:
            combine_dim = output_dim
        
        # Structural features
        if use_structural:
            struct_dim = output_dim // 4
            self.struct_proj = nn.Linear(5, struct_dim)
            combine_dim += struct_dim
        
        # Final combination
        if use_node_types or use_structural:
            self.combine = nn.Sequential(
                nn.Linear(combine_dim, output_dim),
                nn.LayerNorm(output_dim),
                nn.GELU(),
            )
        else:
            self.combine = nn.Identity()
    
    def _compute_structural_features(self, data: Data) -> torch.Tensor:
        """Compute structural features for each node."""
        from torch_geometric.utils import degree
        
        num_nodes = data.x.size(0)
        edge_index = data.edge_index
        
        in_deg = degree(edge_index[1], num_nodes=num_nodes)
        out_deg = degree(edge_index[0], num_nodes=num_nodes)
        total_deg = in_deg + out_deg
        
        max_deg = total_deg.max().clamp(min=1)
        
        return torch.stack([
            in_deg / max_deg,
            out_deg / max_deg,
            total_deg / max_deg,
            (out_deg == 0).float(),
            (in_deg == 0).float(),
        ], dim=1)
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        """
        Embed nodes with compressed GraphCodeBERT.
        
        Args:
            x: Node features [N, 28 + 768] (one-hot + GraphCodeBERT)
            data: PyG Data object
        
        Returns:
            Compressed embeddings [N, output_dim]
        """
        # Split input
        onehot = x[:, :self.num_node_types]
        gcb_emb = x[:, self.num_node_types:]
        
        # Optionally freeze input
        if self.freeze_input:
            gcb_emb = gcb_emb.detach()
        
        # Compress GraphCodeBERT
        compressed = self.compressor(gcb_emb)
        
        # Collect features
        features = [compressed]
        
        # Add node type embedding
        if self.use_node_types:
            node_types = onehot.argmax(dim=1)
            type_emb = self.type_embed(node_types)
            features.append(type_emb)
        
        # Add structural features
        if self.use_structural and data is not None:
            struct_feat = self._compute_structural_features(data)
            struct_emb = self.struct_proj(struct_feat)
            features.append(struct_emb)
        
        # Combine
        combined = torch.cat(features, dim=-1)
        return self.combine(combined)
    
    def get_config(self) -> dict:
        config = super().get_config()
        config.update({
            "input_dim": self.input_dim,
            "compression": self.compression,
            "use_node_types": self.use_node_types,
            "use_structural": self.use_structural,
        })
        return config


class AttentionCompressor(nn.Module):
    """Attention-based dimension compression."""
    
    def __init__(self, input_dim: int, output_dim: int, dropout: float = 0.1):
        super().__init__()
        
        self.input_dim = input_dim
        self.output_dim = output_dim
        
        # Learn which dimensions are important
        self.dim_attention = nn.Sequential(
            nn.Linear(input_dim, input_dim // 4),
            nn.Tanh(),
            nn.Linear(input_dim // 4, input_dim),
            nn.Sigmoid(),
        )
        
        # Project to output dim
        self.projection = nn.Sequential(
            nn.Linear(input_dim, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
    
    def forward(self, x: torch.Tensor) -> torch.Tensor:
        # Compute dimension importance
        attn = self.dim_attention(x)  # [N, input_dim]
        
        # Weight dimensions
        weighted = x * attn
        
        # Project
        return self.projection(weighted)


@EmbedderRegistry.register("codebert_selective")
class SelectiveCodeBERTEmbedder(BaseEmbedder):
    """
    CodeBERT with feature selection (use only discriminative dimensions).
    """
    
    def __init__(
        self,
        input_dim: int = 768,
        output_dim: int = 128,
        num_node_types: int = 28,
        top_k_dims: int = 100,
        selection_method: str = "learned",  # "learned", "fixed"
        fixed_dims: Optional[List[int]] = None,
        dropout: float = 0.1,
        **kwargs,
    ):
        super().__init__(output_dim=output_dim)
        
        self.input_dim = input_dim
        self.num_node_types = num_node_types
        self.top_k_dims = top_k_dims
        self.selection_method = selection_method
        
        if selection_method == "learned":
            # Learn which dimensions to attend to
            self.dim_selector = nn.Sequential(
                nn.Linear(input_dim, input_dim // 2),
                nn.GELU(),
                nn.Linear(input_dim // 2, input_dim),
            )
        elif selection_method == "fixed" and fixed_dims is not None:
            # Use fixed dimension indices
            self.register_buffer('selected_dims', torch.tensor(fixed_dims))
        
        # Projection from selected dims to output
        self.projection = nn.Sequential(
            nn.Linear(top_k_dims, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Node type embedding
        self.type_embed = nn.Embedding(num_node_types, output_dim // 4)
        
        # Combine
        self.combine = nn.Sequential(
            nn.Linear(output_dim + output_dim // 4, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
        )
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        onehot = x[:, :self.num_node_types]
        gcb_emb = x[:, self.num_node_types:]
        
        if self.selection_method == "learned":
            # Compute attention scores for each dimension
            scores = self.dim_selector(gcb_emb)  # [N, input_dim]
            
            # Get top-k dimensions per sample
            _, top_indices = scores.topk(self.top_k_dims, dim=-1)
            
            # Gather selected dimensions
            selected = gcb_emb.gather(1, top_indices)  # [N, top_k]
        else:
            # Use fixed dimensions
            selected = gcb_emb[:, self.selected_dims]
        
        # Project
        projected = self.projection(selected)
        
        # Add node type
        node_types = onehot.argmax(dim=1)
        type_emb = self.type_embed(node_types)
        
        combined = torch.cat([projected, type_emb], dim=-1)
        return self.combine(combined)


@EmbedderRegistry.register("codebert_hybrid")
class HybridCodeBERTEmbedder(BaseEmbedder):
    """
    Hybrid embedder: compressed CodeBERT + learned components.
    
    Combines:
    - Heavily compressed GraphCodeBERT (768 -> 64)
    - Learned node type embeddings
    - Structural features from CPG
    """
    
    def __init__(
        self,
        input_dim: int = 768,  # Renamed from gcb_dim to input_dim
        output_dim: int = 128,
        num_node_types: int = 28,
        compress_to: int = 64,
        dropout: float = 0.2,
        **kwargs,  # Handle extra arguments safely
    ):
        super().__init__(output_dim=output_dim)
        
        self.num_node_types = num_node_types
        
        # Heavily compress GraphCodeBERT (input_dim -> compress_to)
        self.gcb_compress = nn.Sequential(
            nn.Linear(input_dim, compress_to * 2),
            nn.LayerNorm(compress_to * 2),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(compress_to * 2, compress_to),
        )
        
        # Learned node type embedding
        type_dim = output_dim // 4
        self.type_embed = nn.Embedding(num_node_types, type_dim)
        
        # Structural features
        struct_dim = output_dim // 4
        self.struct_proj = nn.Sequential(
            nn.Linear(5, struct_dim),
            nn.GELU(),
        )
        
        # Combine all: compress_to + type_dim + struct_dim -> output_dim
        combine_dim = compress_to + type_dim + struct_dim
        self.combine = nn.Sequential(
            nn.Linear(combine_dim, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(output_dim, output_dim),
            nn.LayerNorm(output_dim),
        )
    
    def _compute_structural_features(self, data: Data) -> torch.Tensor:
        from torch_geometric.utils import degree
        
        num_nodes = data.x.size(0)
        edge_index = data.edge_index
        
        in_deg = degree(edge_index[1], num_nodes=num_nodes)
        out_deg = degree(edge_index[0], num_nodes=num_nodes)
        total_deg = in_deg + out_deg
        max_deg = total_deg.max().clamp(min=1)
        
        return torch.stack([
            in_deg / max_deg,
            out_deg / max_deg,
            total_deg / max_deg,
            (out_deg == 0).float(),
            (in_deg == 0).float(),
        ], dim=1)
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        onehot = x[:, :self.num_node_types]
        gcb_emb = x[:, self.num_node_types:]
        
        # Compress GraphCodeBERT
        gcb_compressed = self.gcb_compress(gcb_emb)
        
        # Node type embedding
        node_types = onehot.argmax(dim=1)
        type_emb = self.type_embed(node_types)
        
        # Structural features
        if data is not None:
            struct_feat = self._compute_structural_features(data).to(x.device)
            struct_emb = self.struct_proj(struct_feat)
        else:
            struct_emb = torch.zeros(x.size(0), self._output_dim // 4, device=x.device)
        
        # Combine
        combined = torch.cat([gcb_compressed, type_emb, struct_emb], dim=-1)
        return self.combine(combined)