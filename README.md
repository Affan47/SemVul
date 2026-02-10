# SemVul

This repository contains the full pipeline to reproduce the SemVul experiments, starting from CPG generation and GraphSON export, through vocabulary building and embedding extraction, and ending with training and evaluating all model variants.

## Repository Layout

- `workspace/A_Preprocessing_scripts`\: dataset inspection, normalization, and per-function splitting.
- `workspace/B_Joern_graphs_generation_scripts`\: Joern-based CPG generation and GraphSON export.
- `CPGs`\: default output location for exported GraphSON (you can change paths).
- `Clean_exports`\: GraphSON parsing, vocabulary building, cache construction.
- `vuln_detection`\: embedding extraction, training, evaluation, diagnostics.
- `results`\: local results (ignored by Git).

## Prerequisites

- Python 3.9+.
- Java (JDK 19+ recommended; required by Joern).
- A working Joern installation (`joern-parse` + `joern-export`).
- CUDA-capable GPU recommended for large embeddings and training.

## Data and Cache Availability

This repository is kept anonymous and within GitHub size limits. As a result, we do not share
large intermediate artifacts such as exported GraphSON, precomputed embedding caches, or trained
model checkpoints. The pipeline below regenerates these artifacts locally using relative paths.

Suggested Python packages:

```bash
pip install torch torch_geometric transformers scikit-learn pandas numpy tqdm
```

Joern installation (required for CPG generation):

We use Joern to parse per-function C/C++ code into CPG binaries and export GraphSON.
Our graph-generation scripts expect `joern-parse` and `joern-export` to be available in
your `PATH`.

Official installation docs:

- https://docs.joern.io/installation
- https://github.com/joernio/joern/releases

Recommended (official installer, default location):

```bash
curl -L -o joern-install.sh \
  https://github.com/joernio/joern/releases/latest/download/joern-install.sh

bash joern-install.sh

# Default install location is typically: ~/bin/joern
export PATH="$HOME/bin/joern/joern-cli:$PATH"

# Sanity-check
command -v joern-parse
command -v joern-export
joern-parse --help >/dev/null
joern-export --help >/dev/null
```

Optional (repo-local install, keeps paths relative):

```bash
curl -L -o joern-install.sh \
  https://github.com/joernio/joern/releases/latest/download/joern-install.sh

bash joern-install.sh --install-dir=./external/joern --reinstall

export PATH="$(pwd)/external/joern/joern-cli:$PATH"

command -v joern-parse
command -v joern-export
```

## Data Preparation

The repository includes per-function manifests (and, where feasible, per-function source files)
under:

```
./workspace/03_PerFunction_datasets/
  original_devign_functions/
    manifest_train.csv
    manifest_validation.csv
    manifest_test.csv
    train/
    validation/
    test/
  draper_functions/
    manifest_train.csv
    manifest_validation.csv
    manifest_test.csv
    draper_per_function_stats.json
    draper_per_function_stats.txt
    train/
    validation/
    test/
  reveal_functions/
    manifest_train.csv
    manifest_validation.csv
    manifest_test.csv
    reveal_per_function_stats.json
    reveal_per_function_stats.txt
  primevul_functions/
    manifest_train.csv
    manifest_validation.csv
    manifest_test.csv
    primevul_per_function_stats.json
    primevul_per_function_stats.txt
  mutant_diff_report_test.csv
```

Per-function source files are tracked for Devign and Draper (they are small enough to include).
For Reveal and PrimeVul, only manifests and stats are tracked; you must generate the
`train/validation/test` per-function `.c` directories locally from the raw datasets. Use relative
paths only. Example raw dataset structure:

```
./datasets/
  devign_full/
    json/
      train.jsonl
      validation.jsonl
      test.jsonl
  draper_raw/
  reveal_raw/
  primevul_raw/
```

Devign per-function source files are already included under
`./workspace/03_PerFunction_datasets/original_devign_functions`. If you want to regenerate them
from the raw Devign dataset, use the included download script and then run the per-function
splitter:

```bash
python scripts/download_devign.py --output ./datasets/devign_full --formats json

python workspace/A_Preprocessing_scripts/01c_split_per_function_devign.py \
  --input-base ./datasets/devign_full/json \
  --output-base ./workspace/03_PerFunction_datasets/original_devign_functions \
  --splits train validation test
```

