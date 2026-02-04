#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
losses.py - Loss functions for vulnerability detection

Includes:
- Focal Loss (handles class imbalance)
- Combined Loss (BCE + Focal)
- Soft F1 Loss (differentiable F1 approximation)
- Label Smoothing BCE
- Anti-Collapse Loss
- Asymmetric Loss (prioritizes recall)
- Recall Priority Loss
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from typing import Optional


class FocalLoss(nn.Module):
    """
    Focal Loss for handling class imbalance.
    
    Reduces the loss contribution from easy examples,
    focusing training on hard examples.
    
    FL(p) = -α * (1-p)^γ * log(p)
    
    Args:
        alpha: Weighting factor (default 0.25)
        gamma: Focusing parameter (default 2.0)
        pos_weight: Additional positive class weight
    """
    
    def __init__(
        self, 
        alpha: float = 0.25, 
        gamma: float = 2.0, 
        reduction: str = "mean",
        pos_weight: Optional[torch.Tensor] = None,
    ):
        super().__init__()
        self.alpha = alpha
        self.gamma = gamma
        self.reduction = reduction
        self.pos_weight = pos_weight
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        """
        Args:
            logits: Predicted logits [B]
            targets: Binary targets [B]
        """
        bce = F.binary_cross_entropy_with_logits(
            logits, targets, reduction='none',
            pos_weight=self.pos_weight
        )
        pt = torch.exp(-bce)  # p if y=1, 1-p if y=0
        focal_weight = self.alpha * (1 - pt) ** self.gamma
        loss = focal_weight * bce
        
        if self.reduction == "mean":
            return loss.mean()
        elif self.reduction == "sum":
            return loss.sum()
        return loss


class LabelSmoothingBCE(nn.Module):
    """
    Binary Cross Entropy with Label Smoothing.
    
    Softens labels: 0 -> smoothing/2, 1 -> 1 - smoothing/2
    This helps calibration and can improve F1.
    
    Args:
        smoothing: Smoothing factor (default 0.1)
        pos_weight: Positive class weight
    """
    
    def __init__(
        self, 
        smoothing: float = 0.1, 
        pos_weight: Optional[torch.Tensor] = None,
    ):
        super().__init__()
        self.smoothing = smoothing
        self.pos_weight = pos_weight
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        # Smooth labels: 0 → 0.05, 1 → 0.95 (for smoothing=0.1)
        targets_smooth = targets * (1 - self.smoothing) + 0.5 * self.smoothing
        
        return F.binary_cross_entropy_with_logits(
            logits, targets_smooth, pos_weight=self.pos_weight
        )


class SoftF1Loss(nn.Module):
    """
    Differentiable approximation to F1 score.
    
    Useful for directly optimizing F1 during training.
    
    Args:
        smooth: Smoothing factor to prevent division by zero
        beta: F-beta score parameter (default 1.0 for F1)
    """
    
    def __init__(self, smooth: float = 1e-7, beta: float = 1.0):
        super().__init__()
        self.smooth = smooth
        self.beta = beta
        self.beta_sq = beta ** 2
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        probs = torch.sigmoid(logits)
        
        # Soft TP, FP, FN
        tp = (probs * targets).sum()
        fp = (probs * (1 - targets)).sum()
        fn = ((1 - probs) * targets).sum()
        
        # Soft precision, recall, F1
        precision = tp / (tp + fp + self.smooth)
        recall = tp / (tp + fn + self.smooth)
        
        # F-beta score
        f_score = (1 + self.beta_sq) * precision * recall / \
                  (self.beta_sq * precision + recall + self.smooth)
        
        return 1 - f_score  # Minimize 1-F1


