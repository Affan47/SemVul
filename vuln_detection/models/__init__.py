#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
models - Neural network models for vulnerability detection

Core models (simple, recommended):
- VulnDetector: Modular base model
- DevignModel: Original Devign architecture (GGNN + Conv readout)
- ImprovedDevign: Optimized architecture (Word2Vec + Structure + Shallow GGNN)
- CallAwareDevign: CALL-node focused architecture (NEW - based on diagnostics!)
- GraphLevelMLP: Best performing (no GNN, multi-stat pooling)
- AttentionVulnDetector: Attention-based pooling

Advanced models (for research):
- MultiViewGGNN: Multi-view processing (AST/CFG/DFG)
- HGTDevignModel: Heterogeneous Graph Transformer
- HyperDevignModel: Hypergraph with Dual Attention
- RGATDevignModel: Relational Graph Attention
- DevignOriginal: Comprehensive Devign implementation

CALL-aware models (NEW):
- CallAwareGNN: GNN layer that focuses on CALL nodes
- CallAwareVulnDetector: Complete CALL-aware model
- SimpleAPIDetector: Simple baseline focusing on API presence

See models.advanced for advanced architectures.
See models.call_aware for CALL-aware components.
"""

from .gnn_layers import (
    GGNN,
    GGNNLayer,
    EdgeTypeGNN,
    EdgeTypeTextGNN,
    ShallowGNN,
    NoGNN,
    create_gnn,
)

from .pooling import (
    MeanPooling,
    MaxPooling,
    MeanMaxPooling,
    MultiStatPooling,
    AttentionPooling,
    # HierarchicalAttentionPooling,  <-- REMOVED
    DevignConvHead,
    CombinedPooling,
    create_pooling,
)

from .vuln_detector import (
    VulnDetector,
    DevignModel,
    ImprovedDevign,
    CallAwareDevign,  # <-- NEW
    GraphLevelMLP,
    AttentionVulnDetector,
    create_model,
)

# Shared layers
from .layers import (
    DevignConvHead as DevignConvHeadOriginal,
    RelGraphConv,
    NodeConditionedAttention,
)

# CALL-aware models (NEW - optional import)
try:
    from .call_aware import (
        CallAwareGNN,
        CallNodeAttention,
        CALLContextEncoder,
        CallAwareVulnDetector,
        SimpleAPIDetector,
        create_call_aware_model,
    )
    CALL_AWARE_AVAILABLE = True
except ImportError:
    CALL_AWARE_AVAILABLE = False
    CallAwareGNN = None
    CallNodeAttention = None
    CALLContextEncoder = None
    CallAwareVulnDetector = None
    SimpleAPIDetector = None
    create_call_aware_model = None

# HAGNN model (NEW - Stage 3)
try:
    from .hagnn import (
        HAGNNVulnDetector,
        HAGNNLayer,
        EdgeTypeGATConv,
        VulnAwarePooling,
        create_hagnn_model,
    )
    HAGNN_AVAILABLE = True
except ImportError:
    HAGNN_AVAILABLE = False
    HAGNNVulnDetector = None

# Advanced models (optional import)
try:
    from .advanced import (
        MultiViewGGNN,
        HGTDevignModel,
        HyperDevignModel,
        RGATDevignModel,
        DevignOriginal,
    )
    ADVANCED_AVAILABLE = True
except ImportError:
    ADVANCED_AVAILABLE = False


__all__ = [
    # GNN layers
    "GGNN",
    "GGNNLayer",
    "EdgeTypeGNN",
    "EdgeTypeTextGNN",
    "ShallowGNN",
    "NoGNN",
    "create_gnn",
    
    # Pooling
    "MeanPooling",
    "MaxPooling",
    "MeanMaxPooling",
    "MultiStatPooling",
    "AttentionPooling",
    # "HierarchicalAttentionPooling", <-- REMOVED
    "DevignConvHead",
    "CombinedPooling",
    "create_pooling",
    
    # Core Models
    "VulnDetector",
    "DevignModel",
    "ImprovedDevign",
    "CallAwareDevign",  # <-- NEW
    "GraphLevelMLP",
    "AttentionVulnDetector",
    "create_model",
    
    # Shared layers
    "DevignConvHeadOriginal",
    "RelGraphConv",
    "NodeConditionedAttention",
    
    # CALL-aware (if available)
    "CallAwareGNN",
    "CallNodeAttention",
    "CALLContextEncoder",
    "CallAwareVulnDetector",
    "SimpleAPIDetector",
    "create_call_aware_model",
    "CALL_AWARE_AVAILABLE",
    
    # Advanced (if available)
    "MultiViewGGNN",
    "HGTDevignModel",
    "HyperDevignModel",
    "RGATDevignModel",
    "DevignOriginal",
    "ADVANCED_AVAILABLE",
]
