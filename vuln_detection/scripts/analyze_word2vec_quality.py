#!/usr/bin/env python3
"""
analyze_word2vec_quality.py - Deep analysis of Word2Vec embedding quality

This script specifically analyzes Word2Vec embeddings to determine if they're
suitable for vulnerability detection. It checks:

1. Vocabulary coverage of code tokens
2. Embedding distribution and quality
3. Semantic relationships (do similar tokens have similar embeddings?)
4. Token frequency vs embedding quality correlation
5. Comparison with expected code semantics

Usage:
    python analyze_word2vec_quality.py \
        --embedding-db /path/to/word2vec_embeddings.sqlite \
        --strings-csv /path/to/strings_to_embed.csv \
        --word2vec-model /path/to/code_word2vec.bin  # Optional: if you have the .bin file
"""

import argparse
import csv
import hashlib
import sqlite3
import sys
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

import numpy as np

try:
    from gensim.models import KeyedVectors
    HAS_GENSIM = True
except ImportError:
    HAS_GENSIM = False


class Word2VecAnalyzer:
    """Analyze Word2Vec embedding quality for code."""
    
    def __init__(self, args):
        self.args = args
        self.issues = []
        self.warnings = []
        self.stats = {}
        
    def log(self, msg: str, level: str = "INFO"):
        prefix = {"INFO": "ℹ️ ", "WARN": "⚠️ ", "ERROR": "❌", "OK": "✅", "DEBUG": "🔍"}
        print(f"{prefix.get(level, '')}[{level}] {msg}")
        if level == "ERROR":
            self.issues.append(msg)
        elif level == "WARN":
            self.warnings.append(msg)
    
    def section(self, title: str):
        print(f"\n{'='*70}\n{title}\n{'='*70}")
    
    # =========================================================================
    # 1. Basic SQLite Analysis
    # =========================================================================
    
    def analyze_sqlite_basics(self):
        """Basic SQLite embedding analysis."""
        self.section("1. SQLITE EMBEDDING DATABASE ANALYSIS")
        
        db_path = Path(self.args.embedding_db)
        if not db_path.exists():
            self.log(f"Database not found: {db_path}", "ERROR")
            return False
        
        self.log(f"Database: {db_path}")
        self.log(f"Size: {db_path.stat().st_size / 1024 / 1024:.2f} MB")
        
        conn = sqlite3.connect(str(db_path))
        cur = conn.cursor()
        
        # Count embeddings
        cur.execute("SELECT COUNT(*) FROM embeddings")
        total = cur.fetchone()[0]
        self.log(f"Total embeddings: {total:,}")
        self.stats["total_embeddings"] = total
        
        if total == 0:
            self.log("Database is EMPTY!", "ERROR")
            conn.close()
            return False
        
        # Get dimension
        cur.execute("SELECT vec FROM embeddings LIMIT 1")
        row = cur.fetchone()
        dim = len(row[0]) // 4
        self.log(f"Embedding dimension: {dim}")
        self.stats["dimension"] = dim
        
        conn.close()
        return True
    
    # =========================================================================
    # 2. Embedding Value Distribution Analysis
    # =========================================================================
    
    def analyze_embedding_distribution(self):
        """Analyze the distribution of embedding values."""
        self.section("2. EMBEDDING VALUE DISTRIBUTION")
        
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        
        # Sample embeddings
        cur.execute("SELECT vec FROM embeddings ORDER BY RANDOM() LIMIT 5000")
        rows = cur.fetchall()
        
        all_values = []
        embedding_norms = []
        zero_count = 0
        extreme_count = 0
        
        for row in rows:
            emb = np.frombuffer(row[0], dtype=np.float32)
            
            # Check for issues
            if np.all(emb == 0):
                zero_count += 1
                continue
            
            if np.any(np.abs(emb) > 100):
                extreme_count += 1
            
            # Collect stats
            norm = np.linalg.norm(emb)
            embedding_norms.append(norm)
            all_values.extend(emb.tolist())
        
        conn.close()
        
        # Report
        self.log(f"Sampled {len(rows)} embeddings")
        self.log(f"  Zero embeddings: {zero_count} ({100*zero_count/len(rows):.1f}%)")
        self.log(f"  Extreme value embeddings: {extreme_count} ({100*extreme_count/len(rows):.1f}%)")
        
        if all_values:
            arr = np.array(all_values)
            
            # Percentiles
            p1, p5, p50, p95, p99 = np.percentile(arr, [1, 5, 50, 95, 99])
            
            self.log(f"\nValue distribution:")
            self.log(f"  Range: [{arr.min():.4f}, {arr.max():.4f}]")
            self.log(f"  Mean: {arr.mean():.4f}, Std: {arr.std():.4f}")
            self.log(f"  Percentiles: 1%={p1:.4f}, 5%={p5:.4f}, 50%={p50:.4f}, 95%={p95:.4f}, 99%={p99:.4f}")
            
            self.stats["value_mean"] = float(arr.mean())
            self.stats["value_std"] = float(arr.std())
            
            # Check for issues
            if arr.std() < 0.01:
                self.log("CRITICAL: Very low variance in embeddings!", "ERROR")
            
            if abs(arr.mean()) > 1:
                self.log("Embedding mean far from 0 - consider centering", "WARN")
        
        if embedding_norms:
            norms = np.array(embedding_norms)
            self.log(f"\nEmbedding norms:")
            self.log(f"  Range: [{norms.min():.4f}, {norms.max():.4f}]")
            self.log(f"  Mean: {norms.mean():.4f}, Std: {norms.std():.4f}")
            
            if norms.std() / norms.mean() < 0.1:
                self.log("Embedding norms very uniform - might indicate collapsed training", "WARN")
    
    # =========================================================================
    # 3. Embedding Similarity Analysis
    # =========================================================================
    
    def analyze_embedding_similarity(self):
        """Check if random embeddings are too similar (collapsed)."""
        self.section("3. EMBEDDING SIMILARITY ANALYSIS")
        
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        
        cur.execute("SELECT sha256, vec FROM embeddings ORDER BY RANDOM() LIMIT 200")
        rows = cur.fetchall()
        conn.close()
        
        embeddings = []
        for sha, vec in rows:
            emb = np.frombuffer(vec, dtype=np.float32)
            if not np.all(emb == 0) and np.all(np.isfinite(emb)):
                embeddings.append(emb)
        
        if len(embeddings) < 10:
            self.log("Not enough valid embeddings for similarity analysis", "WARN")
            return
        
        self.log(f"Computing pairwise similarities for {len(embeddings)} embeddings...")
        
        # Compute pairwise cosine similarities
        similarities = []
        for i in range(min(100, len(embeddings))):
            for j in range(i+1, min(100, len(embeddings))):
                e1, e2 = embeddings[i], embeddings[j]
                n1, n2 = np.linalg.norm(e1), np.linalg.norm(e2)
                if n1 > 0 and n2 > 0:
                    sim = np.dot(e1, e2) / (n1 * n2)
                    similarities.append(sim)
        
        if similarities:
            sims = np.array(similarities)
            
            self.log(f"\nPairwise cosine similarities:")
            self.log(f"  Range: [{sims.min():.4f}, {sims.max():.4f}]")
            self.log(f"  Mean: {sims.mean():.4f}")
            self.log(f"  Std: {sims.std():.4f}")
            
            self.stats["avg_pairwise_similarity"] = float(sims.mean())
            
            # Histogram
            hist = np.histogram(sims, bins=10, range=(-1, 1))
            self.log(f"\nSimilarity histogram:")
            for i in range(len(hist[0])):
                lo, hi = hist[1][i], hist[1][i+1]
                count = hist[0][i]
                bar = "█" * (count // 10) if count > 0 else ""
                self.log(f"  [{lo:+.1f}, {hi:+.1f}]: {count:4d} {bar}")
            
            # Check for problems
            if sims.mean() > 0.9:
                self.log("CRITICAL: Embeddings are >90% similar on average!", "ERROR")
                self.log("This means Word2Vec collapsed - all tokens have nearly identical vectors!", "ERROR")
            elif sims.mean() > 0.7:
                self.log("High average similarity - embeddings may not be discriminative", "WARN")
            elif sims.mean() < 0.1:
                self.log("Good diversity in embeddings", "OK")
    
    # =========================================================================
    # 4. Code Token Coverage Analysis
    # =========================================================================
    
    def analyze_code_token_coverage(self):
        """Check coverage of important code tokens."""
        self.section("4. CODE TOKEN COVERAGE")
        
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        
        # Common C/C++ tokens that MUST be in vocabulary
        essential_tokens = [
            # Keywords
            "int", "char", "void", "return", "if", "else", "for", "while", "do",
            "switch", "case", "break", "continue", "struct", "typedef", "enum",
            "const", "static", "extern", "sizeof", "unsigned", "signed", "long",
            "short", "float", "double", "NULL", "nullptr",
            
            # Common function names
            "main", "printf", "scanf", "malloc", "free", "memcpy", "memset",
            "strcpy", "strlen", "strcmp", "fopen", "fclose", "fread", "fwrite",
            
            # Common variables/patterns
            "i", "j", "k", "n", "len", "size", "count", "ptr", "buf", "str",
            "ret", "err", "result", "data", "tmp", "temp",
            
            # Operators as tokens
            "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=",
            "&&", "||", "!", "&", "|", "^", "~", "<<", ">>",
        ]
        
        found = []
        not_found = []
        
        for token in essential_tokens:
            # Try different hash methods
            sha_raw = hashlib.sha256(token.encode('utf-8')).hexdigest()
            sha_lower = hashlib.sha256(token.lower().encode('utf-8')).hexdigest()
            
            cur.execute("SELECT COUNT(*) FROM embeddings WHERE sha256 = ? OR sha256 = ?",
                       (sha_raw, sha_lower))
            count = cur.fetchone()[0]
            
            if count > 0:
                found.append(token)
            else:
                not_found.append(token)
        
        conn.close()
        
        coverage = 100 * len(found) / len(essential_tokens)
        self.log(f"Essential token coverage: {len(found)}/{len(essential_tokens)} ({coverage:.1f}%)")
        self.stats["essential_token_coverage"] = coverage
        
        if found:
            self.log(f"Found: {found[:20]}{'...' if len(found) > 20 else ''}")
        
        if not_found:
            self.log(f"Missing: {not_found[:20]}{'...' if len(not_found) > 20 else ''}", "WARN")
        
        if coverage < 50:
            self.log("CRITICAL: Less than 50% essential token coverage!", "ERROR")
            self.log("Word2Vec was probably trained on different tokenization!", "ERROR")
        elif coverage < 80:
            self.log("Low coverage - consider retraining Word2Vec", "WARN")
        else:
            self.log("Good essential token coverage", "OK")
    
    # =========================================================================
    # 5. Semantic Relationship Check
    # =========================================================================
    
    def check_semantic_relationships(self):
        """Check if semantically similar tokens have similar embeddings."""
        self.section("5. SEMANTIC RELATIONSHIP CHECK")
        
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        
        def get_embedding(token: str) -> Optional[np.ndarray]:
            sha = hashlib.sha256(token.encode('utf-8')).hexdigest()
            cur.execute("SELECT vec FROM embeddings WHERE sha256 = ?", (sha,))
            row = cur.fetchone()
            if row:
                return np.frombuffer(row[0], dtype=np.float32)
            return None
        
        def cosine_sim(e1: np.ndarray, e2: np.ndarray) -> float:
            n1, n2 = np.linalg.norm(e1), np.linalg.norm(e2)
            if n1 > 0 and n2 > 0:
                return float(np.dot(e1, e2) / (n1 * n2))
            return 0.0
        
        # Token pairs that SHOULD be similar
        similar_pairs = [
            ("int", "long"),
            ("char", "unsigned"),
            ("malloc", "free"),
            ("fopen", "fclose"),
            ("strcpy", "strncpy"),
            ("printf", "fprintf"),
            ("if", "else"),
            ("for", "while"),
            ("++", "--"),
            ("==", "!="),
        ]
        
        # Token pairs that should be DIFFERENT
        different_pairs = [
            ("int", "printf"),
            ("malloc", "if"),
            ("for", "return"),
            ("char", "fopen"),
            ("NULL", "while"),
        ]
        
        self.log("Checking similar token pairs (should have high similarity):")
        similar_sims = []
        for t1, t2 in similar_pairs:
            e1, e2 = get_embedding(t1), get_embedding(t2)
            if e1 is not None and e2 is not None:
                sim = cosine_sim(e1, e2)
                similar_sims.append(sim)
                self.log(f"  {t1} <-> {t2}: {sim:.4f}")
            else:
                self.log(f"  {t1} <-> {t2}: MISSING", "DEBUG")
        
        self.log("\nChecking different token pairs (should have lower similarity):")
        different_sims = []
        for t1, t2 in different_pairs:
            e1, e2 = get_embedding(t1), get_embedding(t2)
            if e1 is not None and e2 is not None:
                sim = cosine_sim(e1, e2)
                different_sims.append(sim)
                self.log(f"  {t1} <-> {t2}: {sim:.4f}")
            else:
                self.log(f"  {t1} <-> {t2}: MISSING", "DEBUG")
        
        conn.close()
        
        # Analysis
        if similar_sims and different_sims:
            avg_similar = np.mean(similar_sims)
            avg_different = np.mean(different_sims)
            
            self.log(f"\nAverage similarity (should-be-similar pairs): {avg_similar:.4f}")
            self.log(f"Average similarity (should-be-different pairs): {avg_different:.4f}")
            self.log(f"Difference: {avg_similar - avg_different:.4f}")
            
            if avg_similar - avg_different < 0.1:
                self.log("CRITICAL: No semantic structure in embeddings!", "ERROR")
                self.log("Similar and different tokens have same similarity!", "ERROR")
            elif avg_similar < avg_different:
                self.log("INVERTED: Different pairs more similar than similar pairs!", "ERROR")
            elif avg_similar - avg_different < 0.2:
                self.log("Weak semantic structure", "WARN")
            else:
                self.log("Good semantic structure", "OK")
    
    # =========================================================================
    # 6. Vocabulary Overlap Analysis
    # =========================================================================
    
    def analyze_vocab_overlap(self):
        """Analyze overlap between strings_to_embed and embedding DB."""
        self.section("6. VOCABULARY OVERLAP ANALYSIS")
        
        if not self.args.strings_csv or not Path(self.args.strings_csv).exists():
            self.log("strings_csv not provided, skipping", "WARN")
            return
        
        # Load DB hashes
        conn = sqlite3.connect(str(self.args.embedding_db))
        cur = conn.cursor()
        cur.execute("SELECT sha256 FROM embeddings")
        db_hashes = set(row[0] for row in cur.fetchall())
        conn.close()
        
        self.log(f"Hashes in embedding DB: {len(db_hashes):,}")
        
        # Check strings_to_embed
        matched = 0
        total = 0
        sample_unmatched = []
        
        with open(self.args.strings_csv, 'r', encoding='utf-8', errors='ignore') as f:
            reader = csv.DictReader(f)
            
            for row in reader:
                text = row.get('text', '') or row.get('string', '')
                if not text.strip():
                    continue
                
                total += 1
                
                # Try different normalizations
                sha = hashlib.sha256(text.encode('utf-8', errors='ignore')).hexdigest()
                
                if sha in db_hashes:
                    matched += 1
                elif len(sample_unmatched) < 20:
                    sample_unmatched.append(text[:30])
                
                if total >= 100000:
                    break
        
        if total > 0:
            overlap = 100 * matched / total
            self.log(f"\nVocabulary overlap: {matched:,}/{total:,} ({overlap:.1f}%)")
            self.stats["vocab_overlap_pct"] = overlap
            
            if overlap < 50:
                self.log("CRITICAL: Less than 50% overlap!", "ERROR")
                self.log("Most vocabulary strings don't have embeddings!", "ERROR")
                
                if sample_unmatched:
                    self.log(f"Sample unmatched: {sample_unmatched[:10]}", "DEBUG")
            elif overlap < 80:
                self.log("Low overlap - many fallback zeros", "WARN")
            else:
                self.log("Good vocabulary overlap", "OK")
    
    # =========================================================================
    # 7. Word2Vec Model File Analysis (if available)
    # =========================================================================
    
    def analyze_word2vec_model(self):
        """Analyze the Word2Vec model file directly."""
        self.section("7. WORD2VEC MODEL FILE ANALYSIS")
        
        if not self.args.word2vec_model:
            self.log("No Word2Vec model file provided", "INFO")
            return
        
        model_path = Path(self.args.word2vec_model)
        if not model_path.exists():
            self.log(f"Model file not found: {model_path}", "WARN")
            return
        
        if not HAS_GENSIM:
            self.log("gensim not installed, skipping model analysis", "WARN")
            return
        
        self.log(f"Loading Word2Vec model: {model_path}")
        
        try:
            if model_path.suffix == ".bin":
                wv = KeyedVectors.load_word2vec_format(str(model_path), binary=True, 
                                                       unicode_errors='ignore')
            else:
                wv = KeyedVectors.load_word2vec_format(str(model_path), binary=False,
                                                       unicode_errors='ignore')
        except Exception as e:
            self.log(f"Error loading model: {e}", "ERROR")
            return
        
        self.log(f"Vocabulary size: {len(wv):,}")
        self.log(f"Embedding dimension: {wv.vector_size}")
        
        # Top words
        self.log(f"\nTop 20 most frequent tokens:")
        for i, word in enumerate(wv.index_to_key[:20]):
            self.log(f"  {i+1}. '{word}'")
        
        # Check for code tokens
        code_tokens = ["int", "return", "if", "for", "void", "char", "NULL"]
        found_code = [t for t in code_tokens if t in wv]
        self.log(f"\nCode tokens found: {len(found_code)}/{len(code_tokens)}")
        
        if len(found_code) < len(code_tokens) / 2:
            self.log("Many basic code tokens missing from vocabulary!", "WARN")
        
        # Most similar test
        if "int" in wv:
            self.log("\nMost similar to 'int':")
            try:
                similar = wv.most_similar("int", topn=5)
                for word, score in similar:
                    self.log(f"  {word}: {score:.4f}")
            except Exception as e:
                self.log(f"Error: {e}", "DEBUG")
    
    # =========================================================================
    # 8. Summary
    # =========================================================================
    
    def generate_summary(self):
        """Generate final summary."""
        self.section("SUMMARY")
        
        self.log(f"\nCritical Issues: {len(self.issues)}")
        for issue in self.issues:
            self.log(f"  ❌ {issue}")
        
        self.log(f"\nWarnings: {len(self.warnings)}")
        for warn in self.warnings:
            self.log(f"  ⚠️ {warn}")
        
        self.log("\nKey Statistics:")
        for k, v in self.stats.items():
            self.log(f"  {k}: {v}")
        
        # Recommendations
        self.log("\n" + "=" * 70)
        self.log("DIAGNOSIS:")
        self.log("=" * 70)
        
        if self.stats.get("avg_pairwise_similarity", 0) > 0.8:
            self.log("\n🔴 WORD2VEC COLLAPSED!")
            self.log("All embeddings are nearly identical. This happens when:")
            self.log("  1. Training corpus was too small")
            self.log("  2. min_count was too high (filtering out most words)")
            self.log("  3. Training epochs were too few")
            self.log("  4. Window size was inappropriate")
            self.log("\nFIX: Retrain Word2Vec with:")
            self.log("  - Larger corpus (all code files)")
            self.log("  - min_count=1 or 2")
            self.log("  - epochs=10-20")
            self.log("  - window=5-10")
        
        if self.stats.get("vocab_overlap_pct", 100) < 50:
            self.log("\n🔴 SHA256 MISMATCH!")
            self.log("Embeddings exist but can't be looked up. This means:")
            self.log("  1. Different text normalization in training vs lookup")
            self.log("  2. Different tokenization approaches")
            self.log("\nFIX: Ensure same normalization everywhere")
        
        if self.stats.get("essential_token_coverage", 100) < 50:
            self.log("\n🔴 WRONG TOKENIZATION!")
            self.log("Basic code tokens missing. Word2Vec may have been trained on:")
            self.log("  1. Split tokens (e.g., 'int' split into 'i', 'n', 't')")
            self.log("  2. Different preprocessing")
            self.log("\nFIX: Check tokenization in training vs vocab_builder")
    
    def run(self):
        """Run all analyses."""
        print("Word2Vec Embedding Quality Analyzer")
        print("=" * 70)
        
        if not self.analyze_sqlite_basics():
            return
        
        self.analyze_embedding_distribution()
        self.analyze_embedding_similarity()
        self.analyze_code_token_coverage()
        self.check_semantic_relationships()
        self.analyze_vocab_overlap()
        self.analyze_word2vec_model()
        self.generate_summary()


def main():
    parser = argparse.ArgumentParser(description="Word2Vec Embedding Quality Analyzer")
    parser.add_argument("--embedding-db", required=True,
                       help="Path to word2vec_embeddings.sqlite")
    parser.add_argument("--strings-csv",
                       help="Path to strings_to_embed.csv")
    parser.add_argument("--word2vec-model",
                       help="Path to Word2Vec .bin or .txt model file")
    
    args = parser.parse_args()
    
    analyzer = Word2VecAnalyzer(args)
    analyzer.run()


if __name__ == "__main__":
    main()



"""

python analyze_word2vec_quality.py \
    --embedding-db "./Clean_exports/cache_devign_v2/word2vec_embeddings.sqlite" \
    --strings-csv "./Clean_exports/devign_vocab_normfunc_v2/strings_to_embed.csv" \
    --word2vec-model "./Clean_exports/word2vec/code_word2vec.bin"


"""