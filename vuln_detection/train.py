#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
train.py - Main training script for vulnerability detection (FIXED V3)

FIXES V3:
  - Added graph truncation support (--max-nodes, --truncation-strategy)
  - Semantic-priority BFS truncation for large graphs
  - Preserves vulnerability-relevant nodes (CALL, CONTROL_STRUCTURE, etc.)

FIXES V2:
  - ALL command line arguments now passed to create_model() for preset models
  - --gnn-layers, --embedder-type, --pooling-type work with improved_devign
  - Better dimension inference

Usage:
    # With graph truncation (RECOMMENDED for faster training):
    python train.py \\
        --cache-dir /path/to/cache \\
        --dataset-name word2vec_200d_full \\
        --cache-signature 86c56b1755c532ee \\
        --model-type improved_devign \\
        --gnn-layers 4 \\
        --max-nodes 600 \\
        --truncation-strategy semantic_bfs \\
        --epochs 100
"""

import argparse
import csv
import os
import random
import sys
import json
from pathlib import Path
from datetime import datetime

import numpy as np
import torch
import torch.nn as nn
from torch_geometric.loader import DataLoader
from sklearn.metrics import accuracy_score, f1_score
from sklearn.metrics import precision_recall_fscore_support

# Add parent to path for imports
sys.path.insert(0, str(Path(__file__).parent.parent))

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x

# Import from our package
from vuln_detection import (
    create_model,
    VulnDetector,
    load_dataset,
    create_data_loaders,
    get_class_weights,
    compute_full_evaluation,
    print_metrics,
    compare_with_baselines,
    create_loss,
)
from vuln_detection.utils import print_dataset_stats

# Import graph truncation (NEW!)
try:
    from vuln_detection.utils.graph_truncation import GraphTruncator
    HAS_TRUNCATION = True
except ImportError:
    HAS_TRUNCATION = False
    GraphTruncator = None


def set_seed(seed: int):
    """Set random seed for reproducibility."""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


def _load_project_map(manifest_path: str) -> tuple[dict, set]:
    """Load function_id -> project mapping and project set from a manifest CSV."""
    func_to_project = {}
    projects = set()
    if not manifest_path:
        return func_to_project, projects
    with open(manifest_path, "r", encoding="utf-8", errors="ignore") as f:
        reader = csv.DictReader(f)
        for row in reader:
            func_id = row.get("function_id")
            project = row.get("project")
            if not func_id or not project:
                continue
            func_to_project[str(func_id).strip()] = str(project).strip()
            projects.add(project)
    return func_to_project, projects


def attach_project_labels(
    data_list,
    func_to_project: dict,
    project_to_idx: dict,
    unk_idx: int,
):
    """Attach project labels to Data objects using func_id."""
    for data in data_list:
        func_id = getattr(data, "func_id", None)
        if func_id is None:
            func_id = getattr(data, "function_id", None)
        if func_id is None:
            func_id = getattr(data, "fid", None)
        if func_id is None:
            continue
        if isinstance(func_id, torch.Tensor):
            try:
                func_id = func_id.item()
            except Exception:
                pass
        func_id = str(func_id).strip()
        project = func_to_project.get(func_id, None)
        proj_idx = project_to_idx.get(project, unk_idx)
        data.project_y = torch.tensor([proj_idx], dtype=torch.long)


def _unpack_model_output(output):
    """Return (logits, graph_emb) from model output."""
    if isinstance(output, dict):
        logits = output.get("logits", output.get("out", output.get("pred", None)))
        graph_emb = output.get("graph_emb", None)
        return logits, graph_emb
    if isinstance(output, tuple) and len(output) == 2:
        return output[0], output[1]
    return output, None


def train_epoch(
    model: nn.Module,
    loader: DataLoader,
    optimizer: torch.optim.Optimizer,
    criterion: nn.Module,
    device: torch.device,
    max_grad_norm: float = 1.0,
    project_head: nn.Module | None = None,
    project_criterion: nn.Module | None = None,
    project_loss_weight: float = 1.0,
) -> float:
    """Train for one epoch."""
    model.train()
    if project_head is not None:
        project_head.train()
    total_loss = 0
    num_batches = 0
    
    for batch in tqdm(loader, desc="Training", leave=False):
        batch = batch.to(device)
        optimizer.zero_grad()

        if project_head is not None and project_criterion is not None and hasattr(batch, "project_y"):
            output = model(batch, return_embeddings=True)
            logits, graph_emb = _unpack_model_output(output)
            logits = logits.view(-1)
            labels = batch.y.float().view(-1)
            loss = criterion(logits, labels)
            if graph_emb is not None:
                project_logits = project_head(graph_emb)
                project_labels = batch.project_y.view(-1)
                project_loss = project_criterion(project_logits, project_labels)
                loss = loss + project_loss_weight * project_loss
        else:
            logits = model(batch).view(-1)
            labels = batch.y.float().view(-1)
            loss = criterion(logits, labels)
        loss.backward()
        
        torch.nn.utils.clip_grad_norm_(model.parameters(), max_grad_norm)
        optimizer.step()
        
        total_loss += loss.item()
        num_batches += 1
    
    return total_loss / max(num_batches, 1)


@torch.no_grad()
def evaluate(
    model: nn.Module,
    loader: DataLoader,
    device: torch.device,
    project_head: nn.Module | None = None,
    return_outputs: bool = False,
) -> dict:
    """Evaluate model."""
    model.eval()
    if project_head is not None:
        project_head.eval()
    all_probs = []
    all_labels = []
    all_ids = []
    all_project_preds = []
    all_project_labels = []
    
    for batch in loader:
        batch = batch.to(device)
        if project_head is not None and hasattr(batch, "project_y"):
            output = model(batch, return_embeddings=True)
            logits, graph_emb = _unpack_model_output(output)
            logits = logits.view(-1)
            if graph_emb is not None:
                project_logits = project_head(graph_emb)
                project_preds = project_logits.argmax(dim=-1)
                all_project_preds.append(project_preds.cpu())
                all_project_labels.append(batch.project_y.cpu().view(-1))
        else:
            logits = model(batch).view(-1)
        probs = torch.sigmoid(logits)

        func_ids = None
        for attr in ("func_id", "function_id", "fid"):
            if hasattr(batch, attr):
                func_ids = getattr(batch, attr)
                break
        if func_ids is not None:
            if isinstance(func_ids, torch.Tensor):
                func_ids = func_ids.view(-1).cpu().tolist()
            elif isinstance(func_ids, (list, tuple)):
                func_ids = list(func_ids)
            else:
                func_ids = [str(func_ids)] * probs.view(-1).size(0)
            all_ids.extend([str(x) for x in func_ids])
        
        all_probs.append(probs.cpu())
        all_labels.append(batch.y.cpu().view(-1))
    
    probs = torch.cat(all_probs).numpy()
    labels = torch.cat(all_labels).numpy()

    metrics = compute_full_evaluation(probs, labels)
    if all_project_labels:
        proj_preds = torch.cat(all_project_preds).numpy()
        proj_labels = torch.cat(all_project_labels).numpy()
        metrics["project_accuracy"] = accuracy_score(proj_labels, proj_preds)
        metrics["project_f1_macro"] = f1_score(proj_labels, proj_preds, average="macro")
    if return_outputs:
        return metrics, {
            "probs": probs,
            "labels": labels,
            "ids": all_ids,
        }
    return metrics


def _save_predictions_csv(save_dir: Path, split: str, probs, labels, ids, threshold: float):
    out_path = save_dir / f"predictions_{split}.csv"
    with open(out_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["idx", "label", "prob", "pred", "func_id"])
        for i, (p, y) in enumerate(zip(probs, labels)):
            pred = 1 if p >= threshold else 0
            fid = ids[i] if i < len(ids) else ""
            writer.writerow([i, int(y), float(p), pred, fid])
    print(f"[Saved] Predictions: {out_path}")


def _save_project_metrics(save_dir: Path, split: str, probs, labels, ids, manifest_path: str, threshold: float):
    if not manifest_path:
        return
    func_to_project = {}
    with open(manifest_path, "r", encoding="utf-8", errors="ignore") as f:
        reader = csv.DictReader(f)
        for row in reader:
            func_id = row.get("function_id")
            project = row.get("project")
            if not func_id or not project:
                continue
            func_to_project[str(func_id).strip()] = str(project).strip()

    if not ids:
        print("[Warning] No func_id found in batches; skipping per-project metrics.")
        return

    project_report = {}
    for i, fid in enumerate(ids):
        proj = func_to_project.get(str(fid), None)
        if proj is None:
            continue
        project_report.setdefault(proj, []).append(i)

    if not project_report:
        print("[Warning] No project matches found; skipping per-project metrics.")
        return

    out = {}
    for proj, idxs in project_report.items():
        p_true = labels[idxs]
        p_pred = (probs[idxs] >= threshold).astype(int)
        prec, rec, f1, _ = precision_recall_fscore_support(
            p_true, p_pred, average="binary", zero_division=0
        )
        out[proj] = {
            "n": int(len(idxs)),
            "precision": float(prec),
            "recall": float(rec),
            "f1": float(f1),
        }

    out_path = save_dir / f"project_metrics_{split}.json"
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=2, sort_keys=True)
    print(f"[Saved] Per-project metrics: {out_path}")


def _save_cwe_metrics(save_dir: Path, split: str, probs, labels, ids, manifest_path: str, threshold: float):
    if not manifest_path:
        return
    if not ids:
        print("[Warning] No func_id found in batches; skipping per-CWE metrics.")
        return

    with open(manifest_path, "r", encoding="utf-8", errors="ignore") as f:
        reader = csv.DictReader(f)
        fieldnames = reader.fieldnames or []
        cwe_fields = [c for c in fieldnames if c.startswith("CWE-")]
        if not cwe_fields:
            print("[Warning] No CWE columns found in manifest; skipping per-CWE metrics.")
            return

        func_to_cwe = {}
        for row in reader:
            func_id = row.get("function_id")
            if not func_id:
                continue
            func_to_cwe[str(func_id).strip()] = {
                c: str(row.get(c, "")).strip().lower() in ("true", "1", "yes")
                for c in cwe_fields
            }

    cwe_report = {c: [] for c in cwe_fields}
    for i, fid in enumerate(ids):
        cwe_map = func_to_cwe.get(str(fid), None)
        if not cwe_map:
            continue
        for c in cwe_fields:
            if cwe_map.get(c, False):
                cwe_report[c].append(i)

    out = {}
    for cwe, idxs in cwe_report.items():
        if not idxs:
            continue
        p_true = labels[idxs]
        p_pred = (probs[idxs] >= threshold).astype(int)
        prec, rec, f1, _ = precision_recall_fscore_support(
            p_true, p_pred, average="binary", zero_division=0
        )
        out[cwe] = {
            "n": int(len(idxs)),
            "precision": float(prec),
            "recall": float(rec),
            "f1": float(f1),
        }

    if not out:
        print("[Warning] No CWE matches found; skipping per-CWE metrics.")
        return

    out_path = save_dir / f"cwe_metrics_{split}.json"
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=2, sort_keys=True)
    print(f"[Saved] Per-CWE metrics: {out_path}")

    # Brief summary to help spot strongest/weakest CWE groups quickly.
    by_f1 = sorted(out.items(), key=lambda kv: kv[1]["f1"], reverse=True)
    top_k = by_f1[:5]
    if top_k:
        summary = ", ".join([f"{k}: f1={v['f1']:.3f} (n={v['n']})" for k, v in top_k])
        print(f"[CWE Summary] Top {len(top_k)} by F1: {summary}")


def find_optimal_threshold(probs: np.ndarray, labels: np.ndarray) -> tuple:
    """Find threshold that maximizes F1 score."""
    from sklearn.metrics import f1_score
    best_f1 = 0
    best_thresh = 0.5
    
    for thresh in np.arange(0.1, 0.9, 0.02):
        preds = (probs > thresh).astype(int)
        f1 = f1_score(labels, preds)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = thresh
    
    return best_thresh, best_f1


def apply_graph_truncation(data_list, max_nodes: int, strategy: str = 'semantic_bfs'):
    """
    Apply graph truncation to a list of Data objects.
    
    Args:
        data_list: List of PyG Data objects
        max_nodes: Maximum nodes per graph
        strategy: Truncation strategy ('semantic_bfs', 'bfs', 'random', 'degree')
    
    Returns:
        Truncated data list and statistics dict
    """
    if not HAS_TRUNCATION:
        print("Warning: graph_truncation module not found. Skipping truncation.")
        return data_list, {'truncated': 0, 'total': len(data_list)}
    
    truncator = GraphTruncator(max_nodes=max_nodes, strategy=strategy, verbose=False)
    
    truncated_data = []
    for data in tqdm(data_list, desc=f"Truncating (max={max_nodes})", leave=False):
        truncated_data.append(truncator.truncate(data))
    
    stats = truncator.get_stats()
    return truncated_data, stats


def main():
    parser = argparse.ArgumentParser(description="Train vulnerability detection model")
    
    # Data arguments
    parser.add_argument("--cache-dir", type=str, required=True,
                       help="Path to cache directory")
    parser.add_argument("--dataset-name", type=str, required=True,
                       help="Dataset name (e.g., devign_normfunc_v2)")
    parser.add_argument("--cache-signature", type=str, required=True,
                       help="Cache signature hash")
    parser.add_argument("--max-train", type=int, default=None,
                       help="Max training samples (for quick testing)")
    # Optional: project-level multi-class classification
    parser.add_argument("--project-manifest-train", type=str, default=None,
                       help="Train manifest CSV with project column")
    parser.add_argument("--project-manifest-val", type=str, default=None,
                       help="Validation manifest CSV with project column")
    parser.add_argument("--project-manifest-test", type=str, default=None,
                       help="Test manifest CSV with project column")
    parser.add_argument("--project-loss-weight", type=float, default=1.0,
                       help="Weight for project classification loss (if enabled)")
    
    # =========================================================================
    # NEW: Graph truncation arguments
    # =========================================================================
    parser.add_argument("--max-nodes", type=int, default=None,
                       help="Max nodes per graph (None=no limit, 500-1000 recommended)")
    parser.add_argument("--truncation-strategy", type=str, default="semantic_bfs",
                       choices=["semantic_bfs", "bfs", "random", "degree"],
                       help="Graph truncation strategy (default: semantic_bfs)")
    # =========================================================================
    
    # Model arguments
    parser.add_argument("--model-type", type=str, default="graph_level_mlp",
                       choices=["devign", "improved_devign", "call_aware", "graph_level_mlp", "attention", "custom"],
                       help="Model type (call_aware = CALL-node focused, recommended based on diagnostics)")
    
    # Model configuration arguments (NOW APPLY TO ALL MODEL TYPES!)
    parser.add_argument("--embedder-type", type=str, default=None,
                       help="Embedder type (overrides preset default)")
    parser.add_argument("--embedding-dim", type=int, default=768,
                       help="Dimension of input code embeddings (default 768 for BERT, 128 for W2V)")
    parser.add_argument("--gnn-type", type=str, default=None,
                       choices=["none", "ggnn", "edge_type", "edge_type_text", "gcn", "gat", "call_aware"],
                       help="GNN type (call_aware = CALL-node focused GNN)")
    parser.add_argument("--gnn-layers", type=int, default=None,
                       help="Number of GNN layers (overrides preset default)")
    parser.add_argument("--num-edge-types", type=int, default=20,
                       help="Number of edge types in the graph")
    parser.add_argument("--pooling-type", type=str, default=None,
                       choices=["mean", "max", "mean_max", "multi_stat", "attention", "combined", "devign"],
                       help="Pooling type (overrides preset default)")
    parser.add_argument("--use-structural-features", action="store_true",
                       help="Augment node features with degree statistics (In/Out/Leaf/Root)")
    parser.add_argument("--hidden-dim", type=int, default=128,
                       help="Hidden dimension")
    parser.add_argument("--edge-text-dim", type=int, default=None,
                       help="Edge text embedding dim (required for edge_type_text if not inferable)")
    
    # =========================================================================
    # NEW: CALL-aware specific arguments
    # =========================================================================
    parser.add_argument("--num-node-types", type=int, default=16,
                       help="Number of node types in one-hot encoding (default: 16)")
    parser.add_argument("--call-node-idx", type=int, default=2,
                       help="Index of CALL node type in one-hot encoding (default: 2)")
    parser.add_argument("--reaching-def-edge-type", type=int, default=9,
                       help="Edge type index for REACHING_DEF edges (default: 9)")
    # =========================================================================
    
    # Training arguments
    parser.add_argument("--epochs", type=int, default=100,
                       help="Number of epochs")
    parser.add_argument("--batch-size", type=int, default=32,
                       help="Batch size")
    parser.add_argument("--lr", type=float, default=0.001,
                       help="Learning rate")
    parser.add_argument("--weight-decay", type=float, default=1e-4,
                       help="Weight decay")
    parser.add_argument("--dropout", type=float, default=0.2,
                       help="Dropout rate")
    parser.add_argument("--patience", type=int, default=20,
                       help="Early stopping patience")
    
    # Loss arguments
    parser.add_argument("--loss-type", type=str, default="combined",
                       choices=["bce", "focal", "combined"],
                       help="Loss type")
    parser.add_argument("--focal-weight", type=float, default=0.3,
                       help="Focal loss weight in combined loss")
    parser.add_argument("--optimize-for", type=str, default="auc",
                       choices=["auc", "f1", "f1_best"],
                       help="Metric to optimize during training (auc=AUC-ROC, f1=F1@0.5, f1_best=best F1 at optimal threshold)")
    
    # Other arguments
    parser.add_argument("--device", type=str, default="auto",
                       help="Device (auto, cpu, cuda)")
    parser.add_argument("--seed", type=int, default=42,
                       help="Random seed")
    parser.add_argument("--save-dir", type=str, default="./checkpoints",
                       help="Directory to save checkpoints")
    parser.add_argument("--experiment-name", type=str, default=None,
                       help="Experiment name for saving")
    
    args = parser.parse_args()
    
    # Set seed
    set_seed(args.seed)
    
    # Device
    if args.device == "auto":
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    else:
        device = torch.device(args.device)
    
    # Experiment name
    if args.experiment_name is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        args.experiment_name = f"{args.model_type}_{timestamp}"
    
    print("=" * 70)
    print("VULNERABILITY DETECTION TRAINING (FIXED V3 - WITH TRUNCATION)")
    print("=" * 70)
    print(f"Model type: {args.model_type}")
    print(f"Device: {device}")
    print(f"Experiment: {args.experiment_name}")
    if args.max_nodes:
        print(f"Graph Truncation: max_nodes={args.max_nodes}, strategy={args.truncation_strategy}")
    else:
        print(f"Graph Truncation: DISABLED")
    print("=" * 70)
    
    # Load data
    print("\n[1/5] Loading data...")
    train_data, val_data, test_data = load_dataset(
        cache_dir=args.cache_dir,
        dataset_name=args.dataset_name,
        cache_signature=args.cache_signature,
        max_train=args.max_train,
    )

    # Optional: attach project labels for multi-class classification
    project_enabled = all([
        args.project_manifest_train,
        args.project_manifest_val,
        args.project_manifest_test,
    ])
    project_to_idx = None
    unk_project_idx = None
    if project_enabled:
        train_map, train_projects = _load_project_map(args.project_manifest_train)
        val_map, _ = _load_project_map(args.project_manifest_val)
        test_map, _ = _load_project_map(args.project_manifest_test)

        project_list = sorted(train_projects)
        project_to_idx = {p: i for i, p in enumerate(project_list)}
        unk_project_idx = len(project_to_idx)
        project_to_idx["__UNK__"] = unk_project_idx

        attach_project_labels(train_data, train_map, project_to_idx, unk_project_idx)
        attach_project_labels(val_data, val_map, project_to_idx, unk_project_idx)
        attach_project_labels(test_data, test_map, project_to_idx, unk_project_idx)

        unk_train = sum(1 for d in train_data if int(d.project_y.item()) == unk_project_idx)
        print(f"[Info] Project classification enabled: {len(project_to_idx)} classes (including UNK)")
        print(f"[Info] Project UNK in train: {unk_train}/{len(train_data)}")
    
    print_dataset_stats(train_data, val_data, test_data)
    
    # =========================================================================
    # NEW: Apply graph truncation if enabled
    # =========================================================================
    if args.max_nodes is not None and args.max_nodes > 0:
        print(f"\n[1a/5] Applying graph truncation (max_nodes={args.max_nodes}, strategy={args.truncation_strategy})...")
        
        # Check how many graphs exceed the limit
        train_over = sum(1 for d in train_data if d.num_nodes > args.max_nodes)
        val_over = sum(1 for d in val_data if d.num_nodes > args.max_nodes)
        test_over = sum(1 for d in test_data if d.num_nodes > args.max_nodes)
        
        print(f"   Graphs exceeding {args.max_nodes} nodes:")
        print(f"     Train: {train_over}/{len(train_data)} ({100*train_over/len(train_data):.1f}%)")
        print(f"     Valid: {val_over}/{len(val_data)} ({100*val_over/len(val_data):.1f}%)")
        print(f"     Test:  {test_over}/{len(test_data)} ({100*test_over/len(test_data):.1f}%)")
        
        # Apply truncation
        train_data, train_stats = apply_graph_truncation(
            train_data, args.max_nodes, args.truncation_strategy
        )
        val_data, val_stats = apply_graph_truncation(
            val_data, args.max_nodes, args.truncation_strategy
        )
        test_data, test_stats = apply_graph_truncation(
            test_data, args.max_nodes, args.truncation_strategy
        )
        
        print(f"\n   Truncation complete:")
        print(f"     Train: {train_stats.get('truncated', 0)} graphs truncated")
        print(f"     Valid: {val_stats.get('truncated', 0)} graphs truncated")
        print(f"     Test:  {test_stats.get('truncated', 0)} graphs truncated")
        
        if train_stats.get('truncated', 0) > 0:
            print(f"     Avg nodes removed per truncated graph: {train_stats.get('avg_nodes_removed', 0):.1f}")
    # =========================================================================
    
    # Fix edge_attr → edge_type naming if needed (for edge_type GNN)
    def fix_edge_type_naming(data_list):
        """Convert edge_attr to edge_type for compatibility with edge-type-aware GNNs."""
        fixed_count = 0
        for data in data_list:
            if hasattr(data, 'edge_attr') and not hasattr(data, 'edge_type'):
                data.edge_type = data.edge_attr
                fixed_count += 1
            elif not hasattr(data, 'edge_type') and not hasattr(data, 'edge_attr'):
                # No edge types at all - create zeros
                if hasattr(data, 'edge_index') and data.edge_index is not None:
                    data.edge_type = torch.zeros(data.edge_index.size(1), dtype=torch.long)
        return fixed_count
    
    # Apply fix to all splits
    train_fixed = fix_edge_type_naming(train_data)
    val_fixed = fix_edge_type_naming(val_data)
    test_fixed = fix_edge_type_naming(test_data)
    
    if train_fixed > 0 or val_fixed > 0 or test_fixed > 0:
        print(f"\n[1b/5] Fixed edge_attr → edge_type: train={train_fixed}, val={val_fixed}, test={test_fixed}")
    
    # Show edge type info
    sample_data = train_data[0]
    if hasattr(sample_data, 'edge_type') and sample_data.edge_type is not None:
        unique_types = sample_data.edge_type.unique()
        print(f"Edge Types: {len(unique_types)} unique values: {unique_types.tolist()}")
    
    edge_text_dim = args.edge_text_dim
    if edge_text_dim is None and hasattr(sample_data, 'edge_text_emb') and sample_data.edge_text_emb is not None:
        edge_text_dim = sample_data.edge_text_emb.size(1)
        print(f"Inferred edge_text_dim from cache: {edge_text_dim}")
    if args.gnn_type == "edge_type_text" and edge_text_dim is None:
        print("[Warning] gnn-type=edge_type_text but edge_text_dim is not set or inferable")
    
    # Create data loaders
    train_loader, val_loader, test_loader = create_data_loaders(
        train_data, val_data, test_data,
        batch_size=args.batch_size,
    )
    
    # Get input dimension from data
    if len(train_data) > 0:
        total_input_dim = train_data[0].x.size(1)
    else:
        print("Error: Empty dataset!")
        return

    print(f"\nTotal Input Feature Dimension: {total_input_dim}")
    
    # Determine Node Type Dimension
    if args.embedding_dim > total_input_dim:
        print(f"[Warning] embedding-dim ({args.embedding_dim}) > total_dim ({total_input_dim}). Adjusting...")
        args.embedding_dim = total_input_dim
        
    num_node_types_inferred = total_input_dim - args.embedding_dim
    print(f"Inferred Config: One-Hot={num_node_types_inferred}, Embedding={args.embedding_dim}")
    
    # Use inferred or specified num_node_types
    if args.num_node_types != 16:  # User explicitly set it
        print(f"Using user-specified num_node_types: {args.num_node_types}")
    else:
        args.num_node_types = max(num_node_types_inferred, 1)
        print(f"Using inferred num_node_types: {args.num_node_types}")
    
    # Create model
    print("\n[2/5] Creating model...")
    
    # Build kwargs dict with all potentially relevant arguments
    # Only include non-None values to allow preset defaults to work
    model_kwargs = {
        "input_dim": total_input_dim,
        "hidden_dim": args.hidden_dim,
        "dropout": args.dropout,
        "num_edge_types": args.num_edge_types,
    }
    
    # Add optional overrides (only if specified)
    if args.gnn_layers is not None:
        model_kwargs["gnn_layers"] = args.gnn_layers
    if args.gnn_type is not None:
        model_kwargs["gnn_type"] = args.gnn_type
    if args.embedder_type is not None:
        model_kwargs["embedder_type"] = args.embedder_type
    if args.pooling_type is not None:
        model_kwargs["pooling_type"] = args.pooling_type
    if args.use_structural_features:
        model_kwargs["use_structural_features"] = True
    if edge_text_dim is not None:
        model_kwargs["edge_text_dim"] = edge_text_dim
    
    # =========================================================================
    # CALL-aware specific kwargs
    # =========================================================================
    if args.model_type == "call_aware" or args.gnn_type == "call_aware":
        model_kwargs["num_node_types"] = args.num_node_types
        model_kwargs["call_node_idx"] = args.call_node_idx
        model_kwargs["reaching_def_edge_type"] = args.reaching_def_edge_type
        print(f"CALL-aware config: num_node_types={args.num_node_types}, "
              f"call_node_idx={args.call_node_idx}, reaching_def_edge_type={args.reaching_def_edge_type}")
    # =========================================================================
    
    # For custom model, add extra kwargs
    if args.model_type == "custom":
        model_kwargs["embedder_kwargs"] = {
            "input_dim": args.embedding_dim,
            "num_node_types": args.num_node_types,
            "output_dim": args.hidden_dim,
            "dropout": args.dropout
        }
        # Set defaults for custom if not specified
        if "gnn_type" not in model_kwargs:
            model_kwargs["gnn_type"] = "ggnn"
        if "gnn_layers" not in model_kwargs:
            model_kwargs["gnn_layers"] = 1
        if "pooling_type" not in model_kwargs:
            model_kwargs["pooling_type"] = "multi_stat"
    
    # Print what we're passing
    print(f"Model kwargs: {model_kwargs}")
    
    model = create_model(args.model_type, **model_kwargs)
    model = model.to(device)
    
    # Count parameters
    total_params = sum(p.numel() for p in model.parameters())
    trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"Total parameters: {total_params:,}")
    print(f"Trainable parameters: {trainable_params:,}")

    # Optional: project classification head
    project_head = None
    project_criterion = None
    if project_enabled:
        with torch.no_grad():
            sample_batch = next(iter(train_loader)).to(device)
            output = model(sample_batch, return_embeddings=True)
            _, graph_emb = _unpack_model_output(output)
        if graph_emb is None:
            print("[Warning] Project classification requested, but graph embeddings unavailable. Disabling project head.")
            project_enabled = False
        else:
            project_in_dim = graph_emb.size(1)
            proj_hidden = max(32, min(args.hidden_dim, project_in_dim))
            project_head = nn.Sequential(
                nn.Linear(project_in_dim, proj_hidden),
                nn.ReLU(),
                nn.Dropout(args.dropout),
                nn.Linear(proj_hidden, len(project_to_idx)),
            ).to(device)

            # Optional class weights for project imbalance
            proj_labels = [int(d.project_y.item()) for d in train_data if hasattr(d, "project_y")]
            if not proj_labels:
                print("[Warning] No project labels found in training data. Disabling project head.")
                project_head = None
                project_criterion = None
            else:
                proj_counts = np.bincount(proj_labels, minlength=len(project_to_idx))
                proj_weights = np.where(proj_counts > 0, 1.0 / np.sqrt(proj_counts), 0.0)
                project_weights = torch.tensor(proj_weights, dtype=torch.float, device=device)
                project_criterion = nn.CrossEntropyLoss(weight=project_weights)
                print(f"[Info] Project head: in_dim={project_in_dim}, classes={len(project_to_idx)}")
    
    # Create loss function
    print("\n[3/5] Setting up training...")
    
    # Get class weights (returns pos_weight as tensor)
    class_weights = get_class_weights(train_data)
    class_weights = class_weights.to(device)  # Move to same device as model!
    print(f"Class weights (pos_weight): {class_weights}")
    
    # Create loss - pass tensor directly (BCEWithLogitsLoss requires tensor)
    criterion = create_loss(
        loss_type=args.loss_type,
        pos_weight=class_weights,
        focal_weight=args.focal_weight if args.loss_type == "combined" else 0.0,
    )
    
    # Optimizer
    opt_params = list(model.parameters())
    if project_head is not None:
        opt_params += list(project_head.parameters())
    optimizer = torch.optim.AdamW(
        opt_params,
        lr=args.lr,
        weight_decay=args.weight_decay,
    )
    
    # Scheduler
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(
        optimizer, mode='max', factor=0.5, patience=10, verbose=True
    )
    
    # Training
    print("\n[4/5] Training...")
    print("=" * 70)
    
    best_metric = 0
    best_epoch = 0
    patience_counter = 0
    
    # Determine which metric to track
    metric_key = {
        'auc': 'auc_roc',
        'f1': 'f1',
        'f1_best': 'f1_best',
    }.get(args.optimize_for, 'auc_roc')
    
    print(f"Optimizing for: {args.optimize_for} (tracking {metric_key})")
    
    for epoch in range(args.epochs):
        # Train
        train_loss = train_epoch(
            model,
            train_loader,
            optimizer,
            criterion,
            device,
            project_head=project_head,
            project_criterion=project_criterion,
            project_loss_weight=args.project_loss_weight,
        )
        
        # Evaluate
        val_metrics = evaluate(model, val_loader, device, project_head=project_head)
        
        # Debug: print available keys on first epoch
        if epoch == 0:
            print(f"Available metrics keys: {list(val_metrics.keys())}")
        
        # Get metrics with fallbacks for different key names
        val_auc = val_metrics.get('auc_roc', val_metrics.get('auc', val_metrics.get('roc_auc', 0)))
        val_f1 = val_metrics.get('f1', val_metrics.get('f1_score', 0))
        val_f1_best = val_metrics.get('f1_best', val_metrics.get('best_f1', val_f1))
        
        # Get current metric for tracking
        if metric_key in val_metrics:
            current_metric = val_metrics[metric_key]
        elif metric_key == 'auc_roc':
            current_metric = val_auc
        elif metric_key == 'f1_best':
            current_metric = val_f1_best
        else:
            current_metric = val_f1
        
        # Update scheduler
        scheduler.step(current_metric)
        
        # Print progress
        progress_line = (
            f"Epoch {epoch+1:3d}/{args.epochs} | "
            f"Loss: {train_loss:.4f} | "
            f"Val AUC: {val_auc:.4f} | "
            f"Val F1: {val_f1:.4f} | "
            f"Val F1_best: {val_f1_best:.4f} | "
            f"LR: {optimizer.param_groups[0]['lr']:.6f}"
        )
        if "project_accuracy" in val_metrics:
            progress_line += f" | Proj Acc: {val_metrics['project_accuracy']:.4f}"
        print(progress_line)
        
        # Check for improvement
        if current_metric > best_metric:
            best_metric = current_metric
            best_epoch = epoch + 1
            patience_counter = 0
            
            # Save best model
            save_dir = Path(args.save_dir) / args.experiment_name
            save_dir.mkdir(parents=True, exist_ok=True)
            ckpt = {
                'epoch': epoch,
                'model_state_dict': model.state_dict(),
                'optimizer_state_dict': optimizer.state_dict(),
                'best_metric': best_metric,
                'args': vars(args),
            }
            if project_head is not None:
                ckpt["project_head_state_dict"] = project_head.state_dict()
                ckpt["project_to_idx"] = project_to_idx
            torch.save(ckpt, save_dir / "best_model.pt")
        else:
            patience_counter += 1
            
            if patience_counter >= args.patience:
                print(f"\nEarly stopping at epoch {epoch+1}")
                break
    
    print("=" * 70)
    print(f"Training complete! Best {args.optimize_for}: {best_metric:.4f} at epoch {best_epoch}")
    
    # Load best model for final evaluation
    print("\n[5/5] Final evaluation on test set...")
    
    save_dir = Path(args.save_dir) / args.experiment_name
    checkpoint = torch.load(save_dir / "best_model.pt", map_location=device)
    model.load_state_dict(checkpoint['model_state_dict'])
    if project_head is not None and "project_head_state_dict" in checkpoint:
        project_head.load_state_dict(checkpoint["project_head_state_dict"])
    
    test_metrics, test_outputs = evaluate(
        model,
        test_loader,
        device,
        project_head=project_head,
        return_outputs=True,
    )
    
    print("\n" + "=" * 70)
    print("FINAL TEST RESULTS")
    print("=" * 70)
    print_metrics(test_metrics)
    
    # Compare with baselines
    print("\n" + "=" * 70)
    print("COMPARISON WITH BASELINES")
    print("=" * 70)
    compare_with_baselines(test_metrics)
    
    # Save final results
    results = {
        'experiment': args.experiment_name,
        'model_type': args.model_type,
        'best_epoch': best_epoch,
        'best_val_metric': best_metric,
        'test_metrics': test_metrics,
        'args': vars(args),
    }
    if project_head is not None:
        results["project_to_idx"] = project_to_idx
    
    with open(save_dir / "results.json", 'w') as f:
        json.dump(results, f, indent=2)

    threshold = float(test_metrics.get("best_threshold", 0.5))
    _save_predictions_csv(
        save_dir,
        "test",
        test_outputs["probs"],
        test_outputs["labels"],
        test_outputs["ids"],
        threshold,
    )

    _save_project_metrics(
        save_dir,
        "test",
        test_outputs["probs"],
        test_outputs["labels"],
        test_outputs["ids"],
        args.project_manifest_test,
        threshold,
    )
    _save_cwe_metrics(
        save_dir,
        "test",
        test_outputs["probs"],
        test_outputs["labels"],
        test_outputs["ids"],
        args.project_manifest_test,
        threshold,
    )
    
    print(f"\nResults saved to: {save_dir}")


if __name__ == "__main__":
    main()

"""
################################################################################
#                    VULNERABILITY DETECTION TRAINING COMMANDS                   #
#                       V9 - NAME-FIRST CALL EXTRACTION                          #
################################################################################

