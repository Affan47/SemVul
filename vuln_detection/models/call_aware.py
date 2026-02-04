#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
call_aware.py - CALL-Aware Vulnerability Detection Components

Based on diagnostic finding: The vulnerability signal is in CALL nodes 
(which APIs are called), not in edge types or graph structure.

Components:
- CallAwareGNN: GNN layer that focuses attention on CALL nodes
- CallNodeAttention: Attention mechanism prioritizing CALL nodes
- CALLContextEncoder: Encodes data-flow context around CALL nodes
- CallAwareVulnDetector: Complete model using CALL-aware architecture

Usage:
    from vuln_detection.models.call_aware import CallAwareGNN, CallAwareVulnDetector
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import GATConv, GCNConv, global_mean_pool, global_max_pool
from torch_geometric.utils import softmax
from typing import Optional, Tuple, Dict, Any


# =============================================================================
# CALL Node Attention
# =============================================================================

class CallNodeAttention(nn.Module):
    """
    Attention mechanism that learns to focus on CALL nodes.
    
    Instead of treating all nodes equally, this learns which nodes
    are important for vulnerability detection.
    """
    
    def __init__(
        self, 
        hidden_dim: int, 
        num_node_types: int = 16,
        call_node_idx: int = 2,
    ):
        super().__init__()
        
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        
        # Learnable importance per node type
        self.node_type_importance = nn.Parameter(torch.ones(num_node_types))
        
        # Attention network
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        # Initialize with prior knowledge about vulnerability-relevant nodes
        # These indices depend on your vocabulary - adjust as needed
        self._init_node_importance()
    
    def _init_node_importance(self):
        """Initialize node type importance based on vulnerability relevance."""
        with torch.no_grad():
            # CALL nodes are most important (index may vary)
            if self.call_node_idx < self.num_node_types:
                self.node_type_importance.data[self.call_node_idx] = 3.0
            
            # Other important nodes (adjust indices based on your vocab)
            # Typical order: METHOD=0, BLOCK=1, CALL=2, IDENTIFIER=3, LITERAL=4, 
            # RETURN=5, LOCAL=6, CONTROL_STRUCTURE=7, ...
            important_indices = [5, 7]  # RETURN, CONTROL_STRUCTURE
            for idx in important_indices:
                if idx < self.num_node_types:
                    self.node_type_importance.data[idx] = 2.0
    
    def forward(
        self, 
        x: torch.Tensor,           # [N, hidden_dim]
        node_types: torch.Tensor,  # [N] - node type indices
        batch: torch.Tensor,       # [N] - batch assignment
    ) -> Tuple[torch.Tensor, torch.Tensor]:
        """
        Returns:
            pooled: [B, hidden_dim] - batch-level representation
            attention_weights: [N] - per-node attention weights
        """
        # Clamp node types to valid range
        node_types_clamped = node_types.clamp(0, self.num_node_types - 1)
        
        # Get node type importance
        type_importance = self.node_type_importance[node_types_clamped]  # [N]
        
        # Compute content-based attention
        content_attention = self.attention(x).squeeze(-1)  # [N]
        
        # Combine type importance with content attention
        combined_attention = type_importance * torch.sigmoid(content_attention)  # [N]
        
        # Normalize within each graph
        attention_weights = softmax(combined_attention, batch)  # [N]
        
        # Weighted aggregation
        weighted_x = x * attention_weights.unsqueeze(-1)  # [N, hidden_dim]
        
        # Sum (since weights already normalized)
        pooled = global_mean_pool(weighted_x, batch) * (batch.bincount().float().unsqueeze(-1).to(x.device))
        
        # Normalize by number of nodes
        num_graphs = batch.max().item() + 1
        node_counts = batch.bincount().float().clamp(min=1).to(x.device)
        pooled = pooled / node_counts.unsqueeze(-1)
        
        return pooled, attention_weights


# =============================================================================
# CALL Context Encoder
# =============================================================================

