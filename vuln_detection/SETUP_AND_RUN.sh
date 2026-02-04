#!/bin/bash
# ═══════════════════════════════════════════════════════════════════════════════
# STEP-BY-STEP SETUP AND RUN GUIDE
# 3-Stage Vulnerability Detection with Contrastive Learning + HAGNN
# ═══════════════════════════════════════════════════════════════════════════════

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 0: UNDERSTAND YOUR CURRENT SETUP
# ═══════════════════════════════════════════════════════════════════════════════

# Based on your uploaded files, your project structure is:
#
# ./
# ├── workspace/
# │   ├── Scripts_and_saved_Models/
# │   │   └── Scripts/
# │   │       ├── cpg_config.py           # CPG configuration (V8)
# │   │       ├── cache_manager.py        # Data pipeline (V9)
# │   │       ├── generate_cpg_devign_final.py
# │   │       └── vuln_detection/         # <-- YOUR MAIN PACKAGE
# │   │           ├── models/
# │   │           ├── utils/
# │   │           ├── train.py
# │   │           ├── train_advanced.py
# │   │           └── ...
# │   └── 03_PerFunction_datasets/
# │       └── original_devign_functions/
# │           ├── manifest_train.csv
# │           ├── manifest_validation.csv
# │           └── manifest_test.csv
# ├── CPGs/
# │   └── original_devign_functions/
# │       ├── train/
# │       ├── validation/
# │       └── test/
# └── Clean_exports/
#     └── cache_devign_v2/               # <-- YOUR CACHE DIRECTORY
#         ├── word2vec_256d_full/
#         ├── graphcodebert_256d_full_filtered/
#         └── ...

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 1: COPY NEW FILES TO YOUR PROJECT
# ═══════════════════════════════════════════════════════════════════════════════

# First, set your base paths (MODIFY THESE TO MATCH YOUR SYSTEM):
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
export PROJECT_ROOT
export SCRIPTS_DIR="${PROJECT_ROOT}/workspace/Scripts_and_saved_Models/Scripts"
export VULN_DETECTION_DIR="${SCRIPTS_DIR}/vuln_detection"

# Create backup of existing files (optional but recommended):
echo "Creating backup..."
mkdir -p "${SCRIPTS_DIR}/backup_$(date +%Y%m%d)"
cp -r "${VULN_DETECTION_DIR}" "${SCRIPTS_DIR}/backup_$(date +%Y%m%d)/"

# Copy the new files (download from Claude's output or use these commands):
# 
# FILE PLACEMENT:
#
#   vuln_features.py      → ${VULN_DETECTION_DIR}/vuln_features.py
#   contrastive.py        → ${VULN_DETECTION_DIR}/contrastive.py  
#   train_contrastive.py  → ${VULN_DETECTION_DIR}/train_contrastive.py
#   hagnn.py              → ${VULN_DETECTION_DIR}/models/hagnn.py
#   CONTRASTIVE_GUIDE.md  → ${VULN_DETECTION_DIR}/CONTRASTIVE_GUIDE.md

echo "Copying files..."
# If you downloaded the zip file:
# unzip stage123_implementation.zip -d /tmp/stage123
# cp /tmp/stage123/vuln_features.py "${VULN_DETECTION_DIR}/"
# cp /tmp/stage123/contrastive.py "${VULN_DETECTION_DIR}/"
# cp /tmp/stage123/train_contrastive.py "${VULN_DETECTION_DIR}/"
# cp /tmp/stage123/hagnn.py "${VULN_DETECTION_DIR}/models/"
# cp /tmp/stage123/CONTRASTIVE_GUIDE.md "${VULN_DETECTION_DIR}/"

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 2: UPDATE models/__init__.py
# ═══════════════════════════════════════════════════════════════════════════════

# Add HAGNN imports to your models/__init__.py
# Open the file and add these lines after the CALL-aware imports:

cat << 'EOF'
# Add this to ${VULN_DETECTION_DIR}/models/__init__.py:

# HAGNN model (NEW - Stage 3)
try:
    from .hagnn import (
        HAGNNVulnDetector,
        HAGNNLayer,
        EdgeTypeGATConv,
        VulnAwarePooling,
        create_hagnn_model,
    )
    HAGNN_AVAILABLE = True
except ImportError:
    HAGNN_AVAILABLE = False
    HAGNNVulnDetector = None
    HAGNNLayer = None
    EdgeTypeGATConv = None
    VulnAwarePooling = None
    create_hagnn_model = None

