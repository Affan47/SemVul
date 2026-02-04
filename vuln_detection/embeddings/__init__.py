#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
embeddings - Node embedding modules for vulnerability detection

Available embedders:
- word2vec: Word2Vec embeddings (like original Devign)
- learned: Learned embeddings from scratch
- codebert/graphcodebert: CodeBERT with compression
- codebert_selective: CodeBERT with feature selection
- codebert_hybrid: Hybrid CodeBERT + learned features
- codet5: CodeT5/CodeT5+ embeddings
- unixcoder: UniXcoder embeddings
- multi_embedder: Combine multiple sources

Usage:
    from vuln_detection.embeddings import EmbedderRegistry, create_embedder
    
    # List available embedders
    print(EmbedderRegistry.list_available())
    
    # Create embedder by name
    embedder = create_embedder("codebert_hybrid", output_dim=128)
"""

from .base import BaseEmbedder, EmbedderRegistry
from .word2vec import Word2VecEmbedder, LearnedEmbedder, train_word2vec
from .codebert import (
    CodeBERTEmbedder,
    SelectiveCodeBERTEmbedder,
    HybridCodeBERTEmbedder,
)
from .codet5 import (
    CodeT5Embedder,
    UniXcoderEmbedder,
    MultiEmbedder,
)


def create_embedder(name: str, **kwargs) -> BaseEmbedder:
    """
    Factory function to create embedders by name.
    
    Args:
        name: Embedder name (see EmbedderRegistry.list_available())
        **kwargs: Arguments passed to embedder constructor
    
    Returns:
        Embedder instance
    
    Example:
        embedder = create_embedder("codebert_hybrid", output_dim=128, dropout=0.2)
    """
    embedder_cls = EmbedderRegistry.get(name)
    return embedder_cls(**kwargs)


def list_embedders() -> list:
    """List all available embedder names."""
    return EmbedderRegistry.list_available()


__all__ = [
    # Base
    "BaseEmbedder",
    "EmbedderRegistry",
    
    # Factory
    "create_embedder",
    "list_embedders",
    
    # Word2Vec
    "Word2VecEmbedder",
    "LearnedEmbedder",
    "train_word2vec",
    
    # CodeBERT
    "CodeBERTEmbedder",
    "SelectiveCodeBERTEmbedder",
    "HybridCodeBERTEmbedder",
    
    # CodeT5
    "CodeT5Embedder",
    "UniXcoderEmbedder",
    "MultiEmbedder",
]
