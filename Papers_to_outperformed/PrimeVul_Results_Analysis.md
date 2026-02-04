# PrimeVul Paper: Detailed Results Analysis

**Paper Title:** Vulnerability Detection with Code Language Models: How Far Are We?

**Authors:** Yangruibo Ding et al. (Columbia University, UC Berkeley, Google DeepMind, University of Maryland)

**Key Contribution:** PrimeVul - a new high-quality vulnerability detection dataset with rigorous labeling and evaluation metrics.

---

## Table of Contents
1. [Dataset Statistics](#1-dataset-statistics)
2. [Label Accuracy Comparison](#2-label-accuracy-comparison)
3. [Data Duplication Analysis](#3-data-duplication-analysis)
4. [Code LM Performance (Table V)](#4-code-lm-performance-table-v)
5. [Class Weights Impact (Table VI)](#5-class-weights-impact-table-vi)
6. [Contrastive Learning Impact (Table VII)](#6-contrastive-learning-impact-table-vii)
7. [GPT Models on Paired Functions (Table VIII)](#7-gpt-models-on-paired-functions-table-viii)
8. [Key Takeaways](#8-key-takeaways)

---

## 1. Dataset Statistics

### PrimeVul Composition (Table III)

| Split | Vulnerable | Benign | Paired Vuln | Paired Benign |
|-------|------------|--------|-------------|---------------|
| Train | 5,574 | 178,853 | 4,354 | 4,354 |
| Dev | 699 | 24,731 | 562 | 562 |
| Test | 695 | 25,216 | 564 | 564 |
| **Total** | **6,968** | **228,800** | **5,480** | **5,480** |

**Key Facts:**
- Covers **140 CWEs** across **755 projects** and **6,827 commits**
- 16.7× more vulnerable C/C++ functions than SVEN (the previous best-quality dataset)
- Vulnerable:Benign ratio is approximately **1:32**

---

## 2. Label Accuracy Comparison

### Comparison with Existing Benchmarks (Table I)

| Benchmark | Manual Labeling | Correct (%) | Notes |
|-----------|-----------------|-------------|-------|
| SVEN | ✓ | **94.0** | Gold standard but only 1.6k samples |
| CodeXGLUE (Devign) | ✓ | 24.0 | Surprisingly low despite manual effort |
| VulnPatchPairs | ✓† | 36.0 | Derived from CodeXGLUE |
| BigVul | ✗ | 25.0 | Most widely used but very noisy |
| CrossVul | ✗ | 47.8 | Automated labeling |
| CVEFixes | ✗ | 51.7 | Automated labeling |
| DiverseVul | ✗ | 60.0 | Best automated before PrimeVul |
| **PRIMEVUL-ONEFUNC** | ✗ | **86.0** | Only single-function commits |
| **PRIMEVUL-NVDCHECK** | ✗ | **92.0** | NVD description verification |

**Key Insight:** PrimeVul achieves manual-labeling quality (86-92%) with automated methods!

---

## 3. Data Duplication Analysis

### Train-Test Leakage (Table II)

| Benchmark | De-duplicated | Copy Rate (%) |
|-----------|---------------|---------------|
| BigVul | ✗ | 12.7 |
| CVEFixes | ✗ | **18.9** |
| CodeXGLUE | ✗ | 0.6 |
| DiverseVul | ✓ | 3.3 |
| **PRIMEVUL** | ✓ | **0.0** |

**Why This Matters:** Up to 18.9% of test samples in existing benchmarks are exact copies from the training set, artificially inflating performance metrics.

---

## 4. Code LM Performance (Table V)

### Understanding the Metrics

| Metric | Full Name | What it Measures | Good Value |
|--------|-----------|------------------|------------|
| **Acc** | Accuracy | % of all predictions correct | Higher ↑ |
| **F1** | F1 Score | Harmonic mean of precision & recall | Higher ↑ |
| **VD-S** | Vulnerability Detection Score | False Negative Rate @ FPR ≤ 0.5% | **Lower ↓** |
| **P-C** | Pair-wise Correct | Both vuln & fixed versions correctly labeled | Higher ↑ |
| **P-V** | Pair-wise Vulnerable | Both versions wrongly labeled as vulnerable | Lower ↓ |
| **P-B** | Pair-wise Benign | Both versions wrongly labeled as benign | Lower ↓ |
| **P-R** | Pair-wise Reversed | Labels are swapped | Lower ↓ |

### Why VD-S is Critical

Traditional metrics are **misleading** for vulnerability detection:
- Code is ~97% non-vulnerable
- Predicting "not vulnerable" always gives 97% accuracy!
- **VD-S asks:** "If we limit false alarms to 0.5%, how many real vulnerabilities do we miss?"
- A VD-S of 90% means **90% of real vulnerabilities are missed** - catastrophic for security!

### Full Results Table

| Model | Train | Test | Acc | F1 | VD-S↓ | P-C↑ | P-V | P-B | P-R |
|-------|-------|------|------|-------|-------|------|------|------|-----|
| **CodeT5** | BV | BV | 95.67 | 64.93 | 77.30 | 24.98 | 50.90 | 22.79 | 1.33 |
| | BV | PV | 97.00 | **5.82** | 95.97 | 0.18 | 3.01 | 96.10 | 0.71 |
| | PV | PV | 96.67 | 19.70 | 89.93 | 1.06 | 12.94 | 84.75 | 1.24 |
| **CodeBERT** | BV | BV | 95.57 | 62.88 | 81.77 | 22.60 | 48.34 | 27.83 | 1.23 |
| | BV | PV | 97.04 | **4.49** | 95.54 | 0.35 | 1.95 | 96.99 | 0.71 |
| | PV | PV | 96.87 | 20.86 | 88.78 | 1.77 | 11.35 | 86.17 | 0.71 |
| **UnixCoder** | BV | BV | 96.46 | 65.46 | 62.30 | 39.60 | 23.74 | 33.24 | 3.42 |
| | BV | PV | 97.27 | **1.94** | 95.11 | 0.35 | 0.35 | 98.76 | 0.53 |
| | PV | PV | 96.86 | 21.43 | 89.21 | 1.60 | 12.06 | 85.11 | 1.24 |
| **StarCoder2 (7B)** | BV | BV | 96.20 | **68.26** | 69.14 | 35.23 | 41.98 | 20.61 | 2.18 |
| | BV | PV | 97.09 | **3.09** | 96.83 | 0.89 | 0.89 | 97.70 | 0.53 |
| | PV | PV | 97.02 | 18.05 | 89.64 | 2.30 | 8.16 | 88.30 | 1.24 |
| **CodeGen2.5 (7B)** | BV | BV | 96.57 | 67.30 | 61.73 | 40.84 | 26.02 | 29.63 | 3.51 |
| | BV | PV | 97.23 | **1.91** | 95.68 | 1.24 | 0.00 | 98.76 | 0.00 |
| | PV | PV | 96.65 | 19.61 | 91.51 | 3.01 | 10.82 | 84.22 | 1.95 |

**BV** = BigVul, **PV** = PrimeVul

### Key Findings

#### Finding 1: The Illusion of Good Performance
```
StarCoder2 on BigVul:   F1 = 68.26%  ← Looks great!
StarCoder2 on PrimeVul: F1 = 3.09%   ← Reality check (65 point drop!)
```

#### Finding 2: VD-S Reveals True Performance
```
CodeBERT on BigVul:
- Accuracy: 95.57% ← Seems acceptable
- F1: 62.88%       ← Seems acceptable
- VD-S: 81.77%     ← MISSES 82% OF VULNERABILITIES!
```

#### Finding 3: Models Can't Distinguish Vulnerable from Fixed Code
```
StarCoder2 on PrimeVul (Trained on PV):
- P-C = 2.30%   → Only 2.3% of pairs correctly classified
- P-B = 88.30%  → 88% of time says BOTH are safe (can't distinguish!)
```

### Understanding Pair-wise Metrics

These metrics evaluate **paired functions** (vulnerable code + its fixed version):

```
Vulnerable Function          Fixed Function
┌─────────────────┐         ┌─────────────────┐
│ char buf[10];   │         │ char buf[100];  │  ← Only difference
│ strcpy(buf, s); │         │ strcpy(buf, s); │
└─────────────────┘         └─────────────────┘
     Should be: 1                Should be: 0

P-C: Model says (1, 0) ✓     - Correctly identifies both
P-V: Model says (1, 1) ✗     - Thinks both are vulnerable
P-B: Model says (0, 0) ✗     - Thinks both are safe (DANGEROUS!)
P-R: Model says (0, 1) ✗     - Completely reversed understanding
```

---

## 5. Class Weights Impact (Table VI)

### The Problem
PrimeVul has ~1:32 ratio of vulnerable to benign samples. The model sees 32× more "benign" examples, so it learns to always predict "benign."

### The Solution Attempted
Increase the penalty (weight) for misclassifying vulnerable samples:

```
Standard Loss:     L = -[y·log(ŷ) + (1-y)·log(1-ŷ)]
Weighted Loss:     L = -[w·y·log(ŷ) + (1-y)·log(1-ŷ)]
                        ↑
                   Weight for vulnerable class
```

### Results (UnixCoder on PrimeVul)

| Weight | Acc | F1 | VD-S↓ | P-C | P-V | P-B | Interpretation |
|--------|------|-------|-------|------|-------|-------|----------------|
| 1 (baseline) | 96.86 | 21.43 | 89.21 | 1.60 | 12.06 | 85.11 | Predicts mostly benign |
| 5 | 96.24 | 25.29 | 90.65 | 1.77 | 18.97 | 78.55 | Slightly more "vulnerable" predictions |
| 20 | 95.28 | 24.26 | 88.92 | 0.89 | 25.71 | 72.16 | More aggressive but less accurate |
| 30 | 96.14 | 24.49 | 90.07 | 2.13 | 18.09 | 78.01 | No consistent improvement |
| 40 | 95.99 | 26.28 | 88.49 | 1.42 | 22.52 | 74.82 | Best F1 but VD-S still ~88% |

### Analysis

```
Weight=1:  Model predicts "benign" 85% of the time for pairs
           ↓
Weight=40: Model predicts "benign" 75% of the time for pairs

But VD-S stays around 88-90% → Still missing ~90% of vulnerabilities!
```

### Conclusion
Class weights provide **marginal F1 improvement** (+5 points) but **fundamentally don't solve the problem**. The model still can't learn what makes code vulnerable.

---

## 6. Contrastive Learning Impact (Table VII)

### The Idea
Contrastive learning helps models learn better representations by:
1. **Pulling together** similar samples (same class)
2. **Pushing apart** different samples (different classes)

```
Representation Space:

Before Contrastive:     After Contrastive:
    🔴 🔵 🔴              🔴🔴🔴
  🔵 🔴 🔵 🔴     →
    🔴 🔵 🔴              🔵🔵🔵
  (Mixed)             (Separated)
```

### Two Approaches Tested

1. **CLR (Contrastive Learning of Representations)**
   - Maximize similarity between a sample and its perturbed version
   - Minimize similarity between random pairs

2. **CA-CLR (Class-Aware CLR)**
   - Only push apart samples with **different labels**
   - More aligned with classification task

### Results (UnixCoder on PrimeVul)

| Method | Acc | F1 | VD-S↓ | P-C | P-V | P-B | P-R |
|--------|------|-------|-------|------|-------|-------|------|
| CLS (baseline) | 96.86 | 21.43 | 89.21 | 1.60 | 12.06 | 85.11 | 1.24 |
| + CLR | 96.83 | 21.73 | 90.07 | 1.77 | 11.35 | 85.82 | 1.06 |
| + CA-CLR | 96.64 | 24.46 | 90.50 | 2.30 | 15.96 | 81.38 | 0.35 |

### Analysis

```
Improvement from CA-CLR:
- F1: 21.43 → 24.46 (+3 points) - marginal
- P-C: 1.60 → 2.30 (+0.7 points) - tiny improvement
- VD-S: 89.21 → 90.50 (got WORSE!) - still missing 90% of vulnerabilities
```

### Key Insight
Even with better-separated representations, the model still fails to identify vulnerability patterns. This suggests the problem is **not just about representation quality** but about the model's fundamental inability to understand security semantics.

---

## 7. GPT Models on Paired Functions (Table VIII)

### The Hope
Maybe larger models (GPT-3.5, GPT-4) with massive pre-training can do better?

### Evaluation Setup
Only evaluated on **paired functions** (564 pairs) - the hardest test:
- Can the model distinguish vulnerable code from its fixed version?

### Methods Tested
1. **Two-shot**: Show 2 examples (1 vuln, 1 benign), then ask about new code
2. **Chain-of-Thought (CoT)**: Ask model to "think step-by-step"
3. **Fine-tune**: Train GPT-3.5 on PrimeVul subset

### Results

| Model | Method | P-C↑ | P-V | P-B | P-R | Behavior |
|-------|--------|------|------|------|------|----------|
| GPT-3.5 | Two-shot | 5.67 | 13.83 | **77.84** | 2.66 | Mostly says "benign" |
| GPT-3.5 | CoT | 6.21 | 4.79 | **83.51** | 5.50 | Even more "benign" bias |
| GPT-3.5 | Fine-tune | 1.24 | 5.32 | **90.96** | 2.48 | Worst! Always says "benign" |
| GPT-4 | Two-shot | 5.14 | **71.63** | 21.45 | 1.77 | Opposite: mostly says "vulnerable" |
| GPT-4 | CoT | 12.94 | **54.26** | 24.47 | 8.33 | Best but still poor |
| **Random Guess** | - | **22.70** | 26.24 | 26.42 | 24.65 | Baseline for comparison |

### The Shocking Finding

```
Random Guessing P-C: 22.70%
GPT-4 + CoT P-C:     12.94%  ← WORSE than random!
GPT-3.5 Fine-tune:    1.24%  ← Much worse than random!
```

### Analysis

#### GPT-3.5 Behavior: Heavy "Benign" Bias
- P-B = 77-91% → Thinks almost everything is safe
- Fine-tuning made it **WORSE** (learned the class imbalance)

#### GPT-4 Behavior: Heavy "Vulnerable" Bias
- P-V = 54-72% → Thinks almost everything is vulnerable
- Opposite problem but equally useless

#### Neither Model Can Distinguish
```
What we want:           What GPT-3.5 does:       What GPT-4 does:
┌─────┬─────┐          ┌─────┬─────┐           ┌─────┬─────┐
│Vuln │Fixed│          │Vuln │Fixed│           │Vuln │Fixed│
├─────┼─────┤          ├─────┼─────┤           ├─────┼─────┤
│  1  │  0  │          │  0  │  0  │           │  1  │  1  │
└─────┴─────┘          └─────┴─────┘           └─────┴─────┘
   Correct!            Both "safe" (P-B)      Both "vuln" (P-V)
```

---

## 8. Key Takeaways

### 1. Existing Benchmarks Massively Overestimate Performance
- StarCoder2: 68% F1 on BigVul → **3% F1** on PrimeVul
- This is a **65 percentage point drop**!

### 2. High Accuracy is Meaningless
- 97% accuracy but missing **90%+ of real vulnerabilities**
- VD-S is the metric that matters for real-world deployment

### 3. Advanced Techniques Don't Help
| Technique | Improvement | Still Useful? |
|-----------|-------------|---------------|
| Class Weights | +5 F1 points | No - VD-S still ~90% |
| Contrastive Learning | +3 F1 points | No - VD-S still ~90% |
| Larger Models (GPT-4) | None | No - worse than random! |

### 4. Fundamental Problem
Code LMs rely on **textual patterns**, not **security understanding**:
- They can't distinguish `buf[10]` (vulnerable) from `buf[100]` (safe)
- They don't understand security concepts like buffer sizes, bounds checking, etc.
- They pattern-match rather than reason about code semantics

### 5. Implications for Research
The paper concludes that **fundamentally new approaches** are needed:
- More context (inter-procedural analysis)
- Security-aware pre-training
- Hybrid systems combining LMs with program analysis tools
- Teaching models to reason about vulnerability semantics

---

## Citation

```bibtex
@article{ding2024primevul,
  title={Vulnerability Detection with Code Language Models: How Far Are We?},
  author={Ding, Yangruibo and Fu, Yanjun and Ibrahim, Omniyyah and Sitawarin, Chawin and Chen, Xinyun and Alomair, Basel and Wagner, David and Ray, Baishakhi and Chen, Yizheng},
  journal={arXiv preprint arXiv:2403.18624},
  year={2024}
}
```

---

*Document generated for SemVul project baseline comparison*
*Last updated: January 2025*
