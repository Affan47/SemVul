#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
hagnn.py - Heterogeneous Attention GNN for Vulnerability Detection (Stage 3)

Based on research findings:
  - HAGNN achieves 96.6% accuracy by processing edge types separately
  - Separate message passing per edge type group dramatically outperforms single-pass
  - Global attention combines different views (AST, CFG, DFG)

Architecture:
  Input → Projection → [HAGNNLayer × N] → VulnAwarePooling → Classifier

Key innovations:
  1. Edge-type-specific GAT layers
  2. Attention-weighted view combination
  3. Dual-path classification (CALL-focused + global)
  4. Learnable node-type importance

Usage:
    from hagnn import HAGNNVulnDetector
    
    model = HAGNNVulnDetector(
        input_dim=272,
        hidden_dim=256,
        num_layers=4,
        num_edge_types=18,
    )
"""

import math
from typing import Dict, List, Optional, Tuple

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import MessagePassing, global_mean_pool, global_max_pool
from torch_geometric.utils import softmax, add_self_loops


# ═══════════════════════════════════════════════════════════════════════════════
# EDGE-TYPE-SPECIFIC GAT LAYER
# ═══════════════════════════════════════════════════════════════════════════════

class EdgeTypeGATConv(MessagePassing):
    """
    Graph Attention layer with edge-type-specific transformations.
    
    For edge type r:
        h_i^{(l+1)} = σ(Σ_{j∈N_i^r} α_{ij}^r W_r h_j^{(l)})
    
    Where:
        W_r = edge-type-specific weight matrix
        α_{ij}^r = edge-type-specific attention coefficients
    """
    
    def __init__(
        self,
        in_channels: int,
        out_channels: int,
        num_edge_types: int,
        heads: int = 4,
        dropout: float = 0.1,
        negative_slope: float = 0.2,
        concat: bool = True,
        bias: bool = True,
    ):
        super().__init__(aggr='add', node_dim=0)
        
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.num_edge_types = num_edge_types
        self.heads = heads
        self.dropout = dropout
        self.negative_slope = negative_slope
        self.concat = concat
        
        self.head_dim = out_channels // heads
        
        # Edge-type-specific transformations
        self.lin_src = nn.ModuleList([
            nn.Linear(in_channels, heads * self.head_dim, bias=False)
            for _ in range(num_edge_types)
        ])
        self.lin_dst = nn.ModuleList([
            nn.Linear(in_channels, heads * self.head_dim, bias=False)
            for _ in range(num_edge_types)
        ])
        
        # Edge-type-specific attention parameters
        self.att_src = nn.ParameterList([
            nn.Parameter(torch.Tensor(1, heads, self.head_dim))
            for _ in range(num_edge_types)
        ])
        self.att_dst = nn.ParameterList([
            nn.Parameter(torch.Tensor(1, heads, self.head_dim))
            for _ in range(num_edge_types)
        ])
        
        if bias and concat:
            self.bias = nn.Parameter(torch.Tensor(heads * self.head_dim))
        elif bias:
            self.bias = nn.Parameter(torch.Tensor(out_channels))
        else:
            self.register_parameter('bias', None)
        
        self._reset_parameters()
    
    def _reset_parameters(self):
        for lin in self.lin_src:
            nn.init.xavier_uniform_(lin.weight)
        for lin in self.lin_dst:
            nn.init.xavier_uniform_(lin.weight)
        for att in self.att_src:
            nn.init.xavier_uniform_(att)
        for att in self.att_dst:
            nn.init.xavier_uniform_(att)
        if self.bias is not None:
            nn.init.zeros_(self.bias)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: torch.Tensor,
    ) -> torch.Tensor:
        """
        Forward pass with edge-type-aware attention.
        
        Args:
            x: Node features [num_nodes, in_channels]
            edge_index: Edge connectivity [2, num_edges]
            edge_type: Edge type indices [num_edges]
        
        Returns:
            Updated node features [num_nodes, out_channels]
        """
        num_nodes = x.size(0)
        device = x.device
        
        # Initialize output accumulator
        out = torch.zeros(num_nodes, self.heads, self.head_dim, device=device)
        
        # Process each edge type separately
        for r in range(self.num_edge_types):
            mask = edge_type == r
            if mask.sum() == 0:
                continue
            
            edge_index_r = edge_index[:, mask]
            
            # Transform source and destination features
            x_src = self.lin_src[r](x).view(-1, self.heads, self.head_dim)
            x_dst = self.lin_dst[r](x).view(-1, self.heads, self.head_dim)
            
            # Compute attention scores
            src, dst = edge_index_r
            alpha_src = (x_src[src] * self.att_src[r]).sum(dim=-1)
            alpha_dst = (x_dst[dst] * self.att_dst[r]).sum(dim=-1)
            alpha = F.leaky_relu(alpha_src + alpha_dst, self.negative_slope)
            
            # Softmax normalization
            alpha = softmax(alpha, dst, num_nodes=num_nodes)
            alpha = F.dropout(alpha, p=self.dropout, training=self.training)
            
            # Message passing for this edge type
            out_r = self.propagate(edge_index_r, x=x_src, alpha=alpha)
            out = out + out_r
        
        # Reshape output
        if self.concat:
            out = out.view(-1, self.heads * self.head_dim)
        else:
            out = out.mean(dim=1)
        
        if self.bias is not None:
            out = out + self.bias
        
        return out
    
    def message(self, x_j: torch.Tensor, alpha: torch.Tensor) -> torch.Tensor:
        return alpha.unsqueeze(-1) * x_j


# ═══════════════════════════════════════════════════════════════════════════════
# HAGNN LAYER WITH VIEW COMBINATION
# ═══════════════════════════════════════════════════════════════════════════════

class HAGNNLayer(nn.Module):
    """
    HAGNN Layer: Processes edge type groups separately, combines via attention.
    
    Edge Type Grouping (based on cpg_config.py analysis):
        - AST Group: AST, ARGUMENT, PARAMETER_LINK, RECEIVER
        - CFG Group: CFG, CALL, CONDITION
        - DFG Group: REACHING_DEF, REF
        - Control Dep Group: CDG, DOMINATE, POST_DOMINATE
    
    Each group is processed by a separate GAT, then combined via global attention.
    """
    
    # Default edge type grouping based on your cpg_config.py
    DEFAULT_EDGE_GROUPS = {
        'AST': [1, 7, 11, 14],      # AST, ARGUMENT, PARAMETER_LINK, RECEIVER
        'CFG': [4, 9, 13],          # CFG, CALL, CONDITION  
        'DFG': [0, 8],              # REACHING_DEF, REF
        'CONTROL': [6, 5, 3],       # CDG, POST_DOMINATE, DOMINATE
        'TYPE': [2, 12, 15],        # EVAL_TYPE, ALIAS_OF, BINDS
    }
    
    def __init__(
        self,
        in_channels: int,
        out_channels: int,
        num_edge_types: int,
        edge_groups: Optional[Dict[str, List[int]]] = None,
        heads: int = 4,
        dropout: float = 0.2,
    ):
        super().__init__()
        
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.num_edge_types = num_edge_types
        
        # Use default or custom edge grouping
        if edge_groups is None:
            self.edge_groups = self._create_edge_groups(num_edge_types)
        else:
            self.edge_groups = edge_groups
        
        self.num_groups = len(self.edge_groups)
        
        # Create GAT for each edge type group
        self.group_convs = nn.ModuleDict()
        for group_name, edge_types in self.edge_groups.items():
            self.group_convs[group_name] = EdgeTypeGATConv(
                in_channels=in_channels,
                out_channels=out_channels,
                num_edge_types=len(edge_types),
                heads=heads,
                dropout=dropout,
            )
        
        # Global attention for combining group outputs
        self.group_attention = nn.Sequential(
            nn.Linear(out_channels, out_channels // 4),
            nn.Tanh(),
            nn.Linear(out_channels // 4, 1),
        )
        
        # Layer normalization and residual
        self.layer_norm = nn.LayerNorm(out_channels)
        self.residual = nn.Linear(in_channels, out_channels) if in_channels != out_channels else nn.Identity()
        self.dropout = nn.Dropout(dropout)
    
    def _create_edge_groups(self, num_edge_types: int) -> Dict[str, List[int]]:
        """Create default edge groups based on number of edge types."""
        if num_edge_types <= 5:
            # Simplified 5-class scheme
            return {
                'AST': [0],
                'CFG': [1],
                'DFG_READ': [2],
                'DFG_WRITE': [3],
                'NCS': [4],
            }
        elif num_edge_types <= 18:
            # Full edge types from cpg_config.py (16 filtered + 2 metadata)
            return {
                'AST': [1, 7, 11, 14],      # AST, ARGUMENT, PARAMETER_LINK, RECEIVER
                'CFG': [4, 9, 13],          # CFG, CALL, CONDITION
                'DFG': [0, 8],              # REACHING_DEF, REF
                'CONTROL': [6, 5, 3],       # CDG, POST_DOMINATE, DOMINATE
                'TYPE': [2, 12, 15],        # EVAL_TYPE, ALIAS_OF, BINDS
            }
        else:
            # Generic grouping for unknown schema
            return {f'group_{i}': [i] for i in range(num_edge_types)}
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: torch.Tensor,
    ) -> torch.Tensor:
        """
        Forward pass with multi-view processing.
        
        1. Process each edge type group with separate GAT
        2. Combine outputs via attention-weighted sum
        3. Add residual connection and normalize
        """
        device = x.device
        num_nodes = x.size(0)
        
        group_outputs = []
        
        for group_name, edge_types in self.edge_groups.items():
            # Create mask for edges in this group
            group_mask = torch.zeros(edge_type.size(0), dtype=torch.bool, device=device)
            local_edge_type = torch.zeros_like(edge_type)
            
            for local_idx, global_idx in enumerate(edge_types):
                type_mask = edge_type == global_idx
                group_mask = group_mask | type_mask
                local_edge_type[type_mask] = local_idx
            
            if group_mask.sum() == 0:
                # No edges in this group - use zeros
                group_outputs.append(torch.zeros(num_nodes, self.out_channels, device=device))
                continue
            
            # Extract edges for this group
            edge_index_group = edge_index[:, group_mask]
            local_edge_type_group = local_edge_type[group_mask]
            
            # Apply group-specific GAT
            out_group = self.group_convs[group_name](x, edge_index_group, local_edge_type_group)
            group_outputs.append(out_group)
        
        # Stack outputs: [num_groups, num_nodes, out_channels]
        group_stack = torch.stack(group_outputs, dim=0)
        
        # Compute attention weights
        attn_scores = self.group_attention(group_stack)  # [num_groups, num_nodes, 1]
        attn_weights = F.softmax(attn_scores, dim=0)
        
        # Weighted combination
        combined = (attn_weights * group_stack).sum(dim=0)  # [num_nodes, out_channels]
        
        # Residual and normalization
        residual = self.residual(x)
        out = self.layer_norm(self.dropout(combined) + residual)
        
        return out


# ═══════════════════════════════════════════════════════════════════════════════
# VULNERABILITY-AWARE POOLING
# ═══════════════════════════════════════════════════════════════════════════════

class VulnAwarePooling(nn.Module):
    """
    Vulnerability-aware graph pooling with dual paths.
    
    Based on diagnostic findings:
    - CALL nodes contain ~100% of vulnerability signal
    - Global mean pooling dilutes this to 5-10%
    
    This pooling:
    1. CALL-focused path: Max pooling over CALL node embeddings
    2. Global path: Attention-weighted pooling over all nodes
    3. Learnable combination of both paths
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_node_types: int = 16,
        call_node_idx: int = 2,
        dropout: float = 0.1,
    ):
        super().__init__()
        
        self.hidden_dim = hidden_dim
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        
        # Learnable node type importance
        self.node_type_importance = nn.Parameter(torch.ones(num_node_types))
        
        # Attention for global pooling
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.Tanh(),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        # Learnable combination weight
        self.alpha = nn.Parameter(torch.tensor(0.7))  # Default: 70% CALL-focused
        
        self.dropout = nn.Dropout(dropout)
    
    def forward(
        self,
        x: torch.Tensor,
        batch: torch.Tensor,
        node_types: Optional[torch.Tensor] = None,
    ) -> Tuple[torch.Tensor, torch.Tensor, torch.Tensor]:
        """
        Dual-path pooling.
        
        Args:
            x: Node embeddings [num_nodes, hidden_dim]
            batch: Batch assignment [num_nodes]
            node_types: Optional node type indices [num_nodes]
        
        Returns:
            call_embedding: CALL-focused embedding [batch_size, hidden_dim]
            global_embedding: Attention-weighted embedding [batch_size, hidden_dim]
            alpha: Combination weight (sigmoid)
        """
        device = x.device
        batch_size = batch.max().item() + 1
        
        # Infer node types from one-hot if not provided
        if node_types is None and x.size(1) > self.num_node_types:
            node_types = x[:, :self.num_node_types].argmax(dim=1)
        
        # ─────────────────────────────────────────────────────────────────────
        # Path 1: CALL-focused pooling (max over CALL nodes)
        # ─────────────────────────────────────────────────────────────────────
        if node_types is not None:
            call_mask = node_types == self.call_node_idx
        else:
            call_mask = torch.zeros(x.size(0), dtype=torch.bool, device=device)
        
        call_embedding = torch.zeros(batch_size, self.hidden_dim, device=device)
        
        if call_mask.sum() > 0:
            # For each graph, max pool over CALL nodes
            for b in range(batch_size):
                graph_mask = batch == b
                call_graph_mask = graph_mask & call_mask
                
                if call_graph_mask.sum() > 0:
                    call_embedding[b] = x[call_graph_mask].max(dim=0)[0]
                else:
                    # Fallback to max over all nodes if no CALL nodes
                    call_embedding[b] = x[graph_mask].max(dim=0)[0]
        else:
            # No CALL nodes detected - use global max
            call_embedding = global_max_pool(x, batch)
        
        # ─────────────────────────────────────────────────────────────────────
        # Path 2: Attention-weighted global pooling
        # ─────────────────────────────────────────────────────────────────────
        
        # Compute attention scores
        attn_scores = self.attention(x).squeeze(-1)
        
        # Weight by node type importance
        if node_types is not None:
            type_weights = self.node_type_importance[node_types]
            attn_scores = attn_scores * type_weights
        
        # Softmax within each graph
        attn_weights = softmax(attn_scores, batch)
        attn_weights = self.dropout(attn_weights)
        
        # Weighted aggregation
        global_embedding = torch.zeros(batch_size, self.hidden_dim, device=device)
        global_embedding.scatter_add_(
            0, 
            batch.unsqueeze(-1).expand_as(x), 
            attn_weights.unsqueeze(-1) * x
        )
        
        # Combination weight
        alpha = torch.sigmoid(self.alpha)
        
        return call_embedding, global_embedding, alpha


