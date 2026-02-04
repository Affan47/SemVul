#!/usr/bin/env python3
"""
Vulnerability Pattern Diagnostic Tool

Analyzes:
1. CPG Structure Quality - Are vulnerability patterns captured?
2. Code String Quality - Do embeddings contain vulnerability signals?
3. Edge Type Distribution - Are data-flow edges present?
4. Vulnerable vs Safe Differences - What distinguishes them?

Usage:
    python vuln_pattern_diagnostic.py \
        --cache-dir /path/to/cache \
        --dataset-name word2vec_256d_full \
        --signature c95a4168d5a65be0 \
        --num-samples 500
"""

import argparse
import json
import csv
import zipfile
import io
from pathlib import Path
from collections import Counter, defaultdict
import numpy as np

try:
    import torch
    HAS_TORCH = True
except ImportError:
    HAS_TORCH = False

# Sensitive API patterns (vulnerability indicators)
SENSITIVE_APIS = {
    # Memory operations (buffer overflow)
    'memory': ['malloc', 'calloc', 'realloc', 'free', 'alloca', 
               'memcpy', 'memmove', 'memset', 'memcmp', 'memchr'],
    
    # String operations (buffer overflow)
    'string': ['strcpy', 'strncpy', 'strcat', 'strncat', 'strlen',
               'strcmp', 'strncmp', 'sprintf', 'snprintf', 'vsprintf',
               'gets', 'fgets', 'scanf', 'sscanf', 'fscanf'],
    
    # Format string
    'format': ['printf', 'fprintf', 'vprintf', 'syslog'],
    
    # File operations
    'file': ['fopen', 'fclose', 'fread', 'fwrite', 'open', 'close', 'read', 'write'],
    
    # Integer operations (overflow)
    'integer': ['atoi', 'atol', 'strtol', 'strtoul', 'strtoll'],
    
    # Dangerous functions
    'dangerous': ['system', 'exec', 'execve', 'popen', 'fork', 'eval'],
}

# Control structures relevant to vulnerabilities
CONTROL_PATTERNS = {
    'bounds_check': ['if', 'while', 'for'],  # Often missing in vulnerable code
    'null_check': ['NULL', 'nullptr', '== 0', '!= 0'],
    'size_check': ['sizeof', 'strlen', 'size', 'len', 'length'],
}


