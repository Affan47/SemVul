#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ENHANCED ALIGNED embedding extractor — compatible with vocab_builder v3–v5.

Key properties:
- Strict alignment with shared_text_norm (single source of truth).
- Parser-signature awareness (v3+ discovery, v5 auto-promotion).
- Robust SHA preflight, integrity verification, and audit logging.
- OOM-safe, resumable embedding to SQLite (with optional token storage).

This script NEVER parses GraphSON. It only embeds strings from CSV produced
by vocab_builder and relies on shared_text_norm for hashing equivalence.
"""

from __future__ import annotations
import argparse
import csv
import json
import logging
import os
import sqlite3
import sys
import time
import zlib
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Set, Tuple

import numpy as np
import torch
from transformers import AutoModel, AutoTokenizer

# -----------------------------------------------------------------------------
# Resolve shared_text_norm from project Scripts/ if available
# -----------------------------------------------------------------------------
def _import_shared_text_norm():
    here = Path(__file__).resolve().parent
    scripts_dir = (here / ".." / "workspace" / "Scripts_and_saved_Models" / "Scripts").resolve()
    if scripts_dir.exists():
        sys.path.insert(0, str(scripts_dir))
    try:
        from shared_text_norm import (
            normalize_for_embedding,
            sha256_normalized,
            get_normalization_config,
            validate_normalization_consistency,  # noqa: F401 (used during dev sometimes)
        )
        cfg = get_normalization_config()
        print(f"[ALIGNMENT] shared_text_norm version: {cfg.get('version')}")
        print(f"[ALIGNMENT] text len window: {cfg['min_len']}-{cfg['max_len']} | "
              f"angle_brackets={cfg['drop_angle_bracketed']}")
        return normalize_for_embedding, sha256_normalized, cfg
    except Exception as e:
        print("[ALIGNMENT ERROR] Could not import shared_text_norm.py:", e)
        raise RuntimeError("shared_text_norm.py is required for SHA alignment.")
# load once
normalize_for_embedding, sha256_normalized, NORM_CFG = _import_shared_text_norm()

# -----------------------------------------------------------------------------
# TQDM fallback
# -----------------------------------------------------------------------------
try:
    from tqdm import tqdm
except Exception:   # pragma: no cover
    def tqdm(x=None, *a, **k):
        return x if x is not None else range(0)

# -----------------------------------------------------------------------------
# Logging
# -----------------------------------------------------------------------------
def setup_logging(log_file: Path) -> logging.Logger:
    logger = logging.getLogger("embed_aligned")
    logger.setLevel(logging.INFO)
    fmt = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s",
                            datefmt="%Y-%m-%d %H:%M:%S")
    log_file.parent.mkdir(parents=True, exist_ok=True)
    fh = logging.FileHandler(log_file, encoding="utf-8")
    fh.setFormatter(fmt)
    ch = logging.StreamHandler()
    ch.setFormatter(fmt)
    logger.handlers.clear()
    logger.addHandler(fh)
    logger.addHandler(ch)
    return logger

# -----------------------------------------------------------------------------
# Parser signature validation (v3–v5 aware)
# -----------------------------------------------------------------------------
def _safe_len_features(features: Any) -> int:
    if isinstance(features, (list, tuple, set)):
        return len(features)
    if isinstance(features, dict):
        return len(features)
    return 1 if features is not None else 0

def validate_csv_alignment(csv_path: Path, logger: logging.Logger) -> bool:
    """
    Check that parser_sig.json exists and contains sane metadata.
    This is intentionally tolerant (warns rather than fails for older versions).
    """
    sig_path = csv_path.parent / "parser_sig.json"
    if not sig_path.exists():
        logger.warning(f"[ALIGNMENT] Missing parser_sig.json next to {csv_path.name} — proceeding cautiously")
        return True

    try:
        parser_sig = json.loads(sig_path.read_text(encoding="utf-8"))
    except Exception as e:
        logger.warning(f"[ALIGNMENT] Could not parse parser_sig.json: {e}")
        return True

    version = str(parser_sig.get("version", "unknown"))
    features = parser_sig.get("features", [])
    logger.info(f"[ALIGNMENT] parser_sig version={version} | features={_safe_len_features(features)}")

    # v3/v4 discovery report
    disc = parser_sig.get("validation", {}).get("discovery_report", {})
    if disc:
        dn = disc.get("discovered_nodes", [])
        de = disc.get("discovered_edges", [])
        logger.info(f"[ALIGNMENT] discovery: nodes={len(dn)} edges={len(de)}")

    # v5 auto-promotion
    auto = parser_sig.get("auto_promotion", {})
    if auto:
        edges = auto.get("edges", {})
        nodes = auto.get("nodes", {})
        e_ok = edges.get("success", False)
        n_ok = nodes.get("success", False)
        e_prom = edges.get("promoted_edges", {}) or {}
        n_sem = nodes.get("promoted_semantic", []) or []
        n_str = nodes.get("promoted_structural", []) or []
        logger.info(f"[ALIGNMENT] v5 auto-promotion: edges_ok={e_ok} nodes_ok={n_ok} "
                    f"| promoted_edges={len(e_prom)} "
                    f"| promoted_nodes={len(n_sem) + len(n_str)}")

    # Basic Devign schema sanity (optional)
    validation = parser_sig.get("validation", {})
    miss = validation.get("edge_types_missing", [])
    if miss:
        logger.warning(f"[ALIGNMENT] Devign edge set incomplete: missing={miss}")
    return True

# -----------------------------------------------------------------------------
# Small helpers
# -----------------------------------------------------------------------------
def now_seconds() -> int:
    return int(time.time())

def batched(items: List[Any], bs: int) -> Iterable[List[Any]]:
    for i in range(0, len(items), bs):
        yield items[i:i + bs]

# -----------------------------------------------------------------------------
# CSV loading
# -----------------------------------------------------------------------------
def load_strings_to_embed(
    csv_paths: List[Path],
    kind_filter: Optional[str],
    logger: Optional[logging.Logger],
    do_validate: bool,
) -> List[Tuple[str, str, str, int]]:
    """
    Returns list of (sha256, kind, string, count), highest-count per SHA kept.
    """
    if logger:
        logger.info(f"[CSV] loading {len(csv_paths)} file(s) | validate={do_validate}")

    if do_validate:
        for p in csv_paths:
            if not validate_csv_alignment(p, logger):
                raise RuntimeError(f"alignment validation failed for {p}")

    merged: Dict[str, Tuple[str, str, int]] = {}
    total_rows = 0

    for p in csv_paths:
        with p.open("r", encoding="utf-8") as f:
            rdr = csv.DictReader(f)
            for row in rdr:
                total_rows += 1
                sha = (row.get("sha256") or "").strip()
                kind = (row.get("kind") or "").strip()
                s = row.get("string") or ""
                try:
                    cnt = int(row.get("count", 1))
                except Exception:
                    cnt = 1

                if kind_filter and kind not in {kind_filter, "mixed"}:
                    continue
                if not sha:
                    continue

                prev = merged.get(sha)
                if prev is None or cnt > prev[2]:
                    merged[sha] = (kind, s, cnt)

    if logger:
        node_cnt = sum(1 for _, (k, _, _) in merged.items() if k == "node_content")
        edge_cnt = sum(1 for _, (k, _, _) in merged.items() if k == "edge_content")
        logger.info(f"[CSV] rows={total_rows} → unique={len(merged)} "
                    f"(node={node_cnt} edge={edge_cnt})")

    # Stable order: by count desc, then kind, then string
    items = sorted(merged.items(), key=lambda kv: (-kv[1][2], kv[1][0], kv[1][1]))
    return [(sha, k, s, c) for sha, (k, s, c) in items]

# -----------------------------------------------------------------------------
# SQLite cache
# -----------------------------------------------------------------------------
class EmbeddingCache:
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
            "cache_size": -200000,      # ~200MB
            "mmap_size": 268435456,     # 256MB
            "foreign_keys": "ON",
            "locking_mode": "NORMAL",
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
                truncated INTEGER
            );
        """)
        con.execute("CREATE INDEX IF NOT EXISTS idx_model ON embeddings(model);")
        con.execute("CREATE INDEX IF NOT EXISTS idx_added_at ON embeddings(added_at);")

        con.execute("""
            CREATE TABLE IF NOT EXISTS strings_meta (
                sha256 TEXT PRIMARY KEY,
                kind   TEXT,
                count  INTEGER
            );
        """)
        con.execute("""
            CREATE TABLE IF NOT EXISTS emb_config (
                key TEXT PRIMARY KEY,
                value TEXT
            );
        """)
        con.execute("""
            CREATE TABLE IF NOT EXISTS alignment_log (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                timestamp  INTEGER NOT NULL,
                event_type TEXT NOT NULL,
                details    TEXT,
                status     TEXT,
                vocab_version TEXT,
                auto_promotion_data TEXT
            );
        """)
        con.execute("""
            CREATE TABLE IF NOT EXISTS promotion_log (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                timestamp  INTEGER NOT NULL,
                vocab_version TEXT NOT NULL,
                edge_promotions TEXT,
                node_promotions TEXT,
                success INTEGER NOT NULL
            );
        """)
        con.commit()
        return con

    # ---- alignment / promotion logs ----
    def log_alignment_event(self, event_type: str, details: str,
                            status: str = "OK",
                            vocab_version: str = "",
                            auto_promotion_data: str = "") -> None:
        self.connection.execute(
            "INSERT INTO alignment_log "
            "(timestamp, event_type, details, status, vocab_version, auto_promotion_data) "
            "VALUES (?, ?, ?, ?, ?, ?)",
            (now_seconds(), event_type, details, status, vocab_version, auto_promotion_data)
        )

    def log_promotion_data(self, vocab_version: str,
                           edge_promotions: Dict[str, str],
                           node_promotions: Dict[str, List[str]],
                           success: bool) -> None:
        ep = json.dumps(edge_promotions or {})
        np = json.dumps(node_promotions or {})
        self.connection.execute(
            "INSERT INTO promotion_log "
            "(timestamp, vocab_version, edge_promotions, node_promotions, success) "
            "VALUES (?, ?, ?, ?, ?)",
            (now_seconds(), vocab_version, ep, np, 1 if success else 0)
        )

    # ---- utilities ----
    def upsert_config(self, kv: Dict[str, str]) -> None:
        rows = list(kv.items())
        self.connection.executemany(
            "INSERT INTO emb_config(key, value) VALUES(?, ?) "
            "ON CONFLICT(key) DO UPDATE SET value=excluded.value;",
            rows
        )
        self.connection.commit()

    def batch_check_existing(self, sha_list: List[str]) -> Set[str]:
        if not sha_list:
            return set()
        found: Set[str] = set()
        for i in range(0, len(sha_list), 900):   # param cap safety
            chunk = sha_list[i:i+900]
            q = f"SELECT sha256 FROM embeddings WHERE sha256 IN ({','.join('?'*len(chunk))})"
            cur = self.connection.execute(q, chunk)
            found.update(x[0] for x in cur.fetchall())
        return found

    def prune_not_in(self, keep_shas: List[str]) -> int:
        if not keep_shas:
            return 0
        con = self.connection
        con.execute("CREATE TEMP TABLE IF NOT EXISTS keep(sha256 TEXT PRIMARY KEY);")
        con.executemany("INSERT OR IGNORE INTO keep(sha256) VALUES (?);", [(s,) for s in keep_shas])
        before = con.execute("SELECT COUNT(*) FROM embeddings;").fetchone()[0]
        con.execute("DELETE FROM embeddings WHERE sha256 NOT IN (SELECT sha256 FROM keep);")
        con.execute("DROP TABLE keep;")
        after = con.execute("SELECT COUNT(*) FROM embeddings;").fetchone()[0]
        con.commit()
        return int(before - after)