# ═══════════════════════════════════════════════════════════════════════════════
# COMPLETE HAGNN VULNERABILITY DETECTOR
# ═══════════════════════════════════════════════════════════════════════════════

class HAGNNVulnDetector(nn.Module):
    """
    Complete HAGNN-based Vulnerability Detector.
    
    Architecture:
        Input → Projection → [HAGNNLayer × N] → VulnAwarePooling → DualClassifier
    
    Features:
        - Separate message passing per edge type group
        - Attention-weighted view combination
        - Dual-path classification (CALL-focused + global)
        - Contrastive learning compatible (returns embeddings)
    """
    
    def __init__(
        self,
        input_dim: int,
        hidden_dim: int = 256,
        num_layers: int = 4,
        num_edge_types: int = 18,
        num_node_types: int = 16,
        call_node_idx: int = 2,
        heads: int = 4,
        dropout: float = 0.2,
        edge_groups: Optional[Dict[str, List[int]]] = None,
    ):
        super().__init__()
        
        self.input_dim = input_dim
        self.hidden_dim = hidden_dim
        self.num_layers = num_layers
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        
        # Input projection
        self.input_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
        
        # HAGNN layers
        self.layers = nn.ModuleList()
        for i in range(num_layers):
            self.layers.append(HAGNNLayer(
                in_channels=hidden_dim,
                out_channels=hidden_dim,
                num_edge_types=num_edge_types,
                edge_groups=edge_groups,
                heads=heads,
                dropout=dropout,
            ))
        
        # Vulnerability-aware pooling
        self.pooling = VulnAwarePooling(
            hidden_dim=hidden_dim,
            num_node_types=num_node_types,
            call_node_idx=call_node_idx,
            dropout=dropout,
        )
        
        # Dual-path classifiers
        self.call_classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        self.global_classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        # For contrastive learning: projection head (optional)
        self.projection_head = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, 128),
        )
    
    def forward(
        self, 
        batch,
        return_embeddings: bool = False,
    ) -> Dict[str, torch.Tensor]:
        """
        Forward pass.
        
        Args:
            batch: PyG Batch object with x, edge_index, edge_type/edge_attr, batch
            return_embeddings: If True, also return graph embeddings for contrastive learning
        
        Returns:
            Dictionary with:
                - logits: Combined classification logits
                - call_logits: CALL-focused logits
                - global_logits: Global attention logits
                - alpha: Combination weight
                - graph_embedding: (optional) For contrastive learning
        """
        x = batch.x
        edge_index = batch.edge_index
        batch_idx = batch.batch
        
        # Get edge types (handle both edge_type and edge_attr naming)
        if hasattr(batch, 'edge_type') and batch.edge_type is not None:
            edge_type = batch.edge_type
        elif hasattr(batch, 'edge_attr') and batch.edge_attr is not None:
            if batch.edge_attr.dim() == 1:
                edge_type = batch.edge_attr
            else:
                edge_type = batch.edge_attr.argmax(dim=1) if batch.edge_attr.size(1) > 1 else batch.edge_attr.squeeze()
        else:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        # Input projection
        h = self.input_proj(x)
        
        # HAGNN layers
        for layer in self.layers:
            h = layer(h, edge_index, edge_type)
        
        # Extract node types for pooling
        if x.size(1) >= self.num_node_types:
            node_types = x[:, :self.num_node_types].argmax(dim=1)
        else:
            node_types = None
        
        # Vulnerability-aware pooling
        call_emb, global_emb, alpha = self.pooling(h, batch_idx, node_types)
        
        # Dual-path classification
        call_logits = self.call_classifier(call_emb).squeeze(-1)
        global_logits = self.global_classifier(global_emb).squeeze(-1)
        
        # Combined logits
        logits = alpha * call_logits + (1 - alpha) * global_logits
        
        result = {
            'logits': logits,
            'call_logits': call_logits,
            'global_logits': global_logits,
            'alpha': alpha,
        }
        
        if return_embeddings:
            # Combined embedding for contrastive learning
            graph_embedding = alpha * call_emb + (1 - alpha) * global_emb
            result['graph_embedding'] = graph_embedding
            result['projection'] = self.projection_head(graph_embedding)
        
        return result
    
    def get_graph_embedding(self, batch) -> torch.Tensor:
        """Get graph-level embedding for contrastive learning."""
        output = self.forward(batch, return_embeddings=True)
        return output['graph_embedding']


