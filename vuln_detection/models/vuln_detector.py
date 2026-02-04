#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
vuln_detector.py - Main vulnerability detection model (FIXED V3 - WITH CALL-AWARE)

FIXES V3:
  - Added CallAwareDevign model type
  - "call_aware" GNN type now supported
  - Diagnostic-driven: focuses attention on CALL nodes

FIXES V2:
  - Preset models (DevignModel, ImprovedDevign) now accept kwargs overrides
  - gnn_layers, embedder_type, pooling_type can be customized
  - create_model() passes through all relevant arguments

Combines:
- Embedder (Word2Vec, CodeBERT, etc.)
- Structural Features (Degree statistics, Leaf/Root indicators)
- GNN (optional, e.g., GGNN, GCN, CallAware)
- Pooling (e.g., Multi-Stat, Attention)
- Classifier
"""

from typing import Optional, Dict, Any, Tuple
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data
from torch_geometric.utils import degree

from ..embeddings import create_embedder, list_embedders
from .gnn_layers import create_gnn
from .pooling import create_pooling


class VulnDetector(nn.Module):
    """
    Modular vulnerability detection model.
    
    Architecture:
        Input → Embedder [+ Structure] → Projection → (optional) GNN → Pooling → Classifier → Output
    
    This flexible architecture supports:
    1. Pure Embedding + MLP (GraphLevelMLP)
    2. Original Devign (Word2Vec + GGNN + Conv Readout)
    3. Improved Devign (Word2Vec + Structure + Shallow GGNN + MultiStat Pool)
    """
    
    def __init__(
        self,
        # Embedder config
        embedder_type: str = "codebert_hybrid",
        embedder_kwargs: Optional[Dict[str, Any]] = None,
        
        # Structural features config
        use_structural_features: bool = False,
        
        # GNN config
        gnn_type: str = "none",  # "none", "ggnn", "edge_type", "gcn", "gat", "call_aware"
        gnn_layers: int = 1,
        num_edge_types: int = 20,
        edge_text_dim: int = 0,
        
        # Pooling config
        pooling_type: str = "combined",  # "mean", "max", "mean_max", "multi_stat", "attention", "combined"
        pooling_kwargs: Optional[Dict[str, Any]] = None,
        
        # General config
        input_dim: int = 796,  # Default for GraphCodeBERT (28 one-hot + 768)
        hidden_dim: int = 128,
        num_classes: int = 1,  # Binary classification
        dropout: float = 0.2,
        
        # Classifier config
        classifier_hidden: Optional[int] = None,  # If None, use hidden_dim // 2
        
        # CALL-aware specific (NEW)
        num_node_types: int = 16,
        call_node_idx: int = 2,
        reaching_def_edge_type: int = 9,
    ):
        super().__init__()
        
        self.hidden_dim = hidden_dim
        self.gnn_type = gnn_type
        self.gnn_layers = gnn_layers
        self.use_structural_features = use_structural_features
        self.num_node_types = num_node_types
        self.edge_text_dim = edge_text_dim
        
        # 1. Create Embedder
        embedder_kwargs = embedder_kwargs or {}
        embedder_kwargs.setdefault("output_dim", hidden_dim)
        embedder_kwargs.setdefault("dropout", dropout)
        
        self.embedder = create_embedder(embedder_type, **embedder_kwargs)
        
        # 2. Structural Feature Projection
        # If enabled, we calculate 5 features (In-Deg, Out-Deg, Total-Deg, Is-Leaf, Is-Root)
        # We concatenate these with the embedding and project back to hidden_dim
        # This ensures the GNN receives the correct dimension size.
        if use_structural_features:
            self.struct_dim = 5
            self.feature_proj = nn.Sequential(
                nn.Linear(hidden_dim + self.struct_dim, hidden_dim),
                nn.LayerNorm(hidden_dim),
                nn.GELU(),
                nn.Dropout(dropout)
            )
        else:
            self.feature_proj = nn.Identity()
        
        # 3. Create GNN (optional)
        if gnn_type != "none":
            self.gnn = create_gnn(
                gnn_type=gnn_type,
                hidden_dim=hidden_dim,
                num_edge_types=num_edge_types,
                num_layers=gnn_layers,
                dropout=dropout,
                # CALL-aware specific kwargs
                num_node_types=num_node_types,
                call_node_idx=call_node_idx,
                reaching_def_edge_type=reaching_def_edge_type,
                edge_text_dim=edge_text_dim,
            )
        else:
            self.gnn = None
        
        # 4. Create Pooling
        pooling_kwargs = pooling_kwargs or {}
        self.pooling = create_pooling(
            pooling_type=pooling_type,
            hidden_dim=hidden_dim,
            dropout=dropout,
            **pooling_kwargs,
        )
        
        # 5. Create Classifier
        classifier_input_dim = self.pooling.output_dim
        classifier_hidden = classifier_hidden or hidden_dim // 2
        
        self.classifier = nn.Sequential(
            nn.Linear(classifier_input_dim, classifier_hidden),
            nn.LayerNorm(classifier_hidden),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(classifier_hidden, num_classes),
        )
        
        # Store config for saving/loading
        self.config = {
            "embedder_type": embedder_type,
            "gnn_type": gnn_type,
            "gnn_layers": gnn_layers,
            "pooling_type": pooling_type,
            "use_structural_features": use_structural_features,
            "hidden_dim": hidden_dim,
            "dropout": dropout,
            "num_node_types": num_node_types,
            "call_node_idx": call_node_idx,
            "edge_text_dim": edge_text_dim,
        }
    
    def _compute_structural_features(self, data: Data) -> torch.Tensor:
        """
        Compute explicit structural features for each node.
        These help simple models (like Word2Vec) understand graph topology.
        
        Features (5 dims):
        1. In-degree (normalized)
        2. Out-degree (normalized)
        3. Total degree (normalized)
        4. Is leaf node (boolean)
        5. Is root node (boolean)
        """
        num_nodes = data.x.size(0)
        edge_index = data.edge_index
        
        # Calculate degrees using PyG utility
        in_deg = degree(edge_index[1], num_nodes=num_nodes)
        out_deg = degree(edge_index[0], num_nodes=num_nodes)
        total_deg = in_deg + out_deg
        
        # Normalize by max degree in the graph (avoiding division by zero)
        max_deg = total_deg.max().clamp(min=1)
        
        return torch.stack([
            in_deg / max_deg,
            out_deg / max_deg,
            total_deg / max_deg,
            (out_deg == 0).float(), # Is Leaf
            (in_deg == 0).float(),  # Is Root
        ], dim=1)

    def forward(
        self, 
        data: Data,
        return_embeddings: bool = False,
    ) -> torch.Tensor:
        """
        Forward pass.
        
        Args:
            data: PyG Data object with x, edge_index, edge_type, batch
            return_embeddings: If True, also return graph embeddings
        
        Returns:
            Logits [B, num_classes] or (logits, graph_embeddings)
        """
        x = data.x.float()
        edge_index = data.edge_index
        edge_type = getattr(data, 'edge_type', None)
        edge_text = getattr(data, 'edge_text_emb', None)
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None \
                else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # 1. Embed nodes
        h = self.embedder(x, data)
        
        # 2. Augment with Structural Features (if enabled)
        if self.use_structural_features:
            struct_feats = self._compute_structural_features(data).to(h.device)
            # Concatenate [Embedding | Structure]
            h = torch.cat([h, struct_feats], dim=-1)
            # Project back to hidden_dim
            h = self.feature_proj(h)
        
        # 3. Apply GNN (if enabled)
        if self.gnn is not None:
            # For call_aware GNN, we may need to pass additional info
            if self.gnn_type == "call_aware":
                # Get node types from input features
                if x.shape[1] >= self.num_node_types:
                    node_types = x[:, :self.num_node_types].argmax(dim=1)
                else:
                    node_types = torch.zeros(x.size(0), dtype=torch.long, device=x.device)
                h = self.gnn(h, edge_index, edge_type, batch, node_types)
            elif self.gnn_type == "edge_type_text":
                h = self.gnn(h, edge_index, edge_type, edge_text)
            else:
                h = self.gnn(h, edge_index, edge_type)
        
        # 4. Pool node features to graph representation
        graph_emb = self.pooling(h, batch)
        
        # 5. Classify
        logits = self.classifier(graph_emb)
        
        if return_embeddings:
            return logits, graph_emb
        return logits
    
    def get_config(self) -> Dict[str, Any]:
        """Get model configuration."""
        return self.config.copy()
    
    @classmethod
    def from_config(cls, config: Dict[str, Any]) -> "VulnDetector":
        """Create model from config dict."""
        return cls(**config)


class DevignModel(VulnDetector):
    """
    Original Devign architecture (for comparison).
    
    Uses:
    - Word2Vec Embeddings (or Learned)
    - Deep GGNN (4 steps by default, but can be overridden)
    - Conv1D Readout (DevignConvHead)
    
    FIXED: Now accepts **kwargs to override defaults.
    """
    def __init__(
        self,
        input_dim: int = 796,
        hidden_dim: int = 200,
        num_edge_types: int = 15,
        gnn_layers: int = 4,  # Default 4 steps, but can be overridden
        dropout: float = 0.1,
        use_word2vec: bool = False,
        embedder_type: str = None,  # Override embedder
        pooling_type: str = None,   # Override pooling
        **kwargs,  # Accept additional kwargs
    ):
        # Allow embedder_type override
        final_embedder = embedder_type or ("word2vec" if use_word2vec else "learned")
        final_pooling = pooling_type or "devign"
        
        super().__init__(
            embedder_type=final_embedder,
            embedder_kwargs={"hidden_dim": hidden_dim},
            gnn_type="ggnn",
            gnn_layers=gnn_layers,  # Now configurable!
            num_edge_types=num_edge_types,
            pooling_type=final_pooling,
            hidden_dim=hidden_dim,
            dropout=dropout,
        )


class ImprovedDevign(VulnDetector):
    """
    Improved Devign Architecture (Recommended).
    
    Optimizations applied based on research findings:
    1. Embedder: Word2Vec (128d) - Captures semantic meaning better than OneHot.
    2. Structure: Explicitly adds Degree/Leaf/Root features to nodes.
    3. GNN: Shallow GGNN (1 layer default) - Prevents over-smoothing of features.
    4. Pooling: Multi-Statistic (Mean + Max + Std) - Captures more graph signal than Conv1D.
    
    FIXED: Now accepts **kwargs to override defaults (gnn_layers, embedder_type, etc.)
    """
    def __init__(
        self,
        input_dim: int = 128,
        hidden_dim: int = 128,
        num_edge_types: int = 20,
        dropout: float = 0.2,
        # NEW: Allow overriding defaults
        gnn_layers: int = 1,
        gnn_type: str = "ggnn",
        embedder_type: str = "word2vec",
        pooling_type: str = "multi_stat",
        use_structural_features: bool = True,
        **kwargs,  # Accept additional kwargs
    ):
        super().__init__(
            embedder_type=embedder_type,
            embedder_kwargs={"output_dim": hidden_dim},
            use_structural_features=use_structural_features,
            gnn_type=gnn_type,
            gnn_layers=gnn_layers,  # Now configurable!
            num_edge_types=num_edge_types,
            pooling_type=pooling_type,
            pooling_kwargs={"project": True},
            hidden_dim=hidden_dim,
            dropout=dropout,
            **kwargs,  # Pass through remaining kwargs
        )


# =============================================================================
# NEW: CallAwareDevign - CALL node focused architecture
# =============================================================================

class CallAwareDevign(VulnDetector):
    """
    CALL-Aware Devign Architecture (NEW - Based on Diagnostic Findings).
    
    Key insight from data analysis:
    - Sensitive APIs (malloc, free, strcpy) appear ONLY in vulnerable code
    - Edge types have identical distribution in vuln/safe (not discriminative)
    - The signal is in CALL nodes, not edge types!
    
    Architecture:
    1. Embedder: Word2Vec - Captures API names
    2. GNN: CALL-aware GNN - Focuses on CALL nodes + data-flow context
    3. Pooling: Multi-stat with CALL attention
    4. Dual-path classifier: CALL-focused + Global
    
    Usage:
        model = create_model("call_aware", input_dim=272, hidden_dim=256, ...)
    """
    def __init__(
        self,
        input_dim: int = 272,
        hidden_dim: int = 256,
        num_edge_types: int = 18,
        num_node_types: int = 16,
        call_node_idx: int = 2,
        reaching_def_edge_type: int = 9,
        dropout: float = 0.2,
        gnn_layers: int = 4,
        embedder_type: str = "word2vec",
        pooling_type: str = "multi_stat",
        use_structural_features: bool = True,
        **kwargs,
    ):
        super().__init__(
            embedder_type=embedder_type,
            embedder_kwargs={"output_dim": hidden_dim},
            use_structural_features=use_structural_features,
            gnn_type="call_aware",  # Use CALL-aware GNN!
            gnn_layers=gnn_layers,
            num_edge_types=num_edge_types,
            pooling_type=pooling_type,
            pooling_kwargs={"project": True},
            hidden_dim=hidden_dim,
            dropout=dropout,
            num_node_types=num_node_types,
            call_node_idx=call_node_idx,
            reaching_def_edge_type=reaching_def_edge_type,
        )


class GraphLevelMLP(VulnDetector):
    """
    Graph-level MLP baseline (No GNN).
    
    Achieves high performance by ignoring graph topology and 
    focusing on aggregate statistics of node features.
    """
    def __init__(
        self,
        input_dim: int = 796,
        hidden_dim: int = 128,
        dropout: float = 0.2,
        gcb_compress_to: int = 64,
        **kwargs,
    ):
        super().__init__(
            embedder_type="codebert_hybrid",
            embedder_kwargs={
                "gcb_dim": input_dim - 28,
                "output_dim": hidden_dim,
                "compress_to": gcb_compress_to,
                "dropout": dropout,
            },
            gnn_type="none",
            pooling_type="multi_stat",
            pooling_kwargs={"project": True},
            hidden_dim=hidden_dim,
            dropout=dropout,
        )


class AttentionVulnDetector(VulnDetector):
    """Attention-based vulnerability detector."""
    def __init__(
        self,
        input_dim: int = 796,
        hidden_dim: int = 128,
        num_edge_types: int = 20,
        dropout: float = 0.2,
        use_gnn: bool = True,
        gnn_layers: int = 1,
        **kwargs,
    ):
        super().__init__(
            embedder_type="codebert",
            embedder_kwargs={
                "compression": "linear",
                "use_structural": True,
            },
            gnn_type="edge_type" if use_gnn else "none",
            gnn_layers=gnn_layers,
            num_edge_types=num_edge_types,
            pooling_type="combined",
            pooling_kwargs={"strategies": ["attention", "mean", "max"]},
            hidden_dim=hidden_dim,
            dropout=dropout,
        )


def create_model(
    model_type: str,
    **kwargs,
) -> VulnDetector:
    """
    Factory function to create models by type.
    
    FIXED V3: Added "call_aware" model type.
    
    Args:
        model_type: "devign", "improved_devign", "call_aware", "graph_level_mlp", "attention", "custom"
        **kwargs: Model-specific arguments (gnn_layers, embedder_type, etc.)
    
    Returns:
        Model instance
    
    Examples:
        # Default improved_devign (1 GNN layer)
        model = create_model("improved_devign", hidden_dim=128)
        
        # CALL-aware model (NEW - recommended based on diagnostics!)
        model = create_model("call_aware", hidden_dim=256, num_edge_types=18)
        
        # Override GNN layers
        model = create_model("improved_devign", hidden_dim=128, gnn_layers=8)
        
        # Override embedder
        model = create_model("improved_devign", embedder_type="learned", gnn_layers=4)
    """
    if model_type == "devign":
        return DevignModel(**kwargs)
    elif model_type == "improved_devign":
        return ImprovedDevign(**kwargs)
    elif model_type == "call_aware":
        # NEW: CALL-aware model
        return CallAwareDevign(**kwargs)
    elif model_type == "graph_level_mlp":
        return GraphLevelMLP(**kwargs)
    elif model_type == "attention":
        return AttentionVulnDetector(**kwargs)
    elif model_type == "custom":
        return VulnDetector(**kwargs)
    else:
        raise ValueError(f"Unknown model type: {model_type}. "
                        f"Choose from: devign, improved_devign, call_aware, graph_level_mlp, attention, custom")
