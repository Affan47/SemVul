#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
train_contrastive.py - Training with Contrastive Learning + HAGNN

Two-Phase Training:
  Phase 1 (Pre-training): Joint contrastive + classification loss
  Phase 2 (Fine-tuning): Classification loss with lower LR

Usage:
    python -m vuln_detection.train_contrastive \
        --model-type hagnn \
        --cache-dir /path/to/cache \
        --dataset-name word2vec_200d_full \
        --cache-signature 86c56b1755c532ee \
        --hidden-dim 256 \
        --num-layers 4 \
        --num-edge-types 18 \
        --loss-type combined \
        --label-smoothing 0.05 \
        --early-stop-metric loss \
        --lr-scheduler-metric loss \
        --contrastive-weight 0.5 \
        --epochs-pretrain 50 \
        --epochs-finetune 100
"""

import argparse
import json
import logging
import random
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.optim import AdamW
from torch.optim.lr_scheduler import CosineAnnealingLR, ReduceLROnPlateau

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x

# PyTorch Geometric
from torch_geometric.loader import DataLoader
from torch_geometric.data import Data

# Add parent to path for imports (same as train.py)
sys.path.insert(0, str(Path(__file__).parent.parent))

# ═══════════════════════════════════════════════════════════════════════════════
# IMPORT FROM EXISTING vuln_detection PACKAGE (same as train.py)
# ═══════════════════════════════════════════════════════════════════════════════
from vuln_detection import (
    load_dataset,
    create_data_loaders,
    get_class_weights,
    compute_full_evaluation,
)
from vuln_detection.utils import print_dataset_stats
from vuln_detection.utils.losses import create_loss

# Logging setup
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[logging.StreamHandler()]
)
logger = logging.getLogger(__name__)


# ═══════════════════════════════════════════════════════════════════════════════
# METRICS
# ═══════════════════════════════════════════════════════════════════════════════

def compute_metrics(preds: np.ndarray, labels: np.ndarray) -> Dict[str, float]:
    """Compute classification metrics."""
    from sklearn.metrics import roc_auc_score, f1_score, precision_score, recall_score
    
    metrics = {}
    
    try:
        metrics['auc'] = roc_auc_score(labels, preds)
    except:
        metrics['auc'] = 0.5
    
    best_f1 = 0
    best_thresh = 0.5
    for thresh in np.arange(0.1, 0.9, 0.05):
        pred_binary = (preds > thresh).astype(int)
        f1 = f1_score(labels, pred_binary, zero_division=0)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = thresh
    
    pred_binary = (preds > best_thresh).astype(int)
    metrics['f1'] = best_f1
    metrics['precision'] = precision_score(labels, pred_binary, zero_division=0)
    metrics['recall'] = recall_score(labels, pred_binary, zero_division=0)
    metrics['threshold'] = best_thresh
    metrics['brier'] = float(np.mean((preds - labels) ** 2))
    
    return metrics


def _metric_lower_is_better(metric_name: str) -> bool:
    return metric_name in {"loss", "brier"}


def _get_metric_value(metrics: Dict[str, float], metric_name: str) -> float:
    if metric_name not in metrics:
        raise KeyError(f"Metric '{metric_name}' not available in metrics.")
    return metrics[metric_name]


def _is_improved(current: float, best: float, metric_name: str, min_delta: float) -> bool:
    if best is None:
        return True
    if _metric_lower_is_better(metric_name):
        return current < (best - min_delta)
    return current > (best + min_delta)


# ═══════════════════════════════════════════════════════════════════════════════
# CONTRASTIVE LOSS
# ═══════════════════════════════════════════════════════════════════════════════

class SupervisedContrastiveLoss(nn.Module):
    """Supervised Contrastive Loss for vulnerability detection."""
    
    def __init__(self, temperature: float = 0.07):
        super().__init__()
        self.temperature = temperature
    
    def forward(self, features: torch.Tensor, labels: torch.Tensor) -> torch.Tensor:
        device = features.device
        batch_size = features.shape[0]
        
        if batch_size < 2:
            return torch.tensor(0.0, device=device, requires_grad=True)
        
        features = F.normalize(features, p=2, dim=1)
        similarity = torch.matmul(features, features.T) / self.temperature
        
        labels = labels.view(-1, 1)
        pos_mask = torch.eq(labels, labels.T).float()
        logits_mask = torch.ones_like(pos_mask) - torch.eye(batch_size, device=device)
        pos_mask = pos_mask * logits_mask
        
        if pos_mask.sum() == 0:
            return torch.tensor(0.0, device=device, requires_grad=True)
        
        logits_max, _ = torch.max(similarity * logits_mask, dim=1, keepdim=True)
        logits = similarity - logits_max.detach()
        
        exp_logits = torch.exp(logits) * logits_mask
        log_prob = logits - torch.log(exp_logits.sum(dim=1, keepdim=True) + 1e-12)
        
        pos_count = pos_mask.sum(dim=1).clamp(min=1.0)
        mean_log_prob = (pos_mask * log_prob).sum(dim=1) / pos_count
        
        return -mean_log_prob.mean()


class ProjectionHead(nn.Module):
    """MLP projection head for contrastive learning."""
    
    def __init__(self, input_dim: int, hidden_dim: int = 256, output_dim: int = 128):
        super().__init__()
        self.mlp = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.BatchNorm1d(hidden_dim),
            nn.ReLU(),
            nn.Dropout(0.1),
            nn.Linear(hidden_dim, output_dim),
        )
    
    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.mlp(x)


# ═══════════════════════════════════════════════════════════════════════════════
# HAGNN MODEL
# ═══════════════════════════════════════════════════════════════════════════════

from torch_geometric.nn import MessagePassing
from torch_geometric.utils import softmax


class EdgeTypeGATConv(MessagePassing):
    """GAT with edge-type-specific transformations."""
    
    def __init__(self, in_channels: int, out_channels: int, num_edge_types: int, 
                 heads: int = 4, dropout: float = 0.1):
        super().__init__(aggr='add', node_dim=0)
        
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.num_edge_types = num_edge_types
        self.heads = heads
        self.head_dim = out_channels // heads
        self.dropout = dropout
        
        self.lin = nn.Linear(in_channels, heads * self.head_dim, bias=False)
        self.att_src = nn.Parameter(torch.Tensor(1, heads, self.head_dim))
        self.att_dst = nn.Parameter(torch.Tensor(1, heads, self.head_dim))
        self.edge_type_emb = nn.Embedding(num_edge_types + 1, heads)
        self.bias = nn.Parameter(torch.Tensor(heads * self.head_dim))
        
        self._reset_parameters()
    
    def _reset_parameters(self):
        nn.init.xavier_uniform_(self.lin.weight)
        nn.init.xavier_uniform_(self.att_src)
        nn.init.xavier_uniform_(self.att_dst)
        nn.init.zeros_(self.bias)
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor, 
                edge_type: torch.Tensor) -> torch.Tensor:
        
        x_transformed = self.lin(x).view(-1, self.heads, self.head_dim)
        src, dst = edge_index
        
        alpha_src = (x_transformed[src] * self.att_src).sum(dim=-1)
        alpha_dst = (x_transformed[dst] * self.att_dst).sum(dim=-1)
        
        edge_type_clamped = edge_type.clamp(0, self.num_edge_types)
        edge_weight = self.edge_type_emb(edge_type_clamped)
        
        alpha = F.leaky_relu(alpha_src + alpha_dst, 0.2)
        alpha = alpha * edge_weight
        alpha = softmax(alpha.mean(dim=-1), dst, num_nodes=x.size(0))
        alpha = F.dropout(alpha, p=self.dropout, training=self.training)
        
        out = self.propagate(edge_index, x=x_transformed, alpha=alpha)
        out = out.view(-1, self.heads * self.head_dim) + self.bias
        
        return out
    
    def message(self, x_j: torch.Tensor, alpha: torch.Tensor) -> torch.Tensor:
        return alpha.unsqueeze(-1).unsqueeze(-1) * x_j


class HAGNNLayer(nn.Module):
    """HAGNN Layer with residual connection."""
    
    def __init__(self, in_channels: int, out_channels: int, num_edge_types: int,
                 heads: int = 4, dropout: float = 0.2):
        super().__init__()
        
        self.conv = EdgeTypeGATConv(in_channels, out_channels, num_edge_types, 
                                     heads=heads, dropout=dropout)
        self.norm = nn.LayerNorm(out_channels)
        self.residual = nn.Linear(in_channels, out_channels) if in_channels != out_channels else nn.Identity()
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor, 
                edge_type: torch.Tensor) -> torch.Tensor:
        residual = self.residual(x)
        out = self.conv(x, edge_index, edge_type)
        out = self.norm(self.dropout(out) + residual)
        return F.relu(out)


class HAGNNVulnDetector(nn.Module):
    """Complete HAGNN Vulnerability Detector with dual-path pooling."""
    
    def __init__(self, input_dim: int, hidden_dim: int = 256, num_layers: int = 4,
                 num_edge_types: int = 18, num_node_types: int = 16, 
                 call_node_idx: int = 2, heads: int = 4, dropout: float = 0.2):
        super().__init__()
        
        self.num_node_types = num_node_types
        self.call_node_idx = call_node_idx
        self.hidden_dim = hidden_dim
        
        self.input_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
        
        self.layers = nn.ModuleList([
            HAGNNLayer(hidden_dim, hidden_dim, num_edge_types, heads, dropout)
            for _ in range(num_layers)
        ])
        
        self.pool_attention = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.Tanh(),
            nn.Linear(hidden_dim // 2, 1),
        )
        
        self.alpha = nn.Parameter(torch.tensor(0.7))
        
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
        
        self.projection_head = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, 128),
        )
    
    def forward(self, batch, return_embeddings: bool = False) -> Dict[str, torch.Tensor]:
        x = batch.x
        edge_index = batch.edge_index
        batch_idx = batch.batch
        
        # Get edge types - handle both edge_type and edge_attr
        if hasattr(batch, 'edge_type') and batch.edge_type is not None:
            edge_type = batch.edge_type.long()
        elif hasattr(batch, 'edge_attr') and batch.edge_attr is not None:
            if batch.edge_attr.dim() == 1:
                edge_type = batch.edge_attr.long()
            else:
                edge_type = batch.edge_attr.argmax(dim=1) if batch.edge_attr.size(1) > 1 else batch.edge_attr.squeeze().long()
        else:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        h = self.input_proj(x)
        
        for layer in self.layers:
            h = layer(h, edge_index, edge_type)
        
        device = h.device
        batch_size = batch_idx.max().item() + 1
        
        # CALL-focused pooling
        if x.size(1) >= self.num_node_types:
            node_types = x[:, :self.num_node_types].argmax(dim=1)
            call_mask = node_types == self.call_node_idx
        else:
            call_mask = torch.zeros(x.size(0), dtype=torch.bool, device=device)
        
        call_emb = torch.zeros(batch_size, self.hidden_dim, device=device)
        for b in range(batch_size):
            graph_mask = batch_idx == b
            call_graph_mask = graph_mask & call_mask
            
            if call_graph_mask.sum() > 0:
                call_emb[b] = h[call_graph_mask].max(dim=0)[0]
            else:
                call_emb[b] = h[graph_mask].max(dim=0)[0]
        
        # Attention pooling
        attn_scores = self.pool_attention(h).squeeze(-1)
        attn_weights = softmax(attn_scores, batch_idx)
        
        global_emb = torch.zeros(batch_size, self.hidden_dim, device=device)
        global_emb.scatter_add_(0, batch_idx.unsqueeze(-1).expand_as(h), 
                                attn_weights.unsqueeze(-1) * h)
        
        alpha = torch.sigmoid(self.alpha)
        
        call_logits = self.call_classifier(call_emb).squeeze(-1)
        global_logits = self.global_classifier(global_emb).squeeze(-1)
        logits = alpha * call_logits + (1 - alpha) * global_logits
        
        result = {'logits': logits, 'call_logits': call_logits, 
                  'global_logits': global_logits, 'alpha': alpha}
        
        if return_embeddings:
            graph_emb = alpha * call_emb + (1 - alpha) * global_emb
            result['graph_embedding'] = graph_emb
            result['projection'] = self.projection_head(graph_emb)
        
        return result


# ═══════════════════════════════════════════════════════════════════════════════
# UTILITIES
# ═══════════════════════════════════════════════════════════════════════════════

def set_seed(seed: int):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


def count_parameters(model: nn.Module) -> Tuple[int, int]:
    total = sum(p.numel() for p in model.parameters())
    trainable = sum(p.numel() for p in model.parameters() if p.requires_grad)
    return total, trainable


def fix_edge_type_naming(data_list):
    """Convert edge_attr to edge_type for compatibility."""
    fixed = 0
    for data in data_list:
        if hasattr(data, 'edge_attr') and not hasattr(data, 'edge_type'):
            data.edge_type = data.edge_attr
            fixed += 1
        elif not hasattr(data, 'edge_type') and not hasattr(data, 'edge_attr'):
            if hasattr(data, 'edge_index') and data.edge_index is not None:
                data.edge_type = torch.zeros(data.edge_index.size(1), dtype=torch.long)
    return fixed


# ═══════════════════════════════════════════════════════════════════════════════
# TRAINING FUNCTIONS
# ═══════════════════════════════════════════════════════════════════════════════

def train_epoch_contrastive(model, loader, optimizer, contrastive_loss_fn, 
                            classification_loss_fn, projection_head, device,
                            alpha=0.5, max_grad_norm=1.0):
    model.train()
    projection_head.train()
    
    total_loss = 0.0
    contrastive_losses = 0.0
    classification_losses = 0.0
    num_batches = 0
    all_preds = []
    all_labels = []
    
    pbar = tqdm(loader, desc="Training", leave=False)
    
    for batch in pbar:
        batch = batch.to(device)
        optimizer.zero_grad()
        
        output = model(batch, return_embeddings=True)
        embeddings = output['graph_embedding']
        logits = output['logits']
        
        if logits.dim() > 1:
            logits = logits.squeeze(-1)
        
        projections = projection_head(embeddings)
        projections = F.normalize(projections, p=2, dim=1)
        
        labels = batch.y
        if labels.dim() > 1:
            labels = labels.squeeze(-1)
        
        l_contrastive = contrastive_loss_fn(projections, labels)
        l_classification = classification_loss_fn(logits, labels.float())
        loss = alpha * l_contrastive + (1 - alpha) * l_classification
        
        loss.backward()
        torch.nn.utils.clip_grad_norm_(model.parameters(), max_grad_norm)
        torch.nn.utils.clip_grad_norm_(projection_head.parameters(), max_grad_norm)
        optimizer.step()
        
        total_loss += loss.item()
        contrastive_losses += l_contrastive.item()
        classification_losses += l_classification.item()
        num_batches += 1
        
        with torch.no_grad():
            preds = torch.sigmoid(logits)
            all_preds.extend(preds.cpu().numpy())
            all_labels.extend(labels.cpu().numpy())
        
        pbar.set_postfix({'loss': f'{loss.item():.4f}', 'scl': f'{l_contrastive.item():.4f}'})
    
    metrics = {
        'loss': total_loss / num_batches,
        'contrastive_loss': contrastive_losses / num_batches,
        'classification_loss': classification_losses / num_batches,
    }
    metrics.update(compute_metrics(np.array(all_preds), np.array(all_labels)))
    
    return metrics


def train_epoch_finetune(model, loader, optimizer, loss_fn, device, max_grad_norm=1.0):
    model.train()
    
    total_loss = 0.0
    num_batches = 0
    all_preds = []
    all_labels = []
    
    pbar = tqdm(loader, desc="Fine-tuning", leave=False)
    
    for batch in pbar:
        batch = batch.to(device)
        optimizer.zero_grad()
        
        output = model(batch)
        logits = output['logits'] if isinstance(output, dict) else output
        
        if logits.dim() > 1:
            logits = logits.squeeze(-1)
        
        labels = batch.y
        if labels.dim() > 1:
            labels = labels.squeeze(-1)
        
        loss = loss_fn(logits, labels.float())
        
        loss.backward()
        torch.nn.utils.clip_grad_norm_(model.parameters(), max_grad_norm)
        optimizer.step()
        
        total_loss += loss.item()
        num_batches += 1
        
        with torch.no_grad():
            preds = torch.sigmoid(logits)
            all_preds.extend(preds.cpu().numpy())
            all_labels.extend(labels.cpu().numpy())
        
        pbar.set_postfix({'loss': f'{loss.item():.4f}'})
    
    metrics = {'loss': total_loss / num_batches}
    metrics.update(compute_metrics(np.array(all_preds), np.array(all_labels)))
    
    return metrics


@torch.no_grad()
def evaluate(model, loader, loss_fn, device):
    model.eval()
    
    total_loss = 0.0
    num_batches = 0
    all_preds = []
    all_labels = []
    
    for batch in loader:
        batch = batch.to(device)
        
        output = model(batch)
        logits = output['logits'] if isinstance(output, dict) else output
        
        if logits.dim() > 1:
            logits = logits.squeeze(-1)
        
        labels = batch.y
        if labels.dim() > 1:
            labels = labels.squeeze(-1)
        
        loss = loss_fn(logits, labels.float())
        total_loss += loss.item()
        num_batches += 1
        
        preds = torch.sigmoid(logits)
        all_preds.extend(preds.cpu().numpy())
        all_labels.extend(labels.cpu().numpy())
    
    metrics = {'loss': total_loss / max(num_batches, 1)}
    metrics.update(compute_metrics(np.array(all_preds), np.array(all_labels)))
    
    return metrics


# ═══════════════════════════════════════════════════════════════════════════════
# MAIN TRAINING LOOP
# ═══════════════════════════════════════════════════════════════════════════════

def train_with_contrastive_learning(model, train_loader, val_loader, test_loader, 
                                     device, args):
    """Two-phase training with contrastive learning."""
    
    contrastive_loss_fn = SupervisedContrastiveLoss(temperature=args.temperature)
    
    # Calculate pos_weight
    num_pos = sum(1 for data in train_loader.dataset if data.y.item() == 1)
    num_neg = len(train_loader.dataset) - num_pos
    pos_weight = torch.tensor([num_neg / max(num_pos, 1)], device=device)
    print(f"Class distribution: {num_pos} pos, {num_neg} neg (weight={pos_weight.item():.2f})")
    
    loss_kwargs = {}
    if args.loss_type in {"combined"}:
        loss_kwargs = {
            "f1_weight": args.f1_weight,
            "label_smoothing": args.label_smoothing,
        }
    elif args.loss_type == "combined_v2":
        loss_kwargs = {
            "bce_weight": args.bce_weight,
            "focal_weight": args.focal_weight,
            "f1_weight": args.f1_weight,
            "smoothing": args.label_smoothing,
            "focal_gamma": args.focal_gamma,
        }
    elif args.loss_type == "focal":
        loss_kwargs = {"gamma": args.focal_gamma}
    elif args.loss_type == "label_smooth":
        loss_kwargs = {"smoothing": args.label_smoothing}

    if args.loss_type == "combined_v2":
        classification_loss_fn = create_loss(
            loss_type=args.loss_type,
            pos_weight=pos_weight,
            **loss_kwargs,
        )
    else:
        classification_loss_fn = create_loss(
            loss_type=args.loss_type,
            pos_weight=pos_weight,
            focal_weight=args.focal_weight,
            **loss_kwargs,
        )

    loss_details = []
    if args.loss_type in {"combined", "combined_v2"}:
        loss_details.append(f"label_smoothing={args.label_smoothing}")
        loss_details.append(f"focal_weight={args.focal_weight}")
        if args.loss_type == "combined_v2":
            loss_details.append(f"bce_weight={args.bce_weight}")
            loss_details.append(f"f1_weight={args.f1_weight}")
            loss_details.append(f"focal_gamma={args.focal_gamma}")
        else:
            loss_details.append(f"f1_weight={args.f1_weight}")
    elif args.loss_type == "focal":
        loss_details.append(f"focal_gamma={args.focal_gamma}")
    elif args.loss_type == "label_smooth":
        loss_details.append(f"label_smoothing={args.label_smoothing}")

    if loss_details:
        print(f"Loss: {args.loss_type} ({', '.join(loss_details)})")
    else:
        print(f"Loss: {args.loss_type}")
    
    projection_head = ProjectionHead(args.hidden_dim, args.hidden_dim, 128).to(device)
    
    # PHASE 1: Contrastive Pre-training
    print("=" * 60)
    print("PHASE 1: Contrastive Pre-training")
    print("=" * 60)
    
    optimizer = AdamW(
        list(model.parameters()) + list(projection_head.parameters()),
        lr=args.lr_pretrain, weight_decay=args.weight_decay,
    )
    scheduler = CosineAnnealingLR(optimizer, T_max=args.epochs_pretrain)
    
    best_val_metric = None
    best_model_state = None
    patience_counter = 0
    
    for epoch in range(args.epochs_pretrain):
        print(f"\nPretrain Epoch {epoch + 1}/{args.epochs_pretrain}")
        
        train_metrics = train_epoch_contrastive(
            model, train_loader, optimizer, contrastive_loss_fn, 
            classification_loss_fn, projection_head, device, args.contrastive_weight,
        )
        scheduler.step()
        
        val_metrics = evaluate(model, val_loader, classification_loss_fn, device)
        
        print(f"  Train - Loss: {train_metrics['loss']:.4f}, "
              f"SCL: {train_metrics['contrastive_loss']:.4f}, "
              f"AUC: {train_metrics['auc']:.4f}, F1: {train_metrics['f1']:.4f}, "
              f"Brier: {train_metrics['brier']:.4f}")
        print(f"  Val   - Loss: {val_metrics['loss']:.4f}, "
              f"AUC: {val_metrics['auc']:.4f}, F1: {val_metrics['f1']:.4f}, "
              f"Brier: {val_metrics['brier']:.4f}")
        
        current_metric = _get_metric_value(val_metrics, args.early_stop_metric)
        if _is_improved(current_metric, best_val_metric, args.early_stop_metric, args.early_stop_min_delta):
            best_val_metric = current_metric
            best_model_state = {k: v.cpu().clone() for k, v in model.state_dict().items()}
            patience_counter = 0
            print(f"  ✓ New best {args.early_stop_metric}: {best_val_metric:.4f}")
        else:
            patience_counter += 1
        
        if patience_counter >= args.patience_pretrain:
            print(f"Early stopping pretrain at epoch {epoch + 1}")
            break
    
    # PHASE 2: Fine-tuning
    print("\n" + "=" * 60)
    print("PHASE 2: Fine-tuning")
    print("=" * 60)
    
    if best_model_state:
        model.load_state_dict(best_model_state)
        print(f"Loaded best pretrained model ({args.early_stop_metric}={best_val_metric:.4f})")
    
    optimizer = AdamW(model.parameters(), lr=args.lr_finetune, weight_decay=args.weight_decay)
    scheduler_mode = "min" if _metric_lower_is_better(args.lr_scheduler_metric) else "max"
    scheduler = ReduceLROnPlateau(
        optimizer,
        mode=scheduler_mode,
        patience=args.lr_scheduler_patience,
        factor=args.lr_scheduler_factor,
        min_lr=args.lr_scheduler_min_lr,
    )
    
    best_val_metric = None
    best_model_state = None
    patience_counter = 0
    
    for epoch in range(args.epochs_finetune):
        print(f"\nFinetune Epoch {epoch + 1}/{args.epochs_finetune}")
        
        train_metrics = train_epoch_finetune(
            model, train_loader, optimizer, classification_loss_fn, device,
        )
        val_metrics = evaluate(model, val_loader, classification_loss_fn, device)
        scheduler_metric = _get_metric_value(val_metrics, args.lr_scheduler_metric)
        scheduler.step(scheduler_metric)
        
        print(f"  Train - Loss: {train_metrics['loss']:.4f}, "
              f"AUC: {train_metrics['auc']:.4f}, F1: {train_metrics['f1']:.4f}, "
              f"Brier: {train_metrics['brier']:.4f}")
        print(f"  Val   - Loss: {val_metrics['loss']:.4f}, "
              f"AUC: {val_metrics['auc']:.4f}, F1: {val_metrics['f1']:.4f}, "
              f"Brier: {val_metrics['brier']:.4f}")
        
        current_metric = _get_metric_value(val_metrics, args.early_stop_metric)
        if _is_improved(current_metric, best_val_metric, args.early_stop_metric, args.early_stop_min_delta):
            best_val_metric = current_metric
            best_model_state = {k: v.cpu().clone() for k, v in model.state_dict().items()}
            patience_counter = 0
            print(f"  ✓ New best {args.early_stop_metric}: {best_val_metric:.4f}")
        else:
            patience_counter += 1
        
        if patience_counter >= args.patience_finetune:
            print(f"Early stopping finetune at epoch {epoch + 1}")
            break
    
    # FINAL EVALUATION
    print("\n" + "=" * 60)
    print("FINAL EVALUATION")
    print("=" * 60)
    
    if best_model_state:
        model.load_state_dict(best_model_state)
    
    test_metrics = evaluate(model, test_loader, classification_loss_fn, device)
    
    print(f"\n{'='*60}")
    print("TEST RESULTS")
    print(f"{'='*60}")
    print(f"  AUC:       {test_metrics['auc']:.4f}")
    print(f"  F1:        {test_metrics['f1']:.4f}")
    print(f"  Precision: {test_metrics['precision']:.4f}")
    print(f"  Recall:    {test_metrics['recall']:.4f}")
    print(f"  Brier:     {test_metrics['brier']:.4f}")
    print(f"{'='*60}")
    
    return model, test_metrics


# ═══════════════════════════════════════════════════════════════════════════════
# CLI AND MAIN
# ═══════════════════════════════════════════════════════════════════════════════

def parse_args():
    parser = argparse.ArgumentParser(description="Train with contrastive learning")
    
    # Data - SAME AS train.py
    parser.add_argument("--cache-dir", type=str, required=True,
                       help="Path to cache directory")
    parser.add_argument("--dataset-name", type=str, required=True,
                       help="Dataset name (e.g., word2vec_200d_full)")
    parser.add_argument("--cache-signature", type=str, required=True,
                       help="Cache signature hash")
    parser.add_argument("--max-train", type=int, default=None,
                       help="Max training samples (for quick testing)")
    
    # Model
    parser.add_argument("--model-type", type=str, default="hagnn", choices=["hagnn"])
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-layers", type=int, default=4)
    parser.add_argument("--num-edge-types", type=int, default=18)
    parser.add_argument("--num-node-types", type=int, default=16)
    parser.add_argument("--call-node-idx", type=int, default=2)
    parser.add_argument("--heads", type=int, default=4)
    parser.add_argument("--dropout", type=float, default=0.2)
    
    # Contrastive learning
    parser.add_argument("--contrastive-weight", type=float, default=0.5,
                       help="Weight for contrastive loss (0-1)")
    parser.add_argument("--temperature", type=float, default=0.07,
                       help="Temperature for contrastive loss")

    # Classification loss (robust calibration)
    parser.add_argument(
        "--loss-type",
        type=str,
        default="combined",
        choices=["bce", "focal", "combined", "combined_v2", "label_smooth"],
        help="Classification loss type",
    )
    parser.add_argument("--label-smoothing", type=float, default=0.05,
                       help="Label smoothing factor for BCE-based losses")
    parser.add_argument("--focal-weight", type=float, default=0.3,
                       help="Focal loss weight for combined losses")
    parser.add_argument("--focal-gamma", type=float, default=2.0,
                       help="Focal gamma (for focal/combined_v2)")
    parser.add_argument("--f1-weight", type=float, default=0.0,
                       help="Soft-F1 weight for combined losses")
    parser.add_argument("--bce-weight", type=float, default=0.4,
                       help="BCE weight for combined_v2")
    
    # Training
    parser.add_argument("--epochs-pretrain", type=int, default=50)
    parser.add_argument("--epochs-finetune", type=int, default=100)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--lr-pretrain", type=float, default=0.001)
    parser.add_argument("--lr-finetune", type=float, default=0.0005)
    parser.add_argument("--weight-decay", type=float, default=1e-4)
    parser.add_argument("--patience-pretrain", type=int, default=15)
    parser.add_argument("--patience-finetune", type=int, default=20)
    parser.add_argument("--early-stop-metric", type=str, default="loss",
                       choices=["loss", "f1", "auc", "brier"],
                       help="Metric for early stopping")
    parser.add_argument("--early-stop-min-delta", type=float, default=0.0,
                       help="Minimum change to qualify as improvement")
    parser.add_argument("--lr-scheduler-metric", type=str, default="loss",
                       choices=["loss", "f1", "auc", "brier"],
                       help="Metric for ReduceLROnPlateau")
    parser.add_argument("--lr-scheduler-patience", type=int, default=10,
                       help="Scheduler patience before reducing LR")
    parser.add_argument("--lr-scheduler-factor", type=float, default=0.5,
                       help="LR reduction factor")
    parser.add_argument("--lr-scheduler-min-lr", type=float, default=1e-6,
                       help="Minimum LR for scheduler")
    
    # Other
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--device", type=str, default="auto")
    parser.add_argument("--save-dir", type=str, default=None)
    
    return parser.parse_args()


def main():
    args = parse_args()
    
    set_seed(args.seed)
    
    # Device - SAME AS train.py
    if args.device == "auto":
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    else:
        device = torch.device(args.device)
    
    print("=" * 70)
    print("VULNERABILITY DETECTION - CONTRASTIVE LEARNING + HAGNN")
    print("=" * 70)
    print(f"Device: {device}")
    print(f"Dataset: {args.dataset_name}")
    print(f"Signature: {args.cache_signature}")
    print("=" * 70)
    
    # Load data - USING EXISTING load_dataset FROM vuln_detection
    print("\n[1/4] Loading data...")
    train_data, val_data, test_data = load_dataset(
        cache_dir=args.cache_dir,
        dataset_name=args.dataset_name,
        cache_signature=args.cache_signature,
        max_train=args.max_train,
    )
    
    print_dataset_stats(train_data, val_data, test_data)
    
    # Fix edge_attr -> edge_type
    train_fixed = fix_edge_type_naming(train_data)
    val_fixed = fix_edge_type_naming(val_data)
    test_fixed = fix_edge_type_naming(test_data)
    
    if train_fixed > 0 or val_fixed > 0 or test_fixed > 0:
        print(f"\nFixed edge_attr → edge_type: train={train_fixed}, val={val_fixed}, test={test_fixed}")
    
    # Show edge type info
    sample_data = train_data[0]
    if hasattr(sample_data, 'edge_type') and sample_data.edge_type is not None:
        unique_types = sample_data.edge_type.unique()
        print(f"Edge Types: {len(unique_types)} unique values: {unique_types.tolist()[:10]}...")
    
    # Get input dimension
    input_dim = train_data[0].x.size(1)
    print(f"\nInput Feature Dimension: {input_dim}")
    
    # Create data loaders
    print("\n[2/4] Creating data loaders...")
    train_loader, val_loader, test_loader = create_data_loaders(
        train_data, val_data, test_data,
        batch_size=args.batch_size,
    )
    
    # Create model
    print("\n[3/4] Creating HAGNN model...")
    model = HAGNNVulnDetector(
        input_dim=input_dim,
        hidden_dim=args.hidden_dim,
        num_layers=args.num_layers,
        num_edge_types=args.num_edge_types,
        num_node_types=args.num_node_types,
        call_node_idx=args.call_node_idx,
        heads=args.heads,
        dropout=args.dropout,
    ).to(device)
    
    total, trainable = count_parameters(model)
    print(f"Model: {total:,} params ({trainable:,} trainable)")
    
    # Train
    print("\n[4/4] Training with contrastive learning...")
    model, test_metrics = train_with_contrastive_learning(
        model, train_loader, val_loader, test_loader, device, args
    )
    
    # Save
    if args.save_dir:
        save_dir = Path(args.save_dir)
        save_dir.mkdir(parents=True, exist_ok=True)
        
        torch.save(model.state_dict(), save_dir / "model.pt")
        
        results = {'args': vars(args), 'test_metrics': test_metrics, 
                   'timestamp': datetime.now().isoformat()}
        with open(save_dir / "results.json", 'w') as f:
            json.dump(results, f, indent=2)
        
        print(f"\nSaved to {save_dir}")


if __name__ == "__main__":
    main()


"""
#!/bin/bash
################################################################################
#                CONTRASTIVE LEARNING TRAINING COMMANDS                         #
#                HAGNN + Supervised Contrastive Loss                            #
#        Updated for cache_reveal_v2 + cache_devign_v2 + cache_draper_v2         #
################################################################################
# NOTE: Project-level multi-class classification is implemented in
# `train.py` and `train_advanced.py`. Contrastive training does not include
# the project head or project loss.
#
# AVAILABLE DATASETS (cache_reveal_v2):
# ------------------------------------
# | Dataset Name                 | Signature        | Edge Types |
# |-----------------------------|------------------|-----------|
# | unixcoder_768d_reveal_full  | da4ba2df98d97bc8 | 19        |
# | graphcodebert_768d_reveal_full | b5d56d026d3be520 | 19        |
# | codet5p_256d_reveal_full    | 924793d828204559 | 19        |
# | word2vec_200d_reveal_full   | 907c2c5a79ce186e | 19        |
# | word2vec_100d_reveal_full   | 7c1030041c027a9f | 19        |
#
# AVAILABLE DATASETS (cache_draper_v2):
# ------------------------------------
# | Dataset Name                  | Signature              | Edge Types |
# |------------------------------|------------------------|-----------|
# | unixcoder_768d_draper_full   | REPLACE_WITH_SIGNATURE | 19        |
# | graphcodebert_768d_draper_full | d487d6f448e3ad18     | 19        |
# | codet5p_256d_draper_full     | f66d810f8ba04b3b      | 19        |
# | word2vec_200d_draper_full    | 236655949834ff6d       | 19        |
# | word2vec_100d_draper_full    | 2c96399b8f4b91d4       | 19        |
#
# AVAILABLE DATASETS (cache_primevul_v2):
# ------------------------------------
# | Dataset Name                  | Signature        | Edge Types |
# |------------------------------|------------------|-----------|
# | word2vec_200d_primevul_full  | bdbf53801c586471 | 19        |
#
# AVAILABLE DATASETS (cache_devign_v2):
# ------------------------------------
# | Dataset Name                 | Signature        | Edge Types |
# |-----------------------------|------------------|-----------|
# | unixcoder_768d_full         | f6f464798e030305 | 18        |
# | graphcodebert_768d_full     | d253d91f25af3d71 | 18        |
# | graphcodebert_128d_full     | 1c3949dcf68534a6 | 18        |
# | codet5p_256d_full           | c60b3d632feea19c | 18        |
# | word2vec_200d_full          | 86c56b1755c532ee | 18        |
# | word2vec_100d_full          | 0b2074fbdf9296d6 | 18        |
#
################################################################################

