#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
train_word2vec.py - Robust Word2Vec Training for Code

Improvements over v1:
- Filters out punctuation and operators (noise)
- Minimum token length = 2 by default
- Memory-efficient streaming
- Progress tracking with ETA
- Embedding quality evaluation
- Resume from checkpoint support

Usage:
    python train_word2vec.py \
        --input-csv /path/to/strings_to_embed.csv \
        --output-dir /path/to/output \
        --dim 128 \
        --epochs 30

Author: Anonymous
"""

import argparse
import csv
import json
import logging
import math
import os
import re
import sys
import time
from collections import Counter
from datetime import datetime
from pathlib import Path
from typing import Dict, Iterator, List, Optional, Set, Tuple

try:
    from gensim.models import Word2Vec, KeyedVectors
    from gensim.models.callbacks import CallbackAny2Vec
    HAS_GENSIM = True
except ImportError:
    HAS_GENSIM = False
    print("=" * 60)
    print("ERROR: gensim not installed!")
    print("Install with: pip install gensim")
    print("=" * 60)
    sys.exit(1)


# =============================================================================
# LOGGING
# =============================================================================

def setup_logging(log_file: Optional[Path] = None) -> logging.Logger:
    """Setup logging with console and optional file output."""
    logger = logging.getLogger("word2vec_v2")
    logger.setLevel(logging.INFO)
    logger.handlers.clear()
    
    fmt = logging.Formatter(
        "%(asctime)s | %(levelname)-8s | %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S"
    )
    
    # Console handler
    ch = logging.StreamHandler()
    ch.setFormatter(fmt)
    logger.addHandler(ch)
    
    # File handler
    if log_file:
        log_file.parent.mkdir(parents=True, exist_ok=True)
        fh = logging.FileHandler(log_file, encoding="utf-8")
        fh.setFormatter(fmt)
        logger.addHandler(fh)
    
    return logger


# =============================================================================
# CODE TOKENIZER (Improved - Filters Noise)
# =============================================================================

class CodeTokenizerV2:
    """
    Improved tokenizer for source code that:
    - Extracts only identifiers and keywords (NO punctuation/operators)
    - Splits CamelCase and snake_case
    - Filters single characters
    - Handles code-specific patterns
    """
    
    # Pattern to extract ONLY identifiers (no punctuation, no operators)
    IDENTIFIER_PATTERN = re.compile(r'[a-zA-Z_][a-zA-Z0-9_]*')
    
    # CamelCase splitting
    CAMEL_SPLIT = re.compile(r'([a-z])([A-Z])')
    CAMEL_CONSECUTIVE = re.compile(r'([A-Z]+)([A-Z][a-z])')
    
    # Common code stopwords (optional filtering)
    CODE_STOPWORDS = {
        'the', 'a', 'an', 'is', 'are', 'was', 'were', 'be', 'been',
        'this', 'that', 'it', 'for', 'to', 'of', 'in', 'on', 'at',
        'todo', 'fixme', 'xxx', 'hack', 'note', 'and', 'or', 'not',
    }
    
    # C/C++ keywords to keep (important for code understanding)
    CODE_KEYWORDS = {
        'if', 'else', 'for', 'while', 'do', 'switch', 'case', 'default',
        'break', 'continue', 'return', 'goto', 'sizeof', 'typedef',
        'struct', 'union', 'enum', 'class', 'public', 'private', 'protected',
        'static', 'extern', 'const', 'volatile', 'register', 'auto',
        'void', 'int', 'char', 'short', 'long', 'float', 'double',
        'signed', 'unsigned', 'bool', 'true', 'false', 'null', 'nullptr',
        'new', 'delete', 'try', 'catch', 'throw', 'virtual', 'override',
        'inline', 'template', 'typename', 'namespace', 'using',
    }
    
    def __init__(
        self,
        split_camel: bool = True,
        split_snake: bool = True,
        lowercase: bool = True,
        min_len: int = 2,
        max_len: int = 30,
        filter_stopwords: bool = True,
        keep_keywords: bool = True,
    ):
        self.split_camel = split_camel
        self.split_snake = split_snake
        self.lowercase = lowercase
        self.min_len = min_len
        self.max_len = max_len
        self.filter_stopwords = filter_stopwords
        self.keep_keywords = keep_keywords
    
    def tokenize(self, text: str) -> List[str]:
        """Tokenize code string into meaningful tokens (no punctuation)."""
        if not text or not isinstance(text, str):
            return []
        
        tokens = []
        
        # Extract only identifiers (automatically filters punctuation/operators)
        for match in self.IDENTIFIER_PATTERN.finditer(text):
            token = match.group()
            
            # Split identifier into subtokens
            subtokens = self._split_identifier(token)
            
            for st in subtokens:
                normalized = self._normalize(st)
                if self._is_valid(normalized):
                    tokens.append(normalized)
        
        return tokens
    
    def _split_identifier(self, token: str) -> List[str]:
        """Split identifier by CamelCase and snake_case."""
        result = token
        
        # Split CamelCase: "getData" -> "get_Data" -> ["get", "Data"]
        if self.split_camel:
            result = self.CAMEL_SPLIT.sub(r'\1_\2', result)
            result = self.CAMEL_CONSECUTIVE.sub(r'\1_\2', result)
        
        # Split by underscore
        if self.split_snake and '_' in result:
            parts = [p for p in result.split('_') if p]
            return parts if parts else [token]
        
        return [result]
    
    def _normalize(self, token: str) -> str:
        """Normalize token."""
        if self.lowercase:
            return token.lower()
        return token
    
    def _is_valid(self, token: str) -> bool:
        """Check if token passes all filters."""
        if not token:
            return False
        
        # Length check
        if len(token) < self.min_len or len(token) > self.max_len:
            # Exception: keep short keywords like "if", "do"
            if self.keep_keywords and token.lower() in self.CODE_KEYWORDS:
                return True
            return False
        
        # Stopword check
        if self.filter_stopwords and token.lower() in self.CODE_STOPWORDS:
            return False
        
        # Must contain at least one letter
        if not any(c.isalpha() for c in token):
            return False
        
        return True


# =============================================================================
# STREAMING CORPUS (Memory Efficient)
# =============================================================================

class StreamingCorpus:
    """
    Memory-efficient corpus that streams from disk.
    Can be iterated multiple times (required for Word2Vec epochs).
    Supports count-weighting and optional kind filtering (node_content/edge_content).
    """
    
    def __init__(
        self,
        csv_paths: List[Path],
        tokenizer: CodeTokenizerV2,
        min_tokens: int = 1,
        max_tokens: int = 500,
        text_columns: Optional[List[str]] = None,
        count_column: str = "count",
        count_weighting: str = "sqrt",
        max_repeat: int = 10,
        kind_filter: Optional[Set[str]] = None,
        logger: Optional[logging.Logger] = None,
    ):
        self.csv_paths = csv_paths
        self.tokenizer = tokenizer
        self.min_tokens = min_tokens
        self.max_tokens = max_tokens
        self.text_columns = text_columns or [
            'string', 'code', 'content', 'text', 'CODE', 
            'FULL_NAME', 'NAME', 'snippet'
        ]
        self.count_column = count_column
        self.count_weighting = count_weighting
        self.max_repeat = max_repeat
        self.kind_filter = kind_filter
        self.logger = logger or logging.getLogger(__name__)
        self._warned_missing_count = False
        self._warned_missing_kind = False
        
        # Statistics (populated by scan())
        self._total_sentences_raw = 0
        self._total_sentences_weighted = 0
        self._total_tokens_raw = 0
        self._total_tokens_weighted = 0
        self._vocab_raw = Counter()
        self._vocab_weighted = Counter()
        self._kind_counts_raw = Counter()
        self._kind_counts_weighted = Counter()
        self._scanned = False
    
    def _parse_count(self, raw_value: Optional[str]) -> int:
        if raw_value is None or raw_value == "":
            return 1
        try:
            count = int(float(raw_value))
        except (TypeError, ValueError):
            return 1
        return max(1, count)

    def _count_to_repeats(self, count: int) -> int:
        if self.count_weighting == "none" or count <= 1:
            return 1
        if self.count_weighting == "repeat":
            return min(self.max_repeat, count)
        if self.count_weighting == "log":
            return min(self.max_repeat, max(1, int(math.log1p(count))))
        # Default: sqrt
        return min(self.max_repeat, max(1, int(math.sqrt(count))))

    def _iter_rows(self) -> Iterator[Tuple[str, Optional[str], int]]:
        for csv_path in self.csv_paths:
            if not csv_path.exists():
                self.logger.warning(f"File not found: {csv_path}")
                continue

            try:
                with open(csv_path, 'r', encoding='utf-8', errors='replace') as f:
                    # Try to detect CSV format
                    sample = f.read(8192)
                    f.seek(0)

                    try:
                        dialect = csv.Sniffer().sniff(sample, delimiters=',\t;|')
                    except csv.Error:
                        dialect = csv.excel  # Default to comma-separated

                    reader = csv.DictReader(f, dialect=dialect)

                    for row in reader:
                        # Find text content
                        text = None
                        for col in self.text_columns:
                            if col in row and row[col]:
                                text = row[col]
                                break

                        if not text:
                            continue

                        kind = row.get("kind") if isinstance(row, dict) else None
                        if kind is not None:
                            kind = kind.strip() or None

                        if self.kind_filter:
                            if kind is None:
                                if not self._warned_missing_kind:
                                    self.logger.warning(
                                        "Kind filter enabled but 'kind' column missing or empty; skipping rows without kind"
                                    )
                                    self._warned_missing_kind = True
                                continue
                            if kind not in self.kind_filter:
                                continue

                        count = 1
                        if isinstance(row, dict) and self.count_column in row:
                            count = self._parse_count(row.get(self.count_column))
                        elif self.count_weighting != "none" and not self._warned_missing_count:
                            self.logger.warning(
                                f"Count weighting enabled but column '{self.count_column}' not found; using count=1"
                            )
                            self._warned_missing_count = True

                        yield text, kind, count

            except Exception as e:
                self.logger.error(f"Error reading {csv_path}: {e}")

    def __iter__(self) -> Iterator[List[str]]:
        """Iterate over tokenized sentences with optional count weighting."""
        for text, kind, count in self._iter_rows():
            tokens = self.tokenizer.tokenize(text)

            # Filter by length
            if self.min_tokens <= len(tokens) <= self.max_tokens:
                repeats = self._count_to_repeats(count)
                for _ in range(repeats):
                    yield tokens
    
    def scan(self) -> Dict:
        """Scan corpus to collect statistics (single pass)."""
        if self._scanned:
            return self.get_stats()
        
        self.logger.info("Scanning corpus for statistics...")
        start = time.time()
        
        self._total_sentences_raw = 0
        self._total_sentences_weighted = 0
        self._total_tokens_raw = 0
        self._total_tokens_weighted = 0
        self._vocab_raw = Counter()
        self._vocab_weighted = Counter()
        self._kind_counts_raw = Counter()
        self._kind_counts_weighted = Counter()
        
        for text, kind, count in self._iter_rows():
            tokens = self.tokenizer.tokenize(text)
            
            if not tokens:
                continue
            
            if self.min_tokens <= len(tokens) <= self.max_tokens:
                self._total_sentences_raw += 1
                self._total_tokens_raw += len(tokens)
                self._vocab_raw.update(tokens)
                
                repeats = self._count_to_repeats(count)
                self._total_sentences_weighted += repeats
                self._total_tokens_weighted += len(tokens) * repeats
                if repeats == 1:
                    self._vocab_weighted.update(tokens)
                else:
                    self._vocab_weighted.update({t: repeats for t in tokens})
                
                if kind:
                    self._kind_counts_raw[kind] += 1
                    self._kind_counts_weighted[kind] += repeats
            
            if self._total_sentences_raw % 50000 == 0:
                self.logger.info(f"  Scanned {self._total_sentences_raw:,} sentences (raw)...")
        
        elapsed = time.time() - start
        self._scanned = True
        
        self.logger.info(f"Scan complete in {elapsed:.1f}s")
        self.logger.info(
            f"  Sentences (raw/weighted): {self._total_sentences_raw:,}/{self._total_sentences_weighted:,}"
        )
        self.logger.info(
            f"  Total tokens (raw/weighted): {self._total_tokens_raw:,}/{self._total_tokens_weighted:,}"
        )
        self.logger.info(
            f"  Unique tokens (raw/weighted): {len(self._vocab_raw):,}/{len(self._vocab_weighted):,}"
        )
        self.logger.info(
            "  Avg tokens/sentence (raw/weighted): "
            f"{self._total_tokens_raw / max(1, self._total_sentences_raw):.1f}/"
            f"{self._total_tokens_weighted / max(1, self._total_sentences_weighted):.1f}"
        )
        if self._kind_counts_raw:
            self.logger.info(f"  Kind distribution (raw): {dict(self._kind_counts_raw)}")
            self.logger.info(f"  Kind distribution (weighted): {dict(self._kind_counts_weighted)}")
        
        return self.get_stats()
    
    def get_stats(self) -> Dict:
        """Get corpus statistics."""
        return {
            'sentences': self._total_sentences_weighted,
            'sentences_raw': self._total_sentences_raw,
            'tokens': self._total_tokens_weighted,
            'tokens_raw': self._total_tokens_raw,
            'unique_tokens': len(self._vocab_weighted),
            'unique_tokens_raw': len(self._vocab_raw),
            'avg_tokens_per_sentence': self._total_tokens_weighted / max(1, self._total_sentences_weighted),
            'avg_tokens_per_sentence_raw': self._total_tokens_raw / max(1, self._total_sentences_raw),
            'top_tokens': self._vocab_weighted.most_common(50),
            'top_tokens_raw': self._vocab_raw.most_common(50),
            'kinds_raw': dict(self._kind_counts_raw),
            'kinds_weighted': dict(self._kind_counts_weighted),
        }


# =============================================================================
# TRAINING CALLBACK
# =============================================================================

class ProgressCallback(CallbackAny2Vec):
    """Enhanced callback with progress tracking and ETA."""
    
    def __init__(self, total_epochs: int, logger: logging.Logger):
        self.total_epochs = total_epochs
        self.logger = logger
        self.epoch = 0
        self.epoch_start = None
        self.training_start = None
        self.epoch_times = []
    
    def on_train_begin(self, model):
        self.training_start = time.time()
        self.logger.info("=" * 60)
        self.logger.info("TRAINING STARTED")
        self.logger.info("=" * 60)
    
    def on_epoch_begin(self, model):
        self.epoch += 1
        self.epoch_start = time.time()
    
    def on_epoch_end(self, model):
        elapsed = time.time() - self.epoch_start
        self.epoch_times.append(elapsed)
        
        # Calculate ETA
        avg_time = sum(self.epoch_times) / len(self.epoch_times)
        remaining = (self.total_epochs - self.epoch) * avg_time
        
        # Format ETA
        if remaining > 3600:
            eta = f"{remaining/3600:.1f}h"
        elif remaining > 60:
            eta = f"{remaining/60:.1f}m"
        else:
            eta = f"{remaining:.0f}s"
        
        self.logger.info(
            f"Epoch {self.epoch:3d}/{self.total_epochs} | "
            f"Time: {elapsed:5.1f}s | "
            f"ETA: {eta}"
        )
    
    def on_train_end(self, model):
        total = time.time() - self.training_start
        
        if total > 3600:
            time_str = f"{total/3600:.1f} hours"
        elif total > 60:
            time_str = f"{total/60:.1f} minutes"
        else:
            time_str = f"{total:.1f} seconds"
        
        self.logger.info("=" * 60)
        self.logger.info(f"TRAINING COMPLETE | Total time: {time_str}")
        self.logger.info("=" * 60)


# =============================================================================
# EMBEDDING EVALUATOR
# =============================================================================

class EmbeddingEvaluator:
    """Evaluate embedding quality with code-specific tests."""
    
    # Code similarity pairs (should be similar)
    SIMILAR_PAIRS = [
        ('int', 'integer'),
        ('str', 'string'),
        ('array', 'list'),
        ('func', 'function'),
        ('ptr', 'pointer'),
        ('buf', 'buffer'),
        ('len', 'length'),
        ('idx', 'index'),
        ('tmp', 'temp'),
        ('src', 'source'),
        ('dst', 'dest'),
        ('init', 'initialize'),
        ('alloc', 'allocate'),
        ('malloc', 'alloc'),
        ('free', 'dealloc'),
        ('err', 'error'),
        ('msg', 'message'),
        ('num', 'number'),
        ('max', 'maximum'),
        ('min', 'minimum'),
    ]
    
    # Analogy tests (a:b :: c:d)
    ANALOGIES = [
        ('read', 'write', 'get', 'set'),
        ('open', 'close', 'lock', 'unlock'),
        ('start', 'stop', 'begin', 'end'),
        ('push', 'pop', 'enqueue', 'dequeue'),
        ('alloc', 'free', 'create', 'destroy'),
        ('input', 'output', 'read', 'write'),
    ]
    
    def __init__(self, wv: KeyedVectors, logger: logging.Logger):
        self.wv = wv
        self.logger = logger
    
    def evaluate(self) -> Dict:
        """Run all evaluations."""
        results = {}
        
        # Similarity tests
        results['similarity'] = self._eval_similarity()
        
        # Analogy tests
        results['analogy'] = self._eval_analogies()
        
        # Coverage stats
        results['coverage'] = self._eval_coverage()
        
        return results
    
    def _eval_similarity(self) -> Dict:
        """Evaluate similarity pairs."""
        scores = []
        found_pairs = []
        
        for w1, w2 in self.SIMILAR_PAIRS:
            if w1 in self.wv and w2 in self.wv:
                sim = self.wv.similarity(w1, w2)
                scores.append(sim)
                found_pairs.append((w1, w2, sim))
        
        if scores:
            avg_sim = sum(scores) / len(scores)
            self.logger.info(f"Similarity test: {len(scores)}/{len(self.SIMILAR_PAIRS)} pairs found")
            self.logger.info(f"  Average similarity: {avg_sim:.3f}")
            
            # Show top pairs
            found_pairs.sort(key=lambda x: x[2], reverse=True)
            self.logger.info(f"  Top similar pairs:")
            for w1, w2, sim in found_pairs[:5]:
                self.logger.info(f"    {w1} <-> {w2}: {sim:.3f}")
            
            return {
                'found': len(scores), 
                'total': len(self.SIMILAR_PAIRS), 
                'avg_similarity': avg_sim,
                'pairs': found_pairs,
            }
        
        return {'found': 0, 'total': len(self.SIMILAR_PAIRS), 'avg_similarity': 0}
    
    def _eval_analogies(self) -> Dict:
        """Evaluate analogy tests."""
        correct = 0
        found = 0
        results = []
        
        for a, b, c, d in self.ANALOGIES:
            if all(w in self.wv for w in [a, b, c, d]):
                found += 1
                try:
                    # a:b :: c:?
                    result = self.wv.most_similar(positive=[b, c], negative=[a], topn=5)
                    predicted = [w for w, _ in result]
                    is_correct = d in predicted
                    if is_correct:
                        correct += 1
                    results.append({
                        'analogy': f"{a}:{b} :: {c}:{d}",
                        'predicted': predicted[:3],
                        'correct': is_correct,
                    })
                except Exception:
                    pass
        
        if found > 0:
            acc = correct / found
            self.logger.info(f"Analogy test: {correct}/{found} correct ({acc:.1%})")
            return {'correct': correct, 'found': found, 'accuracy': acc, 'results': results}
        
        self.logger.info("Analogy test: No complete analogies found in vocabulary")
        return {'correct': 0, 'found': 0, 'accuracy': 0}
    
    def _eval_coverage(self) -> Dict:
        """Evaluate vocabulary coverage of important code terms."""
        vocab_size = len(self.wv)
        
        # Important code keywords
        keywords = [
            'if', 'else', 'for', 'while', 'return', 'int', 'void', 
            'char', 'struct', 'class', 'function', 'null', 'true', 'false',
            'malloc', 'free', 'alloc', 'buffer', 'size', 'length',
            'error', 'null', 'pointer', 'array', 'string', 'memory',
        ]
        covered = [k for k in keywords if k in self.wv]
        
        # Vulnerability-related terms
        vuln_terms = [
            'overflow', 'buffer', 'malloc', 'free', 'memcpy', 'strcpy',
            'sprintf', 'gets', 'scanf', 'bounds', 'check', 'validate',
            'sanitize', 'escape', 'inject', 'null', 'nullptr', 'leak',
        ]
        vuln_covered = [t for t in vuln_terms if t in self.wv]
        
        self.logger.info(f"Coverage: {len(covered)}/{len(keywords)} keywords")
        self.logger.info(f"  Covered: {', '.join(covered[:15])}...")
        self.logger.info(f"Vuln terms: {len(vuln_covered)}/{len(vuln_terms)} covered")
        self.logger.info(f"  Covered: {', '.join(vuln_covered)}")
        
        return {
            'vocab_size': vocab_size,
            'keywords_covered': len(covered),
            'keywords_total': len(keywords),
            'keywords_list': covered,
            'vuln_terms_covered': len(vuln_covered),
            'vuln_terms_total': len(vuln_terms),
            'vuln_terms_list': vuln_covered,
        }
    
    def show_examples(self, n: int = 5):
        """Show example similar words for important terms."""
        test_words = [
            'buffer', 'malloc', 'free', 'string', 'array', 
            'pointer', 'function', 'return', 'size', 'null',
            'error', 'memory', 'alloc', 'check', 'data',
        ]
        
        self.logger.info("\n" + "=" * 60)
        self.logger.info("SAMPLE SIMILAR WORDS")
        self.logger.info("=" * 60)
        
        for word in test_words:
            if word in self.wv:
                try:
                    similar = self.wv.most_similar(word, topn=n)
                    similar_str = ', '.join([f"{w}({s:.2f})" for w, s in similar])
                    self.logger.info(f"{word:12s}: {similar_str}")
                except Exception:
                    pass


# =============================================================================
# MAIN TRAINING FUNCTION
# =============================================================================

def train_word2vec(
    corpus: StreamingCorpus,
    output_dir: Path,
    logger: logging.Logger,
    dim: int = 128,
    window: int = 5,
    min_count: int = 2,
    epochs: int = 30,
    workers: int = 4,
    algorithm: str = 'skipgram',
    negative: int = 10,
    sample: float = 1e-4,
    resume_from: Optional[Path] = None,
) -> Word2Vec:
    """
    Train Word2Vec model with streaming corpus.
    
    Args:
        corpus: Streaming corpus iterator
        output_dir: Directory for outputs
        logger: Logger instance
        dim: Embedding dimension
        window: Context window
        min_count: Minimum word frequency
        epochs: Training epochs
        workers: CPU threads
        algorithm: 'skipgram' or 'cbow'
        negative: Negative samples
        sample: Subsampling threshold
        resume_from: Path to checkpoint to resume from
    
    Returns:
        Trained Word2Vec model
    """
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Configuration
    sg = 1 if algorithm == 'skipgram' else 0
    
    logger.info("=" * 60)
    logger.info("WORD2VEC V2 CONFIGURATION")
    logger.info("=" * 60)
    logger.info(f"Dimension:        {dim}")
    logger.info(f"Window:           {window}")
    logger.info(f"Min count:        {min_count}")
    logger.info(f"Epochs:           {epochs}")
    logger.info(f"Algorithm:        {algorithm}")
    logger.info(f"Negative samples: {negative}")
    logger.info(f"Subsampling:      {sample}")
    logger.info(f"Workers:          {workers}")
    logger.info(f"Sentence len:     min={corpus.min_tokens} max={corpus.max_tokens}")
    logger.info(f"Count weighting:  {corpus.count_weighting} (max_repeat={corpus.max_repeat})")
    if corpus.kind_filter:
        logger.info(f"Kind filter:      {sorted(corpus.kind_filter)}")
    logger.info(f"Output dir:       {output_dir}")
    logger.info("=" * 60)
    
    # Scan corpus for stats
    stats = corpus.scan()
    
    # Show top tokens from corpus
    logger.info("\nTop 30 tokens in corpus (weighted):")
    for i, (token, count) in enumerate(stats['top_tokens'][:30], 1):
        logger.info(f"  {i:2d}. {token:20s} ({count:,})")
    
    # Check if resuming
    if resume_from and resume_from.exists():
        logger.info(f"\nResuming from checkpoint: {resume_from}")
        model = Word2Vec.load(str(resume_from))
        
        # Continue training
        model.train(
            corpus,
            total_examples=stats['sentences'],
            epochs=epochs,
            callbacks=[ProgressCallback(epochs, logger)],
        )
    else:
        # Train new model
        logger.info("\nBuilding vocabulary and training...")
        
        callback = ProgressCallback(epochs, logger)
        
        model = Word2Vec(
            sentences=corpus,
            vector_size=dim,
            window=window,
            min_count=min_count,
            workers=workers,
            epochs=epochs,
            sg=sg,
            negative=negative,
            sample=sample,
            callbacks=[callback],
        )
    
    # Generate output filenames
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    base_name = f"code_word2vec_{dim}d"
    
    # Save in multiple formats
    
    # 1. Binary format (for gensim/production use)
    bin_path = output_dir / f"{base_name}.bin"
    model.wv.save_word2vec_format(str(bin_path), binary=True)
    logger.info(f"\nSaved binary model: {bin_path}")
    
    # 2. Text format (human readable, for inspection)
    txt_path = output_dir / f"{base_name}.txt"
    model.wv.save_word2vec_format(str(txt_path), binary=False)
    logger.info(f"Saved text model: {txt_path}")
    
    # 3. Full gensim model (for continued training)
    model_path = output_dir / f"{base_name}.model"
    model.save(str(model_path))
    logger.info(f"Saved full model: {model_path}")
    
    # 4. Checkpoint with timestamp
    checkpoint_path = output_dir / f"checkpoint_{timestamp}.model"
    model.save(str(checkpoint_path))
    logger.info(f"Saved checkpoint: {checkpoint_path}")
    
    # Evaluate embeddings
    logger.info("\n" + "=" * 60)
    logger.info("EMBEDDING EVALUATION")
    logger.info("=" * 60)
    
    evaluator = EmbeddingEvaluator(model.wv, logger)
    eval_results = evaluator.evaluate()
    evaluator.show_examples()
    
    # Save comprehensive statistics
    full_stats = {
        'timestamp': timestamp,
        'config': {
            'dim': dim,
            'window': window,
            'min_count': min_count,
            'epochs': epochs,
            'algorithm': algorithm,
            'negative': negative,
            'sample': sample,
            'tokenizer': {
                'split_camel': corpus.tokenizer.split_camel,
                'split_snake': corpus.tokenizer.split_snake,
                'lowercase': corpus.tokenizer.lowercase,
                'min_token_len': corpus.tokenizer.min_len,
                'max_token_len': corpus.tokenizer.max_len,
                'filter_stopwords': corpus.tokenizer.filter_stopwords,
                'keep_keywords': corpus.tokenizer.keep_keywords,
            },
            'corpus_weighting': {
                'min_sentence_len': corpus.min_tokens,
                'max_sentence_len': corpus.max_tokens,
                'count_column': corpus.count_column,
                'count_weighting': corpus.count_weighting,
                'max_repeat': corpus.max_repeat,
                'kind_filter': sorted(corpus.kind_filter) if corpus.kind_filter else None,
            },
        },
        'corpus': {
            'sentences': stats['sentences'],
            'sentences_raw': stats['sentences_raw'],
            'tokens': stats['tokens'],
            'tokens_raw': stats['tokens_raw'],
            'unique_tokens': stats['unique_tokens'],
            'unique_tokens_raw': stats['unique_tokens_raw'],
            'avg_tokens_per_sentence': stats['avg_tokens_per_sentence'],
            'avg_tokens_per_sentence_raw': stats['avg_tokens_per_sentence_raw'],
            'kinds_raw': stats['kinds_raw'],
            'kinds_weighted': stats['kinds_weighted'],
        },
        'model': {
            'vocab_size': len(model.wv),
            'vector_size': model.wv.vector_size,
        },
        'evaluation': {
            'similarity': {
                'found': eval_results['similarity']['found'],
                'total': eval_results['similarity']['total'],
                'avg_similarity': eval_results['similarity']['avg_similarity'],
            },
            'coverage': eval_results['coverage'],
        },
        'output_files': {
            'binary': str(bin_path),
            'text': str(txt_path),
            'model': str(model_path),
            'checkpoint': str(checkpoint_path),
        },
    }
    
    stats_path = output_dir / f"{base_name}_stats.json"
    with open(stats_path, 'w') as f:
        json.dump(full_stats, f, indent=2, default=str)
    logger.info(f"\nSaved statistics: {stats_path}")
    
    # Print final summary
    logger.info("\n" + "=" * 60)
    logger.info("TRAINING SUMMARY")
    logger.info("=" * 60)
    logger.info(f"Vocabulary size:     {len(model.wv):,}")
    logger.info(f"Vector dimension:    {dim}")
    logger.info(
        f"Corpus sentences:    {stats['sentences']:,} (weighted), {stats['sentences_raw']:,} (raw)"
    )
    logger.info(f"Similarity score:    {eval_results['similarity']['avg_similarity']:.3f}")
    logger.info(f"Keyword coverage:    {eval_results['coverage']['keywords_covered']}/{eval_results['coverage']['keywords_total']}")
    logger.info(f"Vuln term coverage:  {eval_results['coverage']['vuln_terms_covered']}/{eval_results['coverage']['vuln_terms_total']}")
    logger.info("=" * 60)
    logger.info(f"\n✅ Use this file with multi_extractor.py:")
    logger.info(f"   --word2vec-path \"{bin_path}\"")
    
    return model


# =============================================================================
# CLI
# =============================================================================

def parse_args():
    parser = argparse.ArgumentParser(
        description="Train Word2Vec embeddings on code corpus (V2 - Improved)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # Basic training (128d)
    python train_word2vec.py \\
        --input-csv /path/to/strings_to_embed.csv \\
        --output-dir /path/to/output \\
        --dim 128 \\
        --epochs 30

    # 256d embeddings with more epochs
    python train_word2vec.py \\
        --input-csv /path/to/strings_to_embed.csv \\
        --output-dir /path/to/output \\
        --dim 256 \\
        --epochs 50 \\
        --workers 8

    # Resume from checkpoint
    python train_word2vec.py \\
        --input-csv /path/to/strings_to_embed.csv \\
        --output-dir /path/to/output \\
        --dim 128 \\
        --epochs 20 \\
        --resume-from /path/to/checkpoint.model
        """,
    )
    
    # Input
    parser.add_argument("--input-csv", nargs="+", required=True,
                       help="Path(s) to CSV file(s) with code strings")
    
    # Output
    parser.add_argument("--output-dir", required=True,
                       help="Output directory for models and stats")
    parser.add_argument("--log-file",
                       help="Log file path (default: output_dir/training.log)")
    
    # Word2Vec parameters
    w2v_group = parser.add_argument_group("Word2Vec Parameters")
    w2v_group.add_argument("--dim", type=int, default=128,
                          help="Embedding dimension (default: 128)")
    w2v_group.add_argument("--window", type=int, default=5,
                          help="Context window size (default: 5)")
    w2v_group.add_argument("--min-count", type=int, default=2,
                          help="Minimum word frequency (default: 2)")
    w2v_group.add_argument("--epochs", type=int, default=30,
                          help="Training epochs (default: 30)")
    w2v_group.add_argument("--workers", type=int, default=4,
                          help="CPU threads (default: 4)")
    w2v_group.add_argument("--algorithm", choices=['skipgram', 'cbow'],
                          default='skipgram',
                          help="Training algorithm (default: skipgram)")
    w2v_group.add_argument("--negative", type=int, default=10,
                          help="Negative samples (default: 10)")
    
    # Tokenization
    tok_group = parser.add_argument_group("Tokenization")
    tok_group.add_argument("--min-token-len", type=int, default=2,
                          help="Minimum token length (default: 2)")
    tok_group.add_argument("--max-token-len", type=int, default=30,
                          help="Maximum token length (default: 30)")
    tok_group.add_argument("--min-sentence-len", type=int, default=1,
                          help="Minimum tokens per sentence (default: 1)")
    tok_group.add_argument("--max-sentence-len", type=int, default=500,
                          help="Maximum tokens per sentence (default: 500)")
    tok_group.add_argument("--no-split-camel", action="store_true",
                          help="Don't split CamelCase identifiers")
    tok_group.add_argument("--no-split-snake", action="store_true",
                          help="Don't split snake_case identifiers")
    tok_group.add_argument("--no-lowercase", action="store_true",
                          help="Don't lowercase tokens")
    tok_group.add_argument("--keep-stopwords", action="store_true",
                          help="Keep common stopwords")

    # Corpus weighting / filtering
    corpus_group = parser.add_argument_group("Corpus Weighting")
    corpus_group.add_argument("--count-column", default="count",
                             help="Column name for frequency weighting (default: count)")
    corpus_group.add_argument("--count-weighting",
                             choices=["none", "sqrt", "log", "repeat"],
                             default="sqrt",
                             help="How to weight sentences by count column (default: sqrt)")
    corpus_group.add_argument("--max-repeat", type=int, default=10,
                             help="Max repeats when weighting sentences (default: 10)")
    corpus_group.add_argument("--kinds", default=None,
                             help="Comma-separated kinds to include (default: all kinds)")
    
    # Resume
    parser.add_argument("--resume-from",
                       help="Path to checkpoint to resume training from")
    
    return parser.parse_args()


