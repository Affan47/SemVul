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

Run preprocessing (examples):

```bash
python workspace/A_Preprocessing_scripts/01a_inspect_and_deduplicate_devign.py \
  --input ./datasets/devign_raw \
  --output ./datasets/devign_dedup

python workspace/A_Preprocessing_scripts/01b_normalize_devign.py \
  --input ./datasets/devign_dedup \
  --output ./datasets/devign_norm

python workspace/A_Preprocessing_scripts/01c_split_per_function_devign.py \
  --input ./datasets/devign_norm \
  --output ./workspace/03_PerFunction_datasets/normalized_devign_functions
```

Repeat for Draper, Reveal, PrimeVul with the corresponding scripts:

- `01d_split_per_function_reveal.py`
- `01e_split_per_function_draper.py`
- `01f_split_per_function_primevul.py`

## CPG Generation and GraphSON Export

Generate CPGs with Joern and export GraphSON. Use the dataset-specific scripts in `workspace/B_Joern_graphs_generation_scripts`.

The main generators are:
1. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_devign_final.py`
2. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_draper_final.py`
3. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_primevul_final.py`
4. `workspace/B_Joern_graphs_generation_scripts/generate_cpg_reveal_final.py`

Each of these scripts includes CLI usage examples at the end of the file.

Example for Devign:

```bash
python workspace/B_Joern_graphs_generation_scripts/generate_cpg_devign_final.py \
  --input ./workspace/03_PerFunction_datasets/normalized_devign_functions \
  --output ./CPGs/devign
```

Export GraphSON (if using shell scripts):

```bash
bash workspace/B_Joern_graphs_generation_scripts/04a_export_cpg_devign.sh \
  ./CPGs/devign \
  ./CPGs/devign_graphson
```

Repeat for Draper, Reveal, PrimeVul with the matching scripts.

## GraphSON Parsing and Vocabulary Building

Build vocabularies from GraphSON:

```bash
python Clean_exports/vocab_builder.py \
  --graphson-root ./CPGs/devign_graphson \
  --output ./Clean_exports/devign_vocab
```

Optional sanity checks:

```bash
python vuln_detection/scripts/vocab_extraction_sanity.py \
  --vocab-dir ./Clean_exports/devign_vocab
```

## Embedding Extraction (multi_extractor)

Extract semantic embeddings and build caches. Example for UniXcoder:

```bash
python vuln_detection/multi_extractor.py \
  --strings-csv ./Clean_exports/devign_vocab/strings_to_embed.csv \
  --code-emb-cache ./Clean_exports/cache_devign/unixcoder_768d_devign.sqlite \
  --model-type unixcoder \
  --batch-size 512
```

Repeat for other embedders as needed:

- `word2vec`
- `codebert`
- `graphcodebert`
- `codet5`
- `unixcoder`

## Build PyG Caches

Use the step script to build caches that pair structure with embeddings:

```bash
python vuln_detection/scripts/step1_build_caches.py \
  --graphson-root ./CPGs/devign_graphson \
  --vocab-dir ./Clean_exports/devign_vocab \
  --cache-dir ./Clean_exports/cache_devign
```

After cache build, find the cache signature in:

```
./Clean_exports/cache_devign/<dataset_name>/train/
```

CLI reference notes:
- `Clean_exports/cache_manager.py` includes detailed CLI examples and options near the end of the file.
- `vuln_detection/multi_extractor.py` includes detailed CLI examples and options near the end of the file.
- `vuln_detection/train.py` includes detailed CLI examples near the end of the file.
- `vuln_detection/train_advanced.py` includes detailed CLI examples near the end of the file.

## Train Models

### Basic models

```bash
python vuln_detection/scripts/step2_train.py \
  --model-type mlp \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name devign_normfunc_v2 \
  --cache-signature <SIGNATURE> \
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

### Advanced models

```bash
python vuln_detection/scripts/step2_train_advanced.py \
  --model-type rgat \
  --cache-dir ./Clean_exports/cache_devign \
  --dataset-name devign_normfunc_v2 \
  --cache-signature <SIGNATURE> \
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

## Evaluation and Comparison

Compare all result folders:

```bash
python vuln_detection/scripts/step3_compare_results.py \
  --results-dir ./results
```

The script aggregates per-model metrics into a summary table. Each training run also writes a `results.json` in its output directory.

## Reproducing All Models End-to-End

A full run for each dataset follows this order:

1. Preprocess and split raw data using `workspace/A_Preprocessing_scripts`.
2. Generate CPGs and export GraphSON using `workspace/B_Joern_graphs_generation_scripts`.
3. Build vocabularies with `Clean_exports/vocab_builder.py`.
4. Extract embeddings using `vuln_detection/multi_extractor.py`.
5. Build PyG caches using `vuln_detection/scripts/step1_build_caches.py`.
6. Train all basic models with `vuln_detection/scripts/step2_train.py`.
7. Train all advanced models with `vuln_detection/scripts/step2_train_advanced.py`.
8. Aggregate results with `vuln_detection/scripts/step3_compare_results.py`.

## Notes

- All paths in this repository are relative. Avoid absolute paths when reproducing.
- Model checkpoints and caches are excluded from Git by default.
- If you add new datasets, ensure the node and edge type vocabularies are rebuilt.
