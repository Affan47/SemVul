#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
improved_baseline.py - Models that actually use the CPG structure

Key improvements:
1. Use edge types (REACHING_DEF, CDG, CFG, etc.) 
2. Hierarchical attention to find vulnerable regions
3. Multiple pooling strategies combined
4. Edge-aware message passing
"""

import argparse
import sys
import random
import io
import zipfile
from pathlib import Path
from collections import Counter

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, GATConv, global_mean_pool, global_max_pool, global_add_pool
from torch_geometric.nn import MessagePassing
from torch_geometric.utils import softmax

from sklearn.metrics import roc_auc_score, f1_score, accuracy_score

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


class EdgeTypeConv(MessagePassing):
    """Message passing that uses edge types."""
    
    def __init__(self, hidden_dim, num_edge_types=20, dropout=0.1):
        super().__init__(aggr='mean')
        
        self.hidden_dim = hidden_dim
        self.num_edge_types = num_edge_types
        
        # Edge type embeddings
        self.edge_embedding = nn.Embedding(num_edge_types, hidden_dim)
        
        # Message transformation
        self.msg_mlp = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
        )
        
        # Update
        self.update_mlp = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.ReLU(),
        )
    
    def forward(self, x, edge_index, edge_type=None):
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        edge_type = edge_type.clamp(0, self.num_edge_types - 1)
        edge_attr = self.edge_embedding(edge_type)
        
        return self.propagate(edge_index, x=x, edge_attr=edge_attr)
    
    def message(self, x_i, x_j, edge_attr):
        # Combine source, target, and edge features
        msg = torch.cat([x_i, x_j, edge_attr], dim=-1)
        return self.msg_mlp(msg)
    
    def update(self, aggr_out, x):
        # Combine aggregated messages with original features
        return self.update_mlp(torch.cat([x, aggr_out], dim=-1))


class HierarchicalAttentionPool(nn.Module):
    """Hierarchical attention to find important regions."""
    
    def __init__(self, hidden_dim):
        super().__init__()
        
        # Node importance scoring
        self.node_attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.Tanh(),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        # Graph-level attention
        self.graph_attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.Tanh(),
            nn.Linear(hidden_dim // 2, 1),
        )
    
    def forward(self, x, batch):
        # Compute node importance scores
        node_scores = self.node_attention(x).squeeze(-1)  # [N]
        
        # Softmax per graph
        node_weights = softmax(node_scores, batch)  # [N]
        
        # Weighted sum per graph
        weighted_x = x * node_weights.unsqueeze(-1)
        
        # Aggregate
        graph_emb = global_add_pool(weighted_x, batch)
        
        return graph_emb, node_weights


class ImprovedVulnDetector(nn.Module):
    """Improved model using edge types and hierarchical attention."""
    
    def __init__(self, input_dim, hidden_dim=256, num_edge_types=20, 
                 num_layers=2, dropout=0.2, use_edge_types=True):
        super().__init__()
        
        self.use_edge_types = use_edge_types
        
        # Input projection
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        # GNN layers
        self.convs = nn.ModuleList()
        for _ in range(num_layers):
            if use_edge_types:
                self.convs.append(EdgeTypeConv(hidden_dim, num_edge_types, dropout))
            else:
                self.convs.append(GCNConv(hidden_dim, hidden_dim))
        
        self.dropout = nn.Dropout(dropout)
        
        # Hierarchical attention pooling
        self.pool = HierarchicalAttentionPool(hidden_dim)
        
        # Also compute mean and max for robustness
        # Classifier takes attention + mean + max
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        edge_type = getattr(data, 'edge_type', None)
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Project
        h = F.relu(self.proj(x))
        
        # GNN layers
        for conv in self.convs:
            if self.use_edge_types and isinstance(conv, EdgeTypeConv):
                h_new = conv(h, edge_index, edge_type)
            else:
                h_new = conv(h, edge_index)
            h_new = F.relu(h_new)
            h_new = self.dropout(h_new)
            h = h + h_new  # Residual
        
        # Multi-pooling
        attn_pool, node_weights = self.pool(h, batch)
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        # Combine
        graph_emb = torch.cat([attn_pool, mean_pool, max_pool], dim=-1)
        
        return self.classifier(graph_emb), node_weights


class VulnMLP(nn.Module):
    """Enhanced MLP with better architecture."""
    
    def __init__(self, input_dim, hidden_dim=256, dropout=0.3):
        super().__init__()
        
        # Deep per-node transformation
        self.node_encoder = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
        )
        
        # Node attention for pooling
        self.node_attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 4),
            nn.Tanh(),
            nn.Linear(hidden_dim // 4, 1),
        )
        
        # Classifier
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1),
        )
    
    def forward(self, data):
        x = data.x.float()
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Encode nodes
        h = self.node_encoder(x)
        
        # Attention pooling
        attn_scores = self.node_attention(h).squeeze(-1)
        attn_weights = softmax(attn_scores, batch)
        attn_pool = global_add_pool(h * attn_weights.unsqueeze(-1), batch)
        
        # Also mean pool
        mean_pool = global_mean_pool(h, batch)
        
        # Combine
        graph_emb = torch.cat([attn_pool, mean_pool], dim=-1)
        
        return self.classifier(graph_emb), attn_weights


def load_data(cache_dir, dataset_name, cache_sig, split, max_samples=None):
    """Load data."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            if max_samples:
                random.shuffle(pt_files)
                pt_files = pt_files[:max_samples]
            
            for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                except:
                    continue
    
    return samples