# AVAILABLE DATASETS (cache_reveal_v2 - V9):
# ------------------------------------------
# | Dataset Name                 | Signature          | Embedding Dim | Notes           |
# |-----------------------------|--------------------| --------------|-----------------|
# | unixcoder_768d_reveal_full  | da4ba2df98d97bc8   | 768          | REVEAL          |
# | graphcodebert_768d_reveal_full | b5d56d026d3be520   | 768          | REVEAL          |
# | codet5p_256d_reveal_full    | 924793d828204559   | 256          | REVEAL          |
# | word2vec_200d_reveal_full   | 907c2c5a79ce186e   | 200          | REVEAL          |
# | word2vec_100d_reveal_full   | 7c1030041c027a9f   | 100          | REVEAL          |
#
# AVAILABLE DATASETS (cache_draper_v2 - V9):
# ------------------------------------------
# | Dataset Name                 | Signature          | Embedding Dim | Notes           |
# |-----------------------------|--------------------| --------------|-----------------|
# | unixcoder_768d_draper_full  | REPLACE_WITH_SIGNATURE | 768        | DRAPER          |
# | graphcodebert_768d_draper_full | d487d6f448e3ad18   | 768        | DRAPER          |
# | codet5p_256d_draper_full    | f66d810f8ba04b3b   | 256        | DRAPER          |
# | word2vec_200d_draper_full   | 236655949834ff6d   | 200          | DRAPER          |
# | word2vec_100d_draper_full   | 2c96399b8f4b91d4   | 100          | DRAPER          |
#
# -----------------------------------------------------------------------------
# OPTIONAL: Project classification (multi-class)
# -----------------------------------------------------------------------------
# Add the following flags to any command to enable project classification:
#   --project-manifest-train "/path/to/manifest_train.csv" \
#   --project-manifest-val   "/path/to/manifest_validation.csv" \
#   --project-manifest-test  "/path/to/manifest_test.csv" \
#   --project-loss-weight    1.0
#
# AVAILABLE DATASETS (cache_primevul_v2 - V9):
# ------------------------------------------
# | Dataset Name                 | Signature          | Embedding Dim | Notes           |
# |-----------------------------|--------------------| --------------|-----------------|
# | word2vec_200d_primevul_full | bdbf53801c586471   | 200          | PRIMEVUL        |
#
# AVAILABLE DATASETS (cache_devign_v2 - V9):
# ------------------------------------------
# | Dataset Name                | Signature          | Embedding Dim | Notes           |
# |-----------------------------|--------------------| --------------|-----------------|
# | unixcoder_768d_full         | f6f464798e030305   | 768          | DEVIGN          |
# | graphcodebert_768d_full     | d253d91f25af3d71   | 768          | DEVIGN          |
# | graphcodebert_128d_full     | 1c3949dcf68534a6   | 128          | DEVIGN          |
# | codet5p_256d_full           | c60b3d632feea19c   | 256          | DEVIGN          |
# | word2vec_200d_full          | 86c56b1755c532ee   | 200          | DEVIGN          |
# | word2vec_100d_full          | 0b2074fbdf9296d6   | 100          | DEVIGN          |
#
# NOTE:
# - REVEAL/DRAPER/PRIMEVUL caches use full edge mode (19 edge types)
# - DEVIGN caches use full edge mode (18 edge types)

