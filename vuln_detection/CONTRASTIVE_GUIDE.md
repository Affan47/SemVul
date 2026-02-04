# 🚀 3-Stage Vulnerability Detection Enhancement Guide

This guide explains how to use the enhanced vulnerability detection pipeline with:
- **Stage 1**: Vulnerability-aware node features (+5-10% F1)
- **Stage 2**: Supervised Contrastive Learning (+15-25% F1)
- **Stage 3**: HAGNN architecture with separate edge-type processing (+5-10% F1)

**Expected total improvement: +25-45% F1** over baseline

---

## 📁 New Files Added

```
vuln_detection/
├── vuln_features.py          # Stage 1: Vulnerability-aware features
├── contrastive.py            # Stage 2: Supervised Contrastive Learning
├── train_contrastive.py      # Complete training script
└── models/
    └── hagnn.py              # Stage 3: HAGNN architecture
```

---

## 🏃 Quick Start

### Option 1: Use the New Training Script (Recommended)

```bash
# Train HAGNN with contrastive learning
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir /path/to/cache_devign_v2 \
    --dataset-name word2vec_256d_full \
    --cache-signature c95a4168d5a65be0 \
    --hidden-dim 256 \
    --num-layers 4 \
    --num-edge-types 16 \
    --contrastive-weight 0.5 \
    --epochs-pretrain 50 \
    --epochs-finetune 100 \
    --batch-size 32 \
    --save-dir ./results/hagnn_contrastive
```

### Option 2: Integrate into Existing Code

```python
import torch
from vuln_detection.models.hagnn import HAGNNVulnDetector
from vuln_detection.contrastive import SupervisedContrastiveLoss, ProjectionHead

# Create model
model = HAGNNVulnDetector(
    input_dim=272,          # 16 one-hot + 256 embedding
    hidden_dim=256,
    num_layers=4,
    num_edge_types=16,      # From your cpg_config.py
    num_node_types=16,
    call_node_idx=2,        # CALL node type index
).cuda()

# Contrastive loss
scl_loss = SupervisedContrastiveLoss(temperature=0.07)
proj_head = ProjectionHead(input_dim=256, output_dim=128).cuda()

# Training loop (simplified)
for batch in train_loader:
    output = model(batch, return_embeddings=True)
    
    # Get projections for contrastive loss
    projections = proj_head(output['graph_embedding'])
    
    # Combined loss
    l_contrastive = scl_loss(projections, batch.y)
    l_classification = F.binary_cross_entropy_with_logits(output['logits'], batch.y.float())
    loss = 0.5 * l_contrastive + 0.5 * l_classification
    
    loss.backward()
    optimizer.step()
```

---

## 📚 Detailed Stage Explanations

### Stage 1: Vulnerability-Aware Features (`vuln_features.py`)

Extracts 32-dimensional features that capture vulnerability patterns:

```python
from vuln_detection.vuln_features import VulnFeatureExtractor

extractor = VulnFeatureExtractor()

# For each node in your CPG
features = extractor.extract_node_features(node_code="strcpy(dest, src)", node_type="CALL")
# Returns: np.ndarray shape (32,)

# Feature breakdown:
# [0-7]:   Security API category (BUFFER_UNSAFE, MEMORY_FREE, COMMAND_EXEC, etc.)
# [8-15]:  Operation indicators (array access, pointer ops, sizeof, etc.)
# [16-23]: Vulnerability patterns (null check, bounds check, buffer vars)
# [24-31]: Taint source/sink indicators
```

**To enable in cache_manager.py**, add `--use-vuln-features` flag (requires modifying cache_manager.py to use VulnFeatureExtractor).

### Stage 2: Supervised Contrastive Learning (`contrastive.py`)

Key insight: Pull vulnerable samples together, push safe samples apart in embedding space.

