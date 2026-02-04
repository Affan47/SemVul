#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
vuln_detection - Modular Vulnerability Detection with GNNs

A comprehensive library for vulnerability detection in code using
Graph Neural Networks and various embedding strategies.

Quick Start:
    from vuln_detection import VulnDetector, create_model
    from vuln_detection.embeddings import list_embedders
    from vuln_detection.utils import load_dataset, compute_full_evaluation
    
    # List available embedders
    print(list_embedders())
    # ['word2vec', 'learned', 'codebert', 'graphcodebert', 
    #  'codebert_selective', 'codebert_hybrid', 'codet5', 
    #  'unixcoder', 'multi_embedder']
    
    # Create improved model (Recommended)
    model = create_model("improved_devign")
    
    # Create baseline (Best performing MLP)
    model = create_model("graph_level_mlp")
    
    # Load data
    train, val, test = load_dataset(
        cache_dir="path/to/cache",
        dataset_name="devign_normfunc_v2",
        cache_signature="caffd6ae8652870d",
    )

Training:
    # Basic models
    python -m vuln_detection.train --model-type improved_devign ...
    
    # Advanced models (RGAT, MultiView, HGT, HyperGraph)
    python -m vuln_detection.train_advanced --model-type rgat ...

Author: Anonymous
Purpose: GNN-based vulnerability detection research
"""

__version__ = "1.2.0"

# Import main components
from .models import (
    VulnDetector,
    DevignModel,
    ImprovedDevign,
    GraphLevelMLP,
    AttentionVulnDetector,
    create_model,
)

from .embeddings import (
    create_embedder,
    list_embedders,
    EmbedderRegistry,
)

from .utils import (
    load_dataset,
    create_data_loaders,
    get_class_weights,
    compute_full_evaluation,
    print_metrics,
    compare_with_baselines,
    create_loss,
)
# NEW: Import graph truncation (optional - graceful fallback if not present)
try:
    from .graph_truncation import GraphTruncator, GraphTruncationTransform
except ImportError:
    GraphTruncator = None
    GraphTruncationTransform = None

# Import training modules (for python -m vuln_detection.train)
# from . import train
# from . import train_advanced

# Import advanced models (optional - may not be available)
try:
    from .models.advanced import (
        RGATDevignModel,
        MultiViewGGNN,
        HGTDevignModel,
        HyperDevignModel,
    )
    ADVANCED_MODELS_AVAILABLE = True
except ImportError:
    ADVANCED_MODELS_AVAILABLE = False


__all__ = [
    # Version
    "__version__",
    
    # Models
    "VulnDetector",
    "DevignModel",
    "ImprovedDevign",
    "GraphLevelMLP",
    "AttentionVulnDetector",
    "create_model",
    
    # Embeddings
    "create_embedder",
    "list_embedders",
    "EmbedderRegistry",
    
    # Utils
    "load_dataset",
    "create_data_loaders",
    "get_class_weights",
    "compute_full_evaluation",
    "print_metrics",
    "compare_with_baselines",
    "create_loss",
    
    # Training modules
    "train",
    "train_advanced",
    
    # Advanced models (if available)
    "RGATDevignModel",
    "MultiViewGGNN",
    "HGTDevignModel",
    "HyperDevignModel",
    "ADVANCED_MODELS_AVAILABLE",
]
