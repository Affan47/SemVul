#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gnn_layers.py - GNN layers for vulnerability detection

Includes:
- GGNN (Gated Graph Neural Network) - used in original Devign
- EdgeTypeGNN - edge-type aware message passing
- ShallowGNN - wrapper for 1-2 layer GNNs to avoid over-smoothing
- CallAwareGNN - CALL node focused GNN (NEW!)
"""

from typing import Optional, List
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import MessagePassing, GCNConv, GATv2Conv
from torch_geometric.utils import add_self_loops


class GGNNLayer(MessagePassing):
    """
    Single step of a Gated Graph Neural Network (Devign style).
    
    Mathematical formulation:
        m_v = Σ (W_e * h_u)  for all neighbors u connected by edge type e
        h_v' = GRU(m_v, h_v)
    
    Args:
        hidden_dim: Input and output dimension (must be same for GRU)
        num_edge_types: Number of distinct edge relations (AST, CFG, etc.)
    """
    
    def __init__(self, hidden_dim: int, num_edge_types: int = 1):
        super().__init__(aggr='add')
        
        self.hidden_dim = hidden_dim
        self.num_edge_types = num_edge_types
        
        # Edge-type specific transformations: W_e
        self.edge_transforms = nn.ModuleList([
            nn.Linear(hidden_dim, hidden_dim, bias=False)
            for _ in range(num_edge_types)
        ])
        
        # GRU cell for node update
        self.gru = nn.GRUCell(hidden_dim, hidden_dim)
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor, edge_type: Optional[torch.Tensor] = None) -> torch.Tensor:
        # Default edge type to 0 if not provided
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        # 1. Aggregate messages
        aggr_out = self.propagate(edge_index, x=x, edge_type=edge_type)
        
        # 2. GRU update (Input: aggregated messages, Hidden: current node state)
        return self.gru(aggr_out, x)
    
    def message(self, x_j: torch.Tensor, edge_type: torch.Tensor) -> torch.Tensor:
        """
        Compute messages. Different linear transform based on edge type.
        Masking is used to handle multiple types in one batch efficiently.
        """
        out = torch.zeros_like(x_j)
        
        # Iterate over known edge types
        for et in range(self.num_edge_types):
            mask = (edge_type == et)
            if mask.any():
                # Apply W_e * h_u
                out[mask] = self.edge_transforms[et](x_j[mask])
                
        return out


class GGNN(nn.Module):
    """
    Full GGNN module (Original Devign Architecture).
    
    It unrolls the GGNNLayer for `num_steps`.
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_edge_types: int = 15,
        num_steps: int = 4,
        dropout: float = 0.1,
    ):
        super().__init__()
        
        self.num_steps = num_steps
        self.layer = GGNNLayer(hidden_dim, num_edge_types)
        self.dropout = nn.Dropout(dropout)
        self.norm = nn.LayerNorm(hidden_dim)
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor, edge_type: Optional[torch.Tensor] = None) -> torch.Tensor:
        # Unroll the recurrence
        for _ in range(self.num_steps):
            x = self.layer(x, edge_index, edge_type)
            x = self.dropout(x)
        
        # Final normalization
        return self.norm(x)