Run preprocessing (explicit commands):

```bash
# (Optional) Devign deduplication (writes ./datasets/devign_dedup/workspace/deduped)
python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --in ./datasets/devign_full/json/train.jsonl \
  --tag train \
  --root ./datasets/devign_dedup

python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --in ./datasets/devign_full/json/validation.jsonl \
  --tag validation \
  --root ./datasets/devign_dedup

python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --in ./datasets/devign_full/json/test.jsonl \
  --tag test \
  --root ./datasets/devign_dedup

# (Optional) rename dedup outputs to the expected split names
mv ./datasets/devign_dedup/workspace/deduped/dedup_train.jsonl ./datasets/devign_dedup/workspace/deduped/train.jsonl
mv ./datasets/devign_dedup/workspace/deduped/dedup_validation.jsonl ./datasets/devign_dedup/workspace/deduped/validation.jsonl
mv ./datasets/devign_dedup/workspace/deduped/dedup_test.jsonl ./datasets/devign_dedup/workspace/deduped/test.jsonl

# (Optional) Devign normalization (writes <split>_normalized.jsonl)
python workspace/A_Preprocessing_scripts/01b_normalize_devign.py \
  --input-dir ./datasets/devign_dedup/workspace/deduped \
  --output-dir ./datasets/devign_norm \
  --splits train validation test \
  --func-key func \
  --strategy definition

# Devign per-function split (recommended: original/non-normalized)
python workspace/A_Preprocessing_scripts/01c_split_per_function_devign.py \
  --input-base ./datasets/devign_full/json \
  --output-base ./workspace/03_PerFunction_datasets/original_devign_functions \
  --splits train validation test
```

Reveal:

```bash
python workspace/A_Preprocessing_scripts/01d_split_per_function_reveal.py \
  --input-dir ./datasets/reveal_raw \
  --output-base ./workspace/03_PerFunction_datasets/reveal_functions \
  --splits train validation test
```

Draper:

```bash
python workspace/A_Preprocessing_scripts/01e_split_per_function_draper.py \
  --input-dir ./datasets/draper_raw \
  --output-base ./workspace/03_PerFunction_datasets/draper_functions \
  --splits train validation test \
  --label-column combine
```

PrimeVul:

```bash
python workspace/A_Preprocessing_scripts/01f_split_per_function_primevul.py \
  --input-dir ./datasets/primevul_raw \
  --output-base ./workspace/03_PerFunction_datasets/primevul_functions \
  --splits train validation test \
  --code-field func \
  --label-field target
```

## CPG Generation and GraphSON Export

Generate CPGs with Joern and export GraphSON. Use the dataset-specific scripts in `workspace/B_Joern_graphs_generation_scripts`.

The main generators are:
1. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_devign_final.py`
2. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_draper_final.py`
3. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_primevul_final.py`
4. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_reveal_final.py`

Each of these scripts includes CLI usage examples at the end of the file.

Devign:

```bash
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_devign_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/original_devign_functions \
  --out-base ./CPGs/original_devign_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson \
  --parse-workers 4 \
  --export-workers 4
```

Draper:

```bash
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_draper_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/draper_functions \
  --out-base ./CPGs/draper_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson \
  --parse-workers 4 \
  --export-workers 4
```

Reveal:

```bash
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_reveal_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/reveal_functions \
  --out-base ./CPGs/reveal_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson \
  --parse-workers 4 \
  --export-workers 4
```

PrimeVul:

```bash
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_primevul_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/primevul_functions \
  --out-base ./CPGs/primevul_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson \
  --parse-workers 4 \
  --export-workers 4
```

## GraphSON Parsing and Vocabulary Building

Build vocabularies from GraphSON (explicit for each dataset):

Devign:

```bash
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/original_devign_functions/train \
    ./CPGs/original_devign_functions/validation \
    ./CPGs/original_devign_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/devign_vocab
```

Draper:

```bash
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/draper_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/draper_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/draper_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/draper_functions/train \
    ./CPGs/draper_functions/validation \
    ./CPGs/draper_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/draper_vocab
```

Reveal:

```bash
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/reveal_functions/train \
    ./CPGs/reveal_functions/validation \
    ./CPGs/reveal_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/reveal_vocab
```

