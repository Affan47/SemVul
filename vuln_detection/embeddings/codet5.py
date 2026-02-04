#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
codet5.py - CodeT5, UniXcoder, and other code transformer embeddings

These models may provide better embeddings than GraphCodeBERT
for vulnerability detection.
"""

from typing import Optional, Dict, Any
import torch
import torch.nn as nn
from torch_geometric.data import Data

from .base import BaseEmbedder, EmbedderRegistry


@EmbedderRegistry.register("codet5")
class CodeT5Embedder(BaseEmbedder):
    """
    CodeT5/CodeT5+ embeddings.
    
    CodeT5+ is often better than GraphCodeBERT for code understanding tasks.
    This can be used in two modes:
    1. Extract embeddings online (slow but flexible)
    2. Use pre-extracted embeddings (fast, like GraphCodeBERT)
    """
    
    def __init__(
        self,
        input_dim: int = 768,  # Pre-extracted embeddings
        output_dim: int = 128,
        num_node_types: int = 28,
        compression: str = "linear",
        dropout: float = 0.1,
        # For online extraction (optional)
        model_name: Optional[str] = None,  # e.g., "Salesforce/codet5p-110m-embedding"
        device: str = "cuda",
    ):
        super().__init__(output_dim=output_dim)
        
        self.input_dim = input_dim
        self.num_node_types = num_node_types
        self.model_name = model_name
        
        # Online model (optional)
        self.online_model = None
        self.tokenizer = None
        if model_name:
            self._load_online_model(model_name, device)
        
        # Compression/projection
        if compression == "linear":
            self.compressor = nn.Sequential(
                nn.Linear(input_dim, output_dim),
                nn.LayerNorm(output_dim),
                nn.GELU(),
                nn.Dropout(dropout),
            )
        else:
            self.compressor = nn.Identity()
            self._output_dim = input_dim
        
        # Node type embedding
        type_dim = output_dim // 4
        self.type_embed = nn.Embedding(num_node_types, type_dim)
        
        # Combine
        self.combine = nn.Sequential(
            nn.Linear(output_dim + type_dim, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
        )
    
    def _load_online_model(self, model_name: str, device: str):
        """Load CodeT5 model for online embedding extraction."""
        try:
            from transformers import AutoModel, AutoTokenizer
            
            print(f"[CodeT5] Loading {model_name}...")
            self.tokenizer = AutoTokenizer.from_pretrained(model_name, trust_remote_code=True)
            self.online_model = AutoModel.from_pretrained(model_name, trust_remote_code=True)
            self.online_model.to(device)
            self.online_model.eval()
            print(f"[CodeT5] Loaded successfully")
        except Exception as e:
            print(f"[CodeT5] Could not load online model: {e}")
            self.online_model = None
    
    @torch.no_grad()
    def extract_embeddings(self, code_strings: list, batch_size: int = 32) -> torch.Tensor:
        """Extract embeddings from code strings using online model."""
        if self.online_model is None or self.tokenizer is None:
            raise RuntimeError("Online model not loaded. Provide model_name in constructor.")
        
        embeddings = []
        for i in range(0, len(code_strings), batch_size):
            batch = code_strings[i:i + batch_size]
            inputs = self.tokenizer(
                batch,
                padding=True,
                truncation=True,
                max_length=512,
                return_tensors="pt",
            ).to(self.online_model.device)
            
            outputs = self.online_model(**inputs)
            
            # Use CLS token or mean pooling
            if hasattr(outputs, 'pooler_output') and outputs.pooler_output is not None:
                emb = outputs.pooler_output
            else:
                # Mean pooling
                hidden = outputs.last_hidden_state
                mask = inputs['attention_mask'].unsqueeze(-1)
                emb = (hidden * mask).sum(dim=1) / mask.sum(dim=1).clamp(min=1)
            
            embeddings.append(emb.cpu())
        
        return torch.cat(embeddings, dim=0)
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        """
        Embed nodes.
        
        Args:
            x: Node features [N, 28 + embedding_dim]
            data: PyG Data object
        
        Returns:
            Embeddings [N, output_dim]
        """
        onehot = x[:, :self.num_node_types]
        emb = x[:, self.num_node_types:]
        
        # Compress
        compressed = self.compressor(emb)
        
        # Node type
        node_types = onehot.argmax(dim=1)
        type_emb = self.type_embed(node_types)
        
        # Combine
        combined = torch.cat([compressed, type_emb], dim=-1)
        return self.combine(combined)


@EmbedderRegistry.register("unixcoder")
class UniXcoderEmbedder(BaseEmbedder):
    """
    UniXcoder embeddings (Microsoft).
    
    UniXcoder is a unified cross-modal model for code.
    Similar interface to CodeT5Embedder.
    """
    
    def __init__(
        self,
        input_dim: int = 768,
        output_dim: int = 128,
        num_node_types: int = 28,
        dropout: float = 0.1,
    ):
        super().__init__(output_dim=output_dim)
        
        self.input_dim = input_dim
        self.num_node_types = num_node_types
        
        # Projection
        self.projection = nn.Sequential(
            nn.Linear(input_dim, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Node type
        type_dim = output_dim // 4
        self.type_embed = nn.Embedding(num_node_types, type_dim)
        
        # Combine
        self.combine = nn.Sequential(
            nn.Linear(output_dim + type_dim, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
        )
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        onehot = x[:, :self.num_node_types]
        emb = x[:, self.num_node_types:]
        
        projected = self.projection(emb)
        
        node_types = onehot.argmax(dim=1)
        type_emb = self.type_embed(node_types)
        
        combined = torch.cat([projected, type_emb], dim=-1)
        return self.combine(combined)


@EmbedderRegistry.register("multi_embedder")
class MultiEmbedder(BaseEmbedder):
    """
    Combine multiple embedding sources.
    
    Can combine:
    - GraphCodeBERT
    - Node type embeddings
    - Structural features
    - Word2Vec (if available)
    """
    
    def __init__(
        self,
        gcb_dim: int = 768,
        output_dim: int = 128,
        num_node_types: int = 28,
        components: list = ["gcb", "type", "struct"],
        gcb_compress_to: int = 64,
        dropout: float = 0.1,
    ):
        """
        Args:
            gcb_dim: GraphCodeBERT embedding dimension
            output_dim: Final output dimension
            num_node_types: Number of node types
            components: Which components to include ["gcb", "type", "struct"]
            gcb_compress_to: How much to compress GraphCodeBERT
            dropout: Dropout rate
        """
        super().__init__(output_dim=output_dim)
        
        self.num_node_types = num_node_types
        self.components = components
        
        # Build component embedders
        total_dim = 0
        
        if "gcb" in components:
            self.gcb_compress = nn.Sequential(
                nn.Linear(gcb_dim, gcb_compress_to),
                nn.LayerNorm(gcb_compress_to),
                nn.GELU(),
                nn.Dropout(dropout),
            )
            total_dim += gcb_compress_to
        
        if "type" in components:
            type_dim = output_dim // 4
            self.type_embed = nn.Embedding(num_node_types, type_dim)
            total_dim += type_dim
        
        if "struct" in components:
            struct_dim = output_dim // 4
            self.struct_proj = nn.Linear(5, struct_dim)
            total_dim += struct_dim
        
        # Final projection
        self.final_proj = nn.Sequential(
            nn.Linear(total_dim, output_dim),
            nn.LayerNorm(output_dim),
            nn.GELU(),
            nn.Dropout(dropout),
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
        
        features = []
        
        if "gcb" in self.components:
            gcb_compressed = self.gcb_compress(gcb_emb)
            features.append(gcb_compressed)
        
        if "type" in self.components:
            node_types = onehot.argmax(dim=1)
            type_emb = self.type_embed(node_types)
            features.append(type_emb)
        
        if "struct" in self.components and data is not None:
            struct_feat = self._compute_structural_features(data)
            struct_emb = self.struct_proj(struct_feat)
            features.append(struct_emb)
        
        combined = torch.cat(features, dim=-1)
        return self.final_proj(combined)
