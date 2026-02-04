# 🔤 Word2Vec for Code Embeddings - Complete Guide

This guide walks you through training and using Word2Vec embeddings for vulnerability detection,
similar to the original Devign paper.

---

## 📦 Step 1: Install Gensim

```bash
# Using pip
pip install gensim

# Or with conda
conda install -c conda-forge gensim

# Verify installation
python -c "from gensim.models import Word2Vec; print('gensim OK')"
```

**Required packages:**
- `gensim>=4.0.0` - Word2Vec implementation
- `numpy` - Numerical operations
- `scipy` - Scientific computing (dependency of gensim)

---

## 📊 Step 2: Prepare Your Corpus

You have **3 options** for input data:

### Option A: From `strings_to_embed.csv` (Recommended)
If you already have the `strings_to_embed.csv` from vocab_builder:
```bash
python train_word2vec.py \
    --input-csv /path/to/strings_to_embed.csv \
    --output-model /path/to/code_word2vec \
    --dim 128 \
    --epochs 10
```

### Option B: From GraphSON Files
If you have GraphSON exports from Joern:
```bash
python train_word2vec.py \
    --graphson-dir /path/to/graphson_exports \
    --output-model /path/to/code_word2vec \
    --dim 128 \
    --epochs 10
```

### Option C: From Vocabulary File
If you have a vocabulary JSON file:
```bash
python train_word2vec.py \
    --vocab-file /path/to/vocab.json \
    --input-csv /path/to/strings_to_embed.csv \
    --output-model /path/to/code_word2vec \
    --dim 128
```

---

## 🎯 Step 3: Train Word2Vec

### Full Command with All Options

```bash
python train_word2vec.py \
    --input-csv "./workspace/strings_to_embed.csv" \
    --output-model "./Clean_exports/word2vec/code_word2vec" \
    --dim 128 \
    --window 5 \
    --min-count 2 \
    --epochs 10 \
    --workers 8 \
    --algorithm skipgram \
    --negative 5 \
    --log-file word2vec_training.log
```

### Parameters Explained

| Parameter | Default | Description |
|-----------|---------|-------------|
| `--dim` | 128 | Embedding dimension (Devign uses 128) |
| `--window` | 5 | Context window size |
| `--min-count` | 2 | Minimum word frequency |
| `--epochs` | 10 | Training epochs |
| `--workers` | 4 | Parallel threads |
| `--algorithm` | skipgram | `skipgram` (better) or `cbow` |
| `--negative` | 5 | Negative samples |

### Output Files

After training, you'll get:
```
code_word2vec.bin        # Binary format (use this with multi_extractor.py)
code_word2vec.txt        # Text format (for inspection)
code_word2vec.model      # Full model (for continued training)
code_word2vec.stats.json # Training statistics
```

---

## 🔄 Step 4: Extract Embeddings with Word2Vec

Use your trained Word2Vec model to create embeddings:

```bash
python multi_extractor.py \
    --strings-csv "/path/to/strings_to_embed.csv" \
    --code-emb-cache "/path/to/word2vec_embeddings.sqlite" \
    --model-type word2vec \
    --word2vec-path "/path/to/code_word2vec.bin" \
    --batch-size 256
```

---

## 🏗️ Step 5: Build Cache with Word2Vec Embeddings

After extracting embeddings, build the PyG cache:

```bash
python cache_manager.py \
    --graphson-root "/path/to/graphson_exports" \
    --code-emb-cache "/path/to/word2vec_embeddings.sqlite" \
    --vocab-dir "/path/to/vocab_dir" \
    --cache-root "/path/to/cache_word2vec" \
    --dataset-name "devign_normfunc_v2" \
    --manifest-root "/path/to/manifests" \
    --embedding-fusion early_concat
```

---

## 🚀 Step 6: Train Models with Word2Vec Embeddings

