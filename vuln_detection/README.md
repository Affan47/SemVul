# Vulnerability Detection with GNNs

A modular, production-ready library for vulnerability detection in code using Graph Neural Networks.

##  Current Results vs Baselines

| Method | ACC | F1 | AUC |
|--------|-----|-----|-----|
| **Devign (paper)** | **72.26%** | **73.26%** | - |
| ReVeal | 65% | 48% | 63% |
| IVDetect | 68% | 52% | 65% |


*At threshold 0.50 for fair comparison



##  Complete Package Structure

```
vuln_detection/                        # 412KB total
├── README.md                          # This file
├── __init__.py                        # Main exports
├── train.py                           # Training script
├── multi_extractor.py                 # Multi-model embedding extractor
│
├── embeddings/                        # 43KB - Node embedding modules
│   ├── base.py                       # Base class & registry
│   ├── word2vec.py                   # Word2Vec (like Devign paper)
│   ├── codebert.py                   # CodeBERT with compression
│   └── codet5.py                     # CodeT5, UniXcoder
│
├── models/                            # 166KB - Neural network models
│   ├── gnn_layers.py                 # GGNN, EdgeTypeGNN, ShallowGNN
│   ├── layers.py                     # Shared layers (DevignConvHead, etc.)
│   ├── pooling.py                    # All pooling strategies
│   ├── vuln_detector.py              # Main model class
│   └── advanced/                     # 122KB - Research architectures
│       ├── multiview.py              # Multi-view GGNN (AST/CFG/DFG)
│       ├── hgt.py                    # Heterogeneous Graph Transformer
│       ├── hypergraph.py             # Hypergraph Neural Network
│       ├── rgat.py                   # Relational Graph Attention
│       └── devign_original.py        # Complete Devign implementation
│
├── utils/                             # 72KB - Utilities
│   ├── data_loader.py                # Data loading
│   ├── metrics.py                    # Proper evaluation (F1@0.50!)
│   ├── losses.py                     # BCE, Focal, Combined
│   └── diagnostics/                  # 46KB - Debug tools
│       ├── diagnose_data_integrity.py
│       ├── diagnose_gnn_vs_mlp.py
│       ├── analyze_feature_parts.py
│       └── verify_labels.py
│
└── examples/                          # 78KB - Experiment scripts
    ├── graph_level_classifier.py     # Best result (0.632 AUC)
    ├── mlp_baseline.py               # Simple MLP baseline
    ├── feature_selection_model.py    # Feature selection experiments
    ├── improved_baseline.py          # Edge-type aware baseline
    └── learned_embedding_model.py    # Alternative to GraphCodeBERT
```

##  Quick Start

### Installation

```bash
# Unzip the package
unzip vuln_detection.zip

# Install dependencies
pip install torch torch_geometric transformers scikit-learn tqdm
```

### Training

```bash
# Best performing model (Graph-level MLP)
python -m vuln_detection.train \
    --cache-dir /path/to/cache \
    --dataset-name devign_normfunc_v2 \
    --cache-signature caffd6ae8652870d \
    --model-type graph_level_mlp \
    --epochs 100

# Original Devign architecture
python -m vuln_detection.train \
    --cache-dir /path/to/cache \
    --dataset-name devign_normfunc_v2 \
    --cache-signature caffd6ae8652870d \
    --model-type devign \
    --epochs 100

# Custom configuration
python -m vuln_detection.train \
    --cache-dir /path/to/cache \
    --dataset-name devign_normfunc_v2 \
    --cache-signature caffd6ae8652870d \
    --model-type custom \
    --embedder-type codebert_hybrid \
    --gnn-type edge_type \
    --gnn-layers 1 \
    --pooling-type combined \
    --hidden-dim 128 \
    --epochs 100
```

### Python API