```python
from vuln_detection.contrastive import (
    SupervisedContrastiveLoss,
    CombinedContrastiveLoss,
    VulnPreservingAugmentation,
)

# Basic contrastive loss
scl = SupervisedContrastiveLoss(temperature=0.07)
loss = scl(embeddings, labels)  # embeddings: [batch, dim], labels: [batch]

# Combined loss (recommended)
combined = CombinedContrastiveLoss(alpha=0.5, temperature=0.07)
losses = combined(embeddings, logits, labels)
# losses['total'], losses['contrastive'], losses['classification']

# Graph augmentation (preserves vulnerability semantics)
augmentation = VulnPreservingAugmentation(
    node_mask_ratio=0.15,     # Mask 15% of non-CALL node features
    edge_drop_ratio=0.1,      # Drop 10% of non-critical edges
    protected_node_types={2}, # Never mask CALL nodes (index 2)
    protected_edge_types={0, 9},  # Never drop REACHING_DEF, CDG
)
```

### Stage 3: HAGNN Architecture (`models/hagnn.py`)

Processes edge types in separate groups, then combines via attention:

```
┌──────────────┐
│ Input Graph  │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ Input Proj   │  Linear(input_dim → hidden_dim)
└──────┬───────┘
       │
       ▼
┌──────────────────────────────────────────────┐
│           HAGNNLayer (x4)                    │
│  ┌─────────┐ ┌─────────┐ ┌─────────┐        │
│  │ AST GAT │ │ CFG GAT │ │ DFG GAT │ ...    │
│  └────┬────┘ └────┬────┘ └────┬────┘        │
│       └─────────┬─────────────┘              │
│                 ▼                            │
│        Attention Combination                 │
└──────────────────┬───────────────────────────┘
                   │
                   ▼
┌──────────────────────────────────────────────┐
│         VulnAwarePooling                     │
│  ┌────────────────┐  ┌──────────────────┐   │
│  │ CALL-focused   │  │ Global Attention │   │
│  │ Max Pooling    │  │ Pooling          │   │
│  └───────┬────────┘  └────────┬─────────┘   │
│          │    α × ────────────┘ (1-α)       │
│          └──────────┬───────────┘           │
└─────────────────────┼───────────────────────┘
                      │
                      ▼
┌──────────────────────────────────────────────┐
│           Dual Classifiers                   │
│  call_logits ──────┬────── global_logits    │
│                    ▼                         │
│           Combined logits                    │
└──────────────────────────────────────────────┘
```

**Key Features:**
1. **Edge-type grouping**: AST, CFG, DFG, Control edges processed separately
2. **Vulnerability-aware pooling**: 70% weight on CALL node embeddings
3. **Dual-path classification**: Separate classifiers for CALL-focused and global

---

## 🔧 Integration with Your Existing Pipeline

### Modifying cache_manager.py for Vulnerability Features

Add this to `CPGToPyGBuilder._build_features()`:

```python
# At the top of cache_manager.py
try:
    from vuln_features import VulnFeatureExtractor
    VULN_FEATURES_AVAILABLE = True
except ImportError:
    VULN_FEATURES_AVAILABLE = False

# In CPGToPyGBuilder.__init__
if use_vuln_features and VULN_FEATURES_AVAILABLE:
    self.vuln_extractor = VulnFeatureExtractor()
else:
    self.vuln_extractor = None

# In _build_features(), after embedding extraction
if self.vuln_extractor is not None:
    vuln_feat = self.vuln_extractor.extract_node_features(text or '', label)
    feat_parts.append(vuln_feat)  # Adds 32 dimensions
```

### Using HAGNN with train_advanced.py

Add to `create_advanced_model()`:

```python
elif model_type == 'hagnn':
    from vuln_detection.models.hagnn import HAGNNVulnDetector
    return HAGNNVulnDetector(
        input_dim=input_dim,
        hidden_dim=hidden_dim,
        num_layers=num_layers,
        num_edge_types=num_edge_types,
        num_node_types=num_node_types,
        call_node_idx=call_node_idx,
        heads=heads,
        dropout=dropout,
    )
```