class CALLContextEncoder(nn.Module):
    """
    Encodes the context around CALL nodes using data-flow edges.
    
    For vulnerability detection, we care about:
    1. What data flows INTO the call (arguments)
    2. What data flows OUT of the call (return value)
    """
    
    def __init__(
        self, 
        hidden_dim: int,
        reaching_def_edge_type: int = 9,  # REACHING_DEF edge type index
        dropout: float = 0.2,
    ):
        super().__init__()
        self.reaching_def_type = reaching_def_edge_type
        
        # Encode incoming data flow
        self.incoming_encoder = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
        )
        
        # Encode outgoing data flow
        self.outgoing_encoder = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
        )
        
        # Combine context with CALL representation
        self.context_combiner = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
    
    def forward(
        self,
        x: torch.Tensor,            # [N, hidden_dim]
        edge_index: torch.Tensor,   # [2, E]
        edge_type: torch.Tensor,    # [E]
        call_mask: torch.Tensor,    # [N] boolean
        batch: torch.Tensor,        # [N]
    ) -> torch.Tensor:
        """
        Encode context around CALL nodes.
        
        Returns:
            call_repr: [num_calls, hidden_dim] - enriched CALL representations
        """
        device = x.device
        hidden_dim = x.shape[1]
        
        # Get data-flow edges (REACHING_DEF)
        if edge_type is not None:
            dataflow_mask = edge_type == self.reaching_def_type
            df_src = edge_index[0, dataflow_mask]
            df_dst = edge_index[1, dataflow_mask]
        else:
            df_src = edge_index[0]
            df_dst = edge_index[1]
        
        # Get CALL node indices
        call_indices = call_mask.nonzero(as_tuple=True)[0]
        num_calls = len(call_indices)
        
        if num_calls == 0:
            # No CALL nodes, return empty tensor with correct shape
            return torch.zeros(0, hidden_dim, device=device)
        
        # For each CALL node, aggregate incoming and outgoing neighbors
        incoming_repr = torch.zeros(num_calls, hidden_dim, device=device)
        outgoing_repr = torch.zeros(num_calls, hidden_dim, device=device)
        
        for i, call_idx in enumerate(call_indices):
            # Incoming edges: edges pointing TO this CALL
            incoming_mask = df_dst == call_idx
            if incoming_mask.any():
                source_nodes = df_src[incoming_mask]
                incoming_repr[i] = x[source_nodes].mean(dim=0)
            
            # Outgoing edges: edges pointing FROM this CALL
            outgoing_mask = df_src == call_idx
            if outgoing_mask.any():
                target_nodes = df_dst[outgoing_mask]
                outgoing_repr[i] = x[target_nodes].mean(dim=0)
        
        # Encode contexts
        incoming_encoded = self.incoming_encoder(incoming_repr)
        outgoing_encoded = self.outgoing_encoder(outgoing_repr)
        
        # Get CALL node representations
        call_repr = x[call_mask]  # [num_calls, hidden_dim]
        
        # Combine: [CALL | incoming_context | outgoing_context]
        combined = torch.cat([call_repr, incoming_encoded, outgoing_encoded], dim=-1)
        
        return self.context_combiner(combined)


# =============================================================================
# CALL-Aware GNN Layer
# =============================================================================

