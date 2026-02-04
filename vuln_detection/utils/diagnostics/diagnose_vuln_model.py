#!/usr/bin/env python3
"""
diagnose_vuln_model.py - Analyze Why Your Model is Failing

Handles various cache directory structures:
- Direct .pt files in split folders
- .pt files in subdirectories  
- .zip files containing .pt files
- Mixed structures
"""

import torch
import torch.nn.functional as F
import numpy as np
from pathlib import Path
from collections import defaultdict
from typing import List, Dict, Tuple, Optional
import json
import sys
import zipfile
import io

from torch_geometric.data import Data


def find_pt_files(directory: Path, max_depth: int = 3) -> List[Path]:
    """Recursively find all .pt files up to max_depth."""
    pt_files = []
    
    def search(path: Path, depth: int):
        if depth > max_depth:
            return
        try:
            for item in path.iterdir():
                if item.is_file() and item.suffix == ".pt":
                    pt_files.append(item)
                elif item.is_dir() and not item.name.startswith('.'):
                    search(item, depth + 1)
        except PermissionError:
            pass
    
    search(directory, 0)
    return pt_files


def find_zip_files(directory: Path, max_depth: int = 3) -> List[Path]:
    """Find all .zip files up to max_depth."""
    zip_files = []
    
    def search(path: Path, depth: int):
        if depth > max_depth:
            return
        try:
            for item in path.iterdir():
                if item.is_file() and item.suffix == ".zip":
                    zip_files.append(item)
                elif item.is_dir() and not item.name.startswith('.'):
                    search(item, depth + 1)
        except PermissionError:
            pass
    
    search(directory, 0)
    return zip_files


def load_from_pt_files(pt_files: List[Path], max_graphs: int) -> List[Data]:
    """Load PyG Data objects from .pt files."""
    graphs = []
    for pt_file in pt_files[:max_graphs]:
        try:
            data = torch.load(pt_file, weights_only=False)
            if hasattr(data, 'x') and hasattr(data, 'y'):
                graphs.append(data)
        except Exception as e:
            continue
    return graphs


def load_from_zip(zip_path: Path, max_graphs: int) -> List[Data]:
    """Load PyG Data objects from a zip archive."""
    graphs = []
    try:
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_names = [n for n in zf.namelist() if n.endswith('.pt')]
            print(f"  Found {len(pt_names)} .pt files in {zip_path.name}")
            
            for name in pt_names[:max_graphs]:
                try:
                    with zf.open(name) as f:
                        buffer = io.BytesIO(f.read())
                        data = torch.load(buffer, weights_only=False)
                        if hasattr(data, 'x') and hasattr(data, 'y'):
                            graphs.append(data)
                except Exception:
                    continue
    except Exception as e:
        print(f"  Error reading zip: {e}")
    return graphs


def load_cached_graphs(cache_dir: Path, split: str = "train", max_graphs: int = 1000) -> List[Data]:
    """
    Load PyG graphs from various directory structures.
    
    Tries:
    1. cache_dir/split/*.pt
    2. cache_dir/split/**/*.pt (recursive)
    3. cache_dir/split/*.zip
    4. cache_dir/**/*.zip (look for train/valid/test in zip)
    5. cache_dir (if split folders don't exist, search everything)
    """
    cache_dir = Path(cache_dir)
    graphs = []
    
    print(f"\nSearching for {split} data in: {cache_dir}")
    
    # Strategy 1: Direct split directory
    split_dir = cache_dir / split
    if split_dir.exists():
        print(f"  Found split directory: {split_dir}")
        
        # Look for .pt files
        pt_files = find_pt_files(split_dir)
        if pt_files:
            print(f"  Found {len(pt_files)} .pt files")
            graphs = load_from_pt_files(pt_files, max_graphs)
            if graphs:
                print(f"  Loaded {len(graphs)} graphs from .pt files")
                return graphs
        
        # Look for zip files
        zip_files = find_zip_files(split_dir)
        if zip_files:
            print(f"  Found {len(zip_files)} .zip files")
            for zf in zip_files:
                graphs.extend(load_from_zip(zf, max_graphs - len(graphs)))
                if len(graphs) >= max_graphs:
                    break
            if graphs:
                print(f"  Loaded {len(graphs)} graphs from zip files")
                return graphs
    
    # Strategy 2: Look in subdirectories with same name (double directory issue)
    for subdir in cache_dir.iterdir():
        if subdir.is_dir():
            nested_split = subdir / split
            if nested_split.exists():
                print(f"  Found nested split: {nested_split}")
                pt_files = find_pt_files(nested_split)
                if pt_files:
                    graphs = load_from_pt_files(pt_files, max_graphs)
                    if graphs:
                        print(f"  Loaded {len(graphs)} graphs")
                        return graphs
                
                zip_files = find_zip_files(nested_split)
                for zf in zip_files:
                    graphs.extend(load_from_zip(zf, max_graphs - len(graphs)))
                if graphs:
                    return graphs
    
    # Strategy 3: Search entire cache_dir
    print(f"  Searching entire directory...")
    
    # First try zip files
    all_zips = find_zip_files(cache_dir)
    # Prefer zips with split name
    split_zips = [z for z in all_zips if split in z.name.lower() or f"cache_{split}" in z.name.lower()]
    other_zips = [z for z in all_zips if z not in split_zips]
    
    for zf in split_zips + other_zips:
        print(f"  Trying zip: {zf}")
        graphs.extend(load_from_zip(zf, max_graphs - len(graphs)))
        if len(graphs) >= max_graphs:
            break
    
    if graphs:
        print(f"  Loaded {len(graphs)} graphs from zip files")
        return graphs
    
    # Finally try all .pt files
    all_pts = find_pt_files(cache_dir)
    if all_pts:
        print(f"  Found {len(all_pts)} .pt files total")
        graphs = load_from_pt_files(all_pts, max_graphs)
    
    print(f"  Total loaded: {len(graphs)} graphs")
    return graphs


