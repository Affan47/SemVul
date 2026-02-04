#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
step3_compare_results.py - Compare all experiment results

Usage:
    python step3_compare_results.py --results-dir ./results
    python step3_compare_results.py --results-dir ./results --output report.txt
"""

import argparse
import json
import re
from pathlib import Path
from typing import Dict, List


# ============================================================================
# BASELINES
# ============================================================================

BASELINES = {
    "Devign (paper)": {"acc": 72.26, "f1": 73.26, "auc": None},
    "ReVeal": {"acc": 65.0, "f1": 48.0, "auc": 63.0},
    "IVDetect": {"acc": 68.0, "f1": 52.0, "auc": 65.0},
}


# ============================================================================
# RESULT PARSING
# ============================================================================

def parse_log_file(log_path: Path) -> Dict:
    """Parse a log file for metrics."""
    content = log_path.read_text()
    
    result = {
        "name": log_path.stem,
        "path": str(log_path),
        "auc": None,
        "f1": None,
        "accuracy": None,
    }
    
    # Try multiple patterns
    auc_patterns = [
        r'Test AUC[:\s]+([0-9.]+)',
        r'AUC[:\s]+([0-9.]+)',
        r'"auc"[:\s]+([0-9.]+)',
        r'auc[:\s]+([0-9.]+)',
    ]
    
    f1_patterns = [
        r'Test F1@0.50[:\s]+([0-9.]+)',
        r'F1@0.50[:\s]+([0-9.]+)',
        r'"f1"[:\s]+([0-9.]+)',
        r'F1[:\s]+([0-9.]+)',
    ]
    
    acc_patterns = [
        r'Test Acc(?:uracy)?[:\s]+([0-9.]+)',
        r'"accuracy"[:\s]+([0-9.]+)',
        r'Accuracy[:\s]+([0-9.]+)',
    ]
    
    for pattern in auc_patterns:
        match = re.search(pattern, content, re.IGNORECASE)
        if match:
            result["auc"] = float(match.group(1))
            break
    
    for pattern in f1_patterns:
        match = re.search(pattern, content, re.IGNORECASE)
        if match:
            result["f1"] = float(match.group(1))
            break
    
    for pattern in acc_patterns:
        match = re.search(pattern, content, re.IGNORECASE)
        if match:
            result["accuracy"] = float(match.group(1))
            break
    
    return result


def parse_json_file(json_path: Path) -> Dict:
    """Parse a JSON results file."""
    with open(json_path) as f:
        data = json.load(f)
    
    result = {
        "name": json_path.stem.replace("_results", ""),
        "path": str(json_path),
        "auc": None,
        "f1": None,
        "accuracy": None,
    }
    
    # Handle nested structure
    if "test_metrics" in data:
        metrics = data["test_metrics"]
        result["auc"] = metrics.get("auc")
        result["f1"] = metrics.get("f1")
        result["accuracy"] = metrics.get("accuracy")
    else:
        result["auc"] = data.get("auc") or data.get("test_auc")
        result["f1"] = data.get("f1") or data.get("test_f1")
        result["accuracy"] = data.get("accuracy") or data.get("test_acc")
    
    return result


def collect_results(results_dir: Path) -> List[Dict]:
    """Collect all results from directory."""
    results = []
    
    # Find all log files
    for log_file in results_dir.rglob("*.log"):
        if log_file.name.startswith("00_"):
            continue
        result = parse_log_file(log_file)
        if result["auc"] is not None:
            results.append(result)
    
    # Find all JSON result files
    for json_file in results_dir.rglob("*_results.json"):
        result = parse_json_file(json_file)
        if result["auc"] is not None:
            # Check if not duplicate
            if not any(r["name"] == result["name"] for r in results):
                results.append(result)
    
    return results


def categorize_result(name: str) -> Dict[str, str]:
    """Categorize result by model and embedding type."""
    name_lower = name.lower()
    
    # Embedding type
    if "codebert" in name_lower or "128d" in name_lower:
        embedding = "CodeBERT 128d"
    elif "codet5" in name_lower or "256d" in name_lower:
        embedding = "CodeT5+ 256d"
    elif "unixcoder" in name_lower or "768d" in name_lower:
        embedding = "UniXcoder 768d"
    else:
        embedding = "Unknown"
    
    # Model type
    if "mlp" in name_lower or "graph_level" in name_lower:
        model = "Graph-Level MLP"
    elif "devign" in name_lower:
        model = "Devign (GGNN)"
    elif "attention" in name_lower:
        model = "Attention"
    elif "edge_type" in name_lower:
        model = "Edge-Type GNN"
    elif "multiview" in name_lower:
        model = "MultiView"
    elif "hgt" in name_lower:
        model = "HGT"
    elif "rgat" in name_lower:
        model = "RGAT"
    elif "hypergraph" in name_lower:
        model = "Hypergraph"
    elif "shallow" in name_lower:
        model = "Shallow GNN"
    elif "no_gnn" in name_lower:
        model = "No GNN"
    else:
        model = "Other"
    
    return {"model": model, "embedding": embedding}


# ============================================================================
# REPORT GENERATION
# ============================================================================

def generate_report(results: List[Dict]) -> str:
    """Generate comparison report."""
    lines = []
    
    lines.append("=" * 100)
    lines.append("VULNERABILITY DETECTION - COMPREHENSIVE RESULTS COMPARISON")
    lines.append("=" * 100)
    
    # Baselines
    lines.append("\n📚 PUBLISHED BASELINES (for reference):")
    lines.append("-" * 60)
    lines.append(f"{'Method':<30} {'ACC':>10} {'F1':>10} {'AUC':>10}")
    lines.append("-" * 60)
    
    for name, metrics in BASELINES.items():
        acc = f"{metrics['acc']:.2f}%" if metrics['acc'] else "-"
        f1 = f"{metrics['f1']:.2f}%" if metrics['f1'] else "-"
        auc = f"{metrics['auc']:.2f}%" if metrics['auc'] else "-"
        lines.append(f"{name:<30} {acc:>10} {f1:>10} {auc:>10}")
    
    lines.append("-" * 60)
    
    if not results:
        lines.append("\n❌ No results found!")
        return "\n".join(lines)
    
    # Sort by AUC
    results = sorted(results, key=lambda x: x["auc"] or 0, reverse=True)
    
    # All results table
    lines.append("\n\n📊 ALL EXPERIMENT RESULTS (sorted by AUC):")
    lines.append("-" * 100)
    lines.append(f"{'Rank':<5} {'Experiment':<50} {'AUC':>10} {'F1@0.50':>10} {'Accuracy':>10}")
    lines.append("-" * 100)
    
    for i, r in enumerate(results, 1):
        auc_str = f"{r['auc']:.4f}" if r['auc'] else "N/A"
        f1_str = f"{r['f1']:.4f}" if r['f1'] else "N/A"
        acc_str = f"{r['accuracy']:.4f}" if r['accuracy'] else "N/A"
        lines.append(f"{i:<5} {r['name']:<50} {auc_str:>10} {f1_str:>10} {acc_str:>10}")
    
    lines.append("-" * 100)
    
    # Group by embedding
    lines.append("\n\n📈 RESULTS BY EMBEDDING:")
    
    from collections import defaultdict
    by_embedding = defaultdict(list)
    for r in results:
        cat = categorize_result(r["name"])
        by_embedding[cat["embedding"]].append(r)
    
    for emb, emb_results in sorted(by_embedding.items()):
        if emb_results:
            best = max(emb_results, key=lambda x: x["auc"] or 0)
            avg_auc = sum(r["auc"] for r in emb_results if r["auc"]) / len([r for r in emb_results if r["auc"]])
            lines.append(f"  {emb:<20}: Best AUC = {best['auc']:.4f} | Avg = {avg_auc:.4f} | n={len(emb_results)}")
    
    # Group by model
    lines.append("\n\n📈 RESULTS BY MODEL ARCHITECTURE:")
    
    by_model = defaultdict(list)
    for r in results:
        cat = categorize_result(r["name"])
        by_model[cat["model"]].append(r)
    
    for model, model_results in sorted(by_model.items(), key=lambda x: max(r["auc"] or 0 for r in x[1]), reverse=True):
        if model_results:
            best = max(model_results, key=lambda x: x["auc"] or 0)
            lines.append(f"  {model:<20}: Best AUC = {best['auc']:.4f}")
    
    # Top 10
    lines.append("\n\n🏆 TOP 10 CONFIGURATIONS:")
    lines.append("-" * 80)
    
    for i, r in enumerate(results[:10], 1):
        auc_str = f"{r['auc']:.4f}" if r['auc'] else "N/A"
        f1_str = f"{r['f1']:.4f}" if r['f1'] else "N/A"
        lines.append(f"{i:2d}. {r['name']:<55} AUC: {auc_str} F1: {f1_str}")
    
    # Best result
    best = results[0]
    lines.append("\n\n🥇 BEST OVERALL RESULT:")
    lines.append("-" * 60)
    lines.append(f"Experiment: {best['name']}")
    lines.append(f"AUC: {best['auc']:.4f}")
    if best['f1']:
        lines.append(f"F1@0.50: {best['f1']:.4f}")
    if best['accuracy']:
        lines.append(f"Accuracy: {best['accuracy']:.4f}")
    
    # Comparison to baselines
    lines.append("\n\n📊 COMPARISON TO DEVIGN BASELINE:")
    lines.append("-" * 60)
    
    devign_f1 = BASELINES["Devign (paper)"]["f1"] / 100  # Convert to 0-1 scale
    our_best_auc = best["auc"]
    our_best_f1 = best["f1"] or 0
    
    lines.append(f"Devign Paper F1: {devign_f1:.4f}")
    lines.append(f"Our Best AUC: {our_best_auc:.4f}")
    lines.append(f"Our Best F1: {our_best_f1:.4f}")
    
    if our_best_f1 > 0:
        gap = devign_f1 - our_best_f1
        lines.append(f"\nF1 Gap to Devign: {gap:.4f} ({gap*100:.1f}%)")
        
        if gap > 0.20:
            lines.append("\n⚠️  Significant gap remains. Consider:")
            lines.append("   - Using Word2Vec embeddings instead of transformer")
            lines.append("   - Per-project evaluation protocol")
            lines.append("   - Ensemble methods")
        elif gap > 0.10:
            lines.append("\n📈 Good progress! To close the gap:")
            lines.append("   - Hyperparameter tuning")
            lines.append("   - Ensemble of best models")
        else:
            lines.append("\n✅ Excellent! Close to/beating baseline!")
    
    lines.append("\n" + "=" * 100)
    
    return "\n".join(lines)


# ============================================================================
# MAIN
# ============================================================================

def main():
    parser = argparse.ArgumentParser(description="Compare experiment results")
    parser.add_argument("--results-dir", type=Path, default=Path("."),
                       help="Directory containing result files")
    parser.add_argument("--output", type=str, default=None,
                       help="Output file for report")
    parser.add_argument("--json", action="store_true",
                       help="Output as JSON")
    
    args = parser.parse_args()
    
    print("Collecting results...")
    results = collect_results(args.results_dir)
    print(f"Found {len(results)} results")
    
    if args.json:
        output = json.dumps(results, indent=2)
    else:
        output = generate_report(results)
    
    print(output)
    
    if args.output:
        with open(args.output, "w") as f:
            f.write(output)
        print(f"\nReport saved to: {args.output}")


if __name__ == "__main__":
    main()
