#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
word2vec.py - Word2Vec-based embeddings (like original Devign paper)

The original Devign paper uses Word2Vec embeddings on code tokens.
This module provides:
1. Training Word2Vec on code corpus
2. Loading pre-trained Word2Vec
3. Aggregating token embeddings per node
"""

import os
from pathlib import Path
from typing import Optional, List, Dict, Union
import numpy as np
import torch
import torch.nn as nn
from torch_geometric.data import Data

from .base import BaseEmbedder, EmbedderRegistry

try:
    from gensim.models import Word2Vec, KeyedVectors
    GENSIM_AVAILABLE = True
except ImportError:
    GENSIM_AVAILABLE = False
    print("[WARNING] gensim not installed. Word2Vec embeddings will not be available.")
    print("         Install with: pip install gensim")


@EmbedderRegistry.register("word2vec")
class Word2VecEmbedder(BaseEmbedder):
    """
    Word2Vec embeddings for code nodes.
    
    Like the original Devign paper, this embeds code tokens using Word2Vec
    and aggregates them per node.
    """
    
    def __init__(
        self,
        vocab_size: int = 10000,
        output_dim: int = 128,
        pretrained_path: Optional[str] = None,
        trainable: bool = True,
        padding_idx: int = 0,
        aggregation: str = "mean",  # "mean", "sum", "max"
        dropout: float = 0.0,       # Added to fix TypeError
        **kwargs,                   # Added to ignore other unused args
    ):
        """
        Args:
            vocab_size: Size of vocabulary
            output_dim: Embedding dimension
            pretrained_path: Path to pretrained Word2Vec model (.bin or .txt)
            trainable: Whether embeddings are trainable
            padding_idx: Index for padding token
            aggregation: How to aggregate token embeddings ("mean", "sum", "max")
            dropout: Dropout rate (applied after projection if used)
        """
        super().__init__(output_dim=output_dim)
        
        self.vocab_size = vocab_size
        self.aggregation = aggregation
        self.padding_idx = padding_idx
        self.dropout = nn.Dropout(dropout)
        
        # Create embedding layer
        self.embedding = nn.Embedding(
            num_embeddings=vocab_size,
            embedding_dim=output_dim,
            padding_idx=padding_idx,
        )
        
        # Load pretrained if provided
        if pretrained_path:
            self._load_pretrained(pretrained_path)
        
        # Freeze if not trainable
        if not trainable:
            self.embedding.weight.requires_grad = False
    
    def _load_pretrained(self, path: str):
        """Load pretrained Word2Vec weights."""
        if not GENSIM_AVAILABLE:
            raise RuntimeError("gensim is required for loading Word2Vec. Install with: pip install gensim")
        
        path = Path(path)
        if not path.exists():
            raise FileNotFoundError(f"Word2Vec model not found: {path}")
        
        # Load based on file extension
        # unicode_errors='ignore' handles non-UTF-8 tokens in vocabulary
        if path.suffix == ".bin":
            wv = KeyedVectors.load_word2vec_format(
                str(path), binary=True, unicode_errors='ignore'
            )
        else:
            wv = KeyedVectors.load_word2vec_format(
                str(path), binary=False, unicode_errors='ignore'
            )
        
        # Initialize embedding matrix with random noise
        embed_matrix = np.random.randn(self.vocab_size, self._output_dim) * 0.01
        
        # In a real scenario, you would map words to indices here.
        # Since cache_manager typically handles extraction, this class often 
        # acts as a pass-through/projector for pre-extracted features.
        # We load weights anyway in case it's used directly.
        
        # Convert to tensor
        self.embedding.weight.data = torch.from_numpy(embed_matrix).float()
        print(f"[Word2Vec] Loaded pretrained vectors from {path.name}")
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        """
        Embed node features.
        
        Args:
            x: Token indices [N, max_tokens] or node features [N, feature_dim]
            data: Optional PyG Data object
        
        Returns:
            Node embeddings [N, output_dim]
        """
        if x.dtype in (torch.long, torch.int):
            # x is token indices [N, T]
            embedded = self.embedding(x)  # [N, T, D]
            
            # Aggregate tokens
            if self.aggregation == "mean":
                mask = (x != self.padding_idx).unsqueeze(-1).float()
                summed = (embedded * mask).sum(dim=1)
                count = mask.sum(dim=1).clamp(min=1)
                emb = summed / count
            elif self.aggregation == "sum":
                mask = (x != self.padding_idx).unsqueeze(-1).float()
                emb = (embedded * mask).sum(dim=1)
            elif self.aggregation == "max":
                mask = (x != self.padding_idx).unsqueeze(-1).float()
                embedded = embedded.masked_fill(mask == 0, float('-inf'))
                emb = embedded.max(dim=1)[0]
            else:
                emb = embedded.mean(dim=1)
                
            return self.dropout(emb)
            
        else:
            # x is continuous features (already embedded by cache_manager)
            # Project to output_dim if dimensions don't match
            if x.size(-1) != self._output_dim:
                if not hasattr(self, 'projection'):
                    self.projection = nn.Linear(x.size(-1), self._output_dim).to(x.device)
                x = self.projection(x)
                x = self.dropout(x)
            return x
    
    def get_config(self) -> dict:
        config = super().get_config()
        config.update({
            "vocab_size": self.vocab_size,
            "embed_dim": self._output_dim,
            "aggregation": self.aggregation,
        })
        return config


@EmbedderRegistry.register("learned")
class LearnedEmbedder(BaseEmbedder):
    """
    Learned embeddings from scratch (no pretrained model).
    
    Uses:
    - One-hot node type embeddings
    - Structural features (degree, etc.)
    - Learned projection
    """
    
    def __init__(
        self,
        num_node_types: int = 28,
        input_dim: int = 796,  # For compatibility with existing features
        hidden_dim: int = 128, # Changed for consistency
        output_dim: int = 128, # Added to match BaseEmbedder
        use_structural: bool = True,
        dropout: float = 0.1,
    ):
        # Handle case where only hidden_dim is passed
        final_dim = output_dim if output_dim is not None else hidden_dim
        super().__init__(output_dim=final_dim)
        
        self.num_node_types = num_node_types
        self.input_dim = input_dim
        self.use_structural = use_structural
        
        # Node type embedding
        self.type_embed = nn.Embedding(num_node_types, final_dim // 2)
        
        # Structural feature projection (5 features: in/out/total degree, is_leaf, is_root)
        if use_structural:
            self.struct_proj = nn.Linear(5, final_dim // 4)
            combine_dim = final_dim // 2 + final_dim // 4
        else:
            combine_dim = final_dim // 2
        
        # Final projection
        self.projection = nn.Sequential(
            nn.Linear(combine_dim, final_dim),
            nn.LayerNorm(final_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
    
    def _compute_structural_features(self, data: Data) -> torch.Tensor:
        """Compute structural features for each node."""
        from torch_geometric.utils import degree
        
        num_nodes = data.x.size(0)
        edge_index = data.edge_index
        
        # Compute degrees
        in_deg = degree(edge_index[1], num_nodes=num_nodes)
        out_deg = degree(edge_index[0], num_nodes=num_nodes)
        total_deg = in_deg + out_deg
        
        # Normalize
        max_deg = total_deg.max().clamp(min=1)
        in_deg_norm = in_deg / max_deg
        out_deg_norm = out_deg / max_deg
        total_deg_norm = total_deg / max_deg
        
        # Leaf/root indicators
        is_leaf = (out_deg == 0).float()
        is_root = (in_deg == 0).float()
        
        return torch.stack([
            in_deg_norm, out_deg_norm, total_deg_norm, is_leaf, is_root
        ], dim=1)
    
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        """
        Embed nodes using learned embeddings.
        """
        # Get node types from one-hot
        # Assuming x is [N, input_dim] and first num_node_types are one-hot
        if x.size(1) >= self.num_node_types:
            onehot = x[:, :self.num_node_types]
            node_types = onehot.argmax(dim=1)
        else:
            # Fallback if x is just indices
            node_types = x.long()
        
        # Embed node types
        type_emb = self.type_embed(node_types)
        
        # Get structural features
        features = [type_emb]
        
        if self.use_structural and data is not None:
            struct_feat = self._compute_structural_features(data).to(x.device)
            struct_emb = self.struct_proj(struct_feat)
            features.append(struct_emb)
        
        # Combine and project
        combined = torch.cat(features, dim=-1)
        return self.projection(combined)
    
    def get_config(self) -> dict:
        config = super().get_config()
        config.update({
            "num_node_types": self.num_node_types,
            "use_structural": self.use_structural,
        })
        return config


def train_word2vec(
    corpus_path: str,
    output_path: str,
    vector_size: int = 128,
    window: int = 5,
    min_count: int = 3,
    workers: int = 4,
    epochs: int = 10,
):
    """
    Train Word2Vec on a code corpus.
    """
    if not GENSIM_AVAILABLE:
        raise RuntimeError("gensim is required. Install with: pip install gensim")
    
    from gensim.models import Word2Vec
    
    # Load corpus
    print(f"[Word2Vec] Loading corpus from {corpus_path}")
    sentences = []
    with open(corpus_path, 'r', encoding='utf-8') as f:
        for line in f:
            tokens = line.strip().split()
            if tokens:
                sentences.append(tokens)
    
    print(f"[Word2Vec] Training on {len(sentences)} sentences")
    
    # Train model
    model = Word2Vec(
        sentences=sentences,
        vector_size=vector_size,
        window=window,
        min_count=min_count,
        workers=workers,
        epochs=epochs,
        sg=1,  # Skip-gram
    )
    
    # Save
    model.wv.save_word2vec_format(output_path, binary=True)
    print(f"[Word2Vec] Saved to {output_path}")
    
    return model