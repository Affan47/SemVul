#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
base.py - Base class for all embedding models

All embedders must implement:
- embed_nodes(x, data) -> node embeddings
- output_dim -> embedding dimension
"""

from abc import ABC, abstractmethod
from typing import Optional
import torch
import torch.nn as nn
from torch_geometric.data import Data


class BaseEmbedder(ABC, nn.Module):
    """Abstract base class for node embedding models."""
    
    def __init__(self, output_dim: int):
        super().__init__()
        self._output_dim = output_dim
    
    @property
    def output_dim(self) -> int:
        """Returns the output embedding dimension."""
        return self._output_dim
    
    @abstractmethod
    def forward(self, x: torch.Tensor, data: Optional[Data] = None) -> torch.Tensor:
        """
        Embed node features.
        
        Args:
            x: Node features [N, input_dim]
            data: Optional PyG Data object for structural features
        
        Returns:
            Node embeddings [N, output_dim]
        """
        pass
    
    def get_config(self) -> dict:
        """Return configuration for logging/saving."""
        return {
            "class": self.__class__.__name__,
            "output_dim": self._output_dim,
        }


class EmbedderRegistry:
    """Registry for embedding models."""
    
    _embedders = {}
    
    @classmethod
    def register(cls, name: str):
        """Decorator to register an embedder."""
        def decorator(embedder_cls):
            cls._embedders[name] = embedder_cls
            return embedder_cls
        return decorator
    
    @classmethod
    def get(cls, name: str):
        """Get embedder class by name."""
        if name not in cls._embedders:
            raise ValueError(f"Unknown embedder: {name}. Available: {list(cls._embedders.keys())}")
        return cls._embedders[name]
    
    @classmethod
    def list_available(cls):
        """List all available embedders."""
        return list(cls._embedders.keys())
