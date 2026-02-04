#!/usr/bin/env python3
"""
VulnGNN-SOTA: State-of-the-Art Vulnerability Detection

Key Innovations:
1. SINK-SOURCE ATTENTION: Explicitly models taint propagation paths
2. VULNERABILITY PATTERN MINING: Learns discriminative subgraph patterns
3. MULTI-VIEW FUSION: Separate processing for AST/CFG/DFG with cross-attention
4. HIERARCHICAL READOUT: Statement → Block → Function aggregation
5. CONTRASTIVE GRAPH LEARNING: Learns to separate vulnerable vs safe graphs

Based on insights from:
- Devign (NIPS 2019)
- REVEAL (IEEE S&P 2021)  
- IVDetect (ICSE 2021)
- LineVul (MSR 2022)
- VulBERTa (2022)
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import (
    GATConv, GCNConv, SAGEConv, RGCNConv, RGATConv,
    global_mean_pool, global_max_pool, global_add_pool,
    TopKPooling, SAGPooling
)
from torch_geometric.data import Data, Batch
from torch_geometric.utils import to_dense_batch, softmax
from typing import Optional, Tuple, List, Dict
import math


# ═══════════════════════════════════════════════════════════════════
# CORE INNOVATION 1: Sink-Source Taint Attention
# ═══════════════════════════════════════════════════════════════════

class TaintPropagationAttention(nn.Module):
    """
    Models vulnerability as taint propagation from sources to sinks.
    
    Sources: User inputs, external data (CALL nodes with specific patterns)
    Sinks: Dangerous operations (memcpy, strcpy, free, etc.)
    
    The attention mechanism learns which source-sink paths are vulnerable.
    """
    
    # Known dangerous sinks (CWE patterns)
    SINK_PATTERNS = {
        'memcpy', 'strcpy', 'strcat', 'sprintf', 'gets', 'scanf',
        'free', 'delete', 'realloc', 'malloc',
        'exec', 'system', 'popen', 'eval',
        'sql', 'query', 'execute',
    }
    
    # Known sources (user/external input)
    SOURCE_PATTERNS = {
        'read', 'recv', 'fgets', 'scanf', 'getenv', 'argv',
        'input', 'request', 'param', 'query',
    }
    
    def __init__(self, hidden_dim: int, num_heads: int = 4):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_heads = num_heads
        self.head_dim = hidden_dim // num_heads
        
        # Learnable source/sink detectors
        self.source_detector = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, 1),
            nn.Sigmoid()
        )
        
        self.sink_detector = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, 1),
            nn.Sigmoid()
        )
        
        # Path attention
        self.path_query = nn.Linear(hidden_dim, hidden_dim)
        self.path_key = nn.Linear(hidden_dim, hidden_dim)
        self.path_value = nn.Linear(hidden_dim, hidden_dim)
        
        # Vulnerability scoring
        self.vuln_scorer = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(hidden_dim, 1)
        )
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor, 
                batch: torch.Tensor) -> Tuple[torch.Tensor, torch.Tensor]:
        """
        Returns:
            - Enhanced node features with taint information
            - Per-graph vulnerability scores from source-sink analysis
        """
        # Detect sources and sinks
        source_scores = self.source_detector(x).squeeze(-1)  # [N]
        sink_scores = self.sink_detector(x).squeeze(-1)      # [N]
        
        # Multi-head attention from sinks to sources (backward taint)
        Q = self.path_query(x).view(-1, self.num_heads, self.head_dim)
        K = self.path_key(x).view(-1, self.num_heads, self.head_dim)
        V = self.path_value(x).view(-1, self.num_heads, self.head_dim)
        
        # Compute attention weighted by source/sink scores
        # High attention = potential taint path
        attn_weights = torch.einsum('nhd,mhd->nmh', Q, K) / math.sqrt(self.head_dim)
        
        # Weight attention by source-sink relevance
        source_weight = source_scores.unsqueeze(0).unsqueeze(-1)  # [1, N, 1]
        sink_weight = sink_scores.unsqueeze(1).unsqueeze(-1)      # [N, 1, 1]
        
        attn_weights = attn_weights * source_weight * sink_weight
        attn_weights = F.softmax(attn_weights, dim=1)
        
        # Aggregate taint information
        taint_features = torch.einsum('nmh,mhd->nhd', attn_weights, V)
        taint_features = taint_features.reshape(-1, self.hidden_dim)
        
        # Enhanced features
        enhanced_x = x + taint_features
        
        # Per-graph vulnerability score
        # Combine top source, top sink, and their interaction
        vuln_scores = []
        for graph_idx in batch.unique():
            mask = batch == graph_idx
            graph_x = x[mask]
            graph_sources = source_scores[mask]
            graph_sinks = sink_scores[mask]
            
            # Top source and sink
            top_source_idx = graph_sources.argmax()
            top_sink_idx = graph_sinks.argmax()
            
            top_source = graph_x[top_source_idx]
            top_sink = graph_x[top_sink_idx]
            interaction = top_source * top_sink  # Element-wise interaction
            
            combined = torch.cat([top_source, top_sink, interaction], dim=-1)
            vuln_score = self.vuln_scorer(combined)
            vuln_scores.append(vuln_score)
        
        vuln_scores = torch.cat(vuln_scores, dim=0)
        
        return enhanced_x, vuln_scores


# ═══════════════════════════════════════════════════════════════════
# CORE INNOVATION 2: Multi-View Graph Processing
# ═══════════════════════════════════════════════════════════════════

class MultiViewGNN(nn.Module):
    """
    Processes different edge types with specialized GNNs:
    - AST view: Captures syntactic patterns
    - CFG view: Captures control flow (loops, branches)
    - DFG view: Captures data dependencies
    
    Then fuses views with cross-attention.
    """
    
    def __init__(
        self,
        input_dim: int,
        hidden_dim: int,
        num_layers: int = 3,
        num_edge_types: int = 13,
        dropout: float = 0.2
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_edge_types = num_edge_types
        
        # Edge type groupings
        self.ast_types = {0}  # AST
        self.cfg_types = {1, 2, 9, 10}  # CFG, CDG, DOMINATE, POST_DOMINATE
        self.dfg_types = {3, 4, 6}  # REACHING_DEF, EVAL_TYPE, REF
        
        # Input projection
        self.input_proj = nn.Linear(input_dim, hidden_dim)
        
        # View-specific GNNs
        self.ast_layers = nn.ModuleList([
            GATConv(hidden_dim, hidden_dim // 4, heads=4, dropout=dropout)
            for _ in range(num_layers)
        ])
        
        self.cfg_layers = nn.ModuleList([
            GATConv(hidden_dim, hidden_dim // 4, heads=4, dropout=dropout)
            for _ in range(num_layers)
        ])
        
        self.dfg_layers = nn.ModuleList([
            GATConv(hidden_dim, hidden_dim // 4, heads=4, dropout=dropout)
            for _ in range(num_layers)
        ])
        
        # Cross-view attention
        self.cross_attn = nn.MultiheadAttention(hidden_dim, num_heads=4, dropout=dropout, batch_first=True)
        
        # View fusion
        self.view_fusion = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim * 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim * 2, hidden_dim)
        )
        
        self.layer_norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
    
    def _filter_edges(self, edge_index: torch.Tensor, edge_attr: torch.Tensor, 
                      type_set: set) -> torch.Tensor:
        """Filter edges by type."""
        mask = torch.zeros(edge_attr.size(0), dtype=torch.bool, device=edge_attr.device)
        for t in type_set:
            mask |= (edge_attr == t)
        return edge_index[:, mask]
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor, 
                edge_attr: torch.Tensor, batch: torch.Tensor) -> torch.Tensor:
        # Project input
        x = self.input_proj(x)
        
        # Filter edges by view
        ast_edges = self._filter_edges(edge_index, edge_attr, self.ast_types)
        cfg_edges = self._filter_edges(edge_index, edge_attr, self.cfg_types)
        dfg_edges = self._filter_edges(edge_index, edge_attr, self.dfg_types)
        
        # Process each view
        x_ast = x
        for layer in self.ast_layers:
            if ast_edges.size(1) > 0:
                x_ast = layer(x_ast, ast_edges)
                x_ast = F.elu(x_ast)
                x_ast = self.dropout(x_ast)
        
        x_cfg = x
        for layer in self.cfg_layers:
            if cfg_edges.size(1) > 0:
                x_cfg = layer(x_cfg, cfg_edges)
                x_cfg = F.elu(x_cfg)
                x_cfg = self.dropout(x_cfg)
        
        x_dfg = x
        for layer in self.dfg_layers:
            if dfg_edges.size(1) > 0:
                x_dfg = layer(x_dfg, dfg_edges)
                x_dfg = F.elu(x_dfg)
                x_dfg = self.dropout(x_dfg)
        
        # Cross-view attention (each view attends to others)
        # Stack views: [N, 3, hidden_dim]
        views = torch.stack([x_ast, x_cfg, x_dfg], dim=1)
        
        # Self-attention across views
        attn_out, _ = self.cross_attn(views, views, views)
        
        # Fusion
        fused = self.view_fusion(attn_out.reshape(-1, self.hidden_dim * 3))
        fused = self.layer_norm(fused + x)  # Residual
        
        return fused


# ═══════════════════════════════════════════════════════════════════
# CORE INNOVATION 3: Hierarchical Graph Pooling
# ═══════════════════════════════════════════════════════════════════

class HierarchicalPooling(nn.Module):
    """
    Multi-level pooling that captures patterns at different granularities:
    1. Node-level: Individual statement features
    2. Subgraph-level: Basic blocks / code regions
    3. Graph-level: Whole function
    
    Uses differentiable pooling to learn important substructures.
    """
    
    def __init__(self, hidden_dim: int, pool_ratio: float = 0.5):
        super().__init__()
        self.hidden_dim = hidden_dim
        
        # Level 1: Node importance scoring
        self.node_scorer = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Linear(hidden_dim // 2, 1)
        )
        
        # Level 2: Subgraph pooling (TopK)
        self.subgraph_pool = TopKPooling(hidden_dim, ratio=pool_ratio)
        
        # Level 3: Graph-level aggregation
        self.graph_attn = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.Tanh(),
            nn.Linear(hidden_dim // 2, 1)
        )
        
        # Combine levels
        self.level_fusion = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim)
        )
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor,
                batch: torch.Tensor) -> torch.Tensor:
        # Level 1: Weighted node features
        node_scores = self.node_scorer(x)
        node_scores = softmax(node_scores.squeeze(-1), batch)
        level1 = global_add_pool(x * node_scores.unsqueeze(-1), batch)
        
        # Level 2: Subgraph pooling
        pooled = self.subgraph_pool(x, edge_index, batch=batch)
        x2, edge_index2, _, batch2, perm, score = pooled
        level2 = global_mean_pool(x2, batch2)
        
        # Ensure level2 has same batch size as level1
        if level2.size(0) != level1.size(0):
            # Pad if necessary
            level2_padded = torch.zeros_like(level1)
            level2_padded[:level2.size(0)] = level2
            level2 = level2_padded
        
        # Level 3: Attention-based global pooling
        attn_scores = self.graph_attn(x)
        attn_scores = softmax(attn_scores.squeeze(-1), batch)
        level3 = global_add_pool(x * attn_scores.unsqueeze(-1), batch)
        
        # Fuse all levels
        combined = torch.cat([level1, level2, level3], dim=-1)
        output = self.level_fusion(combined)
        
        return output


# ═══════════════════════════════════════════════════════════════════
# CORE INNOVATION 4: Contrastive Graph Learning
# ═══════════════════════════════════════════════════════════════════

class ContrastiveGraphLearner(nn.Module):
    """
    Uses contrastive learning to create better graph representations:
    - Pulls vulnerable graphs together
    - Pushes vulnerable and safe graphs apart
    - Creates distinct clusters in embedding space
    """
    
    def __init__(self, hidden_dim: int, temperature: float = 0.07):
        super().__init__()
        self.temperature = temperature
        
        # Projection head for contrastive learning
        self.projector = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim // 2)
        )
    
    def forward(self, embeddings: torch.Tensor, labels: torch.Tensor) -> torch.Tensor:
        """
        Compute supervised contrastive loss.
        
        Args:
            embeddings: Graph embeddings [B, D]
            labels: Binary labels [B]
        
        Returns:
            Contrastive loss
        """
        # Project to contrastive space
        z = self.projector(embeddings)
        z = F.normalize(z, dim=1)
        
        # Compute similarity matrix
        sim_matrix = torch.mm(z, z.t()) / self.temperature
        
        # Create mask for positive pairs (same label)
        labels = labels.view(-1, 1)
        mask = torch.eq(labels, labels.t()).float()
        
        # Remove diagonal (self-similarity)
        mask = mask - torch.eye(mask.size(0), device=mask.device)
        
        # Compute loss
        exp_sim = torch.exp(sim_matrix)
        
        # For numerical stability
        exp_sim = exp_sim * (1 - torch.eye(mask.size(0), device=mask.device))
        
        # Positive pairs loss
        pos_sim = exp_sim * mask
        neg_sim = exp_sim.sum(dim=1, keepdim=True) - pos_sim
        
        # Avoid division by zero
        pos_count = mask.sum(dim=1, keepdim=True).clamp(min=1)
        
        loss = -torch.log(pos_sim.sum(dim=1) / (neg_sim.squeeze() + 1e-8) + 1e-8)
        loss = loss / pos_count.squeeze()
        
        return loss.mean()


# ═══════════════════════════════════════════════════════════════════
# MAIN MODEL: VulnGNN-SOTA
# ═══════════════════════════════════════════════════════════════════

class VulnGNNSOTA(nn.Module):
    """
    State-of-the-Art Vulnerability Detection Model
    
    Combines:
    1. Multi-view graph processing (AST/CFG/DFG)
    2. Taint propagation attention (source-sink analysis)
    3. Hierarchical pooling (multi-scale patterns)
    4. Contrastive learning (better representations)
    """
    
    def __init__(
        self,
        input_dim: int,
        hidden_dim: int = 256,
        num_layers: int = 3,
        num_edge_types: int = 13,
        dropout: float = 0.3,
        use_taint_attention: bool = True,
        use_contrastive: bool = True,
        contrastive_weight: float = 0.1
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.use_taint_attention = use_taint_attention
        self.use_contrastive = use_contrastive
        self.contrastive_weight = contrastive_weight
        
        # Multi-view GNN
        self.multi_view_gnn = MultiViewGNN(
            input_dim=input_dim,
            hidden_dim=hidden_dim,
            num_layers=num_layers,
            num_edge_types=num_edge_types,
            dropout=dropout
        )
        
        # Taint propagation attention
        if use_taint_attention:
            self.taint_attention = TaintPropagationAttention(
                hidden_dim=hidden_dim,
                num_heads=4
            )
        
        # Hierarchical pooling
        self.hierarchical_pool = HierarchicalPooling(
            hidden_dim=hidden_dim,
            pool_ratio=0.5
        )
        
        # Contrastive learning
        if use_contrastive:
            self.contrastive_learner = ContrastiveGraphLearner(
                hidden_dim=hidden_dim,
                temperature=0.07
            )
        
        # Final classifier
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim + (1 if use_taint_attention else 0), hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1)
        )
        
        # Initialize weights
        self._init_weights()
    
    def _init_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Linear):
                nn.init.xavier_uniform_(m.weight)
                if m.bias is not None:
                    nn.init.zeros_(m.bias)
    
    def forward(self, data: Data, return_loss: bool = False) -> Dict[str, torch.Tensor]:
        x = data.x
        edge_index = data.edge_index
        edge_attr = data.edge_attr if hasattr(data, 'edge_attr') else None
        batch = data.batch if hasattr(data, 'batch') else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Handle missing edge_attr
        if edge_attr is None:
            edge_attr = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        # Multi-view processing
        x = self.multi_view_gnn(x, edge_index, edge_attr, batch)
        
        # Taint attention
        taint_scores = None
        if self.use_taint_attention:
            x, taint_scores = self.taint_attention(x, edge_index, batch)
        
        # Hierarchical pooling
        graph_embed = self.hierarchical_pool(x, edge_index, batch)
        
        # Combine with taint scores if available
        if taint_scores is not None:
            graph_embed = torch.cat([graph_embed, taint_scores], dim=-1)
        
        # Classification
        logits = self.classifier(graph_embed).squeeze(-1)
        probs = torch.sigmoid(logits)
        
        output = {
            'logits': logits,
            'probs': probs,
            'graph_embed': graph_embed
        }
        
        # Contrastive loss during training
        if return_loss and self.use_contrastive and hasattr(data, 'y'):
            contrastive_loss = self.contrastive_learner(graph_embed[:, :-1] if taint_scores is not None else graph_embed, data.y)
            output['contrastive_loss'] = contrastive_loss
        
        return output
    
    def compute_loss(self, output: Dict[str, torch.Tensor], labels: torch.Tensor) -> torch.Tensor:
        """Compute combined loss."""
        # Binary cross-entropy
        bce_loss = F.binary_cross_entropy_with_logits(output['logits'], labels.float())
        
        # Add contrastive loss
        total_loss = bce_loss
        if 'contrastive_loss' in output:
            total_loss = total_loss + self.contrastive_weight * output['contrastive_loss']
        
        return total_loss


# ═══════════════════════════════════════════════════════════════════
# ALTERNATIVE: Simple but Effective Baseline
# ═══════════════════════════════════════════════════════════════════

class SimpleButEffective(nn.Module):
    """
    A simpler model that might work better than over-engineered solutions.
    
    Key insight: Devign's success comes from:
    1. Proper GGNN message passing
    2. Conv1D over node features (learns local patterns)
    3. Simple but effective pooling
    """
    
    def __init__(
        self,
        input_dim: int,
        hidden_dim: int = 256,
        num_layers: int = 4,
        num_edge_types: int = 13,
        kernel_size: int = 3,
        dropout: float = 0.2
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_edge_types = num_edge_types
        
        # Input projection
        self.input_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout)
        )
        
        # RGCN layers (edge-type aware)
        self.rgcn_layers = nn.ModuleList([
            RGCNConv(hidden_dim, hidden_dim, num_relations=num_edge_types)
            for _ in range(num_layers)
        ])
        
        self.layer_norms = nn.ModuleList([
            nn.LayerNorm(hidden_dim) for _ in range(num_layers)
        ])
        
        # Conv1D for local pattern detection (Devign-style)
        self.conv1d = nn.Sequential(
            nn.Conv1d(hidden_dim, hidden_dim, kernel_size, padding=kernel_size//2),
            nn.ReLU(),
            nn.Conv1d(hidden_dim, hidden_dim, kernel_size, padding=kernel_size//2),
            nn.ReLU()
        )
        
        # Attention pooling
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 4),
            nn.Tanh(),
            nn.Linear(hidden_dim // 4, 1)
        )
        
        # Classifier
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1)
        )
        
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, data: Data) -> Dict[str, torch.Tensor]:
        x = data.x
        edge_index = data.edge_index
        edge_type = data.edge_attr if hasattr(data, 'edge_attr') else torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        batch = data.batch if hasattr(data, 'batch') else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Input projection
        x = self.input_proj(x)
        
        # RGCN message passing with residual connections
        for i, (rgcn, ln) in enumerate(zip(self.rgcn_layers, self.layer_norms)):
            x_new = rgcn(x, edge_index, edge_type)
            x_new = F.relu(x_new)
            x_new = self.dropout(x_new)
            x = ln(x + x_new)  # Residual + LayerNorm
        
        # Convert to dense batch for Conv1D
        x_dense, mask = to_dense_batch(x, batch)  # [B, max_N, D]
        
        # Conv1D (transpose for channel-first)
        x_conv = x_dense.transpose(1, 2)  # [B, D, max_N]
        x_conv = self.conv1d(x_conv)
        x_conv = x_conv.transpose(1, 2)  # [B, max_N, D]
        
        # Mask padded positions
        x_conv = x_conv * mask.unsqueeze(-1)
        
        # Attention pooling
        attn_scores = self.attention(x_conv).squeeze(-1)  # [B, max_N]
        attn_scores = attn_scores.masked_fill(~mask, float('-inf'))
        attn_weights = F.softmax(attn_scores, dim=1)
        
        attn_pool = (x_conv * attn_weights.unsqueeze(-1)).sum(dim=1)  # [B, D]
        
        # Max pooling for salient features
        x_conv_masked = x_conv.masked_fill(~mask.unsqueeze(-1), float('-inf'))
        max_pool = x_conv_masked.max(dim=1)[0]  # [B, D]
        
        # Combine
        graph_embed = torch.cat([attn_pool, max_pool], dim=-1)
        
        # Classify
        logits = self.classifier(graph_embed).squeeze(-1)
        probs = torch.sigmoid(logits)
        
        return {
            'logits': logits,
            'probs': probs,
            'graph_embed': graph_embed
        }


# ═══════════════════════════════════════════════════════════════════
# DIAGNOSTIC: Feature Analysis
# ═══════════════════════════════════════════════════════════════════

def analyze_graph_features(data_list: List[Data]) -> Dict[str, any]:
    """Analyze graph features to understand what model is seeing."""
    
    vuln_graphs = [d for d in data_list if d.y.item() == 1]
    safe_graphs = [d for d in data_list if d.y.item() == 0]
    
    def get_stats(graphs):
        num_nodes = [g.x.size(0) for g in graphs]
        num_edges = [g.edge_index.size(1) for g in graphs]
        feat_mean = torch.stack([g.x.mean(0) for g in graphs]).mean(0)
        feat_std = torch.stack([g.x.std(0) for g in graphs]).mean(0)
        
        # Edge type distribution
        edge_types = {}
        for g in graphs:
            if hasattr(g, 'edge_attr'):
                for et in g.edge_attr.tolist():
                    edge_types[et] = edge_types.get(et, 0) + 1
        
        return {
            'count': len(graphs),
            'avg_nodes': sum(num_nodes) / len(num_nodes),
            'avg_edges': sum(num_edges) / len(num_edges),
            'feat_mean': feat_mean,
            'feat_std': feat_std,
            'edge_type_dist': edge_types
        }
    
    vuln_stats = get_stats(vuln_graphs) if vuln_graphs else None
    safe_stats = get_stats(safe_graphs) if safe_graphs else None
    
    # Feature overlap analysis
    if vuln_stats and safe_stats:
        feat_diff = (vuln_stats['feat_mean'] - safe_stats['feat_mean']).abs()
        discriminative_features = (feat_diff > feat_diff.mean()).sum().item()
        
        print("\n" + "="*70)
        print("FEATURE ANALYSIS")
        print("="*70)
        print(f"Vulnerable graphs: {vuln_stats['count']}")
        print(f"  Avg nodes: {vuln_stats['avg_nodes']:.1f}")
        print(f"  Avg edges: {vuln_stats['avg_edges']:.1f}")
        print(f"\nSafe graphs: {safe_stats['count']}")
        print(f"  Avg nodes: {safe_stats['avg_nodes']:.1f}")
        print(f"  Avg edges: {safe_stats['avg_edges']:.1f}")
        print(f"\nDiscriminative features: {discriminative_features}/{feat_diff.size(0)}")
        print(f"Mean feature difference: {feat_diff.mean():.4f}")
        print("="*70)
    
    return {'vuln': vuln_stats, 'safe': safe_stats}


if __name__ == "__main__":
    # Test the models
    print("Testing VulnGNN-SOTA...")
    
    # Create dummy data
    x = torch.randn(50, 92)  # 50 nodes, 92 features
    edge_index = torch.randint(0, 50, (2, 200))
    edge_attr = torch.randint(0, 13, (200,))
    batch = torch.zeros(50, dtype=torch.long)
    y = torch.tensor([1])
    
    data = Data(x=x, edge_index=edge_index, edge_attr=edge_attr, batch=batch, y=y)
    
    # Test SOTA model
    model = VulnGNNSOTA(input_dim=92, hidden_dim=128, num_edge_types=13)
    output = model(data, return_loss=True)
    print(f"SOTA output: logits={output['logits'].item():.4f}, prob={output['probs'].item():.4f}")
    
    # Test simple model
    model2 = SimpleButEffective(input_dim=92, hidden_dim=128, num_edge_types=13)
    output2 = model2(data)
    print(f"Simple output: logits={output2['logits'].item():.4f}, prob={output2['probs'].item():.4f}")
    
    print("\nModels created successfully!")