class CombinedLoss(nn.Module):
    """
    Combined loss: BCE + Focal + optional Soft F1.
    
    Recommended default for vulnerability detection.
    
    Args:
        pos_weight: Class weight for BCE
        focal_weight: Weight for focal loss component (0 = only BCE)
        f1_weight: Weight for soft F1 loss component
        label_smoothing: Label smoothing factor
    """
    
    def __init__(
        self,
        pos_weight: Optional[torch.Tensor] = None,
        focal_weight: float = 0.3,
        f1_weight: float = 0.0,
        label_smoothing: float = 0.0,
    ):
        super().__init__()
        
        self.focal_weight = focal_weight
        self.f1_weight = f1_weight
        
        if label_smoothing > 0:
            self.bce = LabelSmoothingBCE(label_smoothing, pos_weight)
        else:
            self.bce = nn.BCEWithLogitsLoss(pos_weight=pos_weight)
        
        self.focal = FocalLoss(alpha=0.25, gamma=2.0, pos_weight=pos_weight)
        
        if f1_weight > 0:
            self.f1_loss = SoftF1Loss()
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        # Compute components
        bce_loss = self.bce(logits, targets)
        
        if self.focal_weight > 0:
            focal_loss = self.focal(logits, targets)
        else:
            focal_loss = 0
        
        if self.f1_weight > 0:
            f1_loss = self.f1_loss(logits, targets)
        else:
            f1_loss = 0
        
        # Combine
        total_loss = (
            (1 - self.focal_weight - self.f1_weight) * bce_loss +
            self.focal_weight * focal_loss +
            self.f1_weight * f1_loss
        )
        
        return total_loss


class AntiCollapseLoss(nn.Module):
    """
    Loss that prevents prediction collapse.
    
    Adds penalty when predictions have low variance (all same value).
    
    Args:
        base_loss: The underlying loss function
        collapse_weight: Weight for the anti-collapse penalty
    """
    
    def __init__(self, base_loss: nn.Module, collapse_weight: float = 0.1):
        super().__init__()
        self.base_loss = base_loss
        self.collapse_weight = collapse_weight
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        base = self.base_loss(logits, targets)
        
        # Anti-collapse: penalize low variance
        probs = torch.sigmoid(logits)
        prob_std = probs.std()
        
        # Target std should be ~0.2-0.3 for good predictions
        # Penalize if std < 0.1 (collapse)
        collapse_penalty = F.relu(0.1 - prob_std)
        
        return base + self.collapse_weight * collapse_penalty


# ============================================================================
# ENHANCED LOSS FUNCTIONS (NEW)
# ============================================================================

class AsymmetricLoss(nn.Module):
    """
    Asymmetric Loss for prioritizing recall or precision.
    
    Different gamma values for positive and negative samples:
    - Higher gamma_neg: Focus more on false negatives (improves recall)
    - Higher gamma_pos: Focus more on false positives (improves precision)
    
    For vulnerability detection, we usually want higher recall.
    
    Args:
        gamma_neg: Focusing parameter for negative samples (default 4.0)
        gamma_pos: Focusing parameter for positive samples (default 1.0)
        clip: Probability clipping to prevent gradient explosion
    """
    
    def __init__(
        self,
        gamma_neg: float = 4.0,
        gamma_pos: float = 1.0,
        clip: float = 0.05,
    ):
        super().__init__()
        self.gamma_neg = gamma_neg
        self.gamma_pos = gamma_pos
        self.clip = clip
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        probs = torch.sigmoid(logits)
        
        # Clip probabilities
        probs_pos = probs.clamp(min=self.clip)
        probs_neg = (1 - probs).clamp(min=self.clip)
        
        # Positive samples: standard focal
        loss_pos = targets * (1 - probs_pos) ** self.gamma_pos * (-torch.log(probs_pos))
        
        # Negative samples: asymmetric focal (higher gamma)
        loss_neg = (1 - targets) * probs ** self.gamma_neg * (-torch.log(probs_neg))
        
        return (loss_pos + loss_neg).mean()


class RecallPriorityLoss(nn.Module):
    """
    Loss that prioritizes recall (finding all vulnerabilities).
    
    Uses asymmetric weighting to penalize false negatives more than false positives.
    Good for security applications where missing a vulnerability is worse than a false alarm.
    
    Args:
        fn_weight: Weight for false negative penalty (default 2.0)
        fp_weight: Weight for false positive penalty (default 1.0)
        pos_weight: Additional positive class weight
    """
    
    def __init__(
        self,
        fn_weight: float = 2.0,
        fp_weight: float = 1.0,
        pos_weight: Optional[torch.Tensor] = None,
    ):
        super().__init__()
        self.fn_weight = fn_weight
        self.fp_weight = fp_weight
        self.pos_weight = pos_weight
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        probs = torch.sigmoid(logits)
        
        # False negative loss (missed vulnerabilities)
        fn_loss = targets * (-torch.log(probs.clamp(min=1e-7)))
        
        # False positive loss (false alarms)
        fp_loss = (1 - targets) * (-torch.log((1 - probs).clamp(min=1e-7)))
        
        # Apply asymmetric weights
        loss = self.fn_weight * fn_loss + self.fp_weight * fp_loss
        
        # Apply pos_weight if provided
        if self.pos_weight is not None:
            weight = targets * self.pos_weight + (1 - targets)
            loss = loss * weight
        
        return loss.mean()


