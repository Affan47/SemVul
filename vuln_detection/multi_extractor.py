#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
multi_extractor.py - V3 Multi-model embedding extractor for code

FIXED VERSION with:
  - Matching tokenizer for Word2Vec (same as train_word2vec.py)
  - Overflow protection (clip vectors BEFORE aggregation)
  - Proper OOV handling (zeros, not garbage)
  - NaN/Inf validation
  - Value range clamping

ALIGNED with:
  - vocab_builder.py V7 (reads strings_to_embed.csv)
  - shared_text_norm.py V2 (same normalization for consistency)
  - train_word2vec.py (SAME tokenizer for Word2Vec)

Supports multiple embedding models:
1. GraphCodeBERT (microsoft/graphcodebert-base) - 768 dims
2. CodeBERT (microsoft/codebert-base) - 768 dims
3. CodeT5+ (Salesforce/codet5p-110m-embedding) - 256 dims
4. UniXcoder (microsoft/unixcoder-base) - 768 dims
5. CodeBERTa (huggingface/CodeBERTa-small-v1) - 768 dims
6. Word2Vec (custom trained) - configurable dims
7. Compressed variants (768 -> 64/128/256 dims)

Usage:
    # GraphCodeBERT (default)
    python multi_extractor.py \\
        --strings-csv /path/to/strings_to_embed.csv \\
        --code-emb-cache /path/to/cache.sqlite \\
        --model-type graphcodebert

    # Word2Vec (custom trained)
    python multi_extractor.py \\
        --strings-csv /path/to/strings_to_embed.csv \\
        --code-emb-cache /path/to/cache.sqlite \\
        --model-type word2vec \\
        --word2vec-path /path/to/code_word2vec.bin
