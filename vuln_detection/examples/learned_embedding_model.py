#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
learned_embedding_model.py - Model with LEARNED embeddings (no GraphCodeBERT)

The problem with GraphCodeBERT:
- 97% cosine similarity between different functions
- The vulnerability signal gets lost in semantic similarity

This model:
1. Uses ONLY node type (one-hot, 28 dims) + structural features
2. Learns task-specific embeddings during training
3. Should produce more diverse representations

Expected: Better separation between safe/vulnerable samples
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
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import global_mean_pool, global_max_pool, global_add_pool
from torch_geometric.utils import degree, softmax

from sklearn.metrics import roc_auc_score, f1_score, accuracy_score, precision_score, recall_score
from sklearn.preprocessing import StandardScaler

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def compute_structural_features(data):
    """Compute structural features for each node.
    
    Features:
    - In-degree per edge type
    - Out-degree per edge type
    - Total degree
    - Is leaf node
    - Is root (no incoming edges)
    """
    num_nodes = data.x.size(0)
    edge_index = data.edge_index
    
    # Total degree
    in_deg = degree(edge_index[1], num_nodes=num_nodes)
    out_deg = degree(edge_index[0], num_nodes=num_nodes)
    total_deg = in_deg + out_deg
    
    # Normalized degrees
    max_deg = total_deg.max().clamp(min=1)
    in_deg_norm = in_deg / max_deg
    out_deg_norm = out_deg / max_deg
    total_deg_norm = total_deg / max_deg
    
    # Is leaf (no outgoing) / is root (no incoming)
    is_leaf = (out_deg == 0).float()
    is_root = (in_deg == 0).float()
    
    # Stack features: [num_nodes, 5]
    struct_features = torch.stack([
        in_deg_norm, 
        out_deg_norm, 
        total_deg_norm,
        is_leaf,
        is_root,
    ], dim=1)
    
    return struct_features


