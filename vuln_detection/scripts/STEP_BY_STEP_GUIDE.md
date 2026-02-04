# 🚀 Vulnerability Detection Training - Complete Step-by-Step Guide

This guide walks you through running all training experiments from start to finish.

---

## 📋 Prerequisites

Make sure you have:
1. PyTorch with CUDA support
2. PyTorch Geometric installed
3. scikit-learn installed
4. Your cached `.pt` files ready

```bash
pip install torch torch-geometric scikit-learn tqdm
```

---

## 📁 Directory Structure

Your workspace should look like:
```
./
├── Clean_exports/
│   ├── cache_devign_v2/           # Cached .pt files
│   │   └── devign_normfunc_v2/
│   │       ├── train/
│   │       │   └── YOUR_SIGNATURE/  # ← Find this!
│   │       ├── valid/
│   │       │   └── YOUR_SIGNATURE/
│   │       └── test/
│   │           └── YOUR_SIGNATURE/
│   └── devign_vocab_normfunc_v2/  # Vocabulary files
│       └── devign_rel_vocab.json
└── workspace/
    └── 03_PerFunction_datasets/
        └── normalized_devign_functions/
            └── normalized_devign_functions/
                ├── manifest_train.csv
                ├── manifest_validation.csv
                └── manifest_test.csv
```

---

## 🔍 Step 1: Find Your Cache Signature

```bash
# List train cache directories to find signature
ls ./Clean_exports/cache_devign_v2/devign_normfunc_v2/train/

# Output example: 2913d0ac45337fed
# This is your CACHE_SIGNATURE
```

**Copy this signature - you'll use it in all commands!**

---

## 🔧 Step 2: Set Up Environment Variables (Optional but Recommended)

Create a file `env.sh` to avoid typing long paths:

```bash
#!/bin/bash
export CACHE_DIR="./Clean_exports/cache_devign_v2"
export DATASET_NAME="devign_normfunc_v2"
export CACHE_SIG="YOUR_SIGNATURE_HERE"  # ← UPDATE THIS!
export VOCAB_DIR="./Clean_exports/devign_vocab_normfunc_v2"
export MANIFEST_DIR="./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions"
export TRAIN_MANIFEST="${MANIFEST_DIR}/manifest_train.csv"
export VAL_MANIFEST="${MANIFEST_DIR}/manifest_validation.csv"
export TEST_MANIFEST="${MANIFEST_DIR}/manifest_test.csv"
```

Then source it:
```bash
source env.sh
```

---

## 🏃 Step 3: Run Training

### Option A: Using Environment Variables (if you set them up)

```bash
# Graph-Level MLP (BEST - Start here!)
python step2_train.py \
  --model-type mlp \
  --cache-dir "$CACHE_DIR" \
  --dataset-name "$DATASET_NAME" \
  --cache-signature "$CACHE_SIG" \
  --vocab-dir "$VOCAB_DIR" \
  --train-manifest "$TRAIN_MANIFEST" \
  --val-manifest "$VAL_MANIFEST" \
  --test-manifest "$TEST_MANIFEST" \
  --hidden-dim 128 \
  --epochs 100 \
  --batch-size 64 \
  --output-dir "results_mlp"
```

### Option B: Full Commands (Copy-Paste Ready)

Replace `YOUR_SIGNATURE` with your actual signature from Step 1:

