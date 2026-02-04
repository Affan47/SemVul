#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
examples - Example experiment scripts

These scripts demonstrate different approaches to vulnerability detection:

1. graph_level_classifier.py
   - Best performing approach (0.632 AUC)
   - Uses graph-level statistics (mean + max + std)
   - No GNN (avoids over-smoothing)

2. mlp_baseline.py
   - Simple MLP baseline without GNN
   - Useful for understanding signal in features

3. feature_selection_model.py
   - Experiments with selecting discriminative dimensions
   - Found that top-100 dims WITHOUT one-hot works best

4. improved_baseline.py
   - Edge-type aware GNN with attention pooling
   - Uses CPG structure properly

5. learned_embedding_model.py
   - Alternative to GraphCodeBERT
   - Learned embeddings from node types + structure

Usage:
    Run as standalone scripts:
    
    python -m vuln_detection.examples.graph_level_classifier \\
        --cache-dir /path/to/cache \\
        --dataset-name devign_normfunc_v2 \\
        --cache-signature caffd6ae8652870d
"""

__all__ = []
