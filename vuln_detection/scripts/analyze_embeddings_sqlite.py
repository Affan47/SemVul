#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
analyze_embeddings_sqlite.py

Offline quality checker for embedding SQLite files produced by multi_extractor.py.

It inspects:
  • DB metadata (size, row counts, dims, models)
  • Embedding value distribution (range, mean/std, percentiles)
  • NaN/Inf/zero-norm statistics
  • Norm distribution histogram
  • Pairwise cosine similarity on a random subset
  • Duplicate-rate estimate in a sample
  • Coverage vs strings_to_embed.csv (overall and per kind)
  • Token-length & truncation stats (if present)
"""

import argparse
import sqlite3
from pathlib import Path
from typing import Optional, Sequence, Dict, Tuple, List

import numpy as np


# ---------------------------------------------------------------------
# Small helpers
# ---------------------------------------------------------------------

def fmt_bytes(n: int) -> str:
    for unit in ["B", "KB", "MB", "GB", "TB"]:
        if n < 1024:
            return f"{n:.2f} {unit}"
        n /= 1024.0
    return f"{n:.2f} PB"


def query_one(con: sqlite3.Connection, sql: str, args: Sequence = ()):
    cur = con.execute(sql, args)
    row = cur.fetchone()
    return row[0] if row else None


# ---------------------------------------------------------------------
# 1) Basic DB stats
# ---------------------------------------------------------------------

def basic_db_stats(con: sqlite3.Connection) -> Dict:
    stats: Dict = {}
    stats["total_rows"] = int(query_one(con, "SELECT COUNT(*) FROM embeddings") or 0)

    stats["dim_counts"] = [
        (int(dim), int(cnt))
        for dim, cnt in con.execute(
            "SELECT dim, COUNT(*) FROM embeddings GROUP BY dim ORDER BY dim"
        )
    ]

    stats["model_dim_counts"] = [
        (str(model), int(dim), int(cnt))
        for model, dim, cnt in con.execute(
            "SELECT model, dim, COUNT(*) FROM embeddings GROUP BY model, dim "
            "ORDER BY model, dim"
        )
    ]

    stats["min_rowid"] = query_one(con, "SELECT MIN(rowid) FROM embeddings") or 0
    stats["max_rowid"] = query_one(con, "SELECT MAX(rowid) FROM embeddings") or 0

    # token length / truncation if the columns exist
    try:
        stats["tok_len_stats"] = con.execute(
            "SELECT MIN(tok_len), MAX(tok_len), AVG(tok_len) "
            "FROM embeddings WHERE tok_len IS NOT NULL"
        ).fetchone()
        stats["trunc_count"] = int(
            query_one(con, "SELECT COUNT(*) FROM embeddings WHERE truncated = 1") or 0
        )
    except sqlite3.OperationalError:
        stats["tok_len_stats"] = None
        stats["trunc_count"] = None

    return stats


# ---------------------------------------------------------------------
# 2) Sampling embeddings for numeric checks
# ---------------------------------------------------------------------

def sample_embeddings(
    con: sqlite3.Connection,
    sample_size: int,
    model_filter: Optional[str] = None,
) -> Tuple[np.ndarray, List[str]]:
    sql = "SELECT sha256, dim, vec FROM embeddings"
    args: Tuple = ()
    if model_filter:
        sql += " WHERE model = ?"
        args = (model_filter,)
    sql += " ORDER BY RANDOM() LIMIT ?"
    args = args + (sample_size,)

    cur = con.execute(sql, args)
    embs: List[np.ndarray] = []
    shas: List[str] = []
    bad_rows = 0

    for sha, dim, blob in cur:
        if blob is None:
            bad_rows += 1
            continue

        # default: float32 little-endian
        arr = np.frombuffer(blob, dtype="<f4")
        if arr.size != dim:
            # fallback: generic float32
            arr = np.frombuffer(blob, dtype=np.float32)

        if arr.size != dim:
            bad_rows += 1
            continue

        embs.append(arr.astype(np.float32))
        shas.append(str(sha))

    if bad_rows:
        print(f"[WARN] {bad_rows} sampled rows had invalid blobs or dim mismatch.")

    if not embs:
        return np.empty((0, 0), dtype=np.float32), []

    mat = np.stack(embs, axis=0)
    return mat, shas


def embedding_value_stats(mat: np.ndarray) -> Dict:
    flat = mat.reshape(-1).astype(np.float64)
    stats: Dict = {}
    stats["num_values"] = int(flat.size)
    stats["nan_count"] = int(np.isnan(flat).sum())
    stats["inf_count"] = int(np.isinf(flat).sum())

    finite = flat[np.isfinite(flat)]
    if finite.size == 0:
        stats["finite"] = False
        return stats

    stats["finite"] = True
    stats["min"] = float(np.min(finite))
    stats["max"] = float(np.max(finite))
    stats["mean"] = float(np.mean(finite))
    stats["std"] = float(np.std(finite))
    for q in (1, 5, 50, 95, 99):
        stats[f"p{q}"] = float(np.percentile(finite, q))
    return stats


def norm_stats(mat: np.ndarray) -> Dict:
    norms = np.linalg.norm(mat, axis=1)
    stats: Dict = {}
    stats["num"] = int(norms.size)
    stats["zero_norms"] = int(np.isclose(norms, 0.0).sum())
    stats["nan_norms"] = int(np.isnan(norms).sum())

    if norms.size == 0:
        stats.update(
            {
                "min": 0.0,
                "max": 0.0,
                "mean": 0.0,
                "std": 0.0,
                "p1": 0.0,
                "p5": 0.0,
                "p50": 0.0,
                "p95": 0.0,
                "p99": 0.0,
                "hist": ([], []),
            }
        )
        return stats

    stats["min"] = float(np.nanmin(norms))
    stats["max"] = float(np.nanmax(norms))
    stats["mean"] = float(np.nanmean(norms))
    stats["std"] = float(np.nanstd(norms))
    for q in (1, 5, 50, 95, 99):
        stats[f"p{q}"] = float(np.nanpercentile(norms, q))

    finite = norms[~np.isnan(norms)]
    if finite.size > 0:
        hist, edges = np.histogram(finite, bins=10)
        stats["hist"] = (edges.tolist(), hist.tolist())
    else:
        stats["hist"] = ([], [])
    return stats


def similarity_stats(mat: np.ndarray, max_pairs: int = 512) -> Optional[Dict]:
    n = mat.shape[0]
    if n < 2:
        return None

    k = min(n, max_pairs)
    idx = np.random.choice(n, size=k, replace=False)
    sub = mat[idx]

    norms = np.linalg.norm(sub, axis=1, keepdims=True)
    norms[norms == 0.0] = 1.0
    sub_norm = sub / norms

    sim = sub_norm @ sub_norm.T
    mask = ~np.eye(k, dtype=bool)
    vals = sim[mask].astype(np.float64)

    stats: Dict = {}
    stats["num_pairs"] = int(vals.size)
    stats["min"] = float(np.min(vals))
    stats["max"] = float(np.max(vals))
    stats["mean"] = float(np.mean(vals))
    stats["std"] = float(np.std(vals))

    bins = np.linspace(-1.0, 1.0, 11)
    hist, edges = np.histogram(vals, bins=bins)
    stats["hist"] = (edges.tolist(), hist.tolist())
    return stats


def duplicate_rate(mat: np.ndarray, precision: int = 3) -> float:
    if mat.shape[0] == 0:
        return 0.0
    rounded = np.round(mat.astype(np.float32), decimals=precision)
    seen = set()
    dup = 0
    for row in rounded:
        key = row.tobytes()
        if key in seen:
            dup += 1
        else:
            seen.add(key)
    return float(dup) / float(mat.shape[0])


# ---------------------------------------------------------------------
# 3) Coverage vs strings_to_embed.csv
# ---------------------------------------------------------------------

def coverage_vs_strings(
    con: sqlite3.Connection,
    strings_csv: Path,
    chunk: int = 1000,
) -> Dict:
    import csv

    total_rows = 0
    kinds_total: Dict[str, int] = {}
    sha_to_kind: Dict[str, str] = {}

    with strings_csv.open("r", encoding="utf-8") as f:
        rdr = csv.DictReader(f)
        for row in rdr:
            sha = (row.get("sha256") or "").strip()
            kind = (row.get("kind") or "").strip() or "unknown"
            if not sha:
                continue
            total_rows += 1
            sha_to_kind[sha] = kind
            kinds_total[kind] = kinds_total.get(kind, 0) + 1

    all_shas = list(sha_to_kind.keys())
    found_shas = set()
    cur = con.cursor()

    for i in range(0, len(all_shas), chunk):
        batch = all_shas[i : i + chunk]
        q = (
            "SELECT sha256 FROM embeddings "
            "WHERE sha256 IN (%s)" % ",".join("?" * len(batch))
        )
        cur.execute(q, batch)
        found_shas.update(str(x[0]) for x in cur.fetchall())

    missing_shas = set(all_shas) - found_shas

    kinds_found: Dict[str, int] = {}
    kinds_missing: Dict[str, int] = {}
    for sha in found_shas:
        kind = sha_to_kind.get(sha, "unknown")
        kinds_found[kind] = kinds_found.get(kind, 0) + 1

    for sha in missing_shas:
        kind = sha_to_kind.get(sha, "unknown")
        kinds_missing[kind] = kinds_missing.get(kind, 0) + 1

    out: Dict = {
        "total_rows": total_rows,
        "unique_shas": len(all_shas),
        "covered_shas": len(found_shas),
        "missing_shas": len(missing_shas),
        "coverage_pct": 100.0 * len(found_shas) / max(1, len(all_shas)),
        "kinds_total": kinds_total,
        "kinds_found": kinds_found,
        "kinds_missing": kinds_missing,
        "example_missing": list(sorted(missing_shas))[:10],
    }
    return out


# ---------------------------------------------------------------------
# Main CLI
# ---------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(
        "Analyze embedding SQLite cache (multi_extractor.py)"
    )
    ap.add_argument("--db", type=Path, required=True,
                    help="Path to embeddings SQLite (multi_extractor.py output)")
    ap.add_argument("--strings", type=Path, default=None,
                    help="Optional strings_to_embed.csv for coverage checks")
    ap.add_argument("--sample", type=int, default=5000,
                    help="How many embeddings to sample for numeric stats")
    ap.add_argument("--pairs", type=int, default=512,
                    help="Max pairs for cosine similarity stats")
    ap.add_argument("--model", type=str, default=None,
                    help="Optional filter on embeddings.model")
    args = ap.parse_args()

    db_path: Path = args.db
    if not db_path.exists():
        print(f"[ERROR] DB not found: {db_path}")
        raise SystemExit(1)

    size_bytes = db_path.stat().st_size
    print("=" * 72)
    print("EMBEDDING SQLITE ANALYZER")
    print("=" * 72)
    print(f"DB:   {db_path}")
    print(f"Size: {fmt_bytes(size_bytes)}")

    con = sqlite3.connect(str(db_path))

    # --- 1) Basic stats ---
    try:
        stats = basic_db_stats(con)
    except sqlite3.OperationalError as e:
        print(f"[ERROR] Failed to read basic stats: {e}")
        con.close()
        raise SystemExit(1)

    print("\n[1] BASIC DB STATS")
    print("-------------------")
    print(f"Total rows: {stats['total_rows']}")
    print("Dims:")
    for dim, cnt in stats["dim_counts"]:
        print(f"  dim={dim:4d} : {cnt}")
    print("Model x Dim:")
    for model, dim, cnt in stats["model_dim_counts"]:
        print(f"  model={model:20s} dim={dim:4d} -> {cnt}")
    print(f"rowid range: [{stats['min_rowid']}, {stats['max_rowid']}]")
    if stats.get("tok_len_stats") is not None:
        mn, mx, avg = stats["tok_len_stats"]
        if mn is not None:
            print(f"tok_len: min={mn} max={mx} avg={avg:.2f}")
    if stats.get("trunc_count") is not None:
        print(f"truncated rows: {stats['trunc_count']}")

    # --- 2–4) Sample stats, similarity, duplicates ---
    if args.sample > 0 and stats["total_rows"] > 0:
        mat, shas = sample_embeddings(con, args.sample, args.model)
        print("\n[2] SAMPLE STATS (values + norms)")
        print("----------------------------------")

        if mat.size == 0:
            print("No valid embeddings in sample.")
        else:
            val_stats = embedding_value_stats(mat)
            if not val_stats.get("finite", False):
                print("[WARN] All sample values are NaN/Inf — embeddings likely corrupted.")
            else:
                print(
                    f"Values: min={val_stats['min']:.5f} "
                    f"max={val_stats['max']:.5f} "
                    f"mean={val_stats['mean']:.5f} "
                    f"std={val_stats['std']:.5f}"
                )
                print(
                    "Percentiles: "
                    f"p1={val_stats['p1']:.5f}, "
                    f"p5={val_stats['p5']:.5f}, "
                    f"p50={val_stats['p50']:.5f}, "
                    f"p95={val_stats['p95']:.5f}, "
                    f"p99={val_stats['p99']:.5f}"
                )
                nan_frac = val_stats["nan_count"] / max(1, val_stats["num_values"])
                inf_frac = val_stats["inf_count"] / max(1, val_stats["num_values"])
                print(f"NaN fraction: {nan_frac:.6f}, Inf fraction: {inf_frac:.6f}")

            nstats = norm_stats(mat)
            print("\nNorms:")
            print(
                f"  min={nstats['min']:.5f} "
                f"max={nstats['max']:.5f} "
                f"mean={nstats['mean']:.5f} "
                f"std={nstats['std']:.5f}"
            )
            print(f"  zero_norms={nstats['zero_norms']} / {nstats['num']}")
            print(f"  nan_norms={nstats['nan_norms']} / {nstats['num']}")
            edges, hist = nstats["hist"]
            if edges:
                print("  Histogram (norms):")
                for i in range(len(hist)):
                    print(f"    [{edges[i]:.2f}, {edges[i+1]:.2f}) : {hist[i]}")

            print("\n[3] PAIRWISE COSINE SIMILARITY (sample)")
            print("----------------------------------------")
            sstats = similarity_stats(mat, max_pairs=args.pairs)
            if sstats is None:
                print("Not enough embeddings for similarity stats.")
            else:
                print(
                    f"Pairs: {sstats['num_pairs']}\n"
                    f"  min={sstats['min']:.5f} "
                    f"max={sstats['max']:.5f} "
                    f"mean={sstats['mean']:.5f} "
                    f"std={sstats['std']:.5f}"
                )
                edges, hist = sstats["hist"]
                print("  Histogram (cosine):")
                for i in range(len(hist)):
                    print(f"    [{edges[i]:.2f}, {edges[i+1]:.2f}) : {hist[i]}")

            print("\n[4] DUPLICATE RATE (approx)")
            print("---------------------------")
            dup_frac = duplicate_rate(mat, precision=3)
            print(f"Approx duplicate fraction in sample: {dup_frac*100:.3f}%")

    # --- 5) Coverage vs strings_to_embed.csv ---
    if args.strings is not None:
        print("\n[5] COVERAGE vs strings_to_embed.csv")
        print("-------------------------------------")
        if not args.strings.exists():
            print(f"[ERROR] strings_to_embed.csv not found: {args.strings}")
        else:
            cov = coverage_vs_strings(con, args.strings)
            print(f"Total CSV rows: {cov['total_rows']}")
            print(f"Unique sha256:  {cov['unique_shas']}")
            print(f"Covered sha256: {cov['covered_shas']}")
            print(f"Missing sha256: {cov['missing_shas']}")
            print(f"Coverage:       {cov['coverage_pct']:.2f}%")
            print("Kinds (total / found / missing):")
            for kind, total in cov["kinds_total"].items():
                found = cov["kinds_found"].get(kind, 0)
                missing = cov["kinds_missing"].get(kind, 0)
                print(
                    f"  {kind:15s}: total={total:7d} "
                    f"found={found:7d} missing={missing:7d}"
                )
            if cov["example_missing"]:
                print("Example missing sha256:")
                for sha in cov["example_missing"]:
                    print(f"  {sha}")

    con.close()
    print("\nDone.")


if __name__ == "__main__":
    main()


"""
# Basic DB sanity (no coverage)
python analyze_embeddings_sqlite.py \
  --db /path/to/codebert_v2.sqlite \
  --sample 5000 --pairs 512

# With coverage vs strings_to_embed.csv
python analyze_embeddings_sqlite.py \
  --db ./Clean_exports/cache_devign_v2/graphcodebert_64d.sqlite \
  --strings ./Clean_exports/devign_vocab_normfunc_v2/strings_to_embed.csv\
  --sample 5000 --pairs 512


"""