```bash
# ============================================================================
# BASIC MODELS (step2_train.py)
# ============================================================================

# 1. Graph-Level MLP (BEST MODEL - Start here!)
python step2_train.py \
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
  --batch-size 64 \
  --output-dir "results_mlp"

# 2. Devign GGNN (Original Paper Architecture)
python step2_train.py \
  --model-type devign \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 256 \
  --layers 4 \
  --epochs 100 \
  --batch-size 64 \
  --output-dir "results_devign"

# 3. GCN Model
python step2_train.py \
  --model-type gcn \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 256 \
  --layers 6 \
  --epochs 100 \
  --batch-size 128 \
  --output-dir "results_gcn"

# 4. GAT Model
python step2_train.py \
  --model-type gat \
  --heads 4 \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 256 \
  --layers 6 \
  --epochs 100 \
  --batch-size 128 \
  --output-dir "results_gat"

# 5. Transformer Model
python step2_train.py \
  --model-type transformer \
  --heads 4 \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 256 \
  --layers 4 \
  --epochs 100 \
  --batch-size 32 \
  --output-dir "results_transformer"

# ============================================================================
# ADVANCED MODELS (step2_train_advanced.py)
# ============================================================================

# 6. MultiView GGNN (Separate AST/CFG/DFG encoders)
python step2_train_advanced.py \
  --model-type multiview \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 200 \
  --layers 4 \
  --epochs 100 \
  --batch-size 32 \
  --output-dir "results_multiview"

# 7. HGT (Heterogeneous Graph Transformer)
python step2_train_advanced.py \
  --model-type hgt \
  --heads 4 \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 200 \
  --layers 4 \
  --epochs 100 \
  --batch-size 32 \
  --output-dir "results_hgt"

# 8. Hypergraph / Dual-Attention (GATv2 + Transformer)
python step2_train_advanced.py \
  --model-type hypergraph \
  --heads 4 \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "YOUR_SIGNATURE" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  --hidden-dim 200 \
  --layers 4 \
  --epochs 100 \
  --batch-size 32 \
  --output-dir "results_hypergraph"
```

---

## 📊 Step 4: Compare Results

After running experiments, compare all results:

```bash
python step3_compare_results.py --results-dir ./

# Or save to file
python step3_compare_results.py --results-dir ./ --output comparison_report.txt
```

---

## 📈 Expected Results

| Model | Script | Expected AUC | Notes |
|-------|--------|--------------|-------|
| **MLP** | step2_train.py | **0.63-0.67** | Best & fastest |
| Devign GGNN | step2_train.py | 0.58-0.63 | Original paper |
| GCN | step2_train.py | 0.55-0.60 | Baseline |
| GAT | step2_train.py | 0.58-0.62 | Attention |
| Transformer | step2_train.py | 0.55-0.60 | Long-range |
| MultiView | step2_train_advanced.py | 0.58-0.62 | View separation |
| HGT | step2_train_advanced.py | 0.55-0.60 | Heterogeneous |
| Hypergraph | step2_train_advanced.py | 0.58-0.62 | Dual-attention |

---

## 🏆 Baselines to Beat

| Method | ACC | F1 | AUC |
|--------|-----|-----|-----|
| **Devign (paper)** | 72.26% | **73.26%** | - |
| ReVeal | 65% | 48% | 63% |
| IVDetect | 68% | 52% | 65% |

---

## 🐛 Troubleshooting

### "Signature not found"
```bash
ls /path/to/cache_devign_v2/devign_normfunc_v2/train/
# Use the folder name shown as --cache-signature
```

### "Out of Memory"
```bash
# Reduce batch size
--batch-size 16  # or even 8
```

### "index.csv not found"
```bash
# Check your cache structure
ls -la /path/to/cache_devign_v2/devign_normfunc_v2/train/YOUR_SIGNATURE/meta/
# Should show: index.csv, signature.json
```

### "CUDA out of memory"
```bash
# Clear cache before training
python -c "import torch; torch.cuda.empty_cache()"

# Or reduce model size
--hidden-dim 128  # instead of 200/256
```

---

## 📁 Output Structure

After training, each results folder contains:
```
results_mlp/
├── best_model.pt          # Best model weights
├── best_threshold.txt     # Optimal classification threshold
└── test_results.json      # Final metrics
```

---

## 🔄 Quick Reference

| Model Type | Script | Key Args |
|------------|--------|----------|
| mlp | step2_train.py | `--model-type mlp` |
| devign/ggnn | step2_train.py | `--model-type devign` |
| gcn | step2_train.py | `--model-type gcn` |
| gat | step2_train.py | `--model-type gat --heads 4` |
| transformer | step2_train.py | `--model-type transformer --heads 4` |
| multiview | step2_train_advanced.py | `--model-type multiview` |
| hgt | step2_train_advanced.py | `--model-type hgt --heads 4` |
| hypergraph | step2_train_advanced.py | `--model-type hypergraph --heads 4` |

---

## 💡 Recommended Execution Order

1. **Start with MLP** - fastest, often best results
2. **Try Devign** - compare to original architecture
3. **Run GAT** - attention-based comparison
4. **Try MultiView** - if edge types matter
5. **Run HGT/Hypergraph** - advanced architectures
6. **Compare all results** - find best configuration
