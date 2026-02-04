# 🚀 Vulnerability Detection Training Scripts

This directory contains step-by-step Python scripts for running all experiments.
**Interface matches Devign_baseline.py exactly** - same argument structure!

## 📋 Quick Start

```bash
cd ./01_vuln_detection

# 1. Build caches (run once)
python scripts/step1_build_caches.py

# 2. Find cache signatures
ls -la /path/to/cache_devign_v2/devign_normfunc_v2/train/

# 3. Train models - FULL COMMAND
python scripts/step2_train.py \
  --model-type mlp \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 128 \
  --epochs 100 \
  --output-dir "results_mlp"

# 4. Compare results
python scripts/step3_compare_results.py --results-dir ./results
```

## 📁 Script Overview

| Script | Description | Usage |
|--------|-------------|-------|
| `step1_build_caches.py` | Build PyG caches for all embeddings | `python step1_build_caches.py` |
| `step2_train.py` | Train basic models (MLP, Devign, GCN, GAT, etc.) | See examples below |
| `step2_train_advanced.py` | Train advanced models (MultiView, HGT, RGAT, Hypergraph) | See examples below |
| `step3_compare_results.py` | Compare all results | `python step3_compare_results.py` |

## 🔧 Complete Usage Examples

### Common Arguments (Same for ALL models)

```bash
# These are REQUIRED for all training scripts
--cache-dir "./Clean_exports/cache_devign_v2"
--dataset-name "devign_normfunc_v2"
--cache-signature "YOUR_SIGNATURE"
--vocab-dir "./Clean_exports/devign_vocab_normfunc_v2"
--train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv"
--val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv"
--test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv"
```

### Basic Models (`step2_train.py`)

```bash
# Graph-Level MLP (BEST MODEL - Fastest & Best Results)
python scripts/step2_train.py \
  --model-type mlp \
  --hidden-dim 128 \
  --batch-size 64 \
  --epochs 100 \
  --output-dir "results_mlp" \
  [... data args above ...]

# Devign GGNN (Original Paper Architecture)
python scripts/step2_train.py \
  --model-type devign \
  --hidden-dim 256 \
  --layers 4 \
  --batch-size 64 \
  --output-dir "results_devign" \
  [... data args above ...]

# GCN Model
python scripts/step2_train.py \
  --model-type gcn \
  --hidden-dim 256 \
  --layers 6 \
  --batch-size 128 \
  --output-dir "results_gcn" \
  [... data args above ...]

# GAT Model
python scripts/step2_train.py \
  --model-type gat \
  --heads 4 \
  --hidden-dim 256 \
  --layers 6 \
  --batch-size 128 \
  --output-dir "results_gat" \
  [... data args above ...]

# Transformer Model
python scripts/step2_train.py \
  --model-type transformer \
  --heads 4 \
  --hidden-dim 256 \
  --layers 4 \
  --batch-size 32 \
  --output-dir "results_transformer" \
  [... data args above ...]

# Attention Model
python scripts/step2_train.py \
  --model-type attention \
  --hidden-dim 128 \
  --batch-size 64 \
  --output-dir "results_attention" \
  [... data args above ...]

# Edge-Type GNN
python scripts/step2_train.py \
  --model-type edge_type \
  --hidden-dim 128 \
  --layers 2 \
  --batch-size 64 \
  --output-dir "results_edge_type" \
  [... data args above ...]

# Shallow GNN
python scripts/step2_train.py \
  --model-type shallow \
  --hidden-dim 128 \
  --layers 1 \
  --batch-size 64 \
  --output-dir "results_shallow" \
  [... data args above ...]
```

**Available Model Types:** `mlp`, `devign`, `ggnn`, `gcn`, `gat`, `transformer`, `attention`, `edge_type`, `shallow`

### Advanced Models (`step2_train_advanced.py`)

```bash
# MultiView GGNN (Separate AST/CFG/DFG views)
python scripts/step2_train_advanced.py \
  --model-type multiview \
  --hidden-dim 128 \
  --layers 3 \
  --batch-size 16 \
  --output-dir "results_multiview" \
  [... data args above ...]

# HGT (Heterogeneous Graph Transformer)
python scripts/step2_train_advanced.py \
  --model-type hgt \
  --heads 4 \
  --hidden-dim 128 \
  --layers 2 \
  --batch-size 16 \
  --output-dir "results_hgt" \
  [... data args above ...]

# RGAT (Relational Graph Attention Network)
python scripts/step2_train_advanced.py \
  --model-type rgat \
  --heads 4 \
  --hidden-dim 128 \
  --layers 2 \
  --batch-size 16 \
  --output-dir "results_rgat" \
  [... data args above ...]

# Hypergraph (Dual Attention)
python scripts/step2_train_advanced.py \
  --model-type hypergraph \
  --hidden-dim 128 \
  --layers 2 \
  --batch-size 16 \
  --output-dir "results_hypergraph" \
  [... data args above ...]
```

**Available Advanced Model Types:** `multiview`, `hgt`, `rgat`, `hypergraph`

## 📊 Expected Results

| Model | Expected AUC | Notes |
|-------|--------------|-------|
| **Graph-Level MLP** | **0.63-0.67** | Best & fastest |
| Devign (GGNN) | 0.58-0.63 | Original paper |
| GCN | 0.55-0.60 | Baseline |
| GAT | 0.58-0.62 | Attention-based |
| Edge-Type GNN | 0.60-0.64 | Uses edge types |
| Attention | 0.60-0.64 | Attention pooling |
| MultiView | 0.58-0.62 | Separate views |
| HGT | 0.55-0.60 | Transformer-based |
| RGAT | 0.58-0.62 | Relational attention |

## 🏆 Baselines to Beat

| Method | ACC | F1 | AUC |
|--------|-----|-----|-----|
| **Devign (paper)** | 72.26% | **73.26%** | - |
| ReVeal | 65% | 48% | 63% |
| IVDetect | 68% | 52% | 65% |

## 💡 Tips

1. **Start with Graph-Level MLP** - fastest and often best results
2. **Reduce batch size** for advanced models (16 instead of 64)
3. **Use lower learning rate** for complex models (0.0005)
4. **Watch for overfitting** - early stopping with patience=15

## 🐛 Troubleshooting

### Signature not found
```bash
# Find your cache signature
ls /path/to/cache_devign_v2/devign_normfunc_v2/train/
# Use the folder name (e.g., abc123def45678ab)
```

### Out of Memory
```bash
# Reduce batch size
python step2_train.py --model-type mlp --batch-size 16 [...]
```

### Cache not found
```bash
# Check cache structure
ls -la /path/to/cache_devign_v2/devign_normfunc_v2/
# Should show: train/ valid/ test/
```