def analyze_class_separability(graphs: List[Data]) -> Dict:
    """Analyze if vulnerable and safe graphs are separable."""
    
    vuln_features = []
    safe_features = []
    
    for g in graphs:
        feat = g.x.mean(dim=0).numpy()
        if g.y.item() == 1:
            vuln_features.append(feat)
        else:
            safe_features.append(feat)
    
    if not vuln_features or not safe_features:
        return {"error": "Need both classes", "vuln_count": len(vuln_features), "safe_count": len(safe_features)}
    
    vuln_features = np.array(vuln_features)
    safe_features = np.array(safe_features)
    
    vuln_mean = vuln_features.mean(axis=0)
    safe_mean = safe_features.mean(axis=0)
    
    # Cosine similarity between class centroids
    cosine_sim = np.dot(vuln_mean, safe_mean) / (np.linalg.norm(vuln_mean) * np.linalg.norm(safe_mean) + 1e-8)
    
    # Feature-wise difference
    diff = np.abs(vuln_mean - safe_mean)
    pooled_std = np.sqrt((vuln_features.std(axis=0)**2 + safe_features.std(axis=0)**2) / 2 + 1e-8)
    t_stats = diff / pooled_std
    
    discriminative_count = (t_stats > 2).sum()
    
    # Silhouette-like score
    all_features = np.vstack([vuln_features, safe_features])
    all_labels = np.array([1] * len(vuln_features) + [0] * len(safe_features))
    
    try:
        from sklearn.metrics import silhouette_score
        silhouette = silhouette_score(all_features, all_labels)
    except:
        silhouette = 0.0
    
    interpretation = []
    if silhouette < 0.1:
        interpretation.append("⚠️ CRITICAL: Silhouette < 0.1 - classes highly overlap!")
    if cosine_sim > 0.95:
        interpretation.append("⚠️ CRITICAL: Cosine > 0.95 - class centroids nearly identical!")
    if discriminative_count < all_features.shape[1] * 0.1:
        interpretation.append(f"⚠️ Only {discriminative_count}/{all_features.shape[1]} features discriminative!")
    if not interpretation:
        interpretation.append("✅ Features appear separable")
    
    return {
        "vuln_count": len(vuln_features),
        "safe_count": len(safe_features),
        "feature_dim": all_features.shape[1],
        "discriminative_features": int(discriminative_count),
        "cosine_similarity": float(cosine_sim),
        "silhouette_score": float(silhouette),
        "interpretation": "\n".join(interpretation)
    }