# ═══════════════════════════════════════════════════════════════════════════════
# FACTORY FUNCTION
# ═══════════════════════════════════════════════════════════════════════════════

def create_hagnn_model(
    input_dim: int,
    hidden_dim: int = 256,
    num_layers: int = 4,
    num_edge_types: int = 18,
    num_node_types: int = 16,
    call_node_idx: int = 2,
    heads: int = 4,
    dropout: float = 0.2,
    **kwargs,
) -> HAGNNVulnDetector:
    """
    Factory function to create HAGNN model.
    
    This can be integrated into train_advanced.py's create_advanced_model().
    """
    return HAGNNVulnDetector(
        input_dim=input_dim,
        hidden_dim=hidden_dim,
        num_layers=num_layers,
        num_edge_types=num_edge_types,
        num_node_types=num_node_types,
        call_node_idx=call_node_idx,
        heads=heads,
        dropout=dropout,
    )


# ═══════════════════════════════════════════════════════════════════════════════
# TESTING
# ═══════════════════════════════════════════════════════════════════════════════

if __name__ == "__main__":
    from torch_geometric.data import Data, Batch
    
    print("=" * 70)
    print("HAGNN VULNERABILITY DETECTOR TEST")
    print("=" * 70)
    
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print(f"Device: {device}")
    
    # Create model
    model = HAGNNVulnDetector(
        input_dim=272,     # 16 one-hot + 256 embedding
        hidden_dim=256,
        num_layers=4,
        num_edge_types=16,
        num_node_types=16,
        call_node_idx=2,
        heads=4,
        dropout=0.2,
    ).to(device)
    
    # Count parameters
    total_params = sum(p.numel() for p in model.parameters())
    trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"\nModel parameters:")
    print(f"  Total: {total_params:,}")
    print(f"  Trainable: {trainable_params:,}")
    
    # Create dummy batch
    print("\nCreating dummy batch...")
    graphs = []
    for _ in range(8):  # Batch of 8 graphs
        num_nodes = torch.randint(20, 100, (1,)).item()
        num_edges = torch.randint(50, 300, (1,)).item()
        
        # Node features: 16 one-hot + 256 embedding
        x = torch.randn(num_nodes, 272)
        x[:, :16] = 0
        x[torch.arange(num_nodes), torch.randint(0, 16, (num_nodes,))] = 1
        
        # Add some CALL nodes (type index 2)
        num_calls = max(1, num_nodes // 10)
        call_indices = torch.randperm(num_nodes)[:num_calls]
        x[call_indices, :16] = 0
        x[call_indices, 2] = 1  # Set as CALL nodes
        
        edge_index = torch.randint(0, num_nodes, (2, num_edges))
        edge_type = torch.randint(0, 16, (num_edges,))
        y = torch.tensor([torch.randint(0, 2, (1,)).item()])
        
        graphs.append(Data(x=x, edge_index=edge_index, edge_type=edge_type, y=y))
    
    batch = Batch.from_data_list(graphs).to(device)
    print(f"  Batch: {batch.x.shape[0]} nodes, {batch.edge_index.shape[1]} edges, {batch.num_graphs} graphs")
    
    # Forward pass
    print("\nForward pass...")
    model.eval()
    with torch.no_grad():
        output = model(batch, return_embeddings=True)
    
    print(f"  logits: {output['logits'].shape}")
    print(f"  call_logits: {output['call_logits'].shape}")
    print(f"  global_logits: {output['global_logits'].shape}")
    print(f"  alpha: {output['alpha'].item():.4f}")
    print(f"  graph_embedding: {output['graph_embedding'].shape}")
    print(f"  projection: {output['projection'].shape}")
    
    # Test training step
    print("\nTraining step test...")
    model.train()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
    
    output = model(batch, return_embeddings=True)
    loss = F.binary_cross_entropy_with_logits(output['logits'], batch.y.float())
    
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    
    print(f"  Loss: {loss.item():.4f}")
    print(f"  Gradient norm: {torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0):.4f}")
    
    print("\n" + "=" * 70)
    print("All tests passed!")
    print("=" * 70)
