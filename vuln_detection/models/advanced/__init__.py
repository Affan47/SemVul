#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
advanced - Advanced model architectures for vulnerability detection

Available models:
- MultiViewGGNN: Multi-view GGNN processing AST/CFG/DFG separately
- HGTDevignModel: Heterogeneous Graph Transformer
- HyperDevignModel: Hypergraph Neural Network with Dual Attention
- RGATDevignModel: Relational Graph Attention Network
- DevignModel: Original Devign implementation (comprehensive)

Note: These are the advanced research models. For simpler models,
use the main models module (VulnDetector, GraphLevelMLP, etc.)
"""

# Multi-view GGNN
from .multiview import (
    MultiViewGGNN,
    ViewEncoder,
    NodeConditionedAttentionFusion,
)

# Heterogeneous Graph Transformer
from .hgt import (
    HGTDevignModel,
    HGTBlock,
)

# Hypergraph with Dual Attention
from .hypergraph import (
    HyperDevignModel,
    DualAttentionBlock,
)

# Relational Graph Attention
from .rgat import (
    RGATDevignModel,
    RGATBlock,
    MemoryEfficientRGATConv,
)

# Original Devign (comprehensive implementation)
from .devign_original import (
    DevignModel as DevignOriginal,
    RelGraphConv,
    HybridGPSLayer,
    CachedDataset,
    SizeBucketBatchSampler,
)

__all__ = [
    # Multi-view
    "MultiViewGGNN",
    "ViewEncoder",
    "NodeConditionedAttentionFusion",
    
    # HGT
    "HGTDevignModel",
    "HGTBlock",
    
    # Hypergraph
    "HyperDevignModel",
    "DualAttentionBlock",
    
    # RGAT
    "RGATDevignModel",
    "RGATBlock",
    "MemoryEfficientRGATConv",
    
    # Original Devign
    "DevignOriginal",
    "RelGraphConv",
    "HybridGPSLayer",
    "CachedDataset",
    "SizeBucketBatchSampler",
]
