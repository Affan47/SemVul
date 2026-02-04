# SemVul Paper Revision - Integration Guide

This guide explains how to integrate the revised components into `main.tex`.

## Files Created

| File | Purpose |
|------|---------|
| `introduction_revised.tex` | Restructured introduction with prior work analysis |
| `methodology_streamlined.tex` | Focused methodology (representation approach) |
| `data_preprocessing.tex` | Data pipeline details (for Experimental Setup) |
| `figures.tex` | TikZ figures for architecture and code-to-graph |

## Integration Steps

### Step 1: Update Preamble

Add TikZ packages to the document preamble in `main.tex`:

```latex
% Add after existing package declarations
\usepackage{tikz}
\usetikzlibrary{shapes,arrows,positioning,fit,backgrounds,calc}
```

### Step 2: Replace Introduction

Replace the current introduction (lines 26-95 in `main.tex`) with the content from `introduction_revised.tex`.

The revised introduction:
- Summarizes prior work achievements and shortcomings
- Structures discussion by paradigm (token-based, graph-based, LLM-based)
- References the PrimeVul benchmark findings
- Explains our approach with references to figures
- Lists clear contributions

### Step 3: Add Figures

Insert the figures after the introduction. Add this line where you want the figures:

```latex
\input{figures.tex}
```

This adds:
- **Figure 1**: System architecture overview
- **Figure 2**: Code-to-graph transformation example (buffer overflow)
- **Figure 3**: GNN message passing intuition
- **Figure 4**: Approach comparison diagram

### Step 4: Replace Methodology Section

Replace the current methodology section (lines 96-1183) with the content from `methodology_streamlined.tex`.

Key changes:
- Problem formulation (kept, condensed)
- CPG representation (kept, with figure reference)
- Semantic-enhanced node representation (NEW focus)
- GNN architectures (kept, with intuition)
- Pooling and classification (kept, condensed)
- **REMOVED**: All data pipeline details (moved to Experimental Setup)

### Step 5: Add Data Preprocessing to Experimental Setup

In the Experimental Setup section (currently lines 1189+), add the content from `data_preprocessing.tex` as a new subsection.

Place it after `\subsection{Datasets}` to flow naturally:
1. Datasets (what data we use)
2. Data Preprocessing Pipeline (how we prepare it)
3. Model Configurations (what models we train)
4. Training Hyperparameters (how we train)

## Resulting Structure

```
1. Introduction
   1.1 Achievements and Limitations of Prior Work
       - Token-Based Sequence Models
       - Graph-Based Structural Models
       - Large Language Models
       - The Data Quality Challenge
   1.2 Our Approach: Semantic-Enhanced Graph Learning
   1.3 Why Semantic Enhancement Improves Detection
   1.4 Contributions

[Figure 1: System Architecture]
[Figure 2: Code-to-Graph Example]

2. Background and Related Work
   (Keep existing content, can be trimmed)

3. Methodology
   3.1 Problem Formulation
   3.2 Code Property Graph Representation
   3.3 Semantic-Enhanced Node Representation
   3.4 Graph Neural Network Architectures
       - GGNN, RGAT, Multi-View, Call-Aware
   3.5 Graph-Level Pooling and Classification
   3.6 Summary

[Figure 3: Message Passing Intuition]

4. Experimental Setup
   4.1 Datasets
   4.2 Data Preprocessing Pipeline  <-- NEW (from data_preprocessing.tex)
   4.3 Model Configurations
   4.4 Embedding Configurations
   4.5 Training Hyperparameters

5. Results
   (Keep existing content)

6. Conclusion
```

## Reviewer Suggestions - How They Are Addressed

| Suggestion | Solution |
|------------|----------|
| Summarize prior work achievements/shortcomings | Section 1.1 in revised introduction |
| Focus on main components of proposed mechanism | Section 1.2 + streamlined methodology |
| Add graphical content to illustrate proposal | Figure 1 (system architecture) |
| Add graphical content for code-to-graph pipeline | Figure 2 (buffer overflow example) |
| Don't focus on datasets in methods section | Moved to Section 4.2 (data_preprocessing.tex) |
| Include code-to-graph example | Figure 2 with annotated CPG |

## Space for PrimeVul

As requested, space is left for detailed PrimeVul analysis. The introduction references PrimeVul findings briefly. You can expand this in:
- Section 1.1.4 (The Data Quality Challenge)
- A dedicated Related Work subsection
- The Results section (comparison with PrimeVul baseline)

## Quick Integration Commands

To quickly integrate, you can use these replacements in main.tex:

```bash
# Backup original
cp main.tex main.tex.backup

# The integration should be done manually to preserve
# any customizations in the original file
```

## Word Count Estimates

| Section | Original | Revised | Change |
|---------|----------|---------|--------|
| Introduction | ~600 words | ~800 words | +200 (more structure) |
| Methodology | ~3000 words | ~1200 words | -1800 (moved to exp.) |
| Experimental Setup | ~600 words | ~900 words | +300 (preprocessing) |
| **Net Change** | ~4200 | ~2900 | **-1300 words** |

The revision reduces overall length while improving focus and adding visual content.
