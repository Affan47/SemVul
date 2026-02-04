#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_gnn_vs_mlp.py - Compare GNN message passing vs MLP baseline

Key question: Does GCN message passing destroy information?

Tests:
1. MLP baseline (no message passing) - should learn
2. 1-layer GCN - might learn
3. 3-layer GCN - might collapse due to over-smoothing
4. GCN without LayerNorm - test if LayerNorm causes collapse
"""

import argparse
import sys
import random
import io
import zipfile
from pathlib import Path

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, global_mean_pool

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_samples(cache_dir, dataset_name, cache_sig, split="train", num_samples=500):
    """Load sample data."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            random.shuffle(pt_files)
            
            for pt_name in pt_files[:num_samples * 2]:
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                        if len(samples) >= num_samples:
                            break
                except:
                    continue
    
    return samples


class MLPBaseline(nn.Module):
    """MLP that just pools node features - NO message passing."""
    
    def __init__(self, input_dim, hidden_dim=256):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        self.fc1 = nn.Linear(hidden_dim, hidden_dim)
        self.fc2 = nn.Linear(hidden_dim, hidden_dim)
        self.classifier = nn.Linear(hidden_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Project
        h = F.relu(self.proj(x))
        h = F.relu(self.fc1(h))
        h = F.relu(self.fc2(h))
        
        # Pool (no message passing!)
        graph_emb = global_mean_pool(h, batch)
        
        # Classify
        return self.classifier(graph_emb)


class SimpleGCN_NoNorm(nn.Module):
    """GCN without LayerNorm - test if normalization causes collapse."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        self.convs = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
        
        self.classifier = nn.Linear(hidden_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        
        for conv in self.convs:
            h = conv(h, edge_index)
            h = F.relu(h)
        
        graph_emb = global_mean_pool(h, batch)
        return self.classifier(graph_emb)


class SimpleGCN_WithNorm(nn.Module):
    """GCN with LayerNorm - test if normalization causes collapse."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        self.convs = nn.ModuleList()
        self.norms = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
            self.norms.append(nn.LayerNorm(hidden_dim))
        
        self.classifier = nn.Linear(hidden_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        
        for conv, norm in zip(self.convs, self.norms):
            h_in = h
            h = conv(h, edge_index)
            h = norm(h)
            h = F.relu(h)
            h = h + h_in  # Residual
        
        graph_emb = global_mean_pool(h, batch)
        return self.classifier(graph_emb)


class SimpleGCN_1Layer(nn.Module):
    """Single layer GCN - test for over-smoothing."""
    
    def __init__(self, input_dim, hidden_dim=256):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        self.conv = GCNConv(hidden_dim, hidden_dim)
        self.classifier = nn.Linear(hidden_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        h = F.relu(self.conv(h, edge_index))
        
        graph_emb = global_mean_pool(h, batch)
        return self.classifier(graph_emb)


class JumpingKnowledge(nn.Module):
    """GCN with Jumping Knowledge - concatenate representations from all layers."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        self.convs = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
        
        # Jumping knowledge: concat all layer outputs
        self.jk_proj = nn.Linear(hidden_dim * (num_layers + 1), hidden_dim)
        self.classifier = nn.Linear(hidden_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        layer_outputs = [h]
        
        for conv in self.convs:
            h = F.relu(conv(h, edge_index))
            layer_outputs.append(h)
        
        # Concatenate all layer outputs
        h_jk = torch.cat(layer_outputs, dim=-1)
        h_jk = self.jk_proj(h_jk)
        
        graph_emb = global_mean_pool(h_jk, batch)
        return self.classifier(graph_emb)


def train_and_evaluate(model, train_loader, val_loader, device, epochs=30, lr=0.01, name="Model"):
    """Train and evaluate a model."""
    model = model.to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    
    best_auc = 0.5
    
    for epoch in range(1, epochs + 1):
        # Train
        model.train()
        total_loss = 0
        for batch in train_loader:
            batch = batch.to(device)
            optimizer.zero_grad()
            
            logits = model(batch).view(-1)
            labels = batch.y.float().view(-1)
            
            loss = F.binary_cross_entropy_with_logits(logits, labels)
            loss.backward()
            
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()
            
            total_loss += loss.item()
        
        avg_loss = total_loss / len(train_loader)
        
        # Evaluate
        model.eval()
        all_probs = []
        all_labels = []
        
        with torch.no_grad():
            for batch in val_loader:
                batch = batch.to(device)
                logits = model(batch).view(-1)
                probs = torch.sigmoid(logits)
                all_probs.append(probs.cpu())
                all_labels.append(batch.y.cpu().view(-1))
        
        probs = torch.cat(all_probs)
        labels = torch.cat(all_labels)
        
        from sklearn.metrics import roc_auc_score
        try:
            auc = roc_auc_score(labels.numpy(), probs.numpy())
        except:
            auc = 0.5
        
        prob_std = probs.std().item()
        
        if auc > best_auc:
            best_auc = auc
        
        if epoch % 5 == 0 or epoch == 1:
            print(f"  Epoch {epoch:2d}: loss={avg_loss:.4f}, AUC={auc:.4f}, prob_std={prob_std:.4f}")
    
    return best_auc


def analyze_message_passing(model, batch, device):
    """Analyze what happens during message passing."""
    model.eval()
    model.to(device)
    batch = batch.to(device)
    
    x = batch.x.float()
    edge_index = batch.edge_index
    
    print(f"\n  Input features: mean={x.mean():.4f}, std={x.std():.4f}")
    
    # Get intermediate representations
    if hasattr(model, 'proj'):
        h = F.relu(model.proj(x))
        print(f"  After projection: mean={h.mean():.4f}, std={h.std():.4f}")
        
        if hasattr(model, 'convs'):
            for i, conv in enumerate(model.convs):
                h_before = h.clone()
                h = conv(h, edge_index)
                
                # Check similarity before/after
                cos_sim = F.cosine_similarity(
                    h.view(1, -1), h_before.view(1, -1)
                ).item()
                
                h = F.relu(h)
                print(f"  After GCN layer {i}: mean={h.mean():.4f}, std={h.std():.4f}, cos_sim={cos_sim:.4f}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-samples", type=int, default=1000)
    parser.add_argument("--epochs", type=int, default=30)
    parser.add_argument("--lr", type=float, default=0.01)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 70)
    print("GNN vs MLP DIAGNOSTIC")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load data
    print("\nLoading data...")
    train_data = load_samples(args.cache_dir, args.dataset_name, args.cache_signature, "train", args.num_samples)
    val_data = load_samples(args.cache_dir, args.dataset_name, args.cache_signature, "valid", args.num_samples // 4)
    
    print(f"Train: {len(train_data)} samples")
    print(f"Val: {len(val_data)} samples")
    
    if not train_data:
        print("[ERROR] No data loaded!")
        sys.exit(1)
    
    input_dim = train_data[0].x.size(1)
    print(f"Input dim: {input_dim}")
    
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    
    # Test different models
    models = [
        ("MLP (no message passing)", MLPBaseline(input_dim, args.hidden_dim)),
        ("GCN 1-layer (no norm)", SimpleGCN_1Layer(input_dim, args.hidden_dim)),
        ("GCN 3-layer (no norm)", SimpleGCN_NoNorm(input_dim, args.hidden_dim, num_layers=3)),
        ("GCN 3-layer (with norm + residual)", SimpleGCN_WithNorm(input_dim, args.hidden_dim, num_layers=3)),
        ("GCN 3-layer (Jumping Knowledge)", JumpingKnowledge(input_dim, args.hidden_dim, num_layers=3)),
    ]
    
    results = {}
    
    for name, model in models:
        print(f"\n{'=' * 70}")
        print(f"Testing: {name}")
        print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
        print("=" * 70)
        
        # Analyze message passing
        sample_batch = Batch.from_data_list(train_data[:10]).to(device)
        analyze_message_passing(model, sample_batch, device)
        
        # Train and evaluate
        print("\nTraining...")
        best_auc = train_and_evaluate(
            model, train_loader, val_loader, device,
            epochs=args.epochs, lr=args.lr, name=name
        )
        
        results[name] = best_auc
        print(f"\n→ Best AUC: {best_auc:.4f}")
    
    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY")
    print("=" * 70)
    
    for name, auc in sorted(results.items(), key=lambda x: -x[1]):
        status = "✅" if auc > 0.55 else "⚠️" if auc > 0.52 else "❌"
        print(f"{status} {name}: AUC={auc:.4f}")
    
    print("\n" + "=" * 70)
    print("DIAGNOSIS")
    print("=" * 70)
    
    mlp_auc = results.get("MLP (no message passing)", 0.5)
    gcn1_auc = results.get("GCN 1-layer (no norm)", 0.5)
    gcn3_auc = results.get("GCN 3-layer (no norm)", 0.5)
    gcn3_norm_auc = results.get("GCN 3-layer (with norm + residual)", 0.5)
    
    if mlp_auc > 0.55:
        print("✅ MLP baseline works - features are learnable")
    else:
        print("❌ MLP baseline fails - task may be very hard or labels wrong")
    
    if gcn1_auc > 0.55:
        print("✅ 1-layer GCN works - message passing adds value")
    elif mlp_auc > gcn1_auc + 0.02:
        print("⚠️ 1-layer GCN worse than MLP - message passing may hurt")
    
    if gcn1_auc > gcn3_auc + 0.02:
        print("🚨 OVER-SMOOTHING detected: More layers = worse performance")
    
    if gcn3_norm_auc < gcn3_auc - 0.02:
        print("🚨 LayerNorm + residual hurts performance")


if __name__ == "__main__":
    main()