# -----------------------------------------------------------------------------
# Embedding model wrapper
# -----------------------------------------------------------------------------
class EmbeddingModel:
    def __init__(self,
                 model_name: str,
                 device: str,
                 max_len: int,
                 pooling: str,
                 logger: logging.Logger,
                 hf_revision: Optional[str] = None):
        if device == "auto":
            dev = "cuda" if torch.cuda.is_available() else "cpu"
        else:
            dev = device
        self.device = torch.device(dev)
        self.max_len = min(int(max_len), 510)  # leave room for special tokens
        self.pooling = pooling
        self.logger = logger

        self.logger.info(f"[MODEL] {model_name} on {self.device} | max_len={self.max_len}")

        tok_kwargs = {}
        if hf_revision:
            tok_kwargs["revision"] = hf_revision
        self.tokenizer = AutoTokenizer.from_pretrained(model_name, **tok_kwargs)

        mdl_kwargs = {}
        if hf_revision:
            mdl_kwargs["revision"] = hf_revision
        self.model = AutoModel.from_pretrained(model_name, **mdl_kwargs).to(self.device)
        self.model.eval()

        hidden = getattr(self.model.config, "hidden_size", None)
        mpe = getattr(self.model.config, "max_position_embeddings", None)
        if mpe and self.max_len > int(mpe) - 2:
            self.logger.warning(f"[MODEL] max_len={self.max_len} may exceed capacity={mpe}")
        if hidden:
            self.logger.info(f"[MODEL] hidden_size={int(hidden)}")

    @torch.no_grad()
    def embed_batch(self, texts: List[str], store_token_data: bool = True) -> Dict[str, Any]:
        tok = self.tokenizer(
            texts,
            padding=True,
            truncation=True,
            max_length=self.max_len,
            return_tensors="pt",
            return_attention_mask=True,
        )
        tok = {k: v.to(self.device) for k, v in tok.items()}

        use_amp = (self.device.type == "cuda")
        with torch.autocast(device_type=self.device.type, enabled=use_amp):
            out = self.model(**tok)
            last = out.last_hidden_state  # [B, T, H]
            if self.pooling == "mean":
                mask = tok["attention_mask"].unsqueeze(-1)     # [B, T, 1]
                summed = (last * mask).sum(dim=1)              # [B, H]
                cnt = mask.sum(dim=1).clamp(min=1e-9)          # [B, 1]
                emb = (summed / cnt).to(torch.float32)
            
            elif self.pooling == "max":
                # [Option B] Max Pooling with Masking
                mask = tok["attention_mask"].unsqueeze(-1)     # [B, T, 1]
                # Fill padding positions with -1e9 so they are never selected as max
                # (Standard padding is 0, valid tokens are 1)
                input_masked = last.masked_fill(mask == 0, -1e9)
                emb = torch.max(input_masked, dim=1).values.to(torch.float32)
            else:
                emb = last[:, 0, :].to(torch.float32)          # CLS

        res = {"embeddings": emb.cpu().numpy().astype(np.float32)}
        if store_token_data:
            res["token_data"] = self._pack_token_data(tok)
        return res

    def _pack_token_data(self, tok: Dict[str, torch.Tensor]) -> Dict[str, Any]:
        """
        Store compressed token ids and attention masks (per-sample), and
        compute *true* token length from attention_mask (not padded width).
        """
        ids = tok["input_ids"].detach().cpu().numpy().astype(np.int32)          # [B, T]
        msk = tok["attention_mask"].detach().cpu().numpy().astype(np.int32)     # [B, T]

        def pack_ints(arr: np.ndarray) -> Tuple[bytes, int]:
            return zlib.compress(arr.tobytes()), int(arr.size)

        ids_blobs, msk_blobs, lens, trunc = [], [], [], []
        for i in range(ids.shape[0]):
            b_ids, _ = pack_ints(ids[i])
            b_msk, _ = pack_ints(msk[i])
            ids_blobs.append(b_ids)
            msk_blobs.append(b_msk)
            true_len = int(msk[i].sum())                # number of non-pad tokens
            lens.append(true_len)
            trunc.append(1 if true_len >= self.max_len else 0)

        return {
            "token_ids": ids_blobs,
            "attention_masks": msk_blobs,
            "token_lens": lens,
            "truncations": trunc,
        }

