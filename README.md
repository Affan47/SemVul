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
- A working Joern installation.
- CUDA-capable GPU recommended for large embeddings and training.

Suggested Python packages:

```bash
pip install torch torch_geometric transformers scikit-learn pandas numpy tqdm
```

Joern setup (example):

```bash
export JOERN_HOME=./external/joern
export PATH="$JOERN_HOME:$PATH"
```

## Data Preparation

Place raw datasets under a local `datasets` folder, then run the preprocessing scripts. Use relative paths only. Example structure:

```
./datasets/
  devign_raw/
  draper_raw/
  reveal_raw/
  primevul_raw/
```

Run preprocessing (explicit commands):

```bash
# (Optional) Devign deduplication (writes ./datasets/devign_dedup/workspace/deduped)
python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --in ./datasets/devign_raw/train.jsonl \
  --tag train \
  --root ./datasets/devign_dedup

python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --in ./datasets/devign_raw/validation.jsonl \
  --tag validation \
  --root ./datasets/devign_dedup

python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --in ./datasets/devign_raw/test.jsonl \
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
  --input-base ./datasets/devign_raw \
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

Use the step script to build caches that pair structure with embeddings (one dataset per run):

Devign:

```bash
python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_devign \
  --vocab-dir ./Clean_exports/devign_vocab
```

Before running, open `vuln_detection/scripts/step1_build_caches.py` and update
`DEFAULT_CONFIG` for your dataset:
- `train_manifest`, `val_manifest`, `test_manifest`
- `train_json`, `val_json`, `test_json`
- `cache_root`, `vocab_dir`, and `dataset-name` (inside the cache_manager command)

After cache build, find the cache signature in:

```
./Clean_exports/cache_devign/<dataset_name>/train/
```

Draper / Reveal / PrimeVul:

```bash
python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_draper \
  --vocab-dir ./Clean_exports/draper_vocab

python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_reveal \
  --vocab-dir ./Clean_exports/reveal_vocab

python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_primevul \
  --vocab-dir ./Clean_exports/primevul_vocab
```

CLI reference notes:
- `Clean_exports/cache_manager.py` includes detailed CLI examples and options near the end of the file.
- `vuln_detection/multi_extractor.py` includes detailed CLI examples and options near the end of the file.
- `vuln_detection/train.py` includes detailed CLI examples near the end of the file.
- `vuln_detection/train_advanced.py` includes detailed CLI examples near the end of the file.
- `vuln_detection/embeddings/word2vec.py` defines how Word2Vec embeddings are loaded and aggregated.
- `vuln_detection/scripts/train_word2vec.py` provides a full CLI to train a Word2Vec model on code tokens.

## Train Models

### Basic models (Devign example)

```bash
python vuln_detection/scripts/step2_train.py \
  --model-type mlp \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/devign_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv \
  --hidden-dim 128 \
  --epochs 100 \
  --output-dir ./results/mlp
```

Supported `--model-type` values in `step2_train.py`:

- `mlp`
- `devign`
- `ggnn`
- `gcn`
- `gat`
- `transformer`
- `attention`
- `edge_type`
- `shallow`

### Advanced models (Devign example)

```bash
python vuln_detection/scripts/step2_train_advanced.py \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/devign_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test.csv \
  --hidden-dim 128 \
  --layers 2 \
  --output-dir ./results/rgat
```

Supported `--model-type` values in `step2_train_advanced.py`:

- `multiview`
- `hgt`
- `rgat`
- `hypergraph`

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

This writes a gensim Word2Vec model in the output directory. Use the resulting model path with:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_devign/word2vec_200d_devign.sqlite \
  --model-type word2vec \
  --word2vec-path ./Clean_exports/word2vec_devign/word2vec.bin
```

### Step-by-step flow (full pipeline)

1. **Preprocess and split** raw source files per function to produce `manifest_train/validation/test.csv`.
2. **Generate CPGs** with Joern for each split.
3. **Export GraphSON** JSON for each split (`train/validation/test`).
4. **Build vocabularies** with `Clean_exports/vocab_builder.py` using manifests + JSON roots.
5. **Train Word2Vec** on code strings (optional, for Devign-style embeddings).
6. **Extract embeddings** with `vuln_detection/multi_extractor.py` into SQLite caches.
7. **Build PyG caches** with `vuln_detection/scripts/step1_build_caches.py`.
8. **Train models** with `step2_train.py` and `step2_train_advanced.py`.
9. **Evaluate and compare** with the results summary scripts.

## Reproducing All Models End-to-End

A full run for each dataset follows this order:

1. Preprocess and split raw data using `workspace/A_Preprocessing_scripts`.
2. Generate CPGs and export GraphSON using `workspace/B_Joern_graphs_generation_scripts`.
3. Build vocabularies with `Clean_exports/vocab_builder.py`.
4. Extract embeddings using `vuln_detection/multi_extractor.py`.
5. Build PyG caches using `vuln_detection/scripts/step1_build_caches.py`.
6. Train all basic models with `vuln_detection/scripts/step2_train.py`.
7. Train all advanced models with `vuln_detection/scripts/step2_train_advanced.py`.
8. Aggregate results with the results summary scripts.

