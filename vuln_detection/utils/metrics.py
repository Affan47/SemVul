#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
metrics.py - Evaluation metrics for vulnerability detection

Includes:
- Standard metrics (AUC, F1, Precision, Recall, Accuracy)
- Proper evaluation at threshold 0.50 (for fair comparison)
- Per-class statistics
"""

from typing import Dict, Tuple, Optional
import numpy as np
import torch

from sklearn.metrics import (
    roc_auc_score,
    f1_score,
    precision_score,
    recall_score,
    accuracy_score,
    confusion_matrix,
    roc_curve,
    precision_recall_curve,
    average_precision_score,
)


def compute_metrics(
    probs: np.ndarray,
    labels: np.ndarray,
    threshold: float = 0.50,
) -> Dict[str, float]:
    """
    Compute all metrics.
    
    Args:
        probs: Predicted probabilities [N]
        labels: True labels [N]
        threshold: Classification threshold (default 0.50 for fair comparison)
    
    Returns:
        Dict with metrics
    """
    # Binary predictions at threshold
    preds = (probs > threshold).astype(int)
    
    # AUC (threshold-independent)
    try:
        auc = roc_auc_score(labels, probs)
    except:
        auc = 0.5
    
    # Average Precision (threshold-independent)
    try:
        ap = average_precision_score(labels, probs)
    except:
        ap = 0.0
    
    # Metrics at threshold
    f1 = f1_score(labels, preds, zero_division=0)
    precision = precision_score(labels, preds, zero_division=0)
    recall = recall_score(labels, preds, zero_division=0)
    accuracy = accuracy_score(labels, preds)
    
    # Confusion matrix
    tn, fp, fn, tp = confusion_matrix(labels, preds, labels=[0, 1]).ravel()
    
    # Per-class probabilities
    safe_probs = probs[labels == 0]
    vuln_probs = probs[labels == 1]
    
    return {
        # Threshold-independent
        "auc": auc,
        "average_precision": ap,
        
        # At threshold
        "f1": f1,
        "precision": precision,
        "recall": recall,
        "accuracy": accuracy,
        "threshold": threshold,
        
        # Confusion matrix
        "true_positives": int(tp),
        "true_negatives": int(tn),
        "false_positives": int(fp),
        "false_negatives": int(fn),
        
        # Per-class probabilities
        "safe_prob_mean": float(safe_probs.mean()) if len(safe_probs) > 0 else 0,
        "safe_prob_std": float(safe_probs.std()) if len(safe_probs) > 0 else 0,
        "vuln_prob_mean": float(vuln_probs.mean()) if len(vuln_probs) > 0 else 0,
        "vuln_prob_std": float(vuln_probs.std()) if len(vuln_probs) > 0 else 0,
        "separation": float(vuln_probs.mean() - safe_probs.mean()) if len(vuln_probs) > 0 and len(safe_probs) > 0 else 0,
    }


def compute_vd_s(
    probs: np.ndarray,
    labels: np.ndarray,
    fpr_limit: float = 0.005,
) -> float:
    """
    Vulnerability Detection Score (VD-S) used in PrimeVul:
    False Negative Rate (FNR) when False Positive Rate (FPR) <= fpr_limit.
    
    Lower is better.
    """
    try:
        fpr, tpr, _ = roc_curve(labels, probs)
    except Exception:
        return 1.0
    
    mask = fpr <= fpr_limit
    if not np.any(mask):
        return 1.0
    
    best_tpr = float(tpr[mask].max())
    vd_s = 1.0 - best_tpr
    return vd_s


def find_best_threshold(
    probs: np.ndarray,
    labels: np.ndarray,
    metric: str = "f1",  # "f1", "accuracy", "balanced"
    thresholds: Optional[np.ndarray] = None,
) -> Tuple[float, float]:
    """
    Find best classification threshold.
    
    Args:
        probs: Predicted probabilities
        labels: True labels
        metric: Which metric to optimize
        thresholds: Thresholds to try (default: 0.30 to 0.70)
    
    Returns:
        (best_threshold, best_metric_value)
    """
    if thresholds is None:
        thresholds = np.arange(0.30, 0.71, 0.02)
    
    best_score = 0
    best_thresh = 0.5
    
    for thresh in thresholds:
        preds = (probs > thresh).astype(int)
        
        if metric == "f1":
            score = f1_score(labels, preds, zero_division=0)
        elif metric == "accuracy":
            score = accuracy_score(labels, preds)
        elif metric == "balanced":
            # Balanced accuracy (average of TPR and TNR)
            tn, fp, fn, tp = confusion_matrix(labels, preds, labels=[0, 1]).ravel()
            tpr = tp / (tp + fn) if (tp + fn) > 0 else 0
            tnr = tn / (tn + fp) if (tn + fp) > 0 else 0
            score = (tpr + tnr) / 2
        else:
            raise ValueError(f"Unknown metric: {metric}")
        
        if score > best_score:
            best_score = score
            best_thresh = thresh
    
    return best_thresh, best_score


def compute_full_evaluation(
    probs: np.ndarray,
    labels: np.ndarray,
) -> Dict[str, float]:
    """
    Compute comprehensive evaluation.
    
    Returns metrics at:
    - Threshold 0.50 (fair comparison with baselines)
    - Best F1 threshold
    """
    # At threshold 0.50 (for fair comparison with Devign paper)
    metrics_50 = compute_metrics(probs, labels, threshold=0.50)
    
    # Best F1 threshold
    best_thresh, best_f1 = find_best_threshold(probs, labels, metric="f1")
    metrics_best = compute_metrics(probs, labels, threshold=best_thresh)
    
    return {
        # Threshold-independent
        "auc": metrics_50["auc"],
        "average_precision": metrics_50["average_precision"],
        
        # At 0.50 (fair comparison)
        "f1_at_50": metrics_50["f1"],
        "precision_at_50": metrics_50["precision"],
        "recall_at_50": metrics_50["recall"],
        "accuracy_at_50": metrics_50["accuracy"],
        
        # Best F1
        "f1_best": metrics_best["f1"],
        "precision_best": metrics_best["precision"],
        "recall_best": metrics_best["recall"],
        "accuracy_best": metrics_best["accuracy"],
        "best_threshold": best_thresh,
        
        # Class separation
        "safe_prob_mean": metrics_50["safe_prob_mean"],
        "vuln_prob_mean": metrics_50["vuln_prob_mean"],
        "separation": metrics_50["separation"],
        # PrimeVul metric (lower is better)
        "vd_s": compute_vd_s(probs, labels),
    }


def print_metrics(
    metrics: Dict[str, float],
    title: str = "Evaluation Results",
):
    """Pretty print metrics."""
    print("\n" + "=" * 60)
    print(title)
    print("=" * 60)
    
    print("\n--- Threshold-Independent ---")
    print(f"AUC-ROC: {metrics['auc']:.4f}")
    if "average_precision" in metrics:
        print(f"Average Precision: {metrics['average_precision']:.4f}")
    
    print("\n--- At Threshold 0.50 (Fair Comparison) ---")
    print(f"F1:        {metrics.get('f1_at_50', metrics.get('f1', 0)):.4f}")
    print(f"Precision: {metrics.get('precision_at_50', metrics.get('precision', 0)):.4f}")
    print(f"Recall:    {metrics.get('recall_at_50', metrics.get('recall', 0)):.4f}")
    print(f"Accuracy:  {metrics.get('accuracy_at_50', metrics.get('accuracy', 0)):.4f}")
    
    if "f1_best" in metrics:
        print(f"\n--- Best F1 (Threshold={metrics['best_threshold']:.2f}) ---")
        print(f"F1:        {metrics['f1_best']:.4f}")
        print(f"Precision: {metrics['precision_best']:.4f}")
        print(f"Recall:    {metrics['recall_best']:.4f}")
        print(f"Accuracy:  {metrics['accuracy_best']:.4f}")
    
    if "separation" in metrics:
        print(f"\n--- Class Separation ---")
        print(f"Safe prob:  {metrics['safe_prob_mean']:.3f}")
        print(f"Vuln prob:  {metrics['vuln_prob_mean']:.3f}")
        print(f"Separation: {metrics['separation']:.3f}")
    if "vd_s" in metrics:
        print(f"\n--- PrimeVul Metric ---")
        print(f"VD-S (FNR @ FPR<=0.5%): {metrics['vd_s']:.4f}")
    if "project_accuracy" in metrics:
        print(f"\n--- Project Classification ---")
        print(f"Project Acc:  {metrics['project_accuracy']:.4f}")
        if "project_f1_macro" in metrics:
            print(f"Project F1 (macro): {metrics['project_f1_macro']:.4f}")


def compare_with_baselines(metrics: Dict[str, float]):
    """Compare results with published baselines."""
    print("\n" + "=" * 60)
    print("COMPARISON WITH BASELINES")
    print("=" * 60)
    
    # Baselines from papers
    baselines = {
        "Devign (paper)": {"acc": 72.26, "f1": 73.26, "auc": None},
        "ReVeal": {"acc": 65.0, "f1": 48.0, "auc": 63.0},
        "IVDetect": {"acc": 68.0, "f1": 52.0, "auc": 65.0},
    }
    
    print(f"\n{'Method':<25} {'ACC':>8} {'F1':>8} {'AUC':>8}")
    print("-" * 55)
    
    for name, baseline in baselines.items():
        acc = f"{baseline['acc']:.2f}" if baseline['acc'] else "-"
        f1 = f"{baseline['f1']:.2f}" if baseline['f1'] else "-"
        auc = f"{baseline['auc']:.2f}" if baseline['auc'] else "-"
        print(f"{name:<25} {acc:>8} {f1:>8} {auc:>8}")
    
    # Your results
    acc = metrics.get("accuracy_at_50", metrics.get("accuracy", 0)) * 100
    f1 = metrics.get("f1_at_50", metrics.get("f1", 0)) * 100
    auc = metrics.get("auc", 0) * 100
    
    print(f"{'Your Model':<25} {acc:>8.2f} {f1:>8.2f} {auc:>8.2f}")
    
    # Verdict
    print("\n" + "-" * 55)
    if acc > 72.26:
        print("✅ BEATS Devign paper on accuracy!")
    if f1 > 73.26:
        print("✅ BEATS Devign paper on F1!")
    if auc > 65.0:
        print("✅ BEATS IVDetect on AUC!")
    elif auc > 63.0:
        print("✅ BEATS ReVeal on AUC!")
    elif auc > 60.0:
        print("⚠️ Above random but below published baselines")
    else:
        print("❌ Below baseline performance")