PrimeVul:

```bash
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/primevul_functions/train \
    ./CPGs/primevul_functions/validation \
    ./CPGs/primevul_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/primevul_vocab
```

Optional sanity checks:

```bash
python vuln_detection/scripts/vocab_extraction_sanity.py \
  --vocab-dir ./Clean_exports/devign_vocab
```

## Embedding Extraction (multi_extractor)

Extract semantic embeddings and build caches (examples for UniXcoder per dataset):

Devign:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_devign/unixcoder_768d_devign.sqlite \
  --model-type unixcoder \
  --batch-size 512
```

Draper:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/draper_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_draper/unixcoder_768d_draper.sqlite \
  --model-type unixcoder \
  --batch-size 512
```

Reveal:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/reveal_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_reveal/unixcoder_768d_reveal.sqlite \
  --model-type unixcoder \
  --batch-size 512
```

PrimeVul:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/primevul_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_primevul/unixcoder_768d_primevul.sqlite \
  --model-type unixcoder \
  --batch-size 512
```

## Build PyG Caches

Use `Clean_exports/cache_manager.py` to combine:
1. GraphSON structure (`./CPGs/...`)
2. vocabulary (`./Clean_exports/<dataset>_vocab/`)
3. semantic embeddings (`*.sqlite` from `vuln_detection/multi_extractor.py`)

into PyG caches (`cache_train.zip`, `cache_valid.zip`, `cache_test.zip`) keyed by a deterministic
signature hash.

**Naming convention (recommended):** set `--dataset-name` once and reuse it everywhere (cache
build + training). Example: `devign__full_filtered__unixcoder_768d`.

Devign (UniXcoder + one-hot, full_filtered edges):

```bash
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_devign \
  --vocab-dir ./Clean_exports/devign_vocab \
  --codebert-sqlite ./Clean_exports/cache_devign/unixcoder_768d_devign.sqlite \
  --dataset-name devign__full_filtered__unixcoder_768d \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_train.csv \
  --train-json-root ./CPGs/original_devign_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_validation.csv \
  --val-json-root ./CPGs/original_devign_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_test.csv \
  --test-json-root ./CPGs/original_devign_functions/test
```

Draper:

```bash
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_draper \
  --vocab-dir ./Clean_exports/draper_vocab \
  --codebert-sqlite ./Clean_exports/cache_draper/unixcoder_768d_draper.sqlite \
  --dataset-name draper__full_filtered__unixcoder_768d \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_train.csv \
  --train-json-root ./CPGs/draper_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_validation.csv \
  --val-json-root ./CPGs/draper_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_test.csv \
  --test-json-root ./CPGs/draper_functions/test
```

Reveal:

```bash
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_reveal \
  --vocab-dir ./Clean_exports/reveal_vocab \
  --codebert-sqlite ./Clean_exports/cache_reveal/unixcoder_768d_reveal.sqlite \
  --dataset-name reveal__full_filtered__unixcoder_768d \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv \
  --train-json-root ./CPGs/reveal_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv \
  --val-json-root ./CPGs/reveal_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv \
  --test-json-root ./CPGs/reveal_functions/test
```

PrimeVul:

```bash
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_primevul \
  --vocab-dir ./Clean_exports/primevul_vocab \
  --codebert-sqlite ./Clean_exports/cache_primevul/unixcoder_768d_primevul.sqlite \
  --dataset-name primevul__full_filtered__unixcoder_768d \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv \
  --train-json-root ./CPGs/primevul_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv \
  --val-json-root ./CPGs/primevul_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv \
  --test-json-root ./CPGs/primevul_functions/test
```

After cache build, the script prints `Signature: <CACHE_SIGNATURE>`. You can also find it by:

```bash
ls -1 ./Clean_exports/cache_devign/devign__full_filtered__unixcoder_768d
```

CLI reference notes:
- `Clean_exports/cache_manager.py` includes detailed CLI examples and options near the end of the file.
- `vuln_detection/multi_extractor.py` includes detailed CLI examples and options near the end of the file.
- **Primary training CLIs** are `vuln_detection/train.py` and `vuln_detection/train_advanced.py`
  (use `python -m vuln_detection.train` / `python -m vuln_detection.train_advanced`;
  see examples at the end of each file).