REVEAL_CACHE_DIR = "./Clean_exports/cache_reveal_v2"
DEVIGN_CACHE_DIR = "./Clean_exports/cache_devign_v2"
DRAPER_CACHE_DIR = "./Clean_exports/cache_draper_v2"
PRIMEVUL_CACHE_DIR = "./Clean_exports/cache_primevul_v2"
RESULTS_DIR = "./results"

################################################################################
#                              DRAPER COMMANDS                                  #
################################################################################


################################################################################
#                                                                              #
#  DRAPER - unixcoder_768d_draper_full                                          #
#  Signature: REPLACE_WITH_SIGNATURE                                            #
#  Embedding dim: 768                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "unixcoder_768d_draper_full" \
    --cache-signature "REPLACE_WITH_SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

################################################################################
#                                                                              #
#  DRAPER - graphcodebert_768d_draper_full                                      #
#  Signature: d487d6f448e3ad18                                            #
#  Embedding dim: 768                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "graphcodebert_768d_draper_full" \
    --cache-signature "d487d6f448e3ad18" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

################################################################################
#                                                                              #
#  DRAPER - codet5p_256d_draper_full                                            #
#  Signature: f66d810f8ba04b3b                                            #
#  Embedding dim: 256                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --embedding-dim 256 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 0 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --embedding-dim 256 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --embedding-dim 256 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "codet5p_256d_draper_full" \
    --cache-signature "f66d810f8ba04b3b" \
    --embedding-dim 256 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