def analyze_graph_structure(graphs: List[Data]) -> Dict:
    """Analyze structural differences."""
    
    vuln_stats = defaultdict(list)
    safe_stats = defaultdict(list)
    
    for g in graphs:
        stats = vuln_stats if g.y.item() == 1 else safe_stats
        stats['num_nodes'].append(g.x.size(0))
        stats['num_edges'].append(g.edge_index.size(1))
        
        if hasattr(g, 'edge_attr') and g.edge_attr is not None:
            stats['unique_edge_types'].append(len(torch.unique(g.edge_attr)))
    
    def summarize(d):
        return {k: {"mean": np.mean(v), "std": np.std(v)} for k, v in d.items()}
    
    vuln_summary = summarize(vuln_stats) if vuln_stats else {}
    safe_summary = summarize(safe_stats) if safe_stats else {}
    
    differences = {}
    for key in vuln_summary:
        if key in safe_summary:
            v_mean = vuln_summary[key]['mean']
            s_mean = safe_summary[key]['mean']
            diff_pct = 100 * abs(v_mean - s_mean) / (max(v_mean, s_mean) + 1e-8)
            if diff_pct > 10:
                differences[key] = {"vuln": v_mean, "safe": s_mean, "diff_pct": diff_pct}
    
    return {
        "vuln": vuln_summary,
        "safe": safe_summary,
        "differences": differences,
        "interpretation": "✅ Structural differences found" if differences else "⚠️ No significant structural differences"
    }


def analyze_embeddings(graphs: List[Data]) -> Dict:
    """Analyze embedding quality."""
    
    all_x = torch.cat([g.x for g in graphs], dim=0).numpy()
    
    # Check for zero variance features
    variance = all_x.var(axis=0)
    zero_var = (variance < 1e-6).sum()
    
    # Check magnitude by class
    vuln_x = torch.cat([g.x for g in graphs if g.y.item() == 1], dim=0).numpy()
    safe_x = torch.cat([g.x for g in graphs if g.y.item() == 0], dim=0).numpy()
    
    vuln_mag = np.linalg.norm(vuln_x, axis=1).mean() if len(vuln_x) else 0
    safe_mag = np.linalg.norm(safe_x, axis=1).mean() if len(safe_x) else 0
    
    interpretation = []
    if zero_var > all_x.shape[1] * 0.3:
        interpretation.append(f"⚠️ {zero_var}/{all_x.shape[1]} features have zero variance!")
    if abs(vuln_mag - safe_mag) / (max(vuln_mag, safe_mag) + 1e-8) < 0.05:
        interpretation.append("⚠️ Vuln and safe have similar magnitude - no amplitude signal")
    if not interpretation:
        interpretation.append("✅ Embedding quality acceptable")
    
    return {
        "total_features": all_x.shape[1],
        "zero_variance": int(zero_var),
        "vuln_magnitude": float(vuln_mag),
        "safe_magnitude": float(safe_mag),
        "interpretation": "\n".join(interpretation)
    }


def visualize_embeddings(graphs: List[Data], output_path: Path):
    """Create t-SNE visualization."""
    try:
        from sklearn.manifold import TSNE
        import matplotlib
        matplotlib.use('Agg')
        import matplotlib.pyplot as plt
        
        embeddings = np.array([g.x.mean(dim=0).numpy() for g in graphs])
        labels = np.array([g.y.item() for g in graphs])
        
        print("  Computing t-SNE (this may take a moment)...")
        tsne = TSNE(n_components=2, random_state=42, perplexity=min(30, len(embeddings)-1))
        coords = tsne.fit_transform(embeddings)
        
        plt.figure(figsize=(10, 8))
        vuln_mask = labels == 1
        safe_mask = labels == 0
        
        plt.scatter(coords[safe_mask, 0], coords[safe_mask, 1], c='blue', alpha=0.5, label=f'Safe ({safe_mask.sum()})', s=20)
        plt.scatter(coords[vuln_mask, 0], coords[vuln_mask, 1], c='red', alpha=0.5, label=f'Vulnerable ({vuln_mask.sum()})', s=20)
        
        plt.xlabel('t-SNE 1')
        plt.ylabel('t-SNE 2')
        plt.title('Graph Embeddings (t-SNE)')
        plt.legend()
        plt.tight_layout()
        plt.savefig(output_path, dpi=150)
        plt.close()
        
        print(f"  Saved visualization to {output_path}")
    except ImportError as e:
        print(f"  Skipping visualization (missing dependency: {e})")
    except Exception as e:
        print(f"  Visualization failed: {e}")