def main():
    args = parse_args()

    if args.max_repeat < 1:
        raise ValueError("--max-repeat must be >= 1")
    if args.min_sentence_len < 1:
        raise ValueError("--min-sentence-len must be >= 1")
    if args.max_sentence_len < args.min_sentence_len:
        raise ValueError("--max-sentence-len must be >= --min-sentence-len")
    
    # Setup output directory
    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Setup logging
    log_file = Path(args.log_file) if args.log_file else output_dir / "training.log"
    logger = setup_logging(log_file)
    
    logger.info("=" * 60)
    logger.info("WORD2VEC V2 TRAINER")
    logger.info("=" * 60)
    logger.info(f"Input files: {args.input_csv}")
    logger.info(f"Output dir:  {output_dir}")
    
    # Create tokenizer with improved settings
    tokenizer = CodeTokenizerV2(
        split_camel=not args.no_split_camel,
        split_snake=not args.no_split_snake,
        lowercase=not args.no_lowercase,
        min_len=args.min_token_len,
        max_len=args.max_token_len,
        filter_stopwords=not args.keep_stopwords,
        keep_keywords=True,
    )
    
    # Create streaming corpus
    csv_paths = [Path(p) for p in args.input_csv]
    kind_filter = None
    if args.kinds:
        kind_filter = {k.strip() for k in args.kinds.split(",") if k.strip()}
    corpus = StreamingCorpus(
        csv_paths=csv_paths,
        tokenizer=tokenizer,
        min_tokens=args.min_sentence_len,
        max_tokens=args.max_sentence_len,
        count_column=args.count_column,
        count_weighting=args.count_weighting,
        max_repeat=args.max_repeat,
        kind_filter=kind_filter,
        logger=logger,
    )
    
    # Train model
    model = train_word2vec(
        corpus=corpus,
        output_dir=output_dir,
        logger=logger,
        dim=args.dim,
        window=args.window,
        min_count=args.min_count,
        epochs=args.epochs,
        workers=args.workers,
        algorithm=args.algorithm,
        negative=args.negative,
        resume_from=Path(args.resume_from) if args.resume_from else None,
    )
    
    logger.info("\n✅ Training complete!")
    logger.info(f"Model saved to: {output_dir}")


