#!/usr/bin/env python3
"""
quick_diagnosis.py - Fast check for the most likely culprits causing ~50% precision

This script gives you QUICK answers about why your model isn't learning.
Runs in < 1 minute and checks the TOP 5 most likely causes.

Usage:
    python quick_diagnosis.py \
        --embedding-db /path/to/word2vec_embeddings.sqlite \
        --cache-dir /path/to/cache/train/signature
"""

import argparse
import hashlib
import sqlite3
import sys
from collections import Counter
from pathlib import Path
import numpy as np

try:
    import torch
    HAS_TORCH = True
except ImportError:
    HAS_TORCH = False
    print("ERROR: torch required")
    sys.exit(1)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--embedding-db", required=True)
    parser.add_argument("--cache-dir", required=True)
    args = parser.parse_args()
    
    print("=" * 70)
    print("QUICK DIAGNOSIS - Finding why precision is ~50%")
    print("=" * 70)
    
    issues = []
    
    # =========================================================================
    # CHECK 1: Are embeddings all the same? (COLLAPSED Word2Vec)
    # =========================================================================
    print("\n🔍 CHECK 1: Embedding Diversity (are they all the same?)")
    
    conn = sqlite3.connect(args.embedding_db)
    cur = conn.cursor()
    
    cur.execute("SELECT vec FROM embeddings ORDER BY RANDOM() LIMIT 100")
    rows = cur.fetchall()
    
    embeddings = [np.frombuffer(r[0], dtype=np.float32) for r in rows if r[0]]
    
    if len(embeddings) < 2:
        print("   ❌ Not enough embeddings!")
        issues.append("Empty or nearly empty embedding database")
    else:
        # Compute pairwise similarities
        sims = []
        for i in range(min(50, len(embeddings))):
            for j in range(i+1, min(50, len(embeddings))):
                e1, e2 = embeddings[i], embeddings[j]
                n1, n2 = np.linalg.norm(e1), np.linalg.norm(e2)
                if n1 > 0 and n2 > 0:
                    sim = np.dot(e1, e2) / (n1 * n2)
                    sims.append(sim)
        
        if sims:
            avg_sim = np.mean(sims)
            print(f"   Average cosine similarity between random embeddings: {avg_sim:.4f}")
            
            if avg_sim > 0.95:
                print("   ❌ CRITICAL: Embeddings are >95% similar!")
                print("   ➡️  Word2Vec COLLAPSED - all tokens have nearly identical vectors!")
                issues.append("COLLAPSED EMBEDDINGS - all embeddings are nearly identical")
            elif avg_sim > 0.8:
                print("   ⚠️  WARNING: High similarity (>80%)")
                issues.append("High embedding similarity")
            else:
                print("   ✅ Embeddings have good diversity")
    
    conn.close()
    
    # =========================================================================
    # CHECK 2: Are embeddings being used? (check .pt files)
    # =========================================================================
    print("\n🔍 CHECK 2: Are embeddings actually being used in cached files?")
    
    cache_dir = Path(args.cache_dir)
    pt_files = list(cache_dir.rglob("*.pt"))[:50]
    
    if not pt_files:
        print("   ❌ No .pt files found!")
        issues.append("No cached .pt files")
    else:
        total_nodes = 0
        zero_embedding_nodes = 0
        
        for pt_path in pt_files:
            data = torch.load(pt_path, map_location='cpu', weights_only=False)
            if hasattr(data, 'x') and data.x is not None:
                x = data.x.float()
                total_nodes += x.shape[0]
                
                # Check embedding part (after first 28 dims which are one-hot)
                if x.shape[1] > 28:
                    emb_part = x[:, 28:]
                    zero_rows = (emb_part == 0).all(dim=1).sum().item()
                    zero_embedding_nodes += zero_rows
        
        if total_nodes > 0:
            zero_pct = 100 * zero_embedding_nodes / total_nodes
            print(f"   Nodes with ZERO embeddings: {zero_embedding_nodes}/{total_nodes} ({zero_pct:.1f}%)")
            
            if zero_pct > 80:
                print("   ❌ CRITICAL: >80% of nodes have ZERO embeddings!")
                print("   ➡️  Embeddings are NOT being retrieved - SHA256 mismatch?")
                issues.append("ZERO EMBEDDINGS - >80% nodes have zero embedding vectors")
            elif zero_pct > 50:
                print("   ⚠️  WARNING: >50% zero embeddings")
                issues.append("High percentage of zero embeddings")
            else:
                print("   ✅ Most nodes have embeddings")
    
    # =========================================================================
    # CHECK 3: Do features separate classes?
    # =========================================================================
    print("\n🔍 CHECK 3: Do features separate vulnerable vs non-vulnerable code?")
    
    features_by_label = {0: [], 1: []}
    
    for pt_path in pt_files:
        data = torch.load(pt_path, map_location='cpu', weights_only=False)
        if hasattr(data, 'x') and hasattr(data, 'y'):
            x = data.x.float()
            y = int(data.y.item()) if data.y.dim() == 0 else int(data.y[0].item())
            
            # Graph-level mean
            graph_feat = x.mean(dim=0).numpy()
            if np.all(np.isfinite(graph_feat)) and y in features_by_label:
                features_by_label[y].append(graph_feat)
    
    if len(features_by_label[0]) > 5 and len(features_by_label[1]) > 5:
        feat_0 = np.array(features_by_label[0])
        feat_1 = np.array(features_by_label[1])
        
        mean_0 = feat_0.mean(axis=0)
        mean_1 = feat_1.mean(axis=0)
        
        # Cosine similarity between class means
        n0, n1 = np.linalg.norm(mean_0), np.linalg.norm(mean_1)
        if n0 > 0 and n1 > 0:
            class_sim = np.dot(mean_0, mean_1) / (n0 * n1)
            print(f"   Cosine similarity between class means: {class_sim:.4f}")
            
            if class_sim > 0.999:
                print("   ❌ CRITICAL: Classes have IDENTICAL mean features!")
                print("   ➡️  Model CANNOT distinguish vulnerable from non-vulnerable!")
                issues.append("IDENTICAL CLASS MEANS - features don't separate classes")
            elif class_sim > 0.99:
                print("   ⚠️  WARNING: Very high class similarity")
                issues.append("Very high class similarity")
            else:
                print("   ✅ Classes have different mean features")
        
        # Euclidean distance
        eucl = np.linalg.norm(mean_0 - mean_1)
        print(f"   Euclidean distance between class means: {eucl:.4f}")
        
        if eucl < 0.01:
            print("   ❌ Near-zero distance - features identical!")
    else:
        print("   ⚠️  Not enough samples per class")
    
    # =========================================================================
    # CHECK 4: Label distribution
    # =========================================================================
    print("\n🔍 CHECK 4: Label distribution")
    
    labels = []
    for pt_path in pt_files:
        data = torch.load(pt_path, map_location='cpu', weights_only=False)
        if hasattr(data, 'y'):
            y = int(data.y.item()) if data.y.dim() == 0 else int(data.y[0].item())
            labels.append(y)
    
    if labels:
        counts = Counter(labels)
        print(f"   Label distribution: {dict(counts)}")
        
        if len(counts) == 1:
            print("   ❌ CRITICAL: Only ONE class in data!")
            issues.append("SINGLE CLASS - all samples have same label")
        elif len(counts) == 2:
            vals = list(counts.values())
            ratio = max(vals) / min(vals)
            print(f"   Class ratio: {ratio:.1f}:1")
            if ratio > 10:
                print("   ⚠️  Severe class imbalance")
    
    # =========================================================================
    # CHECK 5: Basic code tokens in embedding DB
    # =========================================================================
    print("\n🔍 CHECK 5: Do embeddings contain basic code tokens?")
    
    conn = sqlite3.connect(args.embedding_db)
    cur = conn.cursor()
    
    basic_tokens = ["int", "return", "if", "else", "for", "void", "char", "NULL", "malloc"]
    found = 0
    
    for token in basic_tokens:
        sha = hashlib.sha256(token.encode('utf-8')).hexdigest()
        cur.execute("SELECT COUNT(*) FROM embeddings WHERE sha256 = ?", (sha,))
        if cur.fetchone()[0] > 0:
            found += 1
    
    conn.close()
    
    print(f"   Basic tokens found: {found}/{len(basic_tokens)}")
    if found < len(basic_tokens) / 2:
        print("   ❌ Most basic C tokens missing!")
        print("   ➡️  Word2Vec may have different tokenization")
        issues.append("MISSING BASIC TOKENS - tokenization mismatch")
    else:
        print("   ✅ Basic tokens present")
    
    # =========================================================================
    # SUMMARY
    # =========================================================================
    print("\n" + "=" * 70)
    print("DIAGNOSIS SUMMARY")
    print("=" * 70)
    
    if not issues:
        print("\n✅ No obvious issues found. Check:")
        print("   - Training hyperparameters (learning rate too high?)")
        print("   - Model architecture")
        print("   - Run full deep_debug_pipeline.py for more analysis")
    else:
        print(f"\n❌ Found {len(issues)} issue(s):\n")
        for i, issue in enumerate(issues, 1):
            print(f"   {i}. {issue}")
        
        print("\n" + "=" * 70)
        print("RECOMMENDED FIXES (in order of priority):")
        print("=" * 70)
        
        if any("COLLAPSED" in i for i in issues):
            print("""
1. 🔴 RETRAIN WORD2VEC
   Your Word2Vec embeddings collapsed - all tokens have the same vector!
   This happens when:
   - Training corpus too small
   - min_count too high
   - Not enough epochs
   
   FIX: Retrain with larger corpus and better parameters:
   python train_word2vec.py \\
       --input-csv /path/to/strings_to_embed.csv \\
       --output-model /path/to/new_word2vec \\
       --dim 128 --min-count 1 --epochs 15 --window 10
""")
        
        if any("ZERO EMBEDDINGS" in i for i in issues):
            print("""
2. 🔴 FIX SHA256 MISMATCH
   Embeddings exist but aren't being looked up correctly.
   The SHA256 hash computation differs between:
   - vocab_builder.py (creating strings_to_embed.csv)
   - multi_extractor.py (storing embeddings in SQLite)
   - cache_manager.py (looking up embeddings)
   
   FIX: Ensure identical normalization everywhere:
   - Check normalize_for_embedding() function
   - Verify sha256_normalized() matches
""")
        
        if any("IDENTICAL CLASS" in i for i in issues):
            print("""
3. 🔴 FEATURES DON'T DISCRIMINATE
   Vulnerable and non-vulnerable code have identical features.
   This could be because:
   - Embeddings are all zeros or all the same
   - Labels are randomly assigned
   - One-hot features dominate (and don't vary)
   
   FIX: 
   - First fix embedding issues above
   - Verify labels are correct in manifest files
   - Try using ONLY one-hot features first (no embeddings)
""")


if __name__ == "__main__":
    main()


"""
python quick_diagnosis.py \
    --embedding-db "./Clean_exports/cache_devign_v2/word2vec_embeddings.sqlite" \
    --cache-dir "./Clean_exports/cache_devign_v2/word2vec128/train/eabf47f3e60df24e"

"""    