export SCRIPTS_DIR="./workspace/Scripts_and_saved_Models/Scripts"
export REVEAL_CACHE_DIR="./Clean_exports/cache_reveal_v2"
export DEVIGN_CACHE_DIR="./Clean_exports/cache_devign_v2"
export DRAPER_CACHE_DIR="./Clean_exports/cache_draper_v2"
export PRIMEVUL_CACHE_DIR="./Clean_exports/cache_primevul_v2"
export RESULTS_DIR="./results"

cd "$SCRIPTS_DIR"
mkdir -p "$RESULTS_DIR"

export LOSS_ARGS="--loss-type combined --label-smoothing 0.05 --focal-weight 0.3 --f1-weight 0.0 --early-stop-metric loss --lr-scheduler-metric loss"

################################################################################
# QUICK TESTS
################################################################################
export CACHE_DIR="$REVEAL_CACHE_DIR"
# REVEAL quick check (2+3 epochs)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --hidden-dim 256 \
    --num-layers 3 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 2 \
    --epochs-finetune 3 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    $LOSS_ARGS

export CACHE_DIR="$DEVIGN_CACHE_DIR"
# DEVIGN quick check (2+3 epochs)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "86c56b1755c532ee" \
    --hidden-dim 256 \
    --num-layers 3 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 2 \
    --epochs-finetune 3 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    $LOSS_ARGS