class LearnedEmbeddingModel(nn.Module):
    """Model that learns embeddings from node types + structure.
    
    NO GraphCodeBERT - learns task-specific representations.
    """
    
    def __init__(self, num_node_types=28, struct_dim=5, hidden_dim=128, dropout=0.3):
        super().__init__()
        
        # Learned node type embeddings
        self.node_type_embed = nn.Embedding(num_node_types, hidden_dim)
        
        # Structural feature projection
        self.struct_proj = nn.Linear(struct_dim, hidden_dim // 2)
        
        # Combine node type + structure
        self.combine = nn.Sequential(
            nn.Linear(hidden_dim + hidden_dim // 2, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Node-level transformation (deeper per-node processing)
        self.node_transform = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
        )
        
        # Attention for pooling
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 4),
            nn.Tanh(),
            nn.Linear(hidden_dim // 4, 1),
        )
        
        # Classifier (takes mean + max + attention pooled)
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.LayerNorm(hidden_dim),
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
        
        # Get node types from one-hot (first 28 dims)
        onehot = x[:, :28]
        node_types = onehot.argmax(dim=1)
        
        # Learned node type embeddings
        type_emb = self.node_type_embed(node_types)  # [N, hidden_dim]
        
        # Structural features
        struct_feat = compute_structural_features(data).to(x.device)
        struct_emb = self.struct_proj(struct_feat)  # [N, hidden_dim//2]
        
        # Combine
        combined = torch.cat([type_emb, struct_emb], dim=-1)
        h = self.combine(combined)
        
        # Per-node transformation
        h = h + self.node_transform(h)  # Residual
        
        # Multi-pooling
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        # Attention pooling
        attn_scores = self.attention(h).squeeze(-1)
        attn_weights = softmax(attn_scores, batch)
        attn_pool = global_add_pool(h * attn_weights.unsqueeze(-1), batch)
        
        # Combine and classify
        graph_emb = torch.cat([mean_pool, max_pool, attn_pool], dim=-1)
        return self.classifier(graph_emb)


class HybridModel(nn.Module):
    """Hybrid: Use GraphCodeBERT but with learned projection + structure.
    
    Key difference: Project GraphCodeBERT to MUCH smaller dim,
    then combine with learned structural features.
    """
    
    def __init__(self, num_node_types=28, gcb_dim=768, hidden_dim=128, dropout=0.3):
        super().__init__()
        
        # Project GraphCodeBERT to small dim (reduce noise)
        self.gcb_proj = nn.Sequential(
            nn.Linear(gcb_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim // 2),  # Compress!
        )
        
        # Learned node type embeddings
        self.node_type_embed = nn.Embedding(num_node_types, hidden_dim // 4)
        
        # Structural features
        self.struct_proj = nn.Linear(5, hidden_dim // 4)
        
        # Combine all: gcb (hidden//2) + type (hidden//4) + struct (hidden//4) = hidden
        self.combine = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Deeper processing
        self.transform = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # Attention pooling
        self.attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 4),
            nn.Tanh(),
            nn.Linear(hidden_dim // 4, 1),
        )
        
        # Classifier
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim * 3, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
    
    def forward(self, data):
        x = data.x.float()
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Split input
        onehot = x[:, :28]
        gcb = x[:, 28:]
        
        # Process each component
        node_types = onehot.argmax(dim=1)
        type_emb = self.node_type_embed(node_types)
        
        gcb_emb = self.gcb_proj(gcb)
        
        struct_feat = compute_structural_features(data).to(x.device)
        struct_emb = self.struct_proj(struct_feat)
        
        # Combine
        combined = torch.cat([gcb_emb, type_emb, struct_emb], dim=-1)
        h = self.combine(combined)
        h = h + self.transform(h)
        
        # Pool
        mean_pool = global_mean_pool(h, batch)
        max_pool = global_max_pool(h, batch)
        
        attn_scores = self.attention(h).squeeze(-1)
        attn_weights = softmax(attn_scores, batch)
        attn_pool = global_add_pool(h * attn_weights.unsqueeze(-1), batch)
        
        graph_emb = torch.cat([mean_pool, max_pool, attn_pool], dim=-1)
        return self.classifier(graph_emb)


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


class FocalLoss(nn.Module):
    def __init__(self, alpha=0.25, gamma=2.0):
        super().__init__()
        self.alpha = alpha
        self.gamma = gamma
    
    def forward(self, logits, targets):
        bce = F.binary_cross_entropy_with_logits(logits, targets, reduction='none')
        pt = torch.exp(-bce)
        focal = self.alpha * (1 - pt) ** self.gamma * bce
        return focal.mean()


def train_epoch(model, loader, optimizer, criterion, device):
    model.train()
    total_loss = 0
    num_batches = 0
    
    for batch in tqdm(loader, desc="Training", leave=False):
        batch = batch.to(device)
        optimizer.zero_grad()
        
        logits = model(batch).view(-1)
        labels = batch.y.float().view(-1)
        
        loss = criterion(logits, labels)
        loss.backward()
        
        torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        optimizer.step()
        
        total_loss += loss.item()
        num_batches += 1
    
    return total_loss / num_batches


def evaluate(model, loader, device):
    model.eval()
    all_probs = []
    all_labels = []
    
    with torch.no_grad():
        for batch in loader:
            batch = batch.to(device)
            logits = model(batch).view(-1)
            probs = torch.sigmoid(logits)
            all_probs.append(probs.cpu())
            all_labels.append(batch.y.cpu().view(-1))
    
    probs = torch.cat(all_probs).numpy()
    labels = torch.cat(all_labels).numpy()
    
    # AUC
    try:
        auc = roc_auc_score(labels, probs)
    except:
        auc = 0.5
    
    # F1 at threshold 0.50 (fair comparison)
    preds_50 = (probs > 0.50).astype(int)
    f1_50 = f1_score(labels, preds_50, zero_division=0)
    prec_50 = precision_score(labels, preds_50, zero_division=0)
    rec_50 = recall_score(labels, preds_50, zero_division=0)
    
    # Best F1 (any threshold)
    best_f1 = 0
    best_thresh = 0.5
    for t in np.arange(0.3, 0.7, 0.02):
        preds = (probs > t).astype(int)
        f1 = f1_score(labels, preds, zero_division=0)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = t
    
    # Prediction distribution
    safe_probs = probs[labels == 0]
    vuln_probs = probs[labels == 1]
    
    return {
        'auc': auc,
        'f1_50': f1_50,
        'precision_50': prec_50,
        'recall_50': rec_50,
        'f1_best': best_f1,
        'best_thresh': best_thresh,
        'safe_mean': safe_probs.mean(),
        'vuln_mean': vuln_probs.mean(),
        'separation': vuln_probs.mean() - safe_probs.mean(),
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    
    parser.add_argument("--model", type=str, default="learned",
                       choices=["learned", "hybrid"],
                       help="learned=no GraphCodeBERT, hybrid=compressed GraphCodeBERT")
    parser.add_argument("--hidden-dim", type=int, default=128)
    parser.add_argument("--dropout", type=float, default=0.3)
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=100)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    parser.add_argument("--seed", type=int, default=42)
    args = parser.parse_args()
    
    random.seed(args.seed)
    np.random.seed(args.seed)
    torch.manual_seed(args.seed)
    
    print("=" * 70)
    print("LEARNED EMBEDDING MODEL")
    print("=" * 70)
    print(f"Model type: {args.model}")
    print(f"Hidden dim: {args.hidden_dim}")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load data
    train_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "train")
    val_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    test_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "test")
    
    print(f"\nData: Train={len(train_data)} | Val={len(val_data)} | Test={len(test_data)}")
    
    # Class balance
    labels = [d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in train_data]
    num_pos = sum(labels)
    num_neg = len(labels) - num_pos
    print(f"Class balance: Neg={num_neg} ({num_neg/len(labels)*100:.1f}%), Pos={num_pos} ({num_pos/len(labels)*100:.1f}%)")
    
    # Data loaders
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    test_loader = DataLoader(test_data, batch_size=args.batch_size, shuffle=False)
    
    # Model
    if args.model == "learned":
        model = LearnedEmbeddingModel(
            hidden_dim=args.hidden_dim,
            dropout=args.dropout,
        ).to(device)
    else:
        model = HybridModel(
            hidden_dim=args.hidden_dim,
            dropout=args.dropout,
        ).to(device)
    
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    # Training setup
    criterion = FocalLoss(alpha=0.25, gamma=2.0)
    optimizer = torch.optim.AdamW(model.parameters(), lr=args.lr, weight_decay=1e-4)
    scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(optimizer, args.epochs)
    
    # Train
    print("\n" + "=" * 70)
    print("TRAINING")
    print("=" * 70)
    
    best_auc = 0.5
    best_epoch = 0
    patience = 20
    no_improve = 0
    
    for epoch in range(1, args.epochs + 1):
        train_loss = train_epoch(model, train_loader, optimizer, criterion, device)
        val_metrics = evaluate(model, val_loader, device)
        scheduler.step()
        
        if val_metrics['auc'] > best_auc:
            best_auc = val_metrics['auc']
            best_epoch = epoch
            torch.save(model.state_dict(), '/tmp/best_learned.pt')
            no_improve = 0
            marker = " ← BEST"
        else:
            no_improve += 1
            marker = ""
        
        if epoch % 5 == 0 or marker:
            print(f"Epoch {epoch:02d} | Loss: {train_loss:.4f} | "
                  f"AUC: {val_metrics['auc']:.4f} | F1@0.5: {val_metrics['f1_50']:.4f} | "
                  f"Sep: {val_metrics['separation']:.3f}{marker}")
        
        if no_improve >= patience:
            print(f"\nEarly stopping at epoch {epoch}")
            break
    
    # Final evaluation
    print("\n" + "=" * 70)
    print("FINAL EVALUATION")
    print("=" * 70)
    
    model.load_state_dict(torch.load('/tmp/best_learned.pt'))
    test_metrics = evaluate(model, test_loader, device)
    
    print(f"\nBest epoch: {best_epoch}")
    print(f"\n--- At Threshold 0.50 (Fair Comparison) ---")
    print(f"AUC: {test_metrics['auc']:.4f}")
    print(f"F1: {test_metrics['f1_50']:.4f}")
    print(f"Precision: {test_metrics['precision_50']:.4f}")
    print(f"Recall: {test_metrics['recall_50']:.4f}")
    
    print(f"\n--- Best F1 (Any Threshold) ---")
    print(f"F1: {test_metrics['f1_best']:.4f} @ threshold={test_metrics['best_thresh']:.2f}")
    
    print(f"\n--- Prediction Distribution ---")
    print(f"Safe samples: {test_metrics['safe_mean']:.3f}")
    print(f"Vuln samples: {test_metrics['vuln_mean']:.3f}")
    print(f"Separation: {test_metrics['separation']:.3f}")
    
    # Comparison
    print("\n" + "=" * 70)
    print("COMPARISON WITH BASELINES")
    print("=" * 70)
    print(f"{'Method':<30} {'AUC':>8} {'F1@0.5':>8} {'Prec':>8} {'Rec':>8}")
    print("-" * 70)
    print(f"{'Devign (original)':<30} {'0.60':>8} {'0.45':>8} {'0.42':>8} {'0.48':>8}")
    print(f"{'ReVeal':<30} {'0.63':>8} {'0.48':>8} {'0.45':>8} {'0.52':>8}")
    print(f"{'Your GCN (collapsed)':<30} {'0.50':>8} {'N/A':>8} {'N/A':>8} {'N/A':>8}")
    print(f"{'Graph-level MLP':<30} {'0.632':>8} {'~0.48':>8} {'~0.45':>8} {'~0.52':>8}")
    print(f"{'This model':<30} {test_metrics['auc']:>8.4f} {test_metrics['f1_50']:>8.4f} {test_metrics['precision_50']:>8.4f} {test_metrics['recall_50']:>8.4f}")
    
    if test_metrics['auc'] > 0.63:
        print(f"\n✅ BEATS ReVeal baseline!")
    elif test_metrics['auc'] > 0.60:
        print(f"\n✅ BEATS Devign baseline!")
    else:
        print(f"\n⚠️ Below baselines - try hybrid model or tune hyperparameters")


if __name__ == "__main__":
    main()