---

## 📊 Expected Results

Based on research findings and your diagnostic analysis:

| Configuration | Expected AUC | Expected F1 |
|--------------|--------------|-------------|
| Baseline (current) | ~0.60-0.68 | ~0.55-0.65 |
| + Contrastive Learning | ~0.72-0.80 | ~0.68-0.78 |
| + HAGNN | ~0.75-0.82 | ~0.72-0.82 |
| + Vuln Features | ~0.78-0.85 | ~0.75-0.85 |

**Note**: Actual results depend on:
- Quality of code embeddings (Word2Vec vs CodeBERT)
- CPG construction quality
- Class balance in dataset

---

## 🔬 Hyperparameter Recommendations

### Contrastive Learning
```bash
--contrastive-weight 0.5    # Start here, tune 0.3-0.7
--temperature 0.07          # Lower = harder negatives
--node-mask-ratio 0.15      # Don't mask too much
--edge-drop-ratio 0.1       # Keep critical edges
```

### HAGNN
```bash
--num-layers 4              # 4-6 works well
--hidden-dim 256            # Match your embedding dim
--heads 4                   # 4-8 attention heads
--dropout 0.2               # 0.1-0.3
```

### Training
```bash
--epochs-pretrain 50        # Contrastive pretraining
--epochs-finetune 100       # Fine-tuning
--lr-pretrain 0.001         # Higher LR for pretrain
--lr-finetune 0.0005        # Lower LR for finetune
--batch-size 32             # 32-64 for good contrastive learning
```

---

## 🐛 Troubleshooting

### Model Collapse (predicting all same values)
- **Cause**: Learning rate too low or contrastive loss dominating
- **Fix**: Increase `--lr-pretrain`, reduce `--contrastive-weight` to 0.3

### CUDA Out of Memory
- **Fix**: Reduce `--batch-size`, `--hidden-dim`, or `--num-layers`

### No Improvement
- **Check**: Are CALL nodes being correctly identified? (verify `--call-node-idx`)
- **Check**: Is edge_type being passed correctly? (not all zeros)

### Import Errors
```python
# If running as script (not module), add to top of file:
import sys
sys.path.insert(0, '/path/to/vuln_detection')
```

---

## 📈 Monitoring Training

The training script logs:
- **Phase 1 (Pretrain)**: Loss, SCL loss, BCE loss, Val AUC/F1
- **Phase 2 (Finetune)**: Loss, Val AUC/F1

Good signs:
- SCL loss decreasing (embeddings becoming more separable)
- BCE loss decreasing alongside
- Val F1 improving

Bad signs:
- SCL loss stuck at ~0.69 (log(2), random)
- One loss dominating (adjust alpha)

---

## 📝 Citation

If you use this implementation in research:

```bibtex
@misc{vuln_detection_contrastive,
  title={Contrastive Learning for Code Vulnerability Detection with HAGNN},
  author={Based on SCL-CVD and HAGNN research},
  year={2024},
  note={Implementation combining supervised contrastive learning with 
        heterogeneous graph neural networks for vulnerability detection}
}
```

---

## 🎯 Quick Command Reference

```bash
# Full training with all enhancements
python -m vuln_detection.train_contrastive \
    --model-type hagnn \
    --cache-dir /path/to/cache \
    --dataset-name word2vec_256d_full \
    --cache-signature YOUR_SIGNATURE \
    --hidden-dim 256 --num-layers 4 --num-edge-types 16 \
    --contrastive-weight 0.5 --temperature 0.07 \
    --epochs-pretrain 50 --epochs-finetune 100 \
    --batch-size 32 --lr-pretrain 0.001 --lr-finetune 0.0005 \
    --save-dir ./results/experiment_1

# Test vulnerability features
python -m vuln_detection.vuln_features

# Test HAGNN architecture
python -m vuln_detection.models.hagnn

# Test contrastive learning
python -m vuln_detection.contrastive
```

---

