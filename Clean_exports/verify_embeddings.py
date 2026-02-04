#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Verify embeddings DB against strings_to_embed.csv (aligned with vocab_builder.py).

Key features:
- Coverage: CSV SHAs vs DB SHAs (missing/extra).
- Integrity: PRAGMA integrity_check.
- Dim stats per model.
- Deep sample stats (norms, NaN/zero, truncation, token len histogram).
- sha(code) round-trip check.
- --restrict-to-csv: sample only rows whose sha is in CSV (prevents legacy extras biasing results).
- --random-sample: random sampling (ORDER BY RANDOM()) when --restrict-to-csv (default off for speed).

If --report points to a directory, the report is written as "<dir>/embed_verify_report.json".
"""

import argparse, csv, json, sqlite3, zlib, hashlib, random, sys, os
from pathlib import Path
from typing import Dict, List, Tuple, Set, Optional
import numpy as np

# ---------------- utils ----------------

def sha256_text(s: str) -> str:
    return hashlib.sha256(s.encode("utf-8", errors="ignore")).hexdigest()

def load_csv_shas(csv_path: Path, kind: Optional[str]=None) -> Dict[str, Tuple[str,int]]:
    """
    returns sha -> (string, count)
    If kind is provided (node_content/edge_content), filter by it.
    Keeps the highest 'count' if duplicates exist.
    """
    out: Dict[str, Tuple[str,int]] = {}
    with csv_path.open("r", encoding="utf-8") as f:
        rdr = csv.DictReader(f)
        for r in rdr:
            if kind and r["kind"].strip() not in {kind, "mixed"}:
                continue
            sha = r["sha256"].strip()
            s = r["string"]
            try:
                cnt = int(r["count"])
            except Exception:
                cnt = 1
            prev = out.get(sha)
            if (prev is None) or (cnt > prev[1]):
                out[sha] = (s, cnt)
    return out

def fetch_db_shas(con: sqlite3.Connection) -> Set[str]:
    cur = con.execute("SELECT sha256 FROM embeddings;")
    return {row[0] for row in cur}

def fetch_dim_stats(con: sqlite3.Connection) -> List[Tuple[str,int,int]]:
    # (model, dim, count)
    cur = con.execute("SELECT model, dim, COUNT(*) FROM embeddings GROUP BY model, dim;")
    return list(cur)

def fetch_sample_any(con: sqlite3.Connection, n: int) -> List[Tuple[str,bytes,bytes,int,int,str,int]]:
    """
    Sample from full table.
    Returns rows: (sha256, vec, tok_ids, tok_len, truncated, code, dim)
    """
    cur = con.execute(
        "SELECT sha256, vec, tok_ids, tok_len, truncated, code, dim FROM embeddings LIMIT ?;", (n,)
    )
    return list(cur)

def fetch_sample_from_keep(con: sqlite3.Connection, n: int, random_sample: bool) -> List[Tuple[str,bytes,bytes,int,int,str,int]]:
    """
    Sample only where sha256 is in TEMP TABLE keep(sha256).
    Returns rows: (sha256, vec, tok_ids, tok_len, truncated, code, dim)
    """
    if random_sample:
        sql = (
            "SELECT e.sha256, e.vec, e.tok_ids, e.tok_len, e.truncated, e.code, e.dim "
            "FROM embeddings e JOIN keep k ON k.sha256 = e.sha256 "
            "ORDER BY RANDOM() LIMIT ?;"
        )
    else:
        sql = (
            "SELECT e.sha256, e.vec, e.tok_ids, e.tok_len, e.truncated, e.code, e.dim "
            "FROM embeddings e JOIN keep k ON k.sha256 = e.sha256 "
            "LIMIT ?;"
        )
    cur = con.execute(sql, (n,))
    return list(cur)

def decode_vec(vec_blob: bytes, dim: int) -> np.ndarray:
    arr = np.frombuffer(vec_blob, dtype=np.float32)
    if arr.size != dim:
        # If blob length doesn't match dim, try to reshape safely but flag error
        raise ValueError(f"Vector blob size {arr.size} != dim {dim}")
    return arr

def try_decompress_ints(blob: Optional[bytes]) -> np.ndarray:
    if blob is None:
        return np.array([], dtype=np.int32)
    try:
        raw = zlib.decompress(blob)
        arr = np.frombuffer(raw, dtype=np.int32)
        return arr
    except Exception:
        return np.array([], dtype=np.int32)

def cosine(a: np.ndarray, b: np.ndarray) -> float:
    na = np.linalg.norm(a); nb = np.linalg.norm(b)
    if na == 0 or nb == 0: return 0.0
    return float(np.dot(a, b) / (na * nb))

# ---------------- main ----------------

def main():
    ap = argparse.ArgumentParser("Verify embeddings DB against strings_to_embed.csv")
    ap.add_argument("--db", required=True, help="Path to SQLite embeddings DB.")
    ap.add_argument("--strings-csv", required=True, help="strings_to_embed.csv from vocab_builder.")
    ap.add_argument("--kind", choices=["node_content","edge_content"],
                    help="Filter CSV to a specific kind.")
    ap.add_argument("--model", default=None,
                    help="Optional model name to sanity-check dim expectations (e.g., 'microsoft/codebert-base' → 768).")
    ap.add_argument("--sample", type=int, default=1000, help="Sample size for deep checks.")
    ap.add_argument("--report", default="./embed_verify_report.json",
                    help="Path to output JSON report. If a directory, writes embed_verify_report.json inside it.")
    ap.add_argument("--restrict-to-csv", action="store_true",
                    help="Sample only rows whose sha appear in the CSV (prevents legacy extras affecting sample).")
    ap.add_argument("--random-sample", action="store_true",
                    help="When --restrict-to-csv, draw a random sample via ORDER BY RANDOM() (slower).")
    args = ap.parse_args()

    # Normalize report path (support directories)
    report_path = Path(args.report)
    if report_path.suffix.lower() not in (".json", ".txt"):
        # Likely a directory (or plain name without suffix) → write default filename
        if report_path.exists() and report_path.is_dir():
            report_path = report_path / "embed_verify_report.json"
        elif str(args.report).endswith(os.sep) or str(args.report).endswith("/"):
            report_path = report_path / "embed_verify_report.json"

    report = {"ok": True, "notes": [], "counts": {}, "problems": []}

    # Load CSV (aligned with vocab_builder output)
    csv_map = load_csv_shas(Path(args.strings_csv), kind=args.kind)   # sha -> (string, count)
    csv_shas = set(csv_map.keys())
    report["counts"]["csv_unique_shas"] = len(csv_shas)

    # DB connect + integrity
    con = sqlite3.connect(args.db)
    integ = con.execute("PRAGMA integrity_check;").fetchone()[0]
    report["integrity_check"] = integ
    if integ != "ok":
        report["ok"] = False
        report["problems"].append(f"PRAGMA integrity_check returned {integ}")

    # Coverage
    db_shas = fetch_db_shas(con)
    report["counts"]["db_unique_shas"] = len(db_shas)
    missing = csv_shas - db_shas
    extra   = db_shas - csv_shas
    report["counts"]["missing_from_db"] = len(missing)
    report["counts"]["extra_in_db"] = len(extra)

    if missing:
        report["ok"] = False
        report["problems"].append(f"{len(missing)} CSV shas missing in DB (first 10): {list(sorted(missing))[:10]}")
    if extra:
        report["notes"].append(f"{len(extra)} DB shas not in CSV (first 10): {list(sorted(extra))[:10]}")

    # Dimensionality stats
    dim_stats = fetch_dim_stats(con)
    report["dim_stats"] = [{"model": m, "dim": d, "count": c} for (m,d,c) in dim_stats]
    if args.model:
        exp_dim = 768 if "codebert-base" in args.model else None
        if exp_dim is not None:
            for m,d,c in dim_stats:
                if m == args.model and d != exp_dim:
                    report["ok"] = False
                    report["problems"].append(f"Model {m} dim={d} (expected {exp_dim})")

    # Deep sample (optionally restricted to CSV)
    if args.restrict_to_csv:
        # Build temp table with CSV SHAs
        con.execute("CREATE TEMP TABLE keep(sha256 TEXT PRIMARY KEY);")
        # executemany is fine; SQLite will handle batching internally
        con.executemany("INSERT INTO keep(sha256) VALUES (?);", [(s,) for s in csv_shas])
        total = con.execute(
            "SELECT COUNT(*) FROM embeddings WHERE sha256 IN (SELECT sha256 FROM keep);"
        ).fetchone()[0]
        k = min(args.sample, total)
        sample_rows = fetch_sample_from_keep(con, k, args.random_sample)
    else:
        total = con.execute("SELECT COUNT(*) FROM embeddings;").fetchone()[0]
        k = min(args.sample, total)
        sample_rows = fetch_sample_any(con, k)

    # If no rows, write minimal report
    if not sample_rows:
        report["sample_checks"] = {
            "sample_size": 0,
            "dim_inferred": None,
            "norm_min": None,
            "norm_max": None,
            "norm_mean": None,
            "nan_vectors": 0,
            "zero_vectors": 0,
            "trunc_count": 0,
            "trunc_ratio": 0.0,
            "tok_len_histogram_top": [],
            "sha_mismatch_in_sample": 0,
            "nn_top5_similarities": []
        }
        report_path.parent.mkdir(parents=True, exist_ok=True)
        with report_path.open("w", encoding="utf-8") as f:
            json.dump(report, f, ensure_ascii=False, indent=2)
        print(json.dumps(report, ensure_ascii=False, indent=2))
        return

    # Derive "dim_inferred" from first row's stored dim
    first_dim = int(sample_rows[0][6])  # dim
    norms: List[float] = []
    nan_count = 0
    zero_count = 0
    bad_sha_res = 0
    trunc_count = 0
    tok_len_hist: Dict[int,int] = {}
    vecs_for_nn: List[np.ndarray] = []

    for (sha, vec_blob, tok_ids_blob, tok_len, truncated, code, dim) in sample_rows:
        # sanity: use the row's dim
        dim = int(dim)

        # sha(code) check
        if code is not None:
            recomputed = sha256_text(code)
            if recomputed != sha:
                bad_sha_res += 1

        # vector decode + stats
        v = decode_vec(vec_blob, dim)
        if np.any(np.isnan(v)):
            nan_count += 1
        nrm = float(np.linalg.norm(v))
        if nrm == 0.0:
            zero_count += 1
        norms.append(nrm)
        vecs_for_nn.append(v)

        # trunc + token lens (NULL-safe)
        if truncated == 1:
            trunc_count += 1
        if tok_len is not None:
            try:
                tok_len_hist[int(tok_len)] = tok_len_hist.get(int(tok_len), 0) + 1
            except Exception:
                pass

    # cosine NN probe on a small subset (optional quality signal)
    nn_pairs: List[float] = []
    if len(vecs_for_nn) >= 40:
        # sample up to 200 rows for a quick NN probe
        idx = list(range(len(vecs_for_nn)))
        random.shuffle(idx)
        idx = idx[:200]
        mats = np.stack([vecs_for_nn[i] for i in idx], axis=0)
        # L2 normalize
        mats = mats / (np.linalg.norm(mats, axis=1, keepdims=True) + 1e-12)
        sims = (mats @ mats.T)
        # exclude self
        for i in range(sims.shape[0]):
            sims[i, i] = -1.0
        # take each row's best neighbor
        best = [float(np.max(sims[i])) for i in range(sims.shape[0])]
        best.sort(reverse=True)
        nn_pairs = best[:5]

    report["sample_checks"] = {
        "sample_size": len(sample_rows),
        "dim_inferred": first_dim,
        "norm_min": float(min(norms)) if norms else None,
        "norm_max": float(max(norms)) if norms else None,
        "norm_mean": float(sum(norms)/len(norms)) if norms else None,
        "nan_vectors": nan_count,
        "zero_vectors": zero_count,
        "trunc_count": trunc_count,
        "trunc_ratio": (trunc_count/len(sample_rows)) if sample_rows else 0.0,
        "tok_len_histogram_top": sorted(tok_len_hist.items(), key=lambda kv:-kv[1])[:10],
        "sha_mismatch_in_sample": bad_sha_res,
        "nn_top5_similarities": nn_pairs
    }

    if nan_count > 0 or zero_count > 0 or bad_sha_res > 0:
        report["ok"] = False
        if nan_count > 0: report["problems"].append(f"{nan_count} vectors contained NaN")
        if zero_count > 0: report["problems"].append(f"{zero_count} vectors had zero norm")
        if bad_sha_res > 0: report["problems"].append(f"{bad_sha_res} sha(code) mismatches in sample")

    # Persist + print
    report_path.parent.mkdir(parents=True, exist_ok=True)
    with report_path.open("w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=2)
    print(json.dumps(report, ensure_ascii=False, indent=2))

if __name__ == "__main__":
    main()




"""

python verify_embeddings.py \
  --db "./Clean_exports/cache_devign_v1/codebert_v3.sqlite" \
  --strings-csv "./Clean_exports/devign_vocab_v1/strings_to_embed.csv" \
  --kind node_content \
  --model "microsoft/codebert-base" \
  --sample 2000 \
  --restrict-to-csv \
  --report "./Clean_exports/cache_devign_v1/embed_verify_report.json"


"""