# -----------------------------------------------------------------------------
# CLI
# -----------------------------------------------------------------------------
def parse_args() -> argparse.Namespace:
    ap = argparse.ArgumentParser("Aligned embedding extractor (v3–v5 compatible)")
    ap.add_argument("--strings-csv", nargs="+", required=True,
                    help="Path(s) to strings_to_embed.csv from vocab_builder.")
    ap.add_argument("--code-emb-cache", required=True, help="Output SQLite path.")
    ap.add_argument("--log-file", default="./embed_aligned.log")

    ap.add_argument("--kind", choices=["node_content", "edge_content"],
                    help="Filter rows by kind (default: both).")

    ap.add_argument("--hf-model", default="microsoft/codebert-base")
    ap.add_argument("--hf-revision", default=None,
                    help="Optional HF commit/tag for reproducibility.")
    ap.add_argument("--max-len", type=int, default=128, 
                    help="Default 128 is feasible for AST nodes. Use 510 only for full functions.")
    ap.add_argument("--batch-size", type=int, default=64)
    ap.add_argument("--device", default="auto", choices=["auto", "cpu", "cuda"])
    ap.add_argument("--pooling", default="cls", choices=["cls", "mean", "max"])

    ap.add_argument("--skip-existing", action="store_true",
                    help="Skip SHAs already in DB.")
    ap.add_argument("--commit-every", type=int, default=10000)

    ap.add_argument("--no-store-token-ids", dest="store_token_ids",
                    action="store_false", default=True)

    ap.add_argument("--no-verify-sha", action="store_true",
                    help="Disable per-row SHA recomputation (faster, less safe).")

    ap.add_argument("--prune-not-in-csv", action="store_true",
                    help="Delete DB rows whose sha256 is NOT in the CSV(s).")

    # Proper on/off pair for enhanced CSV validation
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--enhanced-validation", dest="enhanced_validation",
                   action="store_true", default=True,
                   help="Enable parser_sig checks (default).")
    g.add_argument("--no-enhanced-validation", dest="enhanced_validation",
                   action="store_false",
                   help="Disable parser_sig checks (faster).")

    ap.add_argument("--force-alignment", action="store_true",
                    help="Proceed even if alignment checks fail.")

    return ap.parse_args()