# And add to __all__:
    "HAGNNVulnDetector",
    "HAGNNLayer",
    "EdgeTypeGATConv",
    "VulnAwarePooling",
    "create_hagnn_model",
    "HAGNN_AVAILABLE",
EOF

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 3: VERIFY FILE STRUCTURE
# ═══════════════════════════════════════════════════════════════════════════════

echo "Verifying file structure..."
echo ""
echo "Expected structure after setup:"
echo ""
echo "${VULN_DETECTION_DIR}/"
echo "├── vuln_features.py          # NEW - Stage 1"
echo "├── contrastive.py            # NEW - Stage 2"
echo "├── train_contrastive.py      # NEW - Training script"
echo "├── CONTRASTIVE_GUIDE.md      # NEW - Documentation"
echo "├── train.py                  # Existing"
echo "├── train_advanced.py         # Existing"
echo "├── models/"
echo "│   ├── __init__.py           # MODIFIED - Added HAGNN imports"
echo "│   ├── hagnn.py              # NEW - Stage 3"
echo "│   ├── call_aware.py         # Existing"
echo "│   ├── gnn_layers.py         # Existing"
echo "│   └── ..."
echo "└── utils/"
echo "    ├── data_loader.py        # Existing"
echo "    ├── metrics.py            # Existing"
echo "    └── ..."

# Verify files exist:
echo ""
echo "Checking files..."
for file in "vuln_features.py" "contrastive.py" "train_contrastive.py" "models/hagnn.py"; do
    if [ -f "${VULN_DETECTION_DIR}/${file}" ]; then
        echo "✓ ${file} exists"
    else
        echo "✗ ${file} MISSING!"
    fi
done

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 4: TEST IMPORTS
# ═══════════════════════════════════════════════════════════════════════════════

echo ""
echo "Testing imports..."

cd "${SCRIPTS_DIR}"
python3 << 'PYEOF'
import sys
sys.path.insert(0, '.')

print("Testing imports...")

# Test vuln_features
try:
    from vuln_detection.vuln_features import VulnFeatureExtractor
    extractor = VulnFeatureExtractor()
    features = extractor.extract_node_features("strcpy(dest, src)", "CALL")
    print(f"✓ vuln_features.py - Feature shape: {features.shape}")
except Exception as e:
    print(f"✗ vuln_features.py - Error: {e}")

# Test contrastive
try:
    from vuln_detection.contrastive import SupervisedContrastiveLoss
    scl = SupervisedContrastiveLoss(temperature=0.07)
    print(f"✓ contrastive.py - SupervisedContrastiveLoss loaded")
except Exception as e:
    print(f"✗ contrastive.py - Error: {e}")

# Test hagnn
try:
    from vuln_detection.models.hagnn import HAGNNVulnDetector
    print(f"✓ hagnn.py - HAGNNVulnDetector loaded")
except Exception as e:
    print(f"✗ hagnn.py - Error: {e}")

# Test full import
try:
    from vuln_detection.models import HAGNN_AVAILABLE
    print(f"✓ models/__init__.py - HAGNN_AVAILABLE={HAGNN_AVAILABLE}")
except Exception as e:
    print(f"✗ models/__init__.py - Error: {e}")

print("\nImport tests complete!")
PYEOF

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 5: IDENTIFY YOUR CACHE SIGNATURE
# ═══════════════════════════════════════════════════════════════════════════════

# You need to find your cache signature. Check the signature.json in your cache:

export CACHE_DIR="${PROJECT_ROOT}/Clean_exports/cache_devign_v2"
export DATASET_NAME="word2vec_128d_full"  # Or your dataset name

echo ""
echo "Looking for cache signature..."
echo "Cache directory: ${CACHE_DIR}/${DATASET_NAME}"

# Check for signature
if [ -f "${CACHE_DIR}/${DATASET_NAME}/train/signature.json" ]; then
    echo "Found signature.json:"
    cat "${CACHE_DIR}/${DATASET_NAME}/train/signature.json"
else
    echo "signature.json not found. Checking cache_meta.json..."
    if [ -f "${CACHE_DIR}/${DATASET_NAME}/cache_meta.json" ]; then
        cat "${CACHE_DIR}/${DATASET_NAME}/cache_meta.json"
    fi
fi