################################################################################
#                                                                              #
#  DRAPER - word2vec_200d_draper_full                                           #
#  Signature: 236655949834ff6d                                                 #
#  Embedding dim: 200                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 8 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --embedding-dim 200 \
    --hidden-dim 512 \
    --dropout 0.1 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.001

# Call-Aware GNN (call-node-idx from draper_vocab_full)
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 8 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_200d_draper_full" \
    --cache-signature "236655949834ff6d" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001

################################################################################
#                                                                              #
#  DRAPER - word2vec_100d_draper_full                                           #
#  Signature: 2c96399b8f4b91d4                                                 #
#  Embedding dim: 100                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 16 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.001

# Call-Aware GNN (call-node-idx from draper_vocab_full)
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 15 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --embedding-dim 100 \
    --hidden-dim 512 \
    --dropout 0.1 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --embedding-dim 100 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_draper_v2" \
    --dataset-name "word2vec_100d_draper_full" \
    --cache-signature "2c96399b8f4b91d4" \
    --embedding-dim 100 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001
################################################################################
#                             PRIMEVUL COMMANDS                                 #
################################################################################


################################################################################
#                                                                              #
#  PRIMEVUL - word2vec_200d_primevul_full                                       #
#  Signature: bdbf53801c586471                                                 #
#  Embedding dim: 200                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_primevul_v2" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.1 \
    --epochs 100 \
    --patience 30 \
    --batch-size 16 \
    --lr 0.001