- `vuln_detection/scripts/step2_train.py` and `vuln_detection/scripts/step2_train_advanced.py`
  are convenience wrappers; use `train.py` / `train_advanced.py` for full control.
- `vuln_detection/embeddings/word2vec.py` defines how Word2Vec embeddings are loaded and aggregated.
- `vuln_detection/scripts/train_word2vec.py` provides a full CLI to train a Word2Vec model on code tokens.

## Train Models

The main training entry points are:

- `python -m vuln_detection.train` (baseline and edge-type models)
- `python -m vuln_detection.train_advanced` (RGAT, HGT, MultiView, HyperGraph, Call-Aware)

### Basic models (Devign example with `train.py`)

```bash
python -m vuln_detection.train \
  --model-type improved_devign \
  --embedder-type word2vec \
  --use-structural-features \
  --gnn-type edge_type \
  --gnn-layers 4 \
  --pooling-type multi_stat \
  --num-edge-types 18 \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --hidden-dim 192 \
  --dropout 0.2 \
  --epochs 100 \
  --patience 30 \
  --batch-size 256 \
  --lr 0.001 \
  --max-nodes 500 \
  --save-dir ./checkpoints \
  --experiment-name devign_edge_type
```

Supported `--model-type` values in `train.py`:

- `devign`
- `improved_devign`
- `call_aware`
- `graph_level_mlp`
- `attention`
- `custom`

### Advanced models (Devign example with `train_advanced.py`)

```bash
python -m vuln_detection.train_advanced \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --num-edge-types 18 \
  --num-node-types 15 \
  --hidden-dim 256 \
  --num-heads 4 \
  --num-layers 4 \
  --dropout 0.2 \
  --epochs 150 \
  --patience 30 \
  --batch-size 32 \
  --lr 0.0008 \
  --save-dir ./checkpoints_advanced \
  --experiment-name devign_rgat
```

Supported `--model-type` values in `train_advanced.py`:

- `rgat`
- `multiview`
- `hgt`
- `hypergraph`
- `call_aware`

## Word2Vec Training (Devign-style)

The Word2Vec pipeline mirrors the original Devign approach by training token embeddings on code and aggregating them per node.

### How `word2vec.py` works

`vuln_detection/embeddings/word2vec.py` implements `Word2VecEmbedder` and handles two cases:

1. **Token indices input** (`x` is integer indices):
   - Looks up per-token vectors using `torch.nn.Embedding`.
   - Aggregates token vectors per node using `mean`, `sum`, or `max`.
   - Applies dropout after aggregation.

2. **Continuous features input** (`x` already embedded):
   - If the feature dimension differs from `output_dim`, it projects with a linear layer.
   - Applies dropout and returns the projected embedding.

Pretrained Word2Vec vectors are loaded via gensim (`.bin` or `.txt`) when `pretrained_path` is set.

### Train Word2Vec on code tokens

Use the training CLI in `vuln_detection/scripts/train_word2vec.py`. Example:

```bash
python vuln_detection/scripts/train_word2vec.py \
  --input-csv \
    ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --output-dir ./Clean_exports/word2vec_devign \
  --dim 200 \
  --window 5 \
  --min-count 2 \
  --epochs 30 \
  --workers 8
```

This writes a binary Word2Vec model file:

- `./Clean_exports/word2vec_devign/code_word2vec_200d.bin`

Use that file with `vuln_detection/multi_extractor.py`:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_devign/word2vec_200d_devign.sqlite \
  --model-type word2vec \
  --word2vec-path ./Clean_exports/word2vec_devign/code_word2vec_200d.bin