class CombinedLossV2(nn.Module):
    """
    Enhanced combined loss with multiple components.
    
    Combines:
    - BCE with label smoothing (calibration)
    - Focal loss (hard example mining)
    - Optional F1 soft loss (direct F1 optimization)
    
    Args:
        bce_weight: Weight for BCE component
        focal_weight: Weight for focal component
        f1_weight: Weight for F1 soft loss component
        smoothing: Label smoothing factor
        focal_gamma: Focal loss gamma
        pos_weight: Positive class weight
    """
    
    def __init__(
        self,
        bce_weight: float = 0.4,
        focal_weight: float = 0.4,
        f1_weight: float = 0.2,
        smoothing: float = 0.05,
        focal_gamma: float = 2.0,
        pos_weight: Optional[torch.Tensor] = None,
    ):
        super().__init__()
        self.bce_weight = bce_weight
        self.focal_weight = focal_weight
        self.f1_weight = f1_weight
        
        self.bce = LabelSmoothingBCE(smoothing=smoothing, pos_weight=pos_weight)
        self.focal = FocalLoss(gamma=focal_gamma, pos_weight=pos_weight)
        self.f1_soft = SoftF1Loss()
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        loss = 0.0
        
        if self.bce_weight > 0:
            loss += self.bce_weight * self.bce(logits, targets)
        
        if self.focal_weight > 0:
            loss += self.focal_weight * self.focal(logits, targets)
        
        if self.f1_weight > 0:
            loss += self.f1_weight * self.f1_soft(logits, targets)
        
        return loss


# ============================================================================
# FACTORY FUNCTION
# ============================================================================

def create_loss(
    loss_type: str = "combined",
    pos_weight: Optional[torch.Tensor] = None,
    focal_weight: float = 0.3,
    **kwargs,
) -> nn.Module:
    """
    Factory function to create loss by type.
    
    Args:
        loss_type: Loss type. Options:
            - "bce": Standard BCE
            - "focal": Focal loss
            - "combined": BCE + Focal (default)
            - "combined_v2": BCE + Focal + F1 soft
            - "f1" or "soft_f1": Soft F1 loss
            - "asymmetric": Asymmetric focal loss
            - "recall_priority": Recall-focused loss
            - "anti_collapse": Combined + anti-collapse penalty
            - "label_smooth": BCE with label smoothing
        pos_weight: Class weight
        focal_weight: Weight for focal component in combined loss
        **kwargs: Additional arguments
    
    Returns:
        Loss module
    """
    if loss_type == "bce":
        return nn.BCEWithLogitsLoss(pos_weight=pos_weight)
    
    elif loss_type == "focal":
        return FocalLoss(pos_weight=pos_weight, **kwargs)
    
    elif loss_type == "combined":
        return CombinedLoss(
            pos_weight=pos_weight,
            focal_weight=focal_weight,
            f1_weight=kwargs.get("f1_weight", 0.0),
            label_smoothing=kwargs.get("label_smoothing", 0.0),
        )
    
    elif loss_type == "combined_v2":
        return CombinedLossV2(pos_weight=pos_weight, **kwargs)
    
    elif loss_type in ["f1", "soft_f1"]:
        return SoftF1Loss(**kwargs)
    
    elif loss_type == "asymmetric":
        return AsymmetricLoss(**kwargs)
    
    elif loss_type == "recall_priority":
        return RecallPriorityLoss(pos_weight=pos_weight, **kwargs)
    
    elif loss_type == "anti_collapse":
        base = CombinedLoss(pos_weight=pos_weight, focal_weight=focal_weight)
        return AntiCollapseLoss(base, kwargs.get("collapse_weight", 0.1))
    
    elif loss_type == "label_smooth":
        return LabelSmoothingBCE(
            smoothing=kwargs.get("smoothing", 0.1),
            pos_weight=pos_weight,
        )
    
    else:
        raise ValueError(f"Unknown loss type: {loss_type}")