```python
from vuln_detection import (
    create_model, 
    load_dataset,
    create_data_loaders,
    compute_full_evaluation,
    print_metrics,
)
from vuln_detection.embeddings import list_embedders

# List available embedders
print(list_embedders())
# ['word2vec', 'learned', 'codebert', 'graphcodebert', 
#  'codebert_selective', 'codebert_hybrid', 'codet5', 
#  'unixcoder', 'multi_embedder']

# Create model
model = create_model("graph_level_mlp")

# Load data
train, val, test = load_dataset(
    cache_dir="path/to/cache",
    dataset_name="devign_normfunc_v2",
    cache_signature="caffd6ae8652870d",
)

# Create loaders
train_loader, val_loader, test_loader = create_data_loaders(
    train, val, test, batch_size=32
)
```

##  Available Embedders

| Embedder | Description | Recommended For |
|----------|-------------|-----------------|
| `word2vec` | Word2Vec on code tokens | Original Devign reproduction |
| `learned` | Learned from scratch | When GraphCodeBERT doesn't work |
| `codebert` | CodeBERT with compression | General use |
| `codebert_hybrid` | Compressed CodeBERT + structural | **Best results** |
| `codebert_selective` | Feature selection | When signal is weak |
| `codet5` | CodeT5/CodeT5+ | Better code understanding |
| `unixcoder` | UniXcoder | Multi-modal |

##  Available Models

### DevignModel
Original Devign architecture: GGNN + Conv readout
```python
model = create_model("devign")
```

### GraphLevelMLP
Best performing: No GNN + multi-stat pooling
```python
model = create_model("graph_level_mlp")
```

### AttentionVulnDetector
Attention-based pooling
```python
model = create_model("attention")
```

### Custom
Full control over architecture
```python
from vuln_detection import VulnDetector

model = VulnDetector(
    embedder_type="codebert_hybrid",
    gnn_type="edge_type",
    gnn_layers=1,
    pooling_type="combined",
    hidden_dim=128,
    dropout=0.2,
)
```

##  Evaluation

The package provides proper evaluation with:
- **AUC-ROC** (threshold-independent)
- **F1 at threshold 0.50** (fair comparison with baselines)
- **Best F1** (any threshold)
- **Class separation** analysis

```python
from vuln_detection import compute_full_evaluation, print_metrics

metrics = compute_full_evaluation(probs, labels)
print_metrics(metrics)
```

##  Configuration Options

### Embedder Types
- `word2vec`: Word2Vec embeddings (train your own or load pretrained)
- `learned`: Learned embeddings from node types + structure
- `codebert`: GraphCodeBERT with linear compression
- `codebert_hybrid`: Compressed GraphCodeBERT + learned components
- `codebert_selective`: Feature selection (top-K dimensions)

### GNN Types
- `none`: No GNN (recommended when signal is weak)
- `ggnn`: Gated Graph Neural Network (original Devign)
- `edge_type`: Edge-type aware message passing
- `gcn`: Standard GCN
- `gat`: Graph Attention Network

### Pooling Types
- `mean`: Simple mean pooling
- `max`: Simple max pooling
- `mean_max`: Concatenate mean and max
- `multi_stat`: Mean + max + std (recommended)
- `attention`: Attention-based pooling
- `combined`: Attention + mean + max
- `devign`: Original Devign Conv1D readout

### Loss Functions
- `bce`: Binary Cross Entropy
- `focal`: Focal Loss (handles imbalance)
- `combined`: BCE + Focal (recommended)

```python
model = create_model("devign", gnn_steps=4, use_word2vec=True)
```

### To Maximize AUC

1. Use compressed GraphCodeBERT (768 → 64 dims)
2. Skip GNN (it destroys the signal)
3. Use multi-stat pooling (mean + max + std)

```python
model = create_model("graph_level_mlp")
```

### For Attention Analysis

1. Use attention pooling
2. Extract attention weights for interpretability

```python
model = create_model("attention", use_gnn=False)
logits, attn_weights = model(data, return_embeddings=True)
```

##  References

- [Devign Paper](https://arxiv.org/abs/1909.03496)
- [ReVeal Paper](https://arxiv.org/abs/2009.07235)
- [IVDetect Paper](https://arxiv.org/abs/2102.00298)
- [LineVul Paper](https://arxiv.org/abs/2104.10350)


## 📝 License

MIT License