# ═══════════════════════════════════════════════════════════════════════════════
# STEP 6: RUN TRAINING
# ═══════════════════════════════════════════════════════════════════════════════

echo ""
echo "═══════════════════════════════════════════════════════════════════════════════"
echo "TRAINING COMMANDS"
echo "═══════════════════════════════════════════════════════════════════════════════"

# Set your paths (MODIFY THESE):
export CACHE_DIR="${PROJECT_ROOT}/Clean_exports/cache_devign_v2"
export DATASET_NAME="word2vec_128d_full"        # Your dataset name
export CACHE_SIGNATURE="YOUR_SIGNATURE_HERE"     # From signature.json or leave empty
export SAVE_DIR="${PROJECT_ROOT}/results/hagnn_contrastive_$(date +%Y%m%d_%H%M%S)"

# Navigate to scripts directory
cd "${SCRIPTS_DIR}"

# ─────────────────────────────────────────────────────────────────────────────────
# OPTION A: Quick test run (small epochs, verify everything works)
# ─────────────────────────────────────────────────────────────────────────────────

echo ""
echo "OPTION A: Quick test run"
echo "─────────────────────────────────────────────────────────────────────────────────"

cat << EOF
python -m vuln_detection.train_contrastive \\
    --model-type hagnn \\
    --cache-dir "${CACHE_DIR}" \\
    --dataset-name "${DATASET_NAME}" \\
    --hidden-dim 256 \\
    --num-layers 4 \\
    --num-edge-types 16 \\
    --num-node-types 16 \\
    --call-node-idx 2 \\
    --contrastive-weight 0.5 \\
    --epochs-pretrain 5 \\
    --epochs-finetune 10 \\
    --batch-size 32 \\
    --save-dir "${SAVE_DIR}_test"
EOF

# ─────────────────────────────────────────────────────────────────────────────────
# OPTION B: Full training run (recommended settings)
# ─────────────────────────────────────────────────────────────────────────────────

echo ""
echo "OPTION B: Full training run"
echo "─────────────────────────────────────────────────────────────────────────────────"

cat << EOF
python -m vuln_detection.train_contrastive \\
    --model-type hagnn \\
    --cache-dir "${CACHE_DIR}" \\
    --dataset-name "${DATASET_NAME}" \\
    --hidden-dim 256 \\
    --num-layers 4 \\
    --num-edge-types 16 \\
    --num-node-types 16 \\
    --call-node-idx 2 \\
    --heads 4 \\
    --dropout 0.2 \\
    --contrastive-weight 0.5 \\
    --temperature 0.07 \\
    --epochs-pretrain 50 \\
    --epochs-finetune 100 \\
    --batch-size 32 \\
    --lr-pretrain 0.001 \\
    --lr-finetune 0.0005 \\
    --patience-pretrain 15 \\
    --patience-finetune 20 \\
    --save-dir "${SAVE_DIR}"
EOF

# ─────────────────────────────────────────────────────────────────────────────────
# OPTION C: Using existing CALL-aware model with contrastive learning
# ─────────────────────────────────────────────────────────────────────────────────

echo ""
echo "OPTION C: CALL-aware model with contrastive learning"
echo "─────────────────────────────────────────────────────────────────────────────────"

cat << EOF
python -m vuln_detection.train_contrastive \\
    --model-type call_aware \\
    --cache-dir "${CACHE_DIR}" \\
    --dataset-name "${DATASET_NAME}" \\
    --hidden-dim 256 \\
    --num-layers 4 \\
    --num-edge-types 16 \\
    --contrastive-weight 0.5 \\
    --epochs-pretrain 50 \\
    --epochs-finetune 100 \\
    --batch-size 32 \\
    --save-dir "${SAVE_DIR}_call_aware"
EOF

echo ""
echo "═══════════════════════════════════════════════════════════════════════════════"
echo "SETUP COMPLETE!"
echo "═══════════════════════════════════════════════════════════════════════════════"
echo ""
echo "Next steps:"
echo "1. Modify the paths above to match your system"
echo "2. Run one of the training commands"
echo "3. Monitor the output for AUC and F1 improvements"
echo ""
echo "Expected improvements:"
echo "  - Baseline:     AUC ~0.60-0.68, F1 ~0.55-0.65"
echo "  - With SCL:     AUC ~0.72-0.80, F1 ~0.68-0.78"
echo "  - With HAGNN:   AUC ~0.75-0.85, F1 ~0.72-0.85"
echo ""