"""

from __future__ import annotations
import argparse
import csv
import json
import logging
import os
import re
import sqlite3
import sys
import time
import zlib
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

import numpy as np
import torch
import torch.nn as nn

# Gensim import (for Word2Vec)
try:
    from gensim.models import KeyedVectors
    HAS_GENSIM = True
except ImportError:
    HAS_GENSIM = False
    KeyedVectors = None

# Progress bar
try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x=None, *a, **k):
        return x if x is not None else range(0)


# =============================================================================
# LOAD SHARED TEXT NORMALIZATION (optional, for validation)
# =============================================================================

def load_text_norm():
    """Try to load shared_text_norm for consistency checks."""
    SCRIPT_DIR = Path(__file__).resolve().parent
    sys.path.insert(0, str(SCRIPT_DIR))
    
    try:
        from shared_text_norm import normalize_for_embedding, sha256_normalized
        return normalize_for_embedding, sha256_normalized
    except ImportError:
        return None, None

normalize_func, sha256_func = load_text_norm()


# =============================================================================
# MODEL CONFIGURATIONS
# =============================================================================

MODEL_CONFIGS = {
    "graphcodebert": {
        "hf_name": "microsoft/graphcodebert-base",
        "dim": 768,
        "max_len": 512,
        "description": "GraphCodeBERT - Graph-guided pre-training for code",
        "returns_embedding": False,
    },
    "codebert": {
        "hf_name": "microsoft/codebert-base",
        "dim": 768,
        "max_len": 512,
        "description": "CodeBERT - Pre-trained for programming languages",
        "returns_embedding": False,
    },
    "codet5p": {
        "hf_name": "Salesforce/codet5p-110m-embedding",
        "dim": 256,
        "max_len": 512,
        "description": "CodeT5+ - State-of-art code understanding (embedding model)",
        "returns_embedding": True,
    },
    "codet5p_220m": {
        "hf_name": "Salesforce/codet5p-220m",
        "dim": 768,
        "max_len": 512,
        "description": "CodeT5+ 220M - Larger CodeT5+ variant",
        "returns_embedding": False,
    },
    "unixcoder": {
        "hf_name": "microsoft/unixcoder-base",
        "dim": 768,
        "max_len": 512,
        "description": "UniXcoder - Unified cross-modal code representation",
        "returns_embedding": False,
    },
    "codebert_mlm": {
        "hf_name": "microsoft/codebert-base-mlm",
        "dim": 768,
        "max_len": 512,
        "description": "CodeBERT MLM - Masked language model variant",
        "returns_embedding": False,
    },
    "codeberta": {
        "hf_name": "huggingface/CodeBERTa-small-v1",
        "dim": 768,
        "max_len": 512,
        "description": "CodeBERTa - Smaller RoBERTa for code",
        "returns_embedding": False,
    },
}


# =============================================================================
# LOGGING
# =============================================================================

def setup_logging(log_file: Path) -> logging.Logger:
    """Setup logging with file and console handlers."""
    logger = logging.getLogger("multi_extractor")
    logger.setLevel(logging.INFO)
    logger.handlers.clear()
    
    fmt = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s",
                            datefmt="%Y-%m-%d %H:%M:%S")
    
    log_file.parent.mkdir(parents=True, exist_ok=True)
    fh = logging.FileHandler(log_file, encoding="utf-8")
    fh.setFormatter(fmt)
    
    ch = logging.StreamHandler()
    ch.setFormatter(fmt)
    
    logger.addHandler(fh)
    logger.addHandler(ch)
    
    return logger


# =============================================================================
# TRANSFORMER-BASED EMBEDDING MODEL WRAPPER
# =============================================================================

class MultiModelEmbedder:
    """Multi-model embedding extractor with optional compression."""
    
    def __init__(
        self,
        model_type: str,
        device: str = "auto",
        max_len: int = 510,
        pooling: str = "mean",
        compress_to: Optional[int] = None,
        logger: Optional[logging.Logger] = None,
    ):
        from transformers import AutoModel, AutoTokenizer
        
        self.model_type = model_type
        self.pooling = pooling
        self.compress_to = compress_to
        self.logger = logger or logging.getLogger("multi_extractor")
        
        if model_type not in MODEL_CONFIGS:
            raise ValueError(f"Unknown model type: {model_type}. "
                           f"Available: {list(MODEL_CONFIGS.keys())}")
        
        config = MODEL_CONFIGS[model_type]
        hf_name = config["hf_name"]
        self.base_dim = config["dim"]
        model_max_len = config["max_len"]
        self.returns_embedding = config.get("returns_embedding", False)
        
        # Device
        if device == "auto":
            self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        else:
            self.device = torch.device(device)
        
        self.max_len = min(max_len, model_max_len - 2)
        
        self.logger.info(f"[MODEL] Loading {model_type}: {hf_name}")
        self.logger.info(f"[MODEL] Device: {self.device}, Max len: {self.max_len}")
        
        # Load tokenizer and model
        self.tokenizer = AutoTokenizer.from_pretrained(hf_name, trust_remote_code=True)
        self.model = AutoModel.from_pretrained(hf_name, trust_remote_code=True)
        self.model.to(self.device)
        self.model.eval()
        
        # Compression layer (optional)
        self.compressor = None
        if compress_to and compress_to < self.base_dim:
            self.logger.info(f"[COMPRESS] {self.base_dim} -> {compress_to} dims")
            self.compressor = nn.Sequential(
                nn.Linear(self.base_dim, compress_to),
                nn.LayerNorm(compress_to),
                nn.Tanh(),
            ).to(self.device)
            self.compressor.eval()
            self.output_dim = compress_to
        else:
            self.output_dim = self.base_dim
        
        self.logger.info(f"[MODEL] Output dim: {self.output_dim}")
    
    @property
    def dim(self) -> int:
        return self.output_dim
    
    @torch.no_grad()
    def embed_batch(
        self, 
        texts: List[str],
        store_token_data: bool = False,
    ) -> Dict[str, Any]:
        """Embed a batch of texts."""
        # Handle empty/invalid texts
        valid_texts = []
        valid_indices = []
        for i, text in enumerate(texts):
            if text and isinstance(text, str) and len(text.strip()) > 0:
                valid_texts.append(text)
                valid_indices.append(i)
        
        # Initialize output array with ZEROS
        all_embeddings = np.zeros((len(texts), self.output_dim), dtype=np.float32)
        
        if not valid_texts:
            return {"embeddings": all_embeddings}
        
        # Tokenize
        tok = self.tokenizer(
            valid_texts,
            padding=True,
            truncation=True,
            max_length=self.max_len,
            return_tensors="pt",
            return_attention_mask=True,
        )
        tok = {k: v.to(self.device) for k, v in tok.items()}
        
        # Forward pass with AMP
        use_amp = (self.device.type == "cuda")
        with torch.autocast(device_type=self.device.type, enabled=use_amp):
            out = self.model(**tok)
            
            if isinstance(out, torch.Tensor):
                # CodeT5+ embedding model returns tensor directly
                emb = out.to(torch.float32)
            elif hasattr(out, 'last_hidden_state'):
                last = out.last_hidden_state
                
                if self.pooling == "mean":
                    mask = tok["attention_mask"].unsqueeze(-1)
                    summed = (last * mask).sum(dim=1)
                    cnt = mask.sum(dim=1).clamp(min=1e-9)
                    emb = (summed / cnt).to(torch.float32)
                else:
                    emb = last[:, 0, :].to(torch.float32)
            elif hasattr(out, 'pooler_output') and out.pooler_output is not None:
                emb = out.pooler_output.to(torch.float32)
            else:
                raise ValueError(f"Unknown model output type: {type(out)}")
            
            if self.compressor is not None:
                emb = self.compressor(emb)
        
        # Place embeddings back in correct positions
        emb_np = emb.cpu().numpy().astype(np.float32)
        for i, orig_idx in enumerate(valid_indices):
            all_embeddings[orig_idx] = emb_np[i]
        
        result = {"embeddings": all_embeddings}
        
        if store_token_data:
            result["token_data"] = self._pack_token_data(tok)
        
        return result
    
    def _pack_token_data(self, tok: Dict[str, torch.Tensor]) -> Dict[str, Any]:
        """Pack token data for storage."""
        ids = tok["input_ids"].detach().cpu().numpy().astype(np.int32)
        msk = tok["attention_mask"].detach().cpu().numpy().astype(np.int32)
        
        ids_blobs, msk_blobs, lens, trunc = [], [], [], []
        for i in range(ids.shape[0]):
            ids_blobs.append(zlib.compress(ids[i].tobytes()))
            msk_blobs.append(zlib.compress(msk[i].tobytes()))
            true_len = int(msk[i].sum())
            lens.append(true_len)
            trunc.append(1 if true_len >= self.max_len else 0)
        
        return {
            "token_ids": ids_blobs,
            "attention_masks": msk_blobs,
            "token_lens": lens,
            "truncations": trunc,
        }


# =============================================================================
# CODE TOKENIZER V2 - MUST MATCH train_word2vec.py EXACTLY!
# =============================================================================

class CodeTokenizerV2:
    """
    Code tokenizer that MUST match the one used in train_word2vec.py.
    
    Key features:
    - Extracts only identifiers (NO punctuation, NO operators)
    - Splits CamelCase: "getData" -> ["get", "data"]
    - Splits snake_case: "my_var" -> ["my", "var"]
    - Filters by length (min_len=2 by default)
    - Keeps C/C++ keywords even if short (like "if", "do")
    
    CRITICAL: If this doesn't match train_word2vec.py, you get 80%+ OOV rate!
    """
    
    # Pattern to extract ONLY identifiers (no punctuation, no operators)
    IDENTIFIER_PATTERN = re.compile(r'[a-zA-Z_][a-zA-Z0-9_]*')
    
    # CamelCase splitting patterns
    CAMEL_SPLIT = re.compile(r'([a-z])([A-Z])')
    CAMEL_CONSECUTIVE = re.compile(r'([A-Z]+)([A-Z][a-z])')
    
    # Common stopwords to filter
    CODE_STOPWORDS = {
        'the', 'a', 'an', 'is', 'are', 'was', 'were', 'be', 'been',
        'this', 'that', 'it', 'for', 'to', 'of', 'in', 'on', 'at',
        'todo', 'fixme', 'xxx', 'hack', 'note', 'and', 'or', 'not',
    }
    
    # C/C++ keywords to keep (even if short like "if", "do")
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
        """
        Tokenize code - MUST match train_word2vec.py exactly!
        
        Example:
            "getBufferSize()" -> ["get", "buffer", "size"]
            "my_var = 10;"    -> ["my", "var"]
            "if (x > 0)"      -> ["if"]
        """
        if not text or not isinstance(text, str):
            return []
        
        tokens = []
        
        # Extract only identifiers (automatically filters punctuation/operators)
        for match in self.IDENTIFIER_PATTERN.finditer(text):
            token = match.group()
            subtokens = self._split_identifier(token)
            
            for st in subtokens:
                normalized = self._normalize(st)
                if self._is_valid(normalized):
                    tokens.append(normalized)
        
        return tokens
    
    def _split_identifier(self, token: str) -> List[str]:
        """Split identifier by CamelCase and snake_case."""
        result = token
        
        # Split CamelCase: "getData" -> "get_Data"
        if self.split_camel:
            result = self.CAMEL_SPLIT.sub(r'\1_\2', result)
            result = self.CAMEL_CONSECUTIVE.sub(r'\1_\2', result)
        
        # Split by underscore
        if self.split_snake and '_' in result:
            parts = [p for p in result.split('_') if p]
            return parts if parts else [token]
        
        return [result]
    
    def _normalize(self, token: str) -> str:
        """Normalize token (lowercase by default)."""
        if self.lowercase:
            return token.lower()
        return token
    
    def _is_valid(self, token: str) -> bool:
        """Check if token passes all filters."""
        if not token:
            return False
        
        # Length check (but keep short keywords like "if", "do")
        if len(token) < self.min_len or len(token) > self.max_len:
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
# WORD2VEC EMBEDDER - FIXED VERSION WITH OVERFLOW PROTECTION
# =============================================================================

class Word2VecEmbedder:
    """
    FIXED Word2Vec embedder with:
    1. Matching tokenizer (same as train_word2vec.py)
    2. Overflow protection (clip vectors BEFORE aggregation)
    3. Proper OOV handling (zeros, not garbage)
    4. NaN/Inf validation
    5. Value range clamping
    
    CRITICAL FIXES:
    - OLD tokenizer: re.findall(r'\\w+|[^\\w\\s]', text.lower())
      - Includes punctuation like (, ), ;, ->
      - Does NOT split CamelCase
      - Does NOT split snake_case
      - Result: 80-90% OOV rate!
    
    - NEW tokenizer: CodeTokenizerV2 (matches train_word2vec.py)
      - Only identifiers
      - Splits CamelCase: "getData" -> ["get", "data"]
      - Splits snake_case: "my_var" -> ["my", "var"]
      - Result: Much better match rate!
    """
    
    def __init__(
        self,
        model_path: str,
        aggregation: str = "mean",
        normalize: bool = True,
        clip_value: float = 50.0,
        logger: Optional[logging.Logger] = None,
    ):
        if not HAS_GENSIM:
            raise ImportError("gensim required for Word2Vec. Install: pip install gensim")
        
        self.logger = logger or logging.getLogger("word2vec")
        self.aggregation = aggregation
        self.normalize = normalize
        self.clip_value = clip_value
        
        # Use MATCHING tokenizer (same as train_word2vec.py!)
        self.tokenizer = CodeTokenizerV2(
            split_camel=True,
            split_snake=True,
            lowercase=True,
            min_len=2,
            max_len=30,
            filter_stopwords=True,
            keep_keywords=True,
        )
        
        self.logger.info(f"[WORD2VEC] Loading from {model_path}")
        
        path = Path(model_path)
        if path.suffix == ".bin":
            self.wv = KeyedVectors.load_word2vec_format(
                str(path), binary=True, unicode_errors='ignore'
            )
        elif path.suffix == ".model":
            from gensim.models import Word2Vec
            model = Word2Vec.load(str(path))
            self.wv = model.wv
        else:
            self.wv = KeyedVectors.load_word2vec_format(
                str(path), binary=False, unicode_errors='ignore'
            )
        
        self.output_dim = self.wv.vector_size
        self.logger.info(f"[WORD2VEC] Loaded {len(self.wv):,} vectors of dim {self.output_dim}")
        
        # Validate model
        self._validate_model()
        
        # Statistics
        self.total_tokens = 0
        self.matched_tokens = 0
        self.oov_tokens = 0
        self.clipped_vectors = 0
    
    def _validate_model(self):
        """Check Word2Vec model for issues."""
        sample_size = min(100, len(self.wv))
        if sample_size == 0:
            self.logger.warning("[WORD2VEC] Model appears empty!")
            return
        
        sample_words = list(self.wv.index_to_key[:sample_size])
        vectors = np.array([self.wv[w] for w in sample_words], dtype=np.float32)
        
        has_nan = np.isnan(vectors).any()
        has_inf = np.isinf(vectors).any()
        min_val = float(vectors.min())
        max_val = float(vectors.max())
        mean_val = float(vectors.mean())
        std_val = float(vectors.std())
        
        self.logger.info(f"[WORD2VEC] Model stats: range=[{min_val:.3f}, {max_val:.3f}], "
                        f"mean={mean_val:.3f}, std={std_val:.3f}")
        
        if has_nan:
            self.logger.warning("⚠️  Word2Vec model contains NaN values!")
        if has_inf:
            self.logger.warning("⚠️  Word2Vec model contains Inf values!")
        if abs(max_val) > 100 or abs(min_val) > 100:
            self.logger.warning(f"⚠️  Word2Vec model has extreme values (will be clipped to ±{self.clip_value})")
    
    @property
    def dim(self) -> int:
        return self.output_dim
    
    def embed_batch(
        self,
        texts: List[str],
        store_token_data: bool = False,
    ) -> Dict[str, Any]:
        """
        Embed batch of texts with SAFE handling.
        
        Key safety features:
        - Uses MATCHING tokenizer (same as train_word2vec.py)
        - Returns zeros for OOV tokens (not garbage/uninitialized)
        - Clips vectors BEFORE aggregation (prevents overflow)
        - Validates output for NaN/Inf
        - Clamps final values to reasonable range
        """
        # Initialize with ZEROS (not empty/uninitialized!)
        embeddings = np.zeros((len(texts), self.dim), dtype=np.float32)
        
        for idx, text in enumerate(texts):
            if not text or not isinstance(text, str):
                continue  # Already zeros
            
            # Use MATCHING tokenizer (same as train_word2vec.py!)
            tokens = self.tokenizer.tokenize(text)
            
            if not tokens:
                continue  # Already zeros
            
            # Collect embeddings for tokens in vocabulary
            vectors = []
            for token in tokens:
                self.total_tokens += 1
                
                if token in self.wv:
                    self.matched_tokens += 1
                    vec = self.wv[token].astype(np.float32)
                    
                    # Skip NaN/Inf vectors
                    if np.isnan(vec).any() or np.isinf(vec).any():
                        continue
                    
                    # CLIP BEFORE adding to prevent overflow during aggregation!
                    if np.abs(vec).max() > self.clip_value:
                        vec = np.clip(vec, -self.clip_value, self.clip_value)
                        self.clipped_vectors += 1
                    
                    vectors.append(vec)
                else:
                    self.oov_tokens += 1
            
            if not vectors:
                continue  # Already zeros
            
            # Aggregate (vectors are already clipped, so no overflow)
            vectors = np.array(vectors, dtype=np.float32)
            
            if self.aggregation == "mean":
                emb = vectors.mean(axis=0)
            elif self.aggregation == "max":
                emb = vectors.max(axis=0)
            elif self.aggregation == "sum":
                emb = vectors.sum(axis=0)
            else:
                emb = vectors.mean(axis=0)
            
            # Safety: replace any remaining NaN/Inf with zeros
            emb = np.nan_to_num(emb, nan=0.0, posinf=0.0, neginf=0.0)
            
            # Final clamp to reasonable range
            emb = np.clip(emb, -100.0, 100.0)
            
            # Optional: normalize to unit length
            if self.normalize:
                norm = np.linalg.norm(emb)
                if norm > 1e-8:
                    emb = emb / norm
            
            embeddings[idx] = emb.astype(np.float32)
        
        # Final validation
        if np.isnan(embeddings).any():
            self.logger.warning("NaN detected in output, replacing with zeros")
            embeddings = np.nan_to_num(embeddings, nan=0.0)
        
        if np.isinf(embeddings).any():
            self.logger.warning("Inf detected in output, replacing with zeros")
            embeddings = np.nan_to_num(embeddings, posinf=0.0, neginf=0.0)
        
        return {"embeddings": embeddings}
    
    def get_stats(self) -> Dict[str, Any]:
        """Get tokenization and OOV statistics."""
        total = max(1, self.total_tokens)
        return {
            'total_tokens': self.total_tokens,
            'matched_tokens': self.matched_tokens,
            'oov_tokens': self.oov_tokens,
            'clipped_vectors': self.clipped_vectors,
            'match_rate': f"{100 * self.matched_tokens / total:.1f}%",
            'oov_rate': f"{100 * self.oov_tokens / total:.1f}%",
        }


# =============================================================================
# SQLITE CACHE
# =============================================================================

class EmbeddingCache:
    """SQLite cache for embeddings."""
    
    def __init__(self, db_path: Path, logger: logging.Logger):
        self.db_path = db_path
        self.logger = logger
        self.connection: Optional[sqlite3.Connection] = None
    
    def __enter__(self):
        self.connection = self._init_sqlite()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.connection:
            self.connection.commit()
            self.connection.close()
    
    def _init_sqlite(self) -> sqlite3.Connection:
        self.db_path.parent.mkdir(parents=True, exist_ok=True)
        con = sqlite3.connect(str(self.db_path), timeout=60.0)
        
        pragmas = {
            "journal_mode": "WAL",
            "synchronous": "NORMAL",
            "temp_store": "MEMORY",
            "cache_size": -200000,
            "mmap_size": 268435456,
        }
        for k, v in pragmas.items():
            con.execute(f"PRAGMA {k}={v};")
        
        con.execute("""
            CREATE TABLE IF NOT EXISTS embeddings (
                sha256    TEXT PRIMARY KEY,
                code      TEXT NOT NULL,
                model     TEXT NOT NULL,
                dim       INTEGER NOT NULL,
                vec       BLOB NOT NULL,
                added_at  INTEGER NOT NULL,
                tok_ids   BLOB,
                attn_mask BLOB,
                tok_len   INTEGER,
                truncated INTEGER,
                kind      TEXT
            );
        """)
        con.execute("CREATE INDEX IF NOT EXISTS idx_model ON embeddings(model);")
        con.execute("CREATE INDEX IF NOT EXISTS idx_kind ON embeddings(kind);")
        
        con.execute("""
            CREATE TABLE IF NOT EXISTS emb_config (
                key TEXT PRIMARY KEY,
                value TEXT
            );
        """)
        
        con.commit()
        return con
    
    def upsert_config(self, kv: Dict[str, str]) -> None:
        rows = list(kv.items())
        self.connection.executemany(
            "INSERT INTO emb_config(key, value) VALUES(?, ?) "
            "ON CONFLICT(key) DO UPDATE SET value=excluded.value;",
            rows
        )
        self.connection.commit()
    
    def get_config(self) -> Dict[str, str]:
        cur = self.connection.execute("SELECT key, value FROM emb_config")
        return dict(cur.fetchall())
    
    def batch_check_existing(self, sha_list: List[str], model: Optional[str] = None) -> Set[str]:
        if not sha_list:
            return set()
        found: Set[str] = set()
        for i in range(0, len(sha_list), 900):
            chunk = sha_list[i:i+900]
            placeholders = ",".join("?" * len(chunk))
            if model:
                q = f"SELECT sha256 FROM embeddings WHERE model = ? AND sha256 IN ({placeholders})"
                params = [model] + chunk
            else:
                q = f"SELECT sha256 FROM embeddings WHERE sha256 IN ({placeholders})"
                params = chunk
            cur = self.connection.execute(q, params)
            found.update(x[0] for x in cur.fetchall())
        return found
    
    def get_stats(self) -> Dict[str, Any]:
        cur = self.connection.execute("SELECT COUNT(*) FROM embeddings")
        total = cur.fetchone()[0]
        
        cur = self.connection.execute(
            "SELECT model, dim, COUNT(*) FROM embeddings GROUP BY model, dim"
        )
        by_model = [(m, d, c) for m, d, c in cur.fetchall()]
        
        cur = self.connection.execute(
            "SELECT kind, COUNT(*) FROM embeddings GROUP BY kind"
        )
        by_kind = dict(cur.fetchall())
        
        return {
            "total": total,
            "by_model": by_model,
            "by_kind": by_kind,
        }


# =============================================================================
# CSV LOADING
# =============================================================================

def load_strings_to_embed(
    csv_paths: List[Path],
    kind_filter: Optional[str],
    logger: logging.Logger,
    validate: bool = True,
) -> List[Tuple[str, str, str, int]]:
    """
    Load strings from CSV files generated by vocab_builder.py.
    
    Expected format: sha256, kind, string, count
    """
    logger.info(f"[CSV] Loading {len(csv_paths)} file(s)")
    
    merged: Dict[str, Dict[str, Any]] = {}
    total_rows = 0
    skipped_rows = 0
    
    for p in csv_paths:
        if not p.exists():
            logger.warning(f"[CSV] File not found: {p}")
            continue
        
        with p.open("r", encoding="utf-8", errors="replace") as f:
            rdr = csv.DictReader(f)
            
            if validate and rdr.fieldnames:
                expected = {"sha256", "kind", "string", "count"}
                actual = set(rdr.fieldnames)
                if not expected.issubset(actual):
                    logger.warning(f"[CSV] Unexpected format in {p.name}")
                    logger.warning(f"[CSV]   Expected: {expected}")
                    logger.warning(f"[CSV]   Got: {actual}")
            
            for row in rdr:
                total_rows += 1
                
                sha = (row.get("sha256") or "").strip()
                kind = (row.get("kind") or "").strip()
                s = row.get("string") or ""
                
                try:
                    cnt = int(row.get("count", 1))
                except (ValueError, TypeError):
                    cnt = 1
                
                if not sha or len(sha) != 64:
                    skipped_rows += 1
                    continue
                
                if kind_filter and kind not in {kind_filter, "mixed"}:
                    continue
                
                if not s or not s.strip():
                    skipped_rows += 1
                    continue
                
                if validate and sha256_func:
                    computed_sha = sha256_func(s)
                    if computed_sha != sha:
                        logger.debug(f"[CSV] SHA mismatch for '{s[:30]}...'")
                
                prev = merged.get(sha)
                if prev is None:
                    merged[sha] = {"kind": kind, "string": s, "count": cnt, "kinds": {kind}}
                else:
                    prev["kinds"].add(kind)
                    if cnt > prev["count"]:
                        prev["kind"] = kind
                        prev["string"] = s
                        prev["count"] = cnt
    
    if skipped_rows > 0:
        logger.info(f"[CSV] Skipped {skipped_rows} invalid rows")
    
    logger.info(f"[CSV] rows={total_rows} -> unique={len(merged)}")
    
    mixed = sum(1 for v in merged.values() if len(v["kinds"]) > 1)
    if mixed:
        logger.info(f"[CSV] {mixed} strings appear in multiple kinds")
    
    items = sorted(
        merged.items(),
        key=lambda kv: (-kv[1]["count"], kv[1]["kind"], kv[1]["string"])
    )
    return [
        (
            sha,
            ("mixed" if len(v["kinds"]) > 1 else v["kind"]),
            v["string"],
            v["count"],
        )
        for sha, v in items
    ]


# =============================================================================
# HELPER FUNCTIONS
# =============================================================================

def now_seconds() -> int:
    return int(time.time())


def batched(items: List[Any], bs: int):
    for i in range(0, len(items), bs):
        yield items[i:i + bs]


def format_time(seconds: float) -> str:
    if seconds < 60:
        return f"{seconds:.1f}s"
    elif seconds < 3600:
        return f"{seconds/60:.1f}m"
    else:
        return f"{seconds/3600:.1f}h"


# =============================================================================
# MAIN
# =============================================================================

def parse_args():
    ap = argparse.ArgumentParser(
        description="Multi-model embedding extractor V3 (Fixed)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # GraphCodeBERT (default, 768 dims) - node + edge in one run
    python multi_extractor.py --strings-csv strings.csv --code-emb-cache emb.sqlite \\
        --model-type graphcodebert

    # GraphCodeBERT - node_content only (run separately if you want split passes)
    python multi_extractor.py --strings-csv strings.csv --code-emb-cache emb.sqlite \\
        --model-type graphcodebert --kind node_content

    # GraphCodeBERT - edge_content only (EdgeProperty strings)
    python multi_extractor.py --strings-csv strings.csv --code-emb-cache emb.sqlite \\
        --model-type graphcodebert --kind edge_content

    # Compressed GraphCodeBERT (768 -> 256 dims)
    python multi_extractor.py --strings-csv strings.csv --code-emb-cache emb.sqlite \\
        --model-type graphcodebert --compress-to 256

    # Word2Vec (custom trained)
    python multi_extractor.py --strings-csv strings.csv --code-emb-cache emb.sqlite \\
        --model-type word2vec --word2vec-path /path/to/code_word2vec.bin
"""
    )
    
    ap.add_argument("--strings-csv", nargs="+", required=True,
                   help="Path(s) to strings_to_embed.csv from vocab_builder.py")
    ap.add_argument("--code-emb-cache", required=True,
                   help="Output SQLite path")
    ap.add_argument("--log-file", default="./multi_extractor.log")
    
    ap.add_argument("--kind", choices=["node_content", "edge_content"],
                   help="Filter rows by kind")
    
    # Model selection
    ap.add_argument("--model-type", default="graphcodebert",
                   choices=list(MODEL_CONFIGS.keys()) + ["word2vec"],
                   help="Embedding model type (default: graphcodebert)")
    ap.add_argument("--word2vec-path", default=None,
                   help="Path to Word2Vec model (only if model-type=word2vec)")
    
    # Compression
    ap.add_argument("--compress-to", type=int, default=None,
                   help="Compress embeddings to this dimension (e.g., 64, 128, 256)")
    
    ap.add_argument("--max-len", type=int, default=510,
                   help="Maximum sequence length (default: 510)")
    ap.add_argument("--batch-size", type=int, default=64,
                   help="Batch size (default: 64)")
    ap.add_argument("--device", default="auto", choices=["auto", "cpu", "cuda"],
                   help="Device to use (default: auto)")
    ap.add_argument("--pooling", default="mean", choices=["cls", "mean"],
                   help="Pooling strategy (default: mean)")
    
    ap.add_argument("--skip-existing", action="store_true",
                   help="Skip strings already in cache")
    ap.add_argument("--commit-every", type=int, default=10000,
                   help="Commit to DB every N embeddings")
    
    ap.add_argument("--no-validate", dest="validate", action="store_false", default=True,
                   help="Skip CSV validation")
    
    ap.add_argument("--stats-only", action="store_true",
                   help="Only show cache statistics, don't process")
    ap.add_argument("--allow-mixed-models", action="store_true",
                   help="Allow reusing a cache with different model settings")
    
    # Word2Vec specific options
    ap.add_argument("--no-normalize", dest="normalize", action="store_false", default=True,
                   help="Don't normalize Word2Vec embeddings to unit length")
    ap.add_argument("--clip-value", type=float, default=50.0,
                   help="Clip Word2Vec vectors to this range before aggregation (default: 50.0)")
    
    return ap.parse_args()


