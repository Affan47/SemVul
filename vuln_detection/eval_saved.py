#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
eval_saved.py - Standalone evaluation for saved checkpoints (no retraining).

Supports:
  - train.py checkpoints (basic models via create_model)
  - train_advanced.py checkpoints (advanced models via create_advanced_model)

Optionally computes project-level multiclass metrics if:
  - project_head_state_dict exists in checkpoint, and
  - project manifests are provided to map function_id -> project.
"""

import argparse
import csv
import json
from pathlib import Path
from typing import Dict, Tuple

import numpy as np
import torch
import torch.nn as nn
from torch_geometric.loader import DataLoader
from sklearn.metrics import accuracy_score, f1_score

from vuln_detection import create_model
from vuln_detection.utils import (
    load_dataset,
    compute_full_evaluation,
    compute_metrics,
    print_metrics,
)

# Advanced models
from vuln_detection.models.advanced import (
    RGATDevignModel,
    MultiViewGGNN,
    HGTDevignModel,
    HyperDevignModel,
)
try:
    from vuln_detection.models.hagnn import create_hagnn_model
    HAS_HAGNN = True
except ImportError:
    HAS_HAGNN = False
    create_hagnn_model = None

try:
    from vuln_detection.models.call_aware import CallAwareVulnDetector
    HAS_CALL_AWARE = True
except ImportError:
    HAS_CALL_AWARE = False
    CallAwareVulnDetector = None


def _load_project_map(manifest_path: str) -> Tuple[Dict[str, str], set]:
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


def attach_project_labels(data_list, func_to_project, project_to_idx, unk_idx):
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
        data.project_name = project if project is not None else "__UNK__"


def _unpack_model_output(output):
    if isinstance(output, dict):
        logits = output.get("logits", output.get("out", output.get("pred", None)))
        graph_emb = output.get("graph_emb", None)
        return logits, graph_emb
    if isinstance(output, tuple) and len(output) == 2:
        return output[0], output[1]
    return output, None


def create_advanced_model(
    model_type: str,
    in_dim: int,
    hidden_dim: int,
    num_relations: int,
    num_layers: int = 4,
    num_heads: int = 4,
    dropout: float = 0.2,
    **kwargs,
) -> nn.Module:
    if model_type == "rgat":
        return RGATDevignModel(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_relations=num_relations,
            num_layers=num_layers,
            heads=num_heads,
            dropout=dropout,
            use_checkpoint=kwargs.get("use_checkpoint", False),
        )
    if model_type == "multiview":
        return MultiViewGGNN(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_layers=num_layers,
            dropout=dropout,
            edge_type_config=kwargs.get("edge_type_config", None),
        )
    if model_type == "hgt":
        return HGTDevignModel(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_relations=num_relations,
            num_layers=num_layers,
            heads=num_heads,
            dropout=dropout,
        )
    if model_type == "hypergraph":
        return HyperDevignModel(
            in_dim=in_dim,
            hidden_dim=hidden_dim,
            num_relations=num_relations,
            num_layers=num_layers,
            heads=num_heads,
            dropout=dropout,
        )
    if model_type == "call_aware":
        if not HAS_CALL_AWARE:
            raise ImportError("CallAwareVulnDetector not available.")
        return CallAwareVulnDetector(
            input_dim=in_dim,
            hidden_dim=hidden_dim,
            num_edge_types=num_relations,
            num_layers=num_layers,
            num_node_types=kwargs.get("num_node_types", 16),
            call_node_idx=kwargs.get("call_node_idx", 2),
            reaching_def_edge_type=kwargs.get("reaching_def_edge_type", 9),
            dropout=dropout,
        )
    raise ValueError(f"Unknown advanced model type: {model_type}")


def build_project_head_from_state(state_dict: Dict[str, torch.Tensor], dropout: float) -> nn.Module:
    w0 = state_dict["0.weight"]
    w2 = state_dict["3.weight"]
    in_dim = w0.shape[1]
    hidden_dim = w0.shape[0]
    num_classes = w2.shape[0]
    head = nn.Sequential(
        nn.Linear(in_dim, hidden_dim),
        nn.ReLU(),
        nn.Dropout(dropout),
        nn.Linear(hidden_dim, num_classes),
    )
    head.load_state_dict(state_dict)
    return head


@torch.no_grad()
def evaluate(model, loader, device, project_head=None, threshold: float = 0.5, override_best: bool = False):
    model.eval()
    if project_head is not None:
        project_head.eval()
    all_probs = []
    all_labels = []
    all_project_preds = []
    all_project_labels = []
    all_project_names = []

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
            output = model(batch)
            logits, _ = _unpack_model_output(output)
            logits = logits.view(-1)

        if hasattr(batch, "project_name"):
            all_project_names.extend(list(batch.project_name))

        probs = torch.sigmoid(logits)
        all_probs.append(probs.cpu())
        all_labels.append(batch.y.cpu().view(-1))

    probs = torch.cat(all_probs).numpy()
    labels = torch.cat(all_labels).numpy()
    metrics = compute_full_evaluation(probs, labels)
    if threshold is not None:
        metrics["eval_threshold"] = float(threshold)
        metrics_saved = compute_metrics(probs, labels, threshold=threshold)
        metrics["f1_at_eval_threshold"] = metrics_saved["f1"]
        metrics["precision_at_eval_threshold"] = metrics_saved["precision"]
        metrics["recall_at_eval_threshold"] = metrics_saved["recall"]
        metrics["accuracy_at_eval_threshold"] = metrics_saved["accuracy"]
        if override_best:
            metrics["best_threshold"] = float(threshold)
            metrics["f1_best"] = metrics_saved["f1"]
            metrics["precision_best"] = metrics_saved["precision"]
            metrics["recall_best"] = metrics_saved["recall"]
            metrics["accuracy_best"] = metrics_saved["accuracy"]
    project_report = None
    if all_project_labels:
        proj_preds = torch.cat(all_project_preds).numpy()
        proj_labels = torch.cat(all_project_labels).numpy()
        metrics["project_accuracy"] = accuracy_score(proj_labels, proj_preds)
        metrics["project_f1_macro"] = f1_score(proj_labels, proj_preds, average="macro")
    if all_project_names:
        # Per-project metrics (binary vulnerability)
        from sklearn.metrics import precision_recall_fscore_support
        project_report = {}
        for proj in sorted(set(all_project_names)):
            idx = [i for i, p in enumerate(all_project_names) if p == proj]
            if not idx:
                continue
            p_true = labels[idx]
            p_pred = (probs[idx] >= threshold).astype(int)
            prec, rec, f1, _ = precision_recall_fscore_support(
                p_true, p_pred, average="binary", zero_division=0
            )
            project_report[proj] = {
                "n": int(len(idx)),
                "precision": float(prec),
                "recall": float(rec),
                "f1": float(f1),
            }
    return metrics, project_report


def _load_saved_threshold(checkpoint_path: str):
    ckpt_dir = Path(checkpoint_path).resolve().parent
    results_path = ckpt_dir / "results.json"
    if not results_path.exists():
        return None
    try:
        with open(results_path, "r", encoding="utf-8") as f:
            results = json.load(f)
        test_metrics = results.get("test_metrics", {})
        return test_metrics.get("best_threshold", None)
    except Exception:
        return None


def main():
    parser = argparse.ArgumentParser(description="Evaluate a saved checkpoint")
    parser.add_argument("--checkpoint", type=str, required=True, help="Path to checkpoint .pt")
    parser.add_argument("--model-family", type=str, choices=["basic", "advanced"], default="basic",
                        help="Which training script produced the checkpoint")

    parser.add_argument("--cache-dir", type=str, default=None)
    parser.add_argument("--dataset-name", type=str, default=None)
    parser.add_argument("--cache-signature", type=str, default=None)
    parser.add_argument("--split", type=str, default="test", choices=["train", "valid", "test"])
    parser.add_argument("--batch-size", type=int, default=64)
    parser.add_argument("--device", type=str, default="auto")

    parser.add_argument("--project-manifest-train", type=str, default=None)
    parser.add_argument("--project-manifest-val", type=str, default=None)
    parser.add_argument("--project-manifest-test", type=str, default=None)
    parser.add_argument("--threshold", type=float, default=None,
                        help="Override decision threshold for reporting (defaults to saved best_threshold if available)")

    args = parser.parse_args()

    checkpoint = torch.load(args.checkpoint, map_location="cpu")
    saved_args = checkpoint.get("args", {})

    cache_dir = args.cache_dir or saved_args.get("cache_dir")
    dataset_name = args.dataset_name or saved_args.get("dataset_name")
    cache_signature = args.cache_signature or saved_args.get("cache_signature")
    if not cache_dir or not dataset_name or not cache_signature:
        raise ValueError("cache-dir, dataset-name, cache-signature required (either CLI or saved args).")

    if args.device == "auto":
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    else:
        device = torch.device(args.device)

    train_data, val_data, test_data = load_dataset(
        cache_dir=cache_dir,
        dataset_name=dataset_name,
        cache_signature=cache_signature,
    )
    split_data = {"train": train_data, "valid": val_data, "test": test_data}[args.split]

    project_enabled = all([args.project_manifest_train, args.project_manifest_val, args.project_manifest_test])
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

    loader = DataLoader(split_data, batch_size=args.batch_size, shuffle=False)

    in_dim = split_data[0].x.size(1)
    model_type = saved_args.get("model_type")

    if args.model_family == "basic":
        model_kwargs = {
            "input_dim": in_dim,
            "hidden_dim": saved_args.get("hidden_dim", 128),
            "dropout": saved_args.get("dropout", 0.2),
            "num_edge_types": saved_args.get("num_edge_types", 18),
        }
        for k in ["gnn_layers", "gnn_type", "embedder_type", "pooling_type", "use_structural_features",
                  "num_node_types", "call_node_idx", "reaching_def_edge_type"]:
            if k in saved_args and saved_args[k] is not None:
                model_kwargs[k] = saved_args[k]
        model = create_model(model_type, **model_kwargs)
    elif model_type == "hagnn":
        if not HAS_HAGNN:
            raise ImportError("HAGNN model is not available. Ensure vuln_detection.models.hagnn is installed.")
        model = create_hagnn_model(
            input_dim=in_dim,
            hidden_dim=saved_args.get("hidden_dim", 256),
            num_layers=saved_args.get("num_layers", 4),
            num_edge_types=saved_args.get("num_edge_types", 18),
            num_node_types=saved_args.get("num_node_types", 16),
            call_node_idx=saved_args.get("call_node_idx", 2),
            heads=saved_args.get("heads", 4),
            dropout=saved_args.get("dropout", 0.2),
        )
    else:
        model = create_advanced_model(
            model_type=model_type,
            in_dim=in_dim,
            hidden_dim=saved_args.get("hidden_dim", 256),
            num_relations=saved_args.get("num_edge_types", 18),
            num_layers=saved_args.get("num_layers", 4),
            num_heads=saved_args.get("num_heads", 4),
            dropout=saved_args.get("dropout", 0.2),
            num_node_types=saved_args.get("num_node_types", 16),
            call_node_idx=saved_args.get("call_node_idx", 2),
            reaching_def_edge_type=saved_args.get("reaching_def_edge_type", 9),
        )

    missing, unexpected = model.load_state_dict(checkpoint["model_state_dict"], strict=False)
    if unexpected:
        print(f"[Warning] Unexpected keys in checkpoint: {unexpected}")
    if missing:
        print(f"[Warning] Missing keys in checkpoint: {missing}")
    model = model.to(device)

    project_head = None
    if "project_head_state_dict" in checkpoint:
        project_head = build_project_head_from_state(
            checkpoint["project_head_state_dict"],
            dropout=saved_args.get("dropout", 0.2),
        ).to(device)
        if not project_enabled:
            print("[Warning] Project head found but project manifests not provided; project metrics will be skipped.")

    saved_threshold = _load_saved_threshold(args.checkpoint)
    eval_threshold = args.threshold if args.threshold is not None else (saved_threshold if saved_threshold is not None else 0.5)
    if saved_threshold is not None and args.threshold is None:
        print(f"[Info] Using saved best_threshold from results.json: {saved_threshold:.2f}")
    elif args.threshold is not None:
        print(f"[Info] Using user-provided threshold: {args.threshold:.2f}")
    metrics, project_report = evaluate(
        model,
        loader,
        device,
        project_head=project_head,
        threshold=eval_threshold,
        override_best=True if eval_threshold is not None else False,
    )
    print_metrics(metrics, title=f"Evaluation ({args.split})")
    if project_report:
        out_dir = Path(args.checkpoint).resolve().parent
        out_path = out_dir / f"project_metrics_{args.split}.json"
        with open(out_path, "w", encoding="utf-8") as f:
            json.dump(project_report, f, indent=2, sort_keys=True)
        print(f"[Saved] Per-project metrics: {out_path}")


if __name__ == "__main__":
    main()

"""
PrimeVul evaluation (Word2Vec 200d cache)
=========================================