def run_diagnosis(cache_dir: str, output_dir: str = "diagnostic_output", max_graphs: int = 2000):
    """Run full diagnostic analysis."""
    
    cache_path = Path(cache_dir)
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    print("\n" + "="*70)
    print("VULNERABILITY MODEL DIAGNOSTIC")
    print("="*70)
    
    # Load graphs
    print("\n[1/5] Loading cached graphs...")
    graphs = load_cached_graphs(cache_path, "train", max_graphs)
    
    if not graphs:
        # Try without split specification
        print("  Trying to load from root directory...")
        graphs = load_cached_graphs(cache_path, "", max_graphs)
    
    if not graphs:
        print("\n❌ ERROR: Could not load any graphs!")
        print("\nDebug info:")
        print(f"  Cache dir: {cache_path}")
        print(f"  Exists: {cache_path.exists()}")
        if cache_path.exists():
            print(f"  Contents: {list(cache_path.iterdir())[:10]}")
        return
    
    print(f"\n✅ Loaded {len(graphs)} graphs")
    
    # Check class balance
    vuln_count = sum(1 for g in graphs if g.y.item() == 1)
    safe_count = len(graphs) - vuln_count
    print(f"   Vulnerable: {vuln_count}, Safe: {safe_count}")
    
    # Analyze separability
    print("\n[2/5] Analyzing class separability...")
    separability = analyze_class_separability(graphs)
    print(f"   Cosine similarity: {separability.get('cosine_similarity', 'N/A'):.4f}")
    print(f"   Silhouette score: {separability.get('silhouette_score', 'N/A'):.4f}")
    print(f"   Discriminative features: {separability.get('discriminative_features', 'N/A')}/{separability.get('feature_dim', '?')}")
    print(f"   {separability.get('interpretation', '')}")
    
    # Analyze structure
    print("\n[3/5] Analyzing graph structure...")
    structure = analyze_graph_structure(graphs)
    if structure.get('vuln'):
        print(f"   Vuln avg nodes: {structure['vuln'].get('num_nodes', {}).get('mean', 0):.1f}")
        print(f"   Safe avg nodes: {structure['safe'].get('num_nodes', {}).get('mean', 0):.1f}")
    print(f"   {structure.get('interpretation', '')}")
    
    # Analyze embeddings
    print("\n[4/5] Analyzing embedding quality...")
    embedding = analyze_embeddings(graphs)
    print(f"   Feature dimension: {embedding.get('total_features', '?')}")
    print(f"   Zero variance features: {embedding.get('zero_variance', '?')}")
    print(f"   {embedding.get('interpretation', '')}")
    
    # Visualize
    print("\n[5/5] Creating visualization...")
    visualize_embeddings(graphs, output_path / "embeddings_tsne.png")
    
    # Save report
    report = {
        "num_graphs": len(graphs),
        "vuln_count": vuln_count,
        "safe_count": safe_count,
        "separability": {k: v for k, v in separability.items() if k != 'interpretation'},
        "structure": structure,
        "embedding": {k: v for k, v in embedding.items() if k != 'interpretation'},
    }
    
    with open(output_path / "diagnostic_report.json", "w") as f:
        json.dump(report, f, indent=2, default=str)
    
    # Print recommendations
    print("\n" + "="*70)
    print("RECOMMENDATIONS")
    print("="*70)
    
    if separability.get('cosine_similarity', 0) > 0.95:
        print("""
🔧 CRITICAL: Class centroids are nearly identical!
   Your embeddings don't distinguish vulnerable from safe code.
   
   Solutions:
   1. Use vulnerability-aware embeddings (VulBERTa, fine-tuned CodeBERT)
   2. Add explicit vulnerability features (sink detection, taint analysis)
   3. Try contrastive pre-training on (vulnerable, patched) pairs
""")
    
    if separability.get('silhouette_score', 0) < 0.1:
        print("""
🔧 CRITICAL: Classes heavily overlap in feature space!
   The model cannot learn to separate them.
   
   Solutions:
   1. Focus on LOCAL differences, not global averages
   2. Use attention to highlight vulnerability-relevant nodes
   3. Add domain-specific features (dangerous API calls, bounds checks)
""")
    
    if embedding.get('zero_variance', 0) > embedding.get('total_features', 1) * 0.3:
        print("""
🔧 Many features have zero variance!
   Check if embeddings are being loaded correctly.
   Check if one-hot encoding is dominating.
""")
    
    print(f"\n✅ Report saved to {output_path / 'diagnostic_report.json'}")
    print(f"✅ Visualization saved to {output_path / 'embeddings_tsne.png'}")


if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="Diagnose vulnerability model")
    parser.add_argument("--cache-dir", type=str, required=True)
    parser.add_argument("--output-dir", type=str, default="diagnostic_output")
    parser.add_argument("--max-graphs", type=int, default=2000)
    
    args = parser.parse_args()
    run_diagnosis(args.cache_dir, args.output_dir, args.max_graphs)

"""
python diagnose_vuln_model.py \
    --cache-dir "./Clean_exports/cache_devign_v2/graphcodebert_256d_full_filtered" \
    --output-dir "graphcodebert_256d_full_filtered" 


"""    