class EdgeTypeGNN(MessagePassing):
    """
    Edge-type aware GNN layer (Alternative to GGNN).
    
    Uses an explicit embedding for edge types and concatenates it
    with node features, rather than using separate weight matrices.
    This is often more parameter-efficient if num_edge_types is large.
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_edge_types: int = 20,
        dropout: float = 0.1,
    ):
        super().__init__(aggr='add')
        
        self.hidden_dim = hidden_dim
        
        # Embed edge types: [num_types, hidden_dim]
        self.edge_embed = nn.Embedding(num_edge_types, hidden_dim)
        
        # Message calculation: MLP([source, target, edge]) -> hidden
        self.msg_mlp = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
        )
        
        # Update function: MLP([node, aggregated]) -> hidden
        self.update_mlp = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.GELU(),
        )
        
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        # Get edge embeddings
        edge_attr = self.edge_embed(edge_type)
        
        # Propagate
        out = self.propagate(edge_index, x=x, edge_attr=edge_attr)
        
        # Residual connection + Norm
        return self.norm(x + self.dropout(out))
    
    def message(self, x_i: torch.Tensor, x_j: torch.Tensor, edge_attr: torch.Tensor) -> torch.Tensor:
        # Combine target(i), source(j), and edge info
        return self.msg_mlp(torch.cat([x_i, x_j, edge_attr], dim=-1))
    
    def update(self, aggr_out: torch.Tensor, x: torch.Tensor) -> torch.Tensor:
        # Combine old state and aggregated messages
        return self.update_mlp(torch.cat([x, aggr_out], dim=-1))


class EdgeTypeTextGNN(MessagePassing):
    """
    Edge-type + edge-text aware GNN layer.
    
    Combines edge type embeddings with edge text embeddings (if provided).
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_edge_types: int = 20,
        edge_text_dim: int = 0,
        dropout: float = 0.1,
    ):
        super().__init__(aggr='add')
        
        self.hidden_dim = hidden_dim
        self.edge_text_dim = edge_text_dim
        
        self.edge_embed = nn.Embedding(num_edge_types, hidden_dim)
        
        if edge_text_dim and edge_text_dim > 0:
            self.edge_text_proj = nn.Sequential(
                nn.Linear(edge_text_dim, hidden_dim),
                nn.LayerNorm(hidden_dim),
                nn.GELU(),
            )
        else:
            self.edge_text_proj = None
        
        self.msg_mlp = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
        )
        
        self.update_mlp = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.GELU(),
        )
        
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: Optional[torch.Tensor] = None,
        edge_text: Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        edge_attr = self.edge_embed(edge_type)
        
        if self.edge_text_proj is not None and edge_text is not None:
            if edge_text.dim() == 1:
                edge_text = edge_text.unsqueeze(-1)
            if edge_text.size(0) == edge_attr.size(0):
                edge_text = edge_text.to(edge_attr.device)
                edge_attr = edge_attr + self.edge_text_proj(edge_text)
        
        out = self.propagate(edge_index, x=x, edge_attr=edge_attr)
        return self.norm(x + self.dropout(out))
    
    def message(self, x_i: torch.Tensor, x_j: torch.Tensor, edge_attr: torch.Tensor) -> torch.Tensor:
        return self.msg_mlp(torch.cat([x_i, x_j, edge_attr], dim=-1))
    
    def update(self, aggr_out: torch.Tensor, x: torch.Tensor) -> torch.Tensor:
        return self.update_mlp(torch.cat([x, aggr_out], dim=-1))