# Improved Devign (basic)
python -m vuln_detection.eval_saved \
  --checkpoint "./checkpoints/improved_devign_20260125_194228/best_model.pt" \
  --model-family basic \
  --cache-dir "./Clean_exports/cache_primevul_v2" \
  --dataset-name "word2vec_200d_primevul_full" \
  --cache-signature "bdbf53801c586471" \
  --split test \
  --project-manifest-train "./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv" \
  --project-manifest-val   "./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv" \
  --project-manifest-test  "./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv"

# RGAT (advanced)
python -m vuln_detection.eval_saved \
  --checkpoint "./checkpoints_advanced/rgat_20260123_010930/best_model.pt" \
  --model-family advanced \
  --cache-dir "./Clean_exports/cache_primevul_v2" \
  --dataset-name "word2vec_200d_primevul_full" \
  --cache-signature "bdbf53801c586471" \
  --split test \
  --project-manifest-train "./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv" \
  --project-manifest-val   "./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv" \
  --project-manifest-test  "./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv"

# MultiView (advanced)
python -m vuln_detection.eval_saved \
  --checkpoint "./checkpoints_advanced/multiview_20260122_142634/best_model.pt" \
  --model-family advanced \
  --cache-dir "./Clean_exports/cache_primevul_v2" \
  --dataset-name "word2vec_200d_primevul_full" \
  --cache-signature "bdbf53801c586471" \
  --split test \
  --project-manifest-train "./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv" \
  --project-manifest-val   "./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv" \
  --project-manifest-test  "./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv"

# Hypergraph (advanced)
python -m vuln_detection.eval_saved \
  --checkpoint "./checkpoints_advanced/hypergraph_20260123_091502/best_model.pt" \
  --model-family advanced \
  --cache-dir "./Clean_exports/cache_primevul_v2" \
  --dataset-name "word2vec_200d_primevul_full" \
  --cache-signature "bdbf53801c586471" \
  --split test \
  --project-manifest-train "./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv" \
  --project-manifest-val   "./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv" \
  --project-manifest-test  "./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv"

# HAGNN (contrastive-trained)
python -m vuln_detection.eval_saved \
  --checkpoint "./results/primevul_word2vec_200d_hagnn_v1/model.pt" \
  --model-family advanced \
  --cache-dir "./Clean_exports/cache_primevul_v2" \
  --dataset-name "word2vec_200d_primevul_full" \
  --cache-signature "bdbf53801c586471" \
  --split test \
  --project-manifest-train "./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv" \
  --project-manifest-val   "./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv" \
  --project-manifest-test  "./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv"
"""