export CACHE_DIR="$DRAPER_CACHE_DIR"
# DRAPER quick check (2+3 epochs)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --hidden-dim 256 \
    --num-layers 3 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 2 \
    --epochs-finetune 3 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    $LOSS_ARGS

export CACHE_DIR="$PRIMEVUL_CACHE_DIR"
# PRIMEVUL quick check (2+3 epochs)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --hidden-dim 256 \
    --num-layers 3 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 2 \
    --epochs-finetune 3 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    $LOSS_ARGS

################################################################################
# PRIMEVUL DATASETS
################################################################################

export CACHE_DIR="$PRIMEVUL_CACHE_DIR"
################################################################################
# PRIMEVUL - word2vec_200d_primevul_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.001 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/primevul_word2vec_200d_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/primevul_word2vec_200d_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/primevul_word2vec_200d_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DRAPER DATASETS
################################################################################

export CACHE_DIR="$DRAPER_CACHE_DIR"
################################################################################
# DRAPER - unixcoder_768d_draper_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_unixcoder_768d_draper_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_unixcoder_768d_draper_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_unixcoder_768d_draper_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DRAPER - graphcodebert_768d_draper_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_graphcodebert_768d_draper_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_graphcodebert_768d_draper_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_graphcodebert_768d_draper_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DRAPER - codet5p_256d_draper_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_codet5p_256d_draper_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_codet5p_256d_draper_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_codet5p_256d_draper_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DRAPER - word2vec_200d_draper_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_word2vec_200d_draper_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_word2vec_200d_draper_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_word2vec_200d_draper_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DRAPER - word2vec_100d_draper_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_word2vec_100d_draper_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_word2vec_100d_draper_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/draper_word2vec_100d_draper_full_hagnn_large" \
    $LOSS_ARGS