```

### Step-by-step flow (full pipeline)

1. **Preprocess and split** raw source files per function to produce `manifest_train/validation/test.csv`.
2. **Generate CPGs** with Joern for each split.
3. **Export GraphSON** JSON for each split (`train/validation/test`).
4. **Build vocabularies** with `Clean_exports/vocab_builder.py` using manifests + JSON roots.
5. **Train Word2Vec** on code strings (optional, for Devign-style embeddings).
6. **Extract embeddings** with `vuln_detection/multi_extractor.py` into SQLite caches.
7. **Build PyG caches** with `Clean_exports/cache_manager.py`.
8. **Train models** with `python -m vuln_detection.train` and `python -m vuln_detection.train_advanced`.
9. **Inspect outputs** in `./checkpoints/` and `./checkpoints_advanced/` (metrics are printed during training).

## Reproducing All Models End-to-End

A full run for each dataset follows this order:

1. Preprocess and split raw data using `workspace/A_Preprocessing_scripts`.
2. Generate CPGs and export GraphSON using `workspace/B_Joern_graphs_generation_scripts`.
3. Build vocabularies with `Clean_exports/vocab_builder.py`.
4. Extract embeddings using `vuln_detection/multi_extractor.py`.
5. Build PyG caches using `Clean_exports/cache_manager.py`.
6. Train all basic models with `python -m vuln_detection.train`.
7. Train all advanced models with `python -m vuln_detection.train_advanced`.

Below are explicit end-to-end command sequences for each dataset. Replace
`<CACHE_SIGNATURE>` with the signature printed by `Clean_exports/cache_manager.py`
(or list `./Clean_exports/cache_<dataset>/<dataset_name>/` to find it).

### Devign (original)

```bash
# 1) Split per-function
python workspace/A_Preprocessing_scripts/01c_split_per_function_devign.py \
  --input-base ./datasets/devign_full/json \
  --output-base ./workspace/03_PerFunction_datasets/original_devign_functions \
  --splits train validation test

# 2) CPG + GraphSON
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_devign_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/original_devign_functions \
  --out-base ./CPGs/original_devign_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson

# 3) Vocab
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/original_devign_functions/train \
    ./CPGs/original_devign_functions/validation \
    ./CPGs/original_devign_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/devign_vocab

# 4) Word2Vec (train + extract)
python vuln_detection/scripts/train_word2vec.py \
  --input-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --output-dir ./Clean_exports/word2vec_devign_200d \
  --dim 200 \
  --window 5 \
  --min-count 2 \
  --epochs 30 \
  --workers 8

python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_devign/word2vec_200d_devign.sqlite \
  --model-type word2vec \
  --word2vec-path ./Clean_exports/word2vec_devign_200d/code_word2vec_200d.bin \
  --batch-size 512

# 5) Build caches
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_devign \
  --vocab-dir ./Clean_exports/devign_vocab \
  --codebert-sqlite ./Clean_exports/cache_devign/word2vec_200d_devign.sqlite \
  --dataset-name word2vec_200d_devign_full_filtered \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_train.csv \
  --train-json-root ./CPGs/original_devign_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_validation.csv \
  --val-json-root ./CPGs/original_devign_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_test.csv \
  --test-json-root ./CPGs/original_devign_functions/test

# 6) Train basic models
python -m vuln_detection.train \
  --model-type improved_devign \
  --embedder-type word2vec \
  --use-structural-features \
  --gnn-type edge_type \
  --gnn-layers 4 \
  --pooling-type multi_stat \
  --num-edge-types 18 \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name word2vec_200d_devign_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --hidden-dim 192 \
  --dropout 0.2 \
  --epochs 100 \
  --patience 30 \
  --batch-size 256 \
  --lr 0.001 \
  --max-nodes 500 \
  --save-dir ./checkpoints \
  --experiment-name devign_edge_type

# 7) Train advanced models
python -m vuln_detection.train_advanced \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name word2vec_200d_devign_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --num-edge-types 18 \
  --num-node-types 15 \
  --hidden-dim 256 \
  --num-heads 4 \
  --num-layers 4 \
  --dropout 0.2 \
  --epochs 150 \
  --patience 30 \
  --batch-size 32 \
  --lr 0.0008 \
  --save-dir ./checkpoints_advanced \
  --experiment-name devign_rgat
```

### Draper

```bash
# 1) Split per-function
python workspace/A_Preprocessing_scripts/01e_split_per_function_draper.py \
  --input-dir ./datasets/draper_raw \
  --output-base ./workspace/03_PerFunction_datasets/draper_functions \
  --splits train validation test \
  --label-column combine

# 2) CPG + GraphSON
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_draper_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/draper_functions \
  --out-base ./CPGs/draper_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson

# 3) Vocab
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/draper_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/draper_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/draper_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/draper_functions/train \
    ./CPGs/draper_functions/validation \
    ./CPGs/draper_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/draper_vocab