# Call-Aware GNN (call-node-idx from primevul_vocab_full)
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 0 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_primevul_v2" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_primevul_v2" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --embedding-dim 200 \
    --hidden-dim 216 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 16 \
    --lr 0.001 

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 8 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_primevul_v2" \
    --dataset-name "word2vec_200d_primevul_full" \
    --cache-signature "bdbf53801c586471" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.001 \
    --max-nodes 500

################################################################################
#                              REVEAL COMMANDS                                  #
################################################################################


################################################################################
#                                                                              #
#  REVEAL - unixcoder_768d_reveal_full                                       #
#  Signature: da4ba2df98d97bc8                                              #
#  Embedding dim: 768                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --embedding-dim 768 \
    --hidden-dim 800 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 16 \
    --lr 0.0005 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "unixcoder_768d_reveal_full" \
    --cache-signature "da4ba2df98d97bc8" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500


################################################################################
#                                                                              #
#  REVEAL - graphcodebert_768d_reveal_full                                   #
#  Signature: b5d56d026d3be520                                              #
#  Embedding dim: 768                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --embedding-dim 768 \
    --hidden-dim 800 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 16 \
    --lr 0.0005 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "graphcodebert_768d_reveal_full" \
    --cache-signature "b5d56d026d3be520" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500


################################################################################
#                                                                              #
#  REVEAL - codet5p_256d_reveal_full                                         #
#  Signature: 924793d828204559                                              #
#  Embedding dim: 256                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --embedding-dim 256 \
    --hidden-dim 384 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0008 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "codet5p_256d_reveal_full" \
    --cache-signature "924793d828204559" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500