def main():
    args = parse_args()
    logger = setup_logging(Path(args.log_file))
    
    os.environ.setdefault("TOKENIZERS_PARALLELISM", "false")
    
    logger.info("=" * 60)
    logger.info("MULTI-MODEL EMBEDDING EXTRACTOR V3 (FIXED)")
    logger.info("=" * 60)
    
    # Stats only mode
    if args.stats_only:
        cache_path = Path(args.code_emb_cache)
        if cache_path.exists():
            with EmbeddingCache(cache_path, logger) as cache:
                stats = cache.get_stats()
                config = cache.get_config()
                logger.info(f"[STATS] Cache: {cache_path}")
                logger.info(f"[STATS] Total embeddings: {stats['total']:,}")
                logger.info(f"[STATS] By model: {stats['by_model']}")
                logger.info(f"[STATS] By kind: {stats['by_kind']}")
                logger.info(f"[STATS] Config: {config}")
        else:
            logger.info(f"[STATS] Cache not found: {cache_path}")
        return
    
    logger.info(f"Model type: {args.model_type}")
    if args.compress_to:
        logger.info(f"Compression: -> {args.compress_to} dims")
    
    if normalize_func:
        logger.info("[CONFIG] shared_text_norm loaded for validation")
    else:
        logger.info("[CONFIG] shared_text_norm not available")
    
    # Load CSV
    csv_paths = [Path(p) for p in args.strings_csv]
    rows = load_strings_to_embed(csv_paths, args.kind, logger, validate=args.validate)
    logger.info(f"[CSV] Loaded {len(rows):,} unique strings")
    
    if not rows:
        logger.warning("[CSV] No strings to process!")
        return
    
    # Initialize model
    if args.model_type == "word2vec":
        if not args.word2vec_path:
            raise ValueError("--word2vec-path required for word2vec model")
        model = Word2VecEmbedder(
            args.word2vec_path,
            aggregation="mean",
            normalize=args.normalize,
            clip_value=args.clip_value,
            logger=logger,
        )
        model_name = f"word2vec:{Path(args.word2vec_path).stem}"
    else:
        model = MultiModelEmbedder(
            args.model_type,
            device=args.device,
            max_len=args.max_len,
            pooling=args.pooling,
            compress_to=args.compress_to,
            logger=logger,
        )
        model_name = args.model_type
        if args.compress_to:
            model_name = f"{model_name}_c{args.compress_to}"
    
    # Open cache
    with EmbeddingCache(Path(args.code_emb_cache), logger) as cache:
        expected_config = {
            "model": model_name,
            "model_type": args.model_type,
            "dim": str(model.dim),
            "max_len": str(args.max_len),
            "pooling": args.pooling,
            "compress_to": str(args.compress_to or ""),
            "version": "3.0",
        }
        existing_config = cache.get_config()
        if existing_config:
            mismatches = {}
            for key, value in expected_config.items():
                existing_value = existing_config.get(key)
                if existing_value and existing_value != value:
                    mismatches[key] = (existing_value, value)
            if mismatches and not args.allow_mixed_models:
                logger.error("[CACHE] Existing cache config does not match requested model settings")
                for key, (old, new) in mismatches.items():
                    logger.error(f"[CACHE]   {key}: cache={old} requested={new}")
                logger.error("[CACHE] Use a new cache file or pass --allow-mixed-models")
                return
            if mismatches:
                logger.warning("[CACHE] Proceeding with mixed model settings; cache may be inconsistent")
        cache.upsert_config(expected_config)
        
        # Filter existing
        to_process = rows
        if args.skip_existing:
            keep_shas = [sha for (sha, _, _, _) in rows]
            existing = cache.batch_check_existing(keep_shas, model_name)
            to_process = [(s, k, t, c) for (s, k, t, c) in rows if s not in existing]
            logger.info(f"[SKIP] existing={len(existing):,} -> remaining={len(to_process):,}")
        
        if not to_process:
            logger.info("[DONE] All strings already in cache!")
            return
        
        # Process batches
        INS = (
            "INSERT OR REPLACE INTO embeddings "
            "(sha256, code, model, dim, vec, added_at, kind) "
            "VALUES (?, ?, ?, ?, ?, ?, ?)"
        )
        
        inserted = 0
        errors = 0
        start = time.time()
        
        total_batches = (len(to_process) + args.batch_size - 1) // args.batch_size
        for batch in tqdm(batched(to_process, args.batch_size), total=total_batches, desc="Embedding"):
            texts = [s for (_, _, s, _) in batch]
            shas = [sha for (sha, _, _, _) in batch]
            kinds = [k for (_, k, _, _) in batch]
            
            try:
                out = model.embed_batch(texts, store_token_data=False)
                vecs = out["embeddings"]
                now = now_seconds()
                
                rows_to_insert = [
                    (shas[i], texts[i], model_name, int(vecs.shape[1]),
                     vecs[i].tobytes(), now, kinds[i])
                    for i in range(len(shas))
                ]
                cache.connection.executemany(INS, rows_to_insert)
                inserted += len(rows_to_insert)
                
            except RuntimeError as e:
                if "out of memory" in str(e).lower():
                    logger.warning(f"[OOM] Batch OOM, skipping {len(batch)} strings")
                    torch.cuda.empty_cache()
                    errors += len(batch)
                else:
                    logger.error(f"[ERROR] {e}")
                    errors += len(batch)
            except Exception as e:
                logger.error(f"[ERROR] {e}")
                errors += len(batch)
            
            if inserted and (inserted % args.commit_every == 0):
                cache.connection.commit()
                elapsed = time.time() - start
                rate = inserted / max(elapsed, 1)
                eta = (len(to_process) - inserted) / max(rate, 1)
                logger.info(f"[PROGRESS] {inserted:,}/{len(to_process):,} | "
                           f"{rate:.1f} emb/s | ETA: {format_time(eta)}")
        
        cache.connection.commit()
        elapsed = time.time() - start
        rate = inserted / max(elapsed, 1) if inserted else 0
        
        # Print Word2Vec stats if applicable
        if args.model_type == "word2vec" and hasattr(model, 'get_stats'):
            w2v_stats = model.get_stats()
            logger.info("=" * 60)
            logger.info("WORD2VEC TOKENIZATION STATS")
            logger.info("=" * 60)
            logger.info(f"Total tokens:    {w2v_stats['total_tokens']:,}")
            logger.info(f"Matched tokens:  {w2v_stats['matched_tokens']:,} ({w2v_stats['match_rate']})")
            logger.info(f"OOV tokens:      {w2v_stats['oov_tokens']:,} ({w2v_stats['oov_rate']})")
            logger.info(f"Clipped vectors: {w2v_stats['clipped_vectors']:,}")
        
        logger.info("=" * 60)
        logger.info("EMBEDDING COMPLETE")
        logger.info("=" * 60)
        logger.info(f"Model:    {model_name}")
        logger.info(f"Dim:      {model.dim}")
        logger.info(f"Inserted: {inserted:,}")
        logger.info(f"Errors:   {errors}")
        logger.info(f"Time:     {format_time(elapsed)} ({rate:.1f} emb/s)")
        logger.info(f"Cache:    {args.code_emb_cache}")
        logger.info("=" * 60)