# 4) Word2Vec (train + extract)
python vuln_detection/scripts/train_word2vec.py \
  --input-csv ./Clean_exports/draper_vocab/strings_to_embed.csv \
  --output-dir ./Clean_exports/word2vec_draper_200d \
  --dim 200 \
  --window 5 \
  --min-count 2 \
  --epochs 30 \
  --workers 8

python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/draper_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_draper/word2vec_200d_draper.sqlite \
  --model-type word2vec \
  --word2vec-path ./Clean_exports/word2vec_draper_200d/code_word2vec_200d.bin \
  --batch-size 512

# 5) Build caches
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_draper \
  --vocab-dir ./Clean_exports/draper_vocab \
  --codebert-sqlite ./Clean_exports/cache_draper/word2vec_200d_draper.sqlite \
  --dataset-name word2vec_200d_draper_full_filtered \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_train.csv \
  --train-json-root ./CPGs/draper_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_validation.csv \
  --val-json-root ./CPGs/draper_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_test.csv \
  --test-json-root ./CPGs/draper_functions/test

# 6) Train basic models
python -m vuln_detection.train \
  --model-type improved_devign \
  --embedder-type word2vec \
  --use-structural-features \
  --gnn-type edge_type \
  --gnn-layers 4 \
  --pooling-type multi_stat \
  --num-edge-types 19 \
  --cache-dir ./Clean_exports/cache_draper \
  --dataset-name word2vec_200d_draper_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --hidden-dim 192 \
  --dropout 0.2 \
  --epochs 100 \
  --patience 30 \
  --batch-size 256 \
  --lr 0.001 \
  --max-nodes 500 \
  --save-dir ./checkpoints \
  --experiment-name draper_edge_type

# 7) Train advanced models
python -m vuln_detection.train_advanced \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_draper \
  --dataset-name word2vec_200d_draper_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --num-edge-types 19 \
  --num-node-types 16 \
  --hidden-dim 256 \
  --num-heads 4 \
  --num-layers 4 \
  --dropout 0.2 \
  --epochs 150 \
  --patience 30 \
  --batch-size 32 \
  --lr 0.0008 \
  --save-dir ./checkpoints_advanced \
  --experiment-name draper_rgat
```

### Reveal

```bash
# 1) Split per-function
python workspace/A_Preprocessing_scripts/01d_split_per_function_reveal.py \
  --input-dir ./datasets/reveal_raw \
  --output-base ./workspace/03_PerFunction_datasets/reveal_functions \
  --splits train validation test

# 2) CPG + GraphSON
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_reveal_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/reveal_functions \
  --out-base ./CPGs/reveal_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson

# 3) Vocab
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/reveal_functions/train \
    ./CPGs/reveal_functions/validation \
    ./CPGs/reveal_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/reveal_vocab

# 4) Word2Vec (train + extract)
python vuln_detection/scripts/train_word2vec.py \
  --input-csv ./Clean_exports/reveal_vocab/strings_to_embed.csv \
  --output-dir ./Clean_exports/word2vec_reveal_200d \
  --dim 200 \
  --window 5 \
  --min-count 2 \
  --epochs 30 \
  --workers 8

python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/reveal_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_reveal/word2vec_200d_reveal.sqlite \
  --model-type word2vec \
  --word2vec-path ./Clean_exports/word2vec_reveal_200d/code_word2vec_200d.bin \
  --batch-size 512

# 5) Build caches
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_reveal \
  --vocab-dir ./Clean_exports/reveal_vocab \
  --codebert-sqlite ./Clean_exports/cache_reveal/word2vec_200d_reveal.sqlite \
  --dataset-name word2vec_200d_reveal_full_filtered \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv \
  --train-json-root ./CPGs/reveal_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv \
  --val-json-root ./CPGs/reveal_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv \
  --test-json-root ./CPGs/reveal_functions/test

# 6) Train basic models
python -m vuln_detection.train \
  --model-type improved_devign \
  --embedder-type word2vec \
  --use-structural-features \
  --gnn-type edge_type \
  --gnn-layers 4 \
  --pooling-type multi_stat \
  --num-edge-types 19 \
  --cache-dir ./Clean_exports/cache_reveal \
  --dataset-name word2vec_200d_reveal_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --hidden-dim 192 \
  --dropout 0.2 \
  --epochs 100 \
  --patience 30 \
  --batch-size 256 \
  --lr 0.001 \
  --max-nodes 500 \
  --save-dir ./checkpoints \
  --experiment-name reveal_edge_type