if __name__ == "__main__":
    main()

"""

# Single Word2Vec for node_content + edge_content (strings_to_embed.csv contains both)
# DRAPER (full vocab)
python train_word2vec.py \
    --input-csv "./Clean_exports/draper_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_200d_draper_full" \
    --dim 200 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1

python train_word2vec.py \
    --input-csv "./Clean_exports/draper_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_100d_draper_full" \
    --dim 100 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1

# REVEAL (full_filtered vocab)
python train_word2vec.py \
    --input-csv "./Clean_exports/reveal_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_200d_reveal_full" \
    --dim 200 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1


python train_word2vec.py \
    --input-csv "./Clean_exports/reveal_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_100d_reveal_full" \
    --dim 100 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1    

# DEVIGN (full vocab)
python train_word2vec.py \
    --input-csv "./Clean_exports/devign_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_200d_full" \
    --dim 200 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1

# PRIMEVUL (full vocab)
python train_word2vec.py \
    --input-csv "./Clean_exports/primevul_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_200d_primevul_full" \
    --dim 200 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1

python train_word2vec.py \
    --input-csv "./Clean_exports/primevul_vocab_full/strings_to_embed.csv" \
    --output-dir "./Clean_exports/word2vec_100d_primevul_full" \
    --dim 100 \
    --epochs 50 \
    --workers 8 \
    --count-weighting sqrt \
    --max-repeat 10 \
    --min-sentence-len 1


"""