def train_epoch(model, loader, optimizer, device, pos_weight=None):
    model.train()
    total_loss = 0
    num_samples = 0
    
    criterion = nn.BCEWithLogitsLoss(pos_weight=pos_weight)
    
    for batch in tqdm(loader, desc="Training", leave=False):
        batch = batch.to(device)
        optimizer.zero_grad()
        
        output = model(batch)
        if isinstance(output, tuple):
            logits = output[0].view(-1)
        else:
            logits = output.view(-1)
        
        labels = batch.y.float().view(-1)
        
        loss = criterion(logits, labels)
        loss.backward()
        
        torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        optimizer.step()
        
        total_loss += loss.item() * len(labels)
        num_samples += len(labels)
    
    return total_loss / num_samples


def evaluate(model, loader, device):
    model.eval()
    all_probs = []
    all_labels = []
    
    with torch.no_grad():
        for batch in loader:
            batch = batch.to(device)
            output = model(batch)
            if isinstance(output, tuple):
                logits = output[0].view(-1)
            else:
                logits = output.view(-1)
            
            probs = torch.sigmoid(logits)
            all_probs.append(probs.cpu())
            all_labels.append(batch.y.cpu().view(-1))
    
    probs = torch.cat(all_probs)
    labels = torch.cat(all_labels)
    
    try:
        auc = roc_auc_score(labels.numpy(), probs.numpy())
    except:
        auc = 0.5
    
    # Best threshold
    best_f1 = 0
    best_thresh = 0.5
    for thresh in np.arange(0.3, 0.7, 0.02):
        preds = (probs > thresh).long()
        f1 = f1_score(labels.numpy(), preds.numpy(), zero_division=0)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = thresh
    
    preds = (probs > best_thresh).long()
    acc = accuracy_score(labels.numpy(), preds.numpy())
    
    safe_probs = probs[labels == 0]
    vuln_probs = probs[labels == 1]
    
    return {
        'auc': auc,
        'f1': best_f1,
        'acc': acc,
        'thresh': best_thresh,
        'prob_std': probs.std().item(),
        'safe_mean': safe_probs.mean().item() if len(safe_probs) > 0 else 0,
        'vuln_mean': vuln_probs.mean().item() if len(vuln_probs) > 0 else 0,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--model", type=str, default="improved",
                       choices=["improved", "mlp_attn", "edge_type"])
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-layers", type=int, default=2)
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=50)
    parser.add_argument("--dropout", type=float, default=0.2)
    parser.add_argument("--max-samples", type=int, default=None)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 70)
    print("IMPROVED VULNERABILITY DETECTOR")
    print("=" * 70)
    print(f"Model: {args.model}")
    print(f"Hidden: {args.hidden_dim}, Layers: {args.num_layers}")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load data
    train_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "train", args.max_samples)
    val_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    test_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "test")
    
    print(f"Train: {len(train_data)} | Val: {len(val_data)} | Test: {len(test_data)}")
    
    input_dim = train_data[0].x.size(1)
    
    # Count edge types
    edge_types = set()
    for d in train_data[:1000]:
        if hasattr(d, 'edge_type') and d.edge_type is not None:
            edge_types.update(d.edge_type.tolist())
    num_edge_types = max(20, max(edge_types) + 1 if edge_types else 20)
    print(f"Edge types found: {len(edge_types)} (using {num_edge_types})")
    
    # Class weights
    labels = [d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in train_data]
    num_pos = sum(labels)
    num_neg = len(labels) - num_pos
    pos_weight = torch.tensor([num_neg / num_pos], device=device)
    
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    test_loader = DataLoader(test_data, batch_size=args.batch_size, shuffle=False)
    
    # Create model
    if args.model == "improved":
        model = ImprovedVulnDetector(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            num_edge_types=num_edge_types,
            num_layers=args.num_layers,
            dropout=args.dropout,
            use_edge_types=True,
        )
    elif args.model == "mlp_attn":
        model = VulnMLP(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            dropout=args.dropout,
        )
    else:  # edge_type
        model = ImprovedVulnDetector(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            num_edge_types=num_edge_types,
            num_layers=args.num_layers,
            dropout=args.dropout,
            use_edge_types=True,
        )
    
    model = model.to(device)
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    optimizer = torch.optim.AdamW(model.parameters(), lr=args.lr, weight_decay=1e-4)
    scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(optimizer, args.epochs)
    
    best_auc = 0.5
    best_epoch = 0
    
    for epoch in range(1, args.epochs + 1):
        train_loss = train_epoch(model, train_loader, optimizer, device, pos_weight)
        val_metrics = evaluate(model, val_loader, device)
        scheduler.step()
        
        if val_metrics['auc'] > best_auc:
            best_auc = val_metrics['auc']
            best_epoch = epoch
            torch.save(model.state_dict(), '/tmp/best_improved.pt')
            marker = " ← BEST"
        else:
            marker = ""
        
        if epoch % 5 == 0 or val_metrics['auc'] > best_auc - 0.001:
            print(f"Epoch {epoch:02d} | Loss: {train_loss:.4f} | "
                  f"AUC: {val_metrics['auc']:.4f} | F1: {val_metrics['f1']:.4f} | "
                  f"Safe: {val_metrics['safe_mean']:.3f} Vuln: {val_metrics['vuln_mean']:.3f}{marker}")
    
    # Final evaluation
    print("\n" + "=" * 70)
    print("FINAL EVALUATION")
    print("=" * 70)
    
    model.load_state_dict(torch.load('/tmp/best_improved.pt'))
    test_metrics = evaluate(model, test_loader, device)
    
    print(f"Best epoch: {best_epoch}")
    print(f"Test AUC: {test_metrics['auc']:.4f}")
    print(f"Test F1: {test_metrics['f1']:.4f}")
    print(f"Test Acc: {test_metrics['acc']:.4f}")


if __name__ == "__main__":
    main()