# 7) Train advanced models
python -m vuln_detection.train_advanced \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_reveal \
  --dataset-name word2vec_200d_reveal_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --num-edge-types 19 \
  --num-node-types 16 \
  --hidden-dim 256 \
  --num-heads 4 \
  --num-layers 4 \
  --dropout 0.2 \
  --epochs 150 \
  --patience 30 \
  --batch-size 32 \
  --lr 0.0008 \
  --save-dir ./checkpoints_advanced \
  --experiment-name reveal_rgat
```

### PrimeVul

```bash
# 1) Split per-function
python workspace/A_Preprocessing_scripts/01f_split_per_function_primevul.py \
  --input-dir ./datasets/primevul_raw \
  --output-base ./workspace/03_PerFunction_datasets/primevul_functions \
  --splits train validation test \
  --code-field func \
  --label-field target

# 2) CPG + GraphSON
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_primevul_final.py \
  --perfunc-base ./workspace/03_PerFunction_datasets/primevul_functions \
  --out-base ./CPGs/primevul_functions \
  --splits train,validation,test \
  --stage both \
  --format graphson

# 3) Vocab
python Clean_exports/vocab_builder.py \
  --manifests \
    ./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv \
    ./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv \
    ./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv \
  --json-roots \
    ./CPGs/primevul_functions/train \
    ./CPGs/primevul_functions/validation \
    ./CPGs/primevul_functions/test \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/primevul_vocab

# 4) Word2Vec (train + extract)
python vuln_detection/scripts/train_word2vec.py \
  --input-csv ./Clean_exports/primevul_vocab/strings_to_embed.csv \
  --output-dir ./Clean_exports/word2vec_primevul_200d \
  --dim 200 \
  --window 5 \
  --min-count 2 \
  --epochs 30 \
  --workers 8

python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/primevul_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_primevul/word2vec_200d_primevul.sqlite \
  --model-type word2vec \
  --word2vec-path ./Clean_exports/word2vec_primevul_200d/code_word2vec_200d.bin \
  --batch-size 512

# 5) Build caches
python Clean_exports/cache_manager.py \
  --edge-mode full_filtered \
  --cache-root ./Clean_exports/cache_primevul \
  --vocab-dir ./Clean_exports/primevul_vocab \
  --codebert-sqlite ./Clean_exports/cache_primevul/word2vec_200d_primevul.sqlite \
  --dataset-name word2vec_200d_primevul_full_filtered \
  --use-code-embeddings --one-hot \
  --fusion-mode early_concat \
  --merge-to-zip --delete-shards-after-merge \
  --train-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv \
  --train-json-root ./CPGs/primevul_functions/train \
  --val-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv \
  --val-json-root ./CPGs/primevul_functions/validation \
  --test-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv \
  --test-json-root ./CPGs/primevul_functions/test

# 6) Train basic models
python -m vuln_detection.train \
  --model-type improved_devign \
  --embedder-type word2vec \
  --use-structural-features \
  --gnn-type edge_type \
  --gnn-layers 4 \
  --pooling-type multi_stat \
  --num-edge-types 19 \
  --cache-dir ./Clean_exports/cache_primevul \
  --dataset-name word2vec_200d_primevul_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --hidden-dim 192 \
  --dropout 0.2 \
  --epochs 100 \
  --patience 30 \
  --batch-size 256 \
  --lr 0.001 \
  --max-nodes 500 \
  --save-dir ./checkpoints \
  --experiment-name primevul_edge_type

# 7) Train advanced models
python -m vuln_detection.train_advanced \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_primevul \
  --dataset-name word2vec_200d_primevul_full_filtered \
  --cache-signature <CACHE_SIGNATURE> \
  --embedding-dim 200 \
  --num-edge-types 19 \
  --num-node-types 16 \
  --hidden-dim 256 \
  --num-heads 4 \
  --num-layers 4 \
  --dropout 0.2 \
  --epochs 150 \
  --patience 30 \
  --batch-size 32 \
  --lr 0.0008 \
  --save-dir ./checkpoints_advanced \
  --experiment-name primevul_rgat
```
