#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
utils - Utility functions for vulnerability detection
"""

from .data_loader import (
    load_from_cache,
    load_dataset,
    create_data_loaders,
    get_class_weights,
    get_dataset_stats,
    print_dataset_stats,
)

# NEW: Import graph truncation (optional - graceful fallback if not present)
try:
    from .graph_truncation import GraphTruncator, GraphTruncationTransform
except ImportError:
    GraphTruncator = None
    GraphTruncationTransform = None


from .metrics import (
    compute_metrics,
    find_best_threshold,
    compute_full_evaluation,
    print_metrics,
    compare_with_baselines,
)

from .losses import (
    FocalLoss,
    LabelSmoothingBCE,
    SoftF1Loss,
    CombinedLoss,
    AntiCollapseLoss,
    create_loss,
)


__all__ = [
    # Data loading
    "load_from_cache",
    "load_dataset",
    "create_data_loaders",
    "get_class_weights",
    "get_dataset_stats",
    "print_dataset_stats",
    
    # Metrics
    "compute_metrics",
    "find_best_threshold",
    "compute_full_evaluation",
    "print_metrics",
    "compare_with_baselines",
    
    # Losses
    "FocalLoss",
    "LabelSmoothingBCE",
    "SoftF1Loss",
    "CombinedLoss",
    "AntiCollapseLoss",
    "create_loss",
]