################################################################################
#                                                                              #
#  REVEAL - word2vec_200d_reveal_full                                        #
#  Signature: 907c2c5a79ce186e                                              #
#  Embedding dim: 200                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --embedding-dim 200 \
    --hidden-dim 384 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_200d_reveal_full" \
    --cache-signature "907c2c5a79ce186e" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500


################################################################################
#                                                                              #
#  REVEAL - word2vec_100d_reveal_full                                        #
#  Signature: 7c1030041c027a9f                                              #
#  Embedding dim: 100                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --embedding-dim 100 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 19 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_reveal_v2" \
    --dataset-name "word2vec_100d_reveal_full" \
    --cache-signature "7c1030041c027a9f" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

################################################################################
#                              DEVIGN COMMANDS                                  #
################################################################################


################################################################################
#                                                                              #
#  DEVIGN - unixcoder_768d_full                                              #
#  Signature: f6f464798e030305                                              #
#  Embedding dim: 768                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "f6f464798e030305" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 800 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 16 \
    --lr 0.0005 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "unixcoder_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500


################################################################################
#                                                                              #
#  DEVIGN - graphcodebert_768d_full                                          #
#  Signature: d253d91f25af3d71                                              #
#  Embedding dim: 768                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 800 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 16 \
    --lr 0.0005 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_768d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 768 \
    --hidden-dim 512 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 32 \
    --lr 0.0005 \
    --max-nodes 500