################################################################################
# REVEAL DATASETS
################################################################################
export CACHE_DIR="$REVEAL_CACHE_DIR"
################################################################################
# REVEAL - unixcoder_768d_reveal_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_unixcoder_768d_reveal_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_unixcoder_768d_reveal_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_unixcoder_768d_reveal_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# REVEAL - graphcodebert_768d_reveal_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_graphcodebert_768d_reveal_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_graphcodebert_768d_reveal_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_graphcodebert_768d_reveal_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# REVEAL - codet5p_256d_reveal_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_codet5p_256d_reveal_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_codet5p_256d_reveal_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_codet5p_256d_reveal_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# REVEAL - word2vec_200d_reveal_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_word2vec_200d_reveal_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_word2vec_200d_reveal_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_word2vec_200d_reveal_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# REVEAL - word2vec_100d_reveal_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_word2vec_100d_reveal_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_word2vec_100d_reveal_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/reveal_word2vec_100d_reveal_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DEVIGN DATASETS
################################################################################
export CACHE_DIR="$DEVIGN_CACHE_DIR"
################################################################################
# DEVIGN - unixcoder_768d_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "f6f464798e030305" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_unixcoder_768d_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "f6f464798e030305" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_unixcoder_768d_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "f6f464798e030305" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_unixcoder_768d_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DEVIGN - graphcodebert_768d_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "d253d91f25af3d71" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_graphcodebert_768d_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "d253d91f25af3d71" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_graphcodebert_768d_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "d253d91f25af3d71" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_graphcodebert_768d_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DEVIGN - graphcodebert_128d_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "1c3949dcf68534a6" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_graphcodebert_128d_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "1c3949dcf68534a6" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_graphcodebert_128d_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "1c3949dcf68534a6" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_graphcodebert_128d_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DEVIGN - codet5p_256d_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "c60b3d632feea19c" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_codet5p_256d_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "c60b3d632feea19c" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_codet5p_256d_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "c60b3d632feea19c" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_codet5p_256d_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DEVIGN - word2vec_200d_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "86c56b1755c532ee" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_word2vec_200d_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "86c56b1755c532ee" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_word2vec_200d_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "86c56b1755c532ee" \
    --hidden-dim 384 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_word2vec_200d_full_hagnn_large" \
    $LOSS_ARGS

################################################################################
# DEVIGN - word2vec_100d_full
################################################################################

# Recommended
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "0b2074fbdf9296d6" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.001 \
    --lr-finetune 0.0005 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_word2vec_100d_full_hagnn_v1" \
    $LOSS_ARGS

# Deeper (6 layers)
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "0b2074fbdf9296d6" \
    --hidden-dim 256 \
    --num-layers 6 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.25 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_word2vec_100d_full_hagnn_deep" \
    $LOSS_ARGS

# Larger hidden
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir "$CACHE_DIR" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "0b2074fbdf9296d6" \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --heads 4 \
    --dropout 0.2 \
    --contrastive-weight 0.5 \
    --temperature 0.07 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 24 \
    --lr-pretrain 0.0008 \
    --lr-finetune 0.0003 \
    --patience-pretrain 15 \
    --patience-finetune 20 \
    --save-dir "./results/devign_word2vec_100d_full_hagnn_large" \
    $LOSS_ARGS

"""