if __name__ == "__main__":
    main()


"""
USAGE EXAMPLES:

# ---------------------------------------------------------------------------
# Shared paths (adjust once if needed)
# ---------------------------------------------------------------------------
DEVIGN_VOCAB="./Clean_exports/devign_vocab_full"
DRAPER_VOCAB="./Clean_exports/draper_vocab_full"
REVEAL_VOCAB="./Clean_exports/reveal_vocab_full"
PRIMEVUL_VOCAB="./Clean_exports/primevul_vocab_full"

DEVIGN_CACHE="./Clean_exports/cache_devign_v2"
DRAPER_CACHE="./Clean_exports/cache_draper_v2"
REVEAL_CACHE="./Clean_exports/cache_reveal_v2"
PRIMEVUL_CACHE="./Clean_exports/cache_primevul_v2"

# ---------------------------------------------------------------------------
# DEVIGN (full vocab)
# ---------------------------------------------------------------------------
python multi_extractor.py \
    --strings-csv "$DEVIGN_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DEVIGN_CACHE/graphcodebert_768d_full.sqlite" \
    --model-type graphcodebert \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$DEVIGN_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DEVIGN_CACHE/codet5p_256d_full.sqlite" \
    --model-type codet5p \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$DEVIGN_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DEVIGN_CACHE/unixcoder_768d_full.sqlite" \
    --model-type unixcoder \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$DEVIGN_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DEVIGN_CACHE/word2vec_200d_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_200d_full/code_word2vec_200d.bin" \
    --batch-size 512 \
    --clip-value 50.0

python multi_extractor.py \
    --strings-csv "$DEVIGN_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DEVIGN_CACHE/word2vec_100d_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_100d_full/code_word2vec_100d.bin" \
    --batch-size 512 \
    --clip-value 50.0

# ---------------------------------------------------------------------------
# DRAPER (full vocab)
# ---------------------------------------------------------------------------
python multi_extractor.py \
    --strings-csv "$DRAPER_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DRAPER_CACHE/graphcodebert_768d_draper_full.sqlite" \
    --model-type graphcodebert \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$DRAPER_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DRAPER_CACHE/codet5p_256d_draper_full.sqlite" \
    --model-type codet5p \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$DRAPER_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DRAPER_CACHE/unixcoder_768d_draper_full.sqlite" \
    --model-type unixcoder \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$DRAPER_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DRAPER_CACHE/word2vec_200d_draper_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_200d_draper_full/code_word2vec_200d.bin" \
    --batch-size 512 \
    --clip-value 50.0

python multi_extractor.py \
    --strings-csv "$DRAPER_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$DRAPER_CACHE/word2vec_100d_draper_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_100d_draper_full/code_word2vec_100d.bin" \
    --batch-size 512 \
    --clip-value 50.0

# ---------------------------------------------------------------------------
# REVEAL (full vocab)
# ---------------------------------------------------------------------------
python multi_extractor.py \
    --strings-csv "$REVEAL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$REVEAL_CACHE/graphcodebert_768d_reveal_full.sqlite" \
    --model-type graphcodebert \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$REVEAL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$REVEAL_CACHE/codet5p_256d_reveal_full.sqlite" \
    --model-type codet5p \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$REVEAL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$REVEAL_CACHE/unixcoder_768d_reveal_full.sqlite" \
    --model-type unixcoder \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$REVEAL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$REVEAL_CACHE/word2vec_200d_reveal_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_200d_reveal_full/code_word2vec_200d.bin" \
    --batch-size 512 \
    --clip-value 50.0

python multi_extractor.py \
    --strings-csv "$REVEAL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$REVEAL_CACHE/word2vec_100d_reveal_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_100d_reveal_full/code_word2vec_100d.bin" \
    --batch-size 512 \
    --clip-value 50.0

# ---------------------------------------------------------------------------
# PRIMEVUL (full vocab)
# ---------------------------------------------------------------------------
python multi_extractor.py \
    --strings-csv "$PRIMEVUL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$PRIMEVUL_CACHE/graphcodebert_768d_primevul_full.sqlite" \
    --model-type graphcodebert \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$PRIMEVUL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$PRIMEVUL_CACHE/codet5p_256d_primevul_full.sqlite" \
    --model-type codet5p \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$PRIMEVUL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$PRIMEVUL_CACHE/unixcoder_768d_primevul_full.sqlite" \
    --model-type unixcoder \
    --batch-size 512

python multi_extractor.py \
    --strings-csv "$PRIMEVUL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$PRIMEVUL_CACHE/word2vec_200d_primevul_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_200d_primevul_full/code_word2vec_200d.bin" \
    --batch-size 512 \
    --clip-value 50.0

python multi_extractor.py \
    --strings-csv "$PRIMEVUL_VOCAB/strings_to_embed.csv" \
    --code-emb-cache "$PRIMEVUL_CACHE/word2vec_100d_primevul_full.sqlite" \
    --model-type word2vec \
    --word2vec-path "./Clean_exports/word2vec_100d_primevul_full/code_word2vec_100d.bin" \
    --batch-size 512 \
    --clip-value 50.0

# ---------------------------------------------------------------------------
# Cache stats
# ---------------------------------------------------------------------------
python multi_extractor.py \
    --strings-csv dummy.csv \
    --code-emb-cache /path/to/cache.sqlite \
    --stats-only

"""
