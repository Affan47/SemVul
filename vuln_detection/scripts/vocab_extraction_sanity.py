#!/usr/bin/env python3
"""
Quick sanity check for vocab_builder extraction.

- Samples a few GraphSON files.
- Shows node labels + extracted strings.
- Helps verify that strings_to_embed.csv will contain real code snippets.
"""

import json
import random
from pathlib import Path
from typing import List

from vocab_builder import (
    unwrap_graphson,
    get_vertices_edges,
    extract_node_texts,
    extract_edge_texts,
)


def sample_graphson_files(root: Path, max_files: int = 20) -> List[Path]:
    candidates = sorted(root.rglob("*.json"))
    if len(candidates) <= max_files:
        return candidates
    return random.sample(candidates, max_files)


def sanity_check_graphson(root_dir: str, max_files: int = 10) -> None:
    root = Path(root_dir)
    files = sample_graphson_files(root, max_files=max_files)
    if not files:
        print(f"[ERROR] No .json files found under {root}")
        return

    print(f"[INFO] Sampling {len(files)} GraphSON files under {root}...\n")

    for path in files:
        try:
            raw = path.read_text(encoding="utf-8")
            doc = json.loads(raw)
        except Exception as e:
            print(f"[WARN] Failed to load {path}: {e}")
            continue

        unwrapped = unwrap_graphson(doc)
        vertices, edges = get_vertices_edges(unwrapped)

        print("=" * 70)
        print(f"[FILE] {path}")
        print(f"[INFO] vertices={len(vertices)} edges={len(edges)}")

        # Show a few node texts
        shown = 0
        for v in vertices:
            lbl = v.get("label", "<no-label>")
            texts = list(extract_node_texts(v))
            if not texts:
                continue
            print(f"  [NODE] label={lbl} texts={texts[:3]}")
            shown += 1
            if shown >= 5:
                break

        # Show a few edge texts (usually less interesting)
        shown = 0
        for e in edges:
            lbl = e.get("label", "<no-label>")
            texts = list(extract_edge_texts(e))
            if not texts:
                continue
            print(f"  [EDGE] label={lbl} texts={texts[:3]}")
            shown += 1
            if shown >= 3:
                break

        print()

    print("[DONE] Sanity check finished.")


if __name__ == "__main__":
    import argparse

    ap = argparse.ArgumentParser(
        description="Sanity check for vocab_builder node/edge text extraction"
    )
    ap.add_argument(
        "--json-root",
        required=True,
        help="Root directory containing GraphSON exports (train/valid/test folders).",
    )
    ap.add_argument(
        "--max-files",
        type=int,
        default=10,
        help="Maximum number of GraphSON files to sample.",
    )
    args = ap.parse_args()
    sanity_check_graphson(args.json_root, max_files=args.max_files)


"""

python vocab_extraction_sanity.py \
  --json-root /path/to/normalized_devign_json/train_graphson \
  --max-files 10

"""