def load_samples(cache_path: Path, split: str, max_samples: int = None):
    """Load samples from cache."""
    split_path = cache_path / split
    index_path = split_path / "index.csv"
    
    if not index_path.exists():
        print(f"  Index not found: {index_path}")
        return []
    
    # Read index
    samples = []
    with open(index_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            samples.append({
                'function_id': row.get('function_id', ''),
                'label': int(row.get('label', 0)),
                'num_nodes': int(row.get('num_nodes', 0)),
                'num_edges': int(row.get('num_edges', 0)),
                'filename': row.get('filename', ''),
            })
    
    if max_samples:
        # Sample equally from both classes
        vuln = [s for s in samples if s['label'] == 1]
        safe = [s for s in samples if s['label'] == 0]
        
        n_each = max_samples // 2
        import random
        random.seed(42)
        samples = random.sample(vuln, min(n_each, len(vuln))) + \
                  random.sample(safe, min(n_each, len(safe)))
    
    return samples


def analyze_graph_structure(cache_path: Path, split: str, samples: list):
    """Analyze graph structure from cached PyG data."""
    if not HAS_TORCH:
        print("  PyTorch not available, skipping graph analysis")
        return {}
    
    split_path = cache_path / split
    zip_path = split_path / f"cache_{split}.zip"
    
    if not zip_path.exists():
        print(f"  Zip not found: {zip_path}")
        return {}
    
    stats = {
        'vuln': {'edge_types': Counter(), 'node_degrees': [], 'edge_counts': []},
        'safe': {'edge_types': Counter(), 'node_degrees': [], 'edge_counts': []},
    }
    
    sample_filenames = {s['filename']: s for s in samples}
    
    with zipfile.ZipFile(zip_path, 'r') as zf:
        for name in zf.namelist():
            if name not in sample_filenames:
                continue
            
            sample = sample_filenames[name]
            category = 'vuln' if sample['label'] == 1 else 'safe'
            
            try:
                with zf.open(name) as f:
                    buffer = io.BytesIO(f.read())
                    data = torch.load(buffer, map_location='cpu')
                
                # Edge type distribution
                if hasattr(data, 'edge_type') and data.edge_type is not None:
                    for et in data.edge_type.tolist():
                        stats[category]['edge_types'][et] += 1
                elif hasattr(data, 'edge_attr') and data.edge_attr is not None:
                    for et in data.edge_attr.tolist():
                        stats[category]['edge_types'][et] += 1
                
                # Node degrees
                if hasattr(data, 'edge_index'):
                    num_nodes = data.num_nodes
                    degrees = torch.zeros(num_nodes)
                    degrees.scatter_add_(0, data.edge_index[0], torch.ones(data.edge_index.shape[1]))
                    degrees.scatter_add_(0, data.edge_index[1], torch.ones(data.edge_index.shape[1]))
                    stats[category]['node_degrees'].extend(degrees.tolist())
                    stats[category]['edge_counts'].append(data.edge_index.shape[1])
                    
            except Exception as e:
                continue
    
    return stats


def analyze_code_patterns(strings_csv: Path, samples: list, max_strings: int = 10000):
    """Analyze code strings for vulnerability patterns."""
    if not strings_csv.exists():
        print(f"  Strings CSV not found: {strings_csv}")
        return {}
    
    # Build sample lookup
    sample_lookup = {s['function_id']: s['label'] for s in samples}
    
    stats = {
        'vuln': {cat: Counter() for cat in SENSITIVE_APIS},
        'safe': {cat: Counter() for cat in SENSITIVE_APIS},
    }
    stats['vuln']['control'] = Counter()
    stats['safe']['control'] = Counter()
    
    count = 0
    with open(strings_csv, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            if max_strings and count >= max_strings:
                break
            
            text = row.get('text', row.get('string', '')).lower()
            func_id = row.get('function_id', row.get('source', ''))
            
            # Try to match to sample
            label = None
            for sid, slabel in sample_lookup.items():
                if sid in func_id or func_id in sid:
                    label = slabel
                    break
            
            if label is None:
                continue
            
            category = 'vuln' if label == 1 else 'safe'
            
            # Check for sensitive APIs
            for api_cat, apis in SENSITIVE_APIS.items():
                for api in apis:
                    if api in text:
                        stats[category][api_cat][api] += 1
            
            # Check for control patterns
            for pattern in CONTROL_PATTERNS['bounds_check']:
                if pattern in text:
                    stats[category]['control'][pattern] += 1
            
            count += 1
    
    return stats


def compute_discriminative_power(vuln_counter: Counter, safe_counter: Counter) -> dict:
    """Compute how discriminative each feature is."""
    all_keys = set(vuln_counter.keys()) | set(safe_counter.keys())
    
    results = {}
    for key in all_keys:
        vuln_count = vuln_counter.get(key, 0)
        safe_count = safe_counter.get(key, 0)
        total = vuln_count + safe_count
        
        if total == 0:
            continue
        
        # Compute lift: how much more likely in vuln vs safe
        vuln_ratio = vuln_count / max(sum(vuln_counter.values()), 1)
        safe_ratio = safe_count / max(sum(safe_counter.values()), 1)
        
        if safe_ratio > 0:
            lift = vuln_ratio / safe_ratio
        else:
            lift = float('inf') if vuln_ratio > 0 else 1.0
        
        results[key] = {
            'vuln_count': vuln_count,
            'safe_count': safe_count,
            'total': total,
            'vuln_ratio': vuln_ratio,
            'safe_ratio': safe_ratio,
            'lift': lift,  # >1 means more common in vulnerable
        }
    
    return results


def print_analysis_report(graph_stats: dict, code_stats: dict):
    """Print comprehensive analysis report."""
    
    print("\n" + "=" * 80)
    print("VULNERABILITY PATTERN DIAGNOSTIC REPORT")
    print("=" * 80)
    
    # 1. Graph Structure Analysis
    if graph_stats:
        print("\n" + "-" * 80)
        print("1. GRAPH STRUCTURE ANALYSIS")
        print("-" * 80)
        
        # Edge type comparison
        print("\n  Edge Type Distribution (Vulnerable vs Safe):")
        print(f"  {'Edge Type':<12} {'Vuln Count':>12} {'Safe Count':>12} {'Lift':>10} {'Signal':<10}")
        print("  " + "-" * 60)
        
        edge_disc = compute_discriminative_power(
            graph_stats['vuln']['edge_types'],
            graph_stats['safe']['edge_types']
        )
        
        # Sort by lift (most discriminative first)
        sorted_edges = sorted(edge_disc.items(), key=lambda x: abs(x[1]['lift'] - 1), reverse=True)
        
        for edge_type, info in sorted_edges[:15]:
            lift = info['lift']
            if lift > 1.1:
                signal = "⬆️ VULN"
            elif lift < 0.9:
                signal = "⬇️ SAFE"
            else:
                signal = "→ NEUTRAL"
            
            print(f"  {edge_type:<12} {info['vuln_count']:>12,} {info['safe_count']:>12,} {lift:>10.2f} {signal:<10}")
        
        # Degree statistics
        if graph_stats['vuln']['node_degrees'] and graph_stats['safe']['node_degrees']:
            print("\n  Node Degree Statistics:")
            vuln_deg = np.array(graph_stats['vuln']['node_degrees'])
            safe_deg = np.array(graph_stats['safe']['node_degrees'])
            
            print(f"    Vulnerable - Mean: {vuln_deg.mean():.2f}, Median: {np.median(vuln_deg):.2f}, Max: {vuln_deg.max():.0f}")
            print(f"    Safe       - Mean: {safe_deg.mean():.2f}, Median: {np.median(safe_deg):.2f}, Max: {safe_deg.max():.0f}")
            
            if vuln_deg.mean() > safe_deg.mean() * 1.1:
                print("    ⚠️  Vulnerable code has higher connectivity (more edges)")
            elif safe_deg.mean() > vuln_deg.mean() * 1.1:
                print("    ⚠️  Safe code has higher connectivity")
            else:
                print("    ✓  Connectivity is similar between classes")
    
    # 2. Code Pattern Analysis
    if code_stats:
        print("\n" + "-" * 80)
        print("2. SENSITIVE API ANALYSIS")
        print("-" * 80)
        
        for category in SENSITIVE_APIS.keys():
            if category not in code_stats['vuln'] or category not in code_stats['safe']:
                continue
            
            disc = compute_discriminative_power(
                code_stats['vuln'][category],
                code_stats['safe'][category]
            )
            
            if not disc:
                continue
            
            print(f"\n  {category.upper()} APIs:")
            sorted_apis = sorted(disc.items(), key=lambda x: x[1]['lift'], reverse=True)
            
            for api, info in sorted_apis[:5]:
                lift = info['lift']
                if lift > 1.5:
                    marker = "🔴 HIGH SIGNAL"
                elif lift > 1.1:
                    marker = "🟡 MEDIUM"
                else:
                    marker = "⚪ LOW"
                
                print(f"    {api:<15} Vuln: {info['vuln_count']:>5}, Safe: {info['safe_count']:>5}, Lift: {lift:>6.2f} {marker}")
    
    # 3. Summary & Recommendations
    print("\n" + "-" * 80)
    print("3. KEY FINDINGS & RECOMMENDATIONS")
    print("-" * 80)
    
    findings = []
    
    # Check if sensitive APIs are discriminative
    if code_stats:
        all_api_lifts = []
        for cat in SENSITIVE_APIS.keys():
            if cat in code_stats['vuln']:
                disc = compute_discriminative_power(
                    code_stats['vuln'][cat],
                    code_stats['safe'][cat]
                )
                all_api_lifts.extend([info['lift'] for info in disc.values() if info['lift'] != float('inf')])
        
        if all_api_lifts:
            avg_lift = np.mean(all_api_lifts)
            max_lift = np.max(all_api_lifts)
            
            if avg_lift < 1.2:
                findings.append({
                    'issue': "LOW API DISCRIMINATION",
                    'detail': f"Average API lift = {avg_lift:.2f} (should be >1.3)",
                    'recommendation': "Sensitive APIs appear equally in vuln/safe code. "
                                    "The vulnerability may be in HOW they're used, not WHETHER they're used."
                })
            else:
                findings.append({
                    'issue': "GOOD API DISCRIMINATION",
                    'detail': f"Average API lift = {avg_lift:.2f}, Max = {max_lift:.2f}",
                    'recommendation': "APIs are discriminative. Ensure embeddings capture these patterns."
                })
    
    # Check edge type discrimination
    if graph_stats:
        edge_disc = compute_discriminative_power(
            graph_stats['vuln']['edge_types'],
            graph_stats['safe']['edge_types']
        )
        edge_lifts = [info['lift'] for info in edge_disc.values() if info['lift'] != float('inf')]
        
        if edge_lifts:
            max_edge_lift = max(edge_lifts)
            if max_edge_lift < 1.2:
                findings.append({
                    'issue': "EDGE TYPES NOT DISCRIMINATIVE",
                    'detail': f"Max edge type lift = {max_edge_lift:.2f}",
                    'recommendation': "Edge type distribution is similar. Focus on PATTERNS of edges, not types."
                })
    
    # Print findings
    for i, finding in enumerate(findings, 1):
        print(f"\n  [{i}] {finding['issue']}")
        print(f"      Detail: {finding['detail']}")
        print(f"      Action: {finding['recommendation']}")
    
    print("\n" + "=" * 80)


def main():
    parser = argparse.ArgumentParser(description="Vulnerability Pattern Diagnostic")
    parser.add_argument("--cache-dir", required=True, help="Cache directory")
    parser.add_argument("--dataset-name", required=True, help="Dataset name")
    parser.add_argument("--signature", required=True, help="Cache signature")
    parser.add_argument("--strings-csv", default=None, help="Path to strings_to_embed.csv")
    parser.add_argument("--num-samples", type=int, default=500, help="Number of samples to analyze")
    parser.add_argument("--output", default=None, help="Save results to JSON")
    args = parser.parse_args()
    
    cache_path = Path(args.cache_dir) / args.dataset_name / args.signature
    
    print("=" * 80)
    print("VULNERABILITY PATTERN DIAGNOSTIC")
    print("=" * 80)
    print(f"Cache: {cache_path}")
    print(f"Samples: {args.num_samples}")
    
    # Load samples
    print("\n[1/3] Loading samples...")
    samples = load_samples(cache_path, 'train', args.num_samples)
    print(f"  Loaded {len(samples)} samples")
    print(f"  Vulnerable: {sum(1 for s in samples if s['label'] == 1)}")
    print(f"  Safe: {sum(1 for s in samples if s['label'] == 0)}")
    
    # Analyze graph structure
    print("\n[2/3] Analyzing graph structure...")
    graph_stats = analyze_graph_structure(cache_path, 'train', samples)
    
    # Analyze code patterns
    print("\n[3/3] Analyzing code patterns...")
    code_stats = {}
    if args.strings_csv:
        code_stats = analyze_code_patterns(Path(args.strings_csv), samples)
    else:
        print("  Skipping (no --strings-csv provided)")
    
    # Print report
    print_analysis_report(graph_stats, code_stats)
    
    # Save results
    if args.output:
        results = {
            'num_samples': len(samples),
            'graph_stats': {
                'vuln_edge_types': dict(graph_stats.get('vuln', {}).get('edge_types', {})),
                'safe_edge_types': dict(graph_stats.get('safe', {}).get('edge_types', {})),
            },
            'code_stats': code_stats,
        }
        with open(args.output, 'w') as f:
            json.dump(results, f, indent=2, default=str)
        print(f"\nResults saved to: {args.output}")


if __name__ == "__main__":
    main()

"""
# Run diagnostic
python vuln_pattern_diagnostic.py \
    --cache-dir ./Clean_exports/cache_devign_v2 \
    --dataset-name word2vec_256d_full \
    --signature c95a4168d5a65be0 \
    --strings-csv ./Clean_exports/devign_vocab_full/strings_to_embed.csv\
    --num-samples 2000


"""    