```bash
python step2_train.py \
    --model-type mlp \
    --cache-dir "/path/to/cache_word2vec" \
    --dataset-name "devign_normfunc_v2" \
    --cache-signature "YOUR_WORD2VEC_SIGNATURE" \
    --vocab-dir "/path/to/vocab_dir" \
    --train-manifest "/path/to/manifest_train.csv" \
    --val-manifest "/path/to/manifest_validation.csv" \
    --test-manifest "/path/to/manifest_test.csv" \
    --hidden-dim 128 \
    --epochs 100 \
    --output-dir "results_word2vec_mlp"
```

---

## 📈 Complete Pipeline Example

```bash
# ============================================================================
# COMPLETE WORD2VEC PIPELINE
# ============================================================================

# Set paths
export BASE_DIR="."
export STRINGS_CSV="${BASE_DIR}/workspace/strings_to_embed.csv"
export W2V_DIR="${BASE_DIR}/Clean_exports/word2vec"
export CACHE_DIR="${BASE_DIR}/Clean_exports/cache_word2vec"

# Create directories
mkdir -p ${W2V_DIR}

# Step 1: Train Word2Vec
python train_word2vec.py \
    --input-csv "${STRINGS_CSV}" \
    --output-model "${W2V_DIR}/code_word2vec" \
    --dim 128 \
    --epochs 10 \
    --workers 8 \
    --log-file "${W2V_DIR}/training.log"

# Step 2: Extract embeddings
python multi_extractor.py \
    --strings-csv "${STRINGS_CSV}" \
    --code-emb-cache "${W2V_DIR}/word2vec_embeddings.sqlite" \
    --model-type word2vec \
    --word2vec-path "${W2V_DIR}/code_word2vec.bin" \
    --batch-size 256

# Step 3: Build cache (use your existing cache_manager.py)
# ... (follow normal cache building process)

# Step 4: Train model
# ... (follow normal training process with new cache signature)
```

---

## 🔍 Verifying Your Word2Vec Model

```python
# Quick test script
from gensim.models import KeyedVectors

# Load model
wv = KeyedVectors.load_word2vec_format("code_word2vec.bin", binary=True)

# Print statistics
print(f"Vocabulary size: {len(wv)}")
print(f"Embedding dimension: {wv.vector_size}")

# Test some tokens
test_tokens = ["int", "void", "return", "if", "for", "while", "malloc", "free"]
for token in test_tokens:
    if token in wv:
        print(f"✓ '{token}' found")
        # Get similar words
        similar = wv.most_similar(token, topn=5)
        print(f"  Similar: {[w for w, _ in similar]}")
    else:
        print(f"✗ '{token}' not in vocabulary")
```

---

## 📊 Expected Results Comparison

| Embedding | Dimension | Training Time | Expected AUC |
|-----------|-----------|---------------|--------------|
| Word2Vec | 128 | ~10 min | 0.60-0.65 |
| CodeBERT | 768 | N/A (pretrained) | 0.60-0.63 |
| CodeT5+ | 256 | N/A (pretrained) | 0.63-0.67 |

**Note:** Word2Vec was used in the original Devign paper (F1=73.26%), so it can achieve competitive results with proper training.

---

## 🐛 Troubleshooting

### "gensim not installed"
```bash
pip install gensim --upgrade
```

### "No sentences found in corpus"
- Check that your input CSV/GraphSON files exist
- Verify the CSV has a "string" or "code" column
- Ensure files are not empty

### "Out of memory during training"
```bash
# Reduce workers
--workers 2

# Or train on smaller corpus
--min-count 5  # Filter rare tokens
```

### "KeyError: 'token' not found"
- Some tokens may not be in the vocabulary (filtered by min_count)
- This is normal - unknown tokens get zero vectors

---

## 💡 Tips for Better Word2Vec Models

1. **More data = better embeddings**: Use all your code strings
2. **Skip-gram > CBOW** for code: Better captures rare tokens
3. **Reasonable dimension**: 128-256 works well for code
4. **Sufficient epochs**: 10-20 epochs usually sufficient
5. **Window size**: 5-10 works well for code context
6. **Min count**: 2-5 to filter very rare tokens