class ShallowGNN(nn.Module):
    """
    Shallow GNN Wrapper (1-2 layers).
    
    This wrapper enforces a standard structure:
    Layer -> Activation -> Norm -> Residual -> Dropout
    
    It supports multiple backbone types: 'ggnn', 'edge_type', 'gcn', 'gat'.
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_edge_types: int = 20,
        num_layers: int = 1,
        gnn_type: str = "ggnn", 
        edge_text_dim: int = 0,
        dropout: float = 0.1,
    ):
        super().__init__()
        
        self.layers = nn.ModuleList()
        self.norms = nn.ModuleList()
        self.dropout = nn.Dropout(dropout)
        self.gnn_type = gnn_type
        
        for _ in range(num_layers):
            if gnn_type == "ggnn":
                self.layers.append(GGNNLayer(hidden_dim, num_edge_types))
            elif gnn_type == "edge_type":
                self.layers.append(EdgeTypeGNN(hidden_dim, num_edge_types, dropout))
            elif gnn_type == "edge_type_text":
                self.layers.append(
                    EdgeTypeTextGNN(
                        hidden_dim,
                        num_edge_types,
                        edge_text_dim=edge_text_dim,
                        dropout=dropout,
                    )
                )
            elif gnn_type == "gcn":
                self.layers.append(GCNConv(hidden_dim, hidden_dim))
            elif gnn_type == "gat":
                self.layers.append(GATv2Conv(hidden_dim, hidden_dim, heads=1))
            else:
                raise ValueError(f"Unknown GNN type for ShallowGNN: {gnn_type}")
            
            self.norms.append(nn.LayerNorm(hidden_dim))
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: Optional[torch.Tensor] = None,
        edge_text: Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        for layer, norm in zip(self.layers, self.norms):
            x_in = x
            
            # Apply layer
            if self.gnn_type in ["ggnn", "edge_type"]:
                x_out = layer(x, edge_index, edge_type)
            elif self.gnn_type == "edge_type_text":
                x_out = layer(x, edge_index, edge_type, edge_text)
            else:
                x_out = layer(x, edge_index)
            
            # For GGNN/EdgeType, they handle their own non-linearities usually,
            # but we apply standard stabilization here for the shallow block.
            if self.gnn_type != "ggnn": 
                # GGNNLayer uses GRU which has tanh, so explicit ReLU isn't strictly needed 
                # but valid. For GCN/GAT we definitely need it.
                x_out = F.gelu(x_out)
            
            # Norm + Residual + Dropout
            # Note: GGNNLayer output includes the 'x' update via GRU, so x_out is the new state.
            # However, adding a residual (x_in + x_out) essentially makes it a ResNet-style block.
            # For very shallow networks (1 layer), this is fine.
            x = norm(x_out + self.dropout(x_in))
            
        return x


class NoGNN(nn.Module):
    """
    Identity pass-through (No GNN).
    Used when we only want to evaluate the Embedder + Pooling.
    """
    
    def __init__(self, hidden_dim: int, **kwargs):
        super().__init__()
        self.hidden_dim = hidden_dim
    
    def forward(self, x, edge_index, edge_type=None, edge_text=None):
        return x


# =============================================================================
# NEW: CallAwareGNN - imported from call_aware module
# =============================================================================

try:
    from .call_aware import CallAwareGNN
    CALL_AWARE_AVAILABLE = True
except ImportError:
    CALL_AWARE_AVAILABLE = False
    CallAwareGNN = None


def create_gnn(
    gnn_type: str,
    hidden_dim: int,
    num_edge_types: int = 20,
    num_layers: int = 1,
    dropout: float = 0.1,
    **kwargs,
) -> nn.Module:
    """
    Factory function to create GNN by type.
    
    Args:
        gnn_type: "ggnn", "edge_type", "edge_type_text", "gcn", "gat", "call_aware", "none"
        hidden_dim: Hidden dimension
        num_edge_types: Number of edge types
        num_layers: Number of GNN layers
        dropout: Dropout rate
        **kwargs: Additional arguments (num_node_types, call_node_idx for call_aware)
    
    Returns:
        GNN module
    """
    if gnn_type == "none":
        return NoGNN(hidden_dim)
    
    # NEW: CALL-aware GNN
    if gnn_type == "call_aware":
        if not CALL_AWARE_AVAILABLE:
            raise ImportError(
                "CallAwareGNN not available. Make sure call_aware.py is in the models directory."
            )
        return CallAwareGNN(
            hidden_dim=hidden_dim,
            num_edge_types=num_edge_types,
            num_layers=num_layers,
            num_node_types=kwargs.get('num_node_types', 16),
            call_node_idx=kwargs.get('call_node_idx', 2),
            reaching_def_edge_type=kwargs.get('reaching_def_edge_type', 9),
            dropout=dropout,
        )
    
    # For standard Devign (Deep GGNN), we use the dedicated class
    if gnn_type == "ggnn" and num_layers > 2:
        return GGNN(hidden_dim, num_edge_types, num_steps=num_layers, dropout=dropout)
    
    # For "Improved Devign" (Shallow) or other types, we use the Shallow wrapper
    # This supports 'ggnn', 'edge_type', 'edge_type_text', 'gcn', 'gat'
    return ShallowGNN(
        hidden_dim=hidden_dim, 
        num_edge_types=num_edge_types, 
        num_layers=num_layers, 
        gnn_type=gnn_type, 
        edge_text_dim=kwargs.get('edge_text_dim', 0),
        dropout=dropout
    )