# -----------------------------------------------------------------------------
# Main
# -----------------------------------------------------------------------------
def main() -> None:
    args = parse_args()
    logger = setup_logging(Path(args.log_file))

    os.environ.setdefault("HF_HOME", os.path.expanduser("~/.cache/huggingface"))
    os.environ.setdefault("TOKENIZERS_PARALLELISM", "false")

    logger.info("=== ALIGNED EMBEDDING EXTRACTOR ===")
    logger.info(f"[ALIGNMENT] norm_cfg={NORM_CFG}")
    logger.info(f"[ALIGNMENT] enhanced_validation={args.enhanced_validation}")

    csv_paths = [Path(p) for p in args.strings_csv]

    # Load CSV (optional enhanced validation)
    try:
        rows = load_strings_to_embed(csv_paths,
                                     kind_filter=args.kind,
                                     logger=logger,
                                     do_validate=args.enhanced_validation)
        logger.info(f"[CSV] loaded unique strings: {len(rows)}")
    except RuntimeError as e:
        if args.force_alignment:
            logger.warning(f"[ALIGNMENT] validation failed but --force-alignment: {e}")
            rows = load_strings_to_embed(csv_paths,
                                         kind_filter=args.kind,
                                         logger=None,
                                         do_validate=False)
        else:
            raise

    keep_shas = [sha for (sha, _, _, _) in rows]

    # Preflight SHA checks on a sample
    sample_n = min(50, len(rows))
    mism = 0
    logger.info("[ALIGNMENT] preflight SHA check sample size=%d", sample_n)
    for i, (sha, kind, s, cnt) in enumerate(rows[:sample_n]):
        rec = sha256_normalized(s)
        if rec != sha:
            mism += 1
            logger.error("[ALIGNMENT FAIL] row=%d kind=%s cnt=%s csv_sha=%s recomputed=%s text='%s...'",
                         i, kind, cnt, sha[:16], rec[:16], s[:80])
    if mism > 0 and not args.force_alignment:
        raise ValueError(f"SHA preflight mismatches: {mism}/{sample_n}")

    # Open DB
    with EmbeddingCache(Path(args.code_emb_cache), logger) as cache:
        cache.log_alignment_event("sha_validation",
                                  f"sample={sample_n} mismatches={mism}",
                                  "OK" if mism == 0 else "WARNING",
                                  NORM_CFG.get("version", ""),
                                  json.dumps({"sample_size": sample_n, "mismatches": mism}))

        # Log promotions if available from the first CSV’s sig
        sig0 = csv_paths[0].parent / "parser_sig.json"
        if sig0.exists():
            try:
                sig = json.loads(sig0.read_text(encoding="utf-8"))
                auto = sig.get("auto_promotion", {})
                edge_prom = auto.get("edges", {}).get("promoted_edges", {}) or {}
                node_prom = {
                    "semantic": auto.get("nodes", {}).get("promoted_semantic", []) or [],
                    "structural": auto.get("nodes", {}).get("promoted_structural", []) or [],
                }
                ok = bool(auto.get("edges", {}).get("success", False)) and bool(auto.get("nodes", {}).get("success", False))
                cache.log_promotion_data(str(sig.get("version", "unknown")), edge_prom, node_prom, ok)
            except Exception as e:
                logger.warning("[PROMOTION_LOG] could not parse/log: %s", e)

        # Optional pruning BEFORE embedding (keeps DB consistent with CSV)
        if args.prune_not_in_csv:
            deleted = cache.prune_not_in(keep_shas)
            logger.info("[PRUNE] removed rows not in CSV: %d", deleted)
            cache.log_alignment_event("database_prune", f"removed={deleted}")

        # Init model (we need this before writing emb_config so we know dim & effective max_len)
        model = EmbeddingModel(args.hf_model, args.device, args.max_len,
                               args.pooling, logger, hf_revision=args.hf_revision)

        # Record configuration (including embedding dimension) for cache_manager / CacheSignature
        code_dim = int(getattr(model.model.config, "hidden_size", 768))
        cache.upsert_config({
            "model": args.hf_model,
            "hf_revision": str(args.hf_revision or ""),
            "dim": str(code_dim),                         # ← NEW: exposes embedding dimension
            "max_len": str(int(model.max_len)),           # ← use effective max_len (clamped)
            "pooling": args.pooling,
            "store_token_ids": "1" if args.store_token_ids else "0",
            "no_verify_sha": "1" if args.no_verify_sha else "0",
            "alignment_version": NORM_CFG.get("version", ""),
            "text_limits": f"{NORM_CFG['min_len']}-{NORM_CFG['max_len']}",
            "enhanced_validation": "1" if args.enhanced_validation else "0",
            "force_alignment": "1" if args.force_alignment else "0",
        })

        # Filter already-present SHAs
        to_process = rows
        if args.skip_existing:
            existing = cache.batch_check_existing(keep_shas)
            to_process = [(s, k, t, c) for (s, k, t, c) in rows if s not in existing]
            logger.info("[SKIP] existing=%d → remaining=%d", len(existing), len(to_process))


        INS_FULL = (
            "INSERT OR REPLACE INTO embeddings "
            "(sha256, code, model, dim, vec, added_at, tok_ids, attn_mask, tok_len, truncated) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
        )
        INS_MIN = (
            "INSERT OR REPLACE INTO embeddings "
            "(sha256, code, model, dim, vec, added_at) "
            "VALUES (?, ?, ?, ?, ?, ?)"
        )

        inserted = 0
        ok_shas: Set[str] = set()
        skipped: Set[str] = set()
        start = time.time()
        base_bs = max(1, int(args.batch_size))

        for big in tqdm(list(batched(to_process, base_bs)), desc="[embed] batches", unit="batch"):
            texts: List[str] = []
            shas: List[str] = []
            for (sha, _kind, s, _cnt) in big:
                if not args.no_verify_sha:
                    if sha256_normalized(s) != sha:
                        skipped.add(sha)
                        continue
                shas.append(sha)
                texts.append(s)
            if not texts:
                continue

            # OOM-adaptive sub-batching
            left = list(zip(shas, texts))
            sub_bs = len(left)
            while left:
                cur_bs = min(sub_bs, len(left))
                chunk = left[:cur_bs]
                chunk_shas = [x[0] for x in chunk]
                chunk_txts = [x[1] for x in chunk]
                try:
                    out = model.embed_batch(chunk_txts, store_token_data=args.store_token_ids)
                    vecs = out["embeddings"]
                    tokd = out.get("token_data")
                    now = now_seconds()

                    if args.store_token_ids and tokd:
                        rows_to_insert = [
                            (chunk_shas[i], chunk_txts[i], args.hf_model, int(vecs.shape[1]),
                             vecs[i].tobytes(), now,
                             tokd["token_ids"][i], tokd["attention_masks"][i],
                             int(tokd["token_lens"][i]), int(tokd["truncations"][i]))
                            for i in range(len(chunk_shas))
                        ]
                        cache.connection.executemany(INS_FULL, rows_to_insert)
                        inserted += len(rows_to_insert)
                    else:
                        rows_to_insert = [
                            (chunk_shas[i], chunk_txts[i], args.hf_model, int(vecs.shape[1]),
                             vecs[i].tobytes(), now)
                            for i in range(len(chunk_shas))
                        ]
                        cache.connection.executemany(INS_MIN, rows_to_insert)
                        inserted += len(rows_to_insert)

                    ok_shas.update(chunk_shas)
                    left = left[cur_bs:]
                except RuntimeError as e:
                    msg = str(e).lower()
                    if "out of memory" in msg or "cuda" in msg:
                        if cur_bs == 1:
                            logger.error("[OOM] single-item still OOM; skipping text='%s...'", chunk_txts[0][:100])
                            left = left[1:]
                        else:
                            sub_bs = max(1, cur_bs // 2)
                            logger.warning("[OOM] reducing sub-batch → %d", sub_bs)
                            torch.cuda.empty_cache()
                    else:
                        logger.error("[EMBED ERROR] %s", e)
                        left = left[cur_bs:]

            if inserted and (inserted % max(1, args.commit_every) == 0):
                cache.connection.commit()
                elapsed = time.time() - start
                rate = inserted / max(elapsed, 1e-9)
                logger.info("[PROGRESS] inserted=%d | %.1fs | %.1f emb/s", inserted, elapsed, rate)

        # Final commit & integrity verification
        cache.connection.commit()
        elapsed = time.time() - start
        rate = inserted / max(elapsed, 1e-9)

        logger.info("[INTEGRITY] verifying presence of all CSV SHAs …")
        db_shas: Set[str] = set()
        for chunk in batched(keep_shas, 900):
            q = f"SELECT sha256 FROM embeddings WHERE sha256 IN ({','.join('?'*len(chunk))})"
            cur = cache.connection.execute(q, chunk)
            db_shas.update(x[0] for x in cur.fetchall())

        missing = set(keep_shas) - db_shas
        if missing:
            logger.error("[INTEGRITY] missing=%d (showing up to 5): %s",
                         len(missing), list(sorted(missing))[:5])
            cache.log_alignment_event("integrity_check",
                                      f"missing={len(missing)}", "ERROR",
                                      NORM_CFG.get("version", ""))
            raise ValueError(f"Integrity check failed: {len(missing)} missing embeddings")
        else:
            logger.info("[INTEGRITY] all %d SHAs present", len(keep_shas))
            cache.log_alignment_event("integrity_check",
                                      f"present={len(keep_shas)}", "OK",
                                      NORM_CFG.get("version", ""))

        # strings_meta
        keep_set = set(keep_shas)
        meta_rows = [(sha, kind, int(cnt))
                     for (sha, kind, _s, cnt) in rows
                     if sha in keep_set and sha in ok_shas]
        if meta_rows:
            cache.connection.executemany(
                "INSERT INTO strings_meta(sha256, kind, count) VALUES (?, ?, ?) "
                "ON CONFLICT(sha256) DO UPDATE SET kind=excluded.kind, count=excluded.count;",
                meta_rows
            )
            cache.connection.commit()
            logger.info("[META] upserted rows=%d", len(meta_rows))

        logger.info("=== EMBEDDING COMPLETE ===")
        logger.info("inserted=%d | ok=%d | skipped_sha_mismatch=%d", inserted, len(ok_shas), len(skipped))
        logger.info("elapsed=%.1fs | rate=%.1f emb/s | db=%s", elapsed, rate, args.code_emb_cache)


if __name__ == "__main__":
    main()


"""
python simple_extractor.py \
  --strings-csv "./Clean_exports/devign_vocab_normfunc_v2/strings_to_embed.csv" \
  --code-emb-cache "./Clean_exports/cache_devign_v2/codebert_v2.sqlite" \
  --hf-model "microsoft/graphcodebert-base"" \
  --max-len 128 \
  --batch-size 256 \
  --pooling max \
  --skip-existing \
  --prune-not-in-csv \
  --log-file "./Clean_exports/cache_devign_v2/embed_devign_normfunc.log"

"""