class CallAwareGNN(nn.Module):
    """
    CALL-Aware GNN that processes the graph with special attention to CALL nodes.
    
    Architecture:
    1. Standard message passing for structural context
    2. Parallel CALL-focused processing
    3. Fusion of both representations
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_edge_types: int = 18,
        num_layers: int = 4,
        num_node_types: int = 16,
        call_node_idx: int = 2,
        reaching_def_edge_type: int = 9,
        dropout: float = 0.2,
    ):
        super().__init__()
        
        self.hidden_dim = hidden_dim
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        self.num_layers = num_layers
        
        # Standard GNN layers for structural processing
        self.gnn_layers = nn.ModuleList()
        self.gnn_norms = nn.ModuleList()
        
        for _ in range(num_layers):
            self.gnn_layers.append(
                GATConv(hidden_dim, hidden_dim // 4, heads=4, dropout=dropout, concat=True)
            )
            self.gnn_norms.append(nn.LayerNorm(hidden_dim))
        
        # CALL context encoder
        self.call_context = CALLContextEncoder(
            hidden_dim=hidden_dim,
            reaching_def_edge_type=reaching_def_edge_type,
            dropout=dropout,
        )
        
        # Fusion layer: combine structural and CALL representations
        self.fusion = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
        
        self.dropout = nn.Dropout(dropout)
    
    def forward(
        self, 
        x: torch.Tensor, 
        edge_index: torch.Tensor, 
        edge_type: Optional[torch.Tensor] = None,
        batch: Optional[torch.Tensor] = None,
        node_types: Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        """
        Forward pass.
        
        Args:
            x: Node features [N, hidden_dim]
            edge_index: Edge indices [2, E]
            edge_type: Edge types [E]
            batch: Batch assignment [N]
            node_types: Node type indices [N]
        
        Returns:
            Updated node features [N, hidden_dim]
        """
        device = x.device
        
        # Create batch if not provided
        if batch is None:
            batch = torch.zeros(x.size(0), dtype=torch.long, device=device)
        
        # Get node types from one-hot if not provided
        if node_types is None:
            if x.shape[1] > self.hidden_dim:
                # Assume first num_node_types dims are one-hot
                node_types = x[:, :self.num_node_types].argmax(dim=1)
            else:
                node_types = torch.zeros(x.size(0), dtype=torch.long, device=device)
        
        # Identify CALL nodes
        call_mask = node_types == self.call_node_idx
        
        # Path 1: Standard GNN processing
        h = x
        for gnn, norm in zip(self.gnn_layers, self.gnn_norms):
            h_new = gnn(h, edge_index)
            h_new = F.relu(h_new)
            h = norm(h + self.dropout(h_new))  # Residual connection
        
        # Path 2: CALL-focused processing
        if call_mask.any() and edge_type is not None:
            call_repr = self.call_context(h, edge_index, edge_type, call_mask, batch)
            
            # Create enhanced representations for CALL nodes
            h_enhanced = h.clone()
            
            # Fuse CALL context with GNN output for CALL nodes
            call_h_original = h[call_mask]
            fused_call = self.fusion(torch.cat([call_h_original, call_repr], dim=-1))
            h_enhanced[call_mask] = fused_call
            
            return h_enhanced
        
        return h


# =============================================================================
# Complete CALL-Aware Vulnerability Detector
# =============================================================================

class CallAwareVulnDetector(nn.Module):
    """
    Complete vulnerability detector that focuses on CALL nodes.
    
    Architecture:
    1. Input projection
    2. CALL-aware GNN for structural + CALL context
    3. CALL-prioritized attention pooling
    4. Dual-path classification (CALL-focused + global)
    """
    
    def __init__(
        self,
        input_dim: int = 272,
        hidden_dim: int = 256,
        num_edge_types: int = 18,
        num_node_types: int = 16,
        num_layers: int = 4,
        call_node_idx: int = 2,
        reaching_def_edge_type: int = 9,
        dropout: float = 0.2,
        **kwargs,  # Accept extra kwargs for compatibility
    ):
        super().__init__()
        
        self.input_dim = input_dim
        self.hidden_dim = hidden_dim
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        
        # Input projection
        self.input_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
        
        # CALL-aware GNN
        self.gnn = CallAwareGNN(
            hidden_dim=hidden_dim,
            num_edge_types=num_edge_types,
            num_layers=num_layers,
            num_node_types=num_node_types,
            call_node_idx=call_node_idx,
            reaching_def_edge_type=reaching_def_edge_type,
            dropout=dropout,
        )
        
        # CALL-prioritized attention
        self.call_attention = CallNodeAttention(
            hidden_dim=hidden_dim,
            num_node_types=num_node_types,
            call_node_idx=call_node_idx,
        )
        
        # CALL-specific classifier
        self.call_classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        # Global classifier (combines attention-pooled + max-pooled)
        self.global_classifier = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
        
        # Learnable combination weights
        self.call_weight = nn.Parameter(torch.tensor(0.6))
        self.global_weight = nn.Parameter(torch.tensor(0.4))
        
        # Store config
        self.config = {
            "input_dim": input_dim,
            "hidden_dim": hidden_dim,
            "num_edge_types": num_edge_types,
            "num_node_types": num_node_types,
            "num_layers": num_layers,
            "call_node_idx": call_node_idx,
            "dropout": dropout,
        }
    
    def forward(self, data, return_embeddings: bool = False):
        """
        Forward pass.
        
        Args:
            data: PyG Data/Batch object with x, edge_index, edge_type, batch
        
        Returns:
            logits: [B, 1] classification logits
        """
        x = data.x.float()
        edge_index = data.edge_index
        edge_type = getattr(data, 'edge_type', None)
        batch = getattr(data, 'batch', None)
        
        if batch is None:
            batch = torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Get node types from one-hot encoding
        if x.shape[1] >= self.num_node_types:
            node_types = x[:, :self.num_node_types].argmax(dim=1)
        else:
            node_types = torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Identify CALL nodes
        call_mask = node_types == self.call_node_idx
        
        # Project input
        h = self.input_proj(x)
        
        # Apply CALL-aware GNN
        h = self.gnn(h, edge_index, edge_type, batch, node_types)
        
        num_graphs = batch.max().item() + 1
        
        # Path 1: CALL-focused prediction
        if call_mask.any():
            call_h = h[call_mask]
            call_batch = batch[call_mask]
            
            # Pool CALL nodes per graph using max (capture most suspicious API)
            call_pooled = global_max_pool(call_h, call_batch)
            
            # Handle graphs without CALL nodes
            if call_pooled.shape[0] < num_graphs:
                # Some graphs have no CALL nodes, pad with zeros
                full_call_pooled = torch.zeros(num_graphs, self.hidden_dim, device=x.device)
                unique_batches = call_batch.unique()
                full_call_pooled[unique_batches] = call_pooled
                call_pooled = full_call_pooled
            
            call_logits = self.call_classifier(call_pooled).squeeze(-1)
        else:
            call_logits = torch.zeros(num_graphs, device=x.device)
        
        # Path 2: Global representation with CALL attention
        attn_pooled, _ = self.call_attention(h, node_types, batch)
        max_pooled = global_max_pool(h, batch)
        
        global_repr = torch.cat([attn_pooled, max_pooled], dim=-1)
        global_logits = self.global_classifier(global_repr).squeeze(-1)
        
        # Combine with learned weights
        weights = torch.softmax(torch.stack([self.call_weight, self.global_weight]), dim=0)
        logits = weights[0] * call_logits + weights[1] * global_logits
        if return_embeddings:
            return {
                "logits": logits.unsqueeze(-1),
                "graph_emb": global_repr,
            }
        return logits.unsqueeze(-1)
    
    def get_config(self) -> Dict[str, Any]:
        """Get model configuration."""
        return self.config.copy()


# =============================================================================
# Simple API Detector (Baseline)
# =============================================================================

class SimpleAPIDetector(nn.Module):
    """
    Simple baseline: Focus only on CALL node content.
    
    If sensitive APIs (malloc, strcpy, etc.) are only present in vulnerable code,
    a simple detector checking for their presence might work well.
    """
    
    def __init__(
        self,
        input_dim: int = 272,
        hidden_dim: int = 128,
        num_node_types: int = 16,
        call_node_idx: int = 2,
        dropout: float = 0.2,
        **kwargs,
    ):
        super().__init__()
        
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        self.hidden_dim = hidden_dim
        
        # Project CALL node embeddings
        self.call_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
        
        # Classify based on CALL representations (max pooled)
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        # Fallback for graphs without CALL nodes
        self.fallback = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
    
    def forward(self, data) -> torch.Tensor:
        x = data.x.float()
        batch = getattr(data, 'batch', None)
        
        if batch is None:
            batch = torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Get node types
        if x.shape[1] >= self.num_node_types:
            node_types = x[:, :self.num_node_types].argmax(dim=1)
        else:
            node_types = torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Find CALL nodes
        call_mask = node_types == self.call_node_idx
        num_graphs = batch.max().item() + 1
        
        logits = torch.zeros(num_graphs, device=x.device)
        
        if call_mask.any():
            # Project CALL embeddings
            call_x = x[call_mask]
            call_h = self.call_proj(call_x)
            call_batch = batch[call_mask]
            
            # Max pool per graph (capture most suspicious API)
            call_pooled = global_max_pool(call_h, call_batch)
            
            # Classify
            call_logits = self.classifier(call_pooled).squeeze(-1)
            
            # Map back to full batch
            unique_batches = call_batch.unique()
            logits[unique_batches] = call_logits
        
        # Handle graphs without CALL nodes using fallback
        for graph_id in range(num_graphs):
            graph_mask = batch == graph_id
            has_calls = (call_mask & graph_mask).any()
            
            if not has_calls:
                graph_x = x[graph_mask].mean(dim=0)
                logits[graph_id] = self.fallback(graph_x).squeeze()
        
        return logits.unsqueeze(-1)


# =============================================================================
# Factory function
# =============================================================================

def create_call_aware_model(
    model_type: str = "call_aware",
    **kwargs,
) -> nn.Module:
    """
    Create a CALL-aware model.
    
    Args:
        model_type: "call_aware" or "simple_api"
        **kwargs: Model arguments
    
    Returns:
        Model instance
    """
    if model_type == "call_aware":
        return CallAwareVulnDetector(**kwargs)
    elif model_type == "simple_api":
        return SimpleAPIDetector(**kwargs)
    else:
        raise ValueError(f"Unknown model type: {model_type}")
