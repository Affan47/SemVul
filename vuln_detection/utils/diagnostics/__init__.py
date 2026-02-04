#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnostics - Diagnostic tools for debugging vulnerability detection models

Available tools:
- diagnose_data_integrity: Check data labels, features, similarity
- diagnose_gnn_vs_mlp: Compare GNN vs MLP performance
- analyze_feature_parts: Analyze one-hot vs embedding features
- verify_labels: Verify label alignment with manifest

Usage:
    Run as standalone scripts or import functions:
    
    python -m vuln_detection.utils.diagnostics.diagnose_data_integrity \\
        --cache-dir /path/to/cache \\
        --dataset-name devign_normfunc_v2 \\
        --cache-signature caffd6ae8652870d
"""

# These are meant to be run as scripts, but key functions can be imported
# from .diagnose_data_integrity import (
#     check_label_distribution,
#     check_feature_similarity,
#     check_feature_uniqueness,
# )

__all__ = []