################################################################################
#                                                                              #
#  DEVIGN - graphcodebert_128d_full                                          #
#  Signature: 1c3949dcf68534a6                                              #
#  Embedding dim: 128                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 128 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 128 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 128 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 128 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 128 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.001 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "graphcodebert_128d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 128 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500


################################################################################
#                                                                              #
#  DEVIGN - codet5p_256d_full                                                #
#  Signature: c60b3d632feea19c                                              #
#  Embedding dim: 256                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 256 \
    --hidden-dim 384 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0008 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "codet5p_256d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 256 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0008 \
    --max-nodes 500


################################################################################
#                                                                              #
#  DEVIGN - word2vec_200d_full                                               #
#  Signature: 86c56b1755c532ee                                              #
#  Embedding dim: 200                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 200 \
    --hidden-dim 384 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 64 \
    --lr 0.0005 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_200d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 200 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.0005 \
    --max-nodes 500


################################################################################
#                                                                              #
#  DEVIGN - word2vec_100d_full                                               #
#  Signature: 0b2074fbdf9296d6                                              #
#  Embedding dim: 100                                                          #
#                                                                              #
################################################################################
# Edge-Type GNN (baseline)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# Call-Aware GNN
python -m vuln_detection.train \
    --model-type call_aware \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type call_aware \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --num-node-types 16 \
    --call-node-idx 2 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# Deep GGNN (6 layers)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type ggnn \
    --gnn-layers 6 \
    --pooling-type devign \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# GAT with Attention Pooling
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type gat \
    --gnn-layers 4 \
    --pooling-type attention \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.2 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