Below are explicit end-to-end command sequences for each dataset. Replace
`<CACHE_SIGNATURE>` with the actual cache signature you find under
`./Clean_exports/cache_<dataset>/<dataset_name>/train/`.

### Devign (original)

```bash
# 1) Split per-function
python workspace/A_Preprocessing_scripts/01c_split_per_function_devign.py \
  --input-base ./datasets/devign_raw \
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
    ./CPGs/original_devign_functions/train/exports \
    ./CPGs/original_devign_functions/validation/exports \
    ./CPGs/original_devign_functions/test/exports \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/devign_vocab

# 4) Embeddings (example: UniXcoder)
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_devign/unixcoder_768d_devign.sqlite \
  --model-type unixcoder \
  --batch-size 512

# 5) Build caches (edit DEFAULT_CONFIG inside step1_build_caches.py first)
python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_devign \
  --vocab-dir ./Clean_exports/devign_vocab

# 6) Train basic models
python vuln_detection/scripts/step2_train.py \
  --model-type edge_type \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/devign_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_test.csv \
  --hidden-dim 128 \
  --epochs 100 \
  --output-dir ./results/devign_edge_type

# 7) Train advanced models
python vuln_detection/scripts/step2_train_advanced.py \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/devign_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/original_devign_functions/manifest_test.csv \
  --hidden-dim 128 \
  --layers 2 \
  --output-dir ./results/devign_rgat
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
    ./CPGs/draper_functions/train/exports \
    ./CPGs/draper_functions/validation/exports \
    ./CPGs/draper_functions/test/exports \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/draper_vocab

# 4) Embeddings (example: UniXcoder)
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/draper_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_draper/unixcoder_768d_draper.sqlite \
  --model-type unixcoder \
  --batch-size 512

# 5) Build caches (edit DEFAULT_CONFIG inside step1_build_caches.py first)
python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_draper \
  --vocab-dir ./Clean_exports/draper_vocab

# 6) Train basic models
python vuln_detection/scripts/step2_train.py \
  --model-type edge_type \
  --cache-dir ./Clean_exports/cache_draper \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/draper_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_test.csv \
  --hidden-dim 128 \
  --epochs 100 \
  --output-dir ./results/draper_edge_type

# 7) Train advanced models
python vuln_detection/scripts/step2_train_advanced.py \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_draper \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/draper_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/draper_functions/manifest_test.csv \
  --hidden-dim 128 \
  --layers 2 \
  --output-dir ./results/draper_rgat
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
    ./CPGs/reveal_functions/train/exports \
    ./CPGs/reveal_functions/validation/exports \
    ./CPGs/reveal_functions/test/exports \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/reveal_vocab

# 4) Embeddings (example: UniXcoder)
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/reveal_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_reveal/unixcoder_768d_reveal.sqlite \
  --model-type unixcoder \
  --batch-size 512

# 5) Build caches (edit DEFAULT_CONFIG inside step1_build_caches.py first)
python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_reveal \
  --vocab-dir ./Clean_exports/reveal_vocab

# 6) Train basic models
python vuln_detection/scripts/step2_train.py \
  --model-type edge_type \
  --cache-dir ./Clean_exports/cache_reveal \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/reveal_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv \
  --hidden-dim 128 \
  --epochs 100 \
  --output-dir ./results/reveal_edge_type

# 7) Train advanced models
python vuln_detection/scripts/step2_train_advanced.py \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_reveal \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/reveal_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv \
  --hidden-dim 128 \
  --layers 2 \
  --output-dir ./results/reveal_rgat
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
    ./CPGs/primevul_functions/train/exports \
    ./CPGs/primevul_functions/validation/exports \
    ./CPGs/primevul_functions/test/exports \
  --edge-mode full_filtered \
  --out-dir ./Clean_exports/primevul_vocab

# 4) Embeddings (example: UniXcoder)
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/primevul_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_primevul/unixcoder_768d_primevul.sqlite \
  --model-type unixcoder \
  --batch-size 512

# 5) Build caches (edit DEFAULT_CONFIG inside step1_build_caches.py first)
python vuln_detection/scripts/step1_build_caches.py \
  --cache-root ./Clean_exports/cache_primevul \
  --vocab-dir ./Clean_exports/primevul_vocab

# 6) Train basic models
python vuln_detection/scripts/step2_train.py \
  --model-type edge_type \
  --cache-dir ./Clean_exports/cache_primevul \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/primevul_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv \
  --hidden-dim 128 \
  --epochs 100 \
  --output-dir ./results/primevul_edge_type

# 7) Train advanced models
python vuln_detection/scripts/step2_train_advanced.py \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_primevul \
  --dataset-name <DATASET_NAME> \
  --cache-signature <CACHE_SIGNATURE> \
  --vocab-dir ./Clean_exports/primevul_vocab \
  --train-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_train.csv \
  --val-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_validation.csv \
  --test-manifest ./workspace/03_PerFunction_datasets/primevul_functions/manifest_test.csv \
  --hidden-dim 128 \
  --layers 2 \
  --output-dir ./results/primevul_rgat
```