# Deeper Edge-Type (5 layers, larger hidden)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 5 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --loss-type combined \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 100 \
    --hidden-dim 256 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 128 \
    --lr 0.001 \
    --max-nodes 500

# Focal Loss (Hard Example Mining)
python -m vuln_detection.train \
    --model-type improved_devign \
    --embedder-type word2vec \
    --use-structural-features \
    --gnn-type edge_type \
    --gnn-layers 4 \
    --pooling-type multi_stat \
    --num-edge-types 18 \
    --focal-weight 0.7 \
    --loss-type focal \
    --optimize-for f1_best \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "word2vec_100d_full" \
    --cache-signature "SIGNATURE" \
    --embedding-dim 100 \
    --hidden-dim 192 \
    --dropout 0.25 \
    --epochs 100 \
    --patience 30 \
    --batch-size 256 \
    --lr 0.001 \
    --max-nodes 500

################################################################################
#                              DATASET SUMMARY                                  #
################################################################################
#
# REVEAL:
# - unixcoder_768d_reveal_full: (dim=768, edge_types=19)
# - graphcodebert_768d_reveal_full:  (dim=768, edge_types=19)
# - codet5p_256d_reveal_full:  (dim=256, edge_types=19)
# - word2vec_200d_reveal_full:  (dim=200, edge_types=19)
# - word2vec_100d_reveal_full:  (dim=100, edge_types=19)
#
# DEVIGN:
# - unixcoder_768d_full:  (dim=768, edge_types=18)
# - graphcodebert_768d_full:  (dim=768, edge_types=18)
# - graphcodebert_128d_full:  (dim=128, edge_types=18)
# - codet5p_256d_full:  (dim=256, edge_types=18)
# - word2vec_200d_full:  (dim=200, edge_types=18)
# - word2vec_100d_full:  (dim=100, edge_types=18)
#
"""
