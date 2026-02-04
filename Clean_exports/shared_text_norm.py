#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
SHARED TEXT NORMALIZATION - V2 for Original (Non-Normalized) CPGs

Updates in V2:
  - Preserves real function names (strcpy, malloc, g_malloc0)
  - Preserves real variable names (xen_9pdev, ring_order)
  - Handles C operators as node text (still filters pure operators)
  - Better handling of struct access patterns (->field, .member)
  - Supports longer code snippets common in original CPGs

This module provides consistent text normalization across:
  - vocab_builder.py (vocabulary generation)
  - simple_extractor.py (embedding extraction)
  - cache_manager.py (cache building)
"""

from __future__ import annotations
import re
import hashlib
from typing import Optional, Dict, List, Set

# ============================================================================
# SHARED CONSTANTS
# ============================================================================

# Length constraints - wider for original code
MIN_LEN: int = 1      # Allow single chars (x, y, i) IF alphanumeric
MAX_LEN: int = 4000   # Increased for original code snippets

# Placeholder filtering (angle-bracket "meta" tokens or known sentinels)
DROP_IF_ANGLE_BRACKETED: bool = True
PLACEHOLDER_SET: Set[str] = {
    "<empty>", "<global>", "<includes>", "<unknown>", "ANY",
    "<unreachable>", "<operator>", "<init>", "<clinit>",
    "RET", "VOID", "void",  # Uninformative return types
}
PLACEHOLDER_RE = re.compile(r"^<[^>]*>$")
ANGLE_PLACEHOLDER_TOKENS: Set[str] = {
    t for t in PLACEHOLDER_SET if t.startswith("<") and t.endswith(">")
}

# Whitespace normalization
WHITESPACE_RE = re.compile(r"\s+")

# NOISE FILTER: Pure C operators that are semantically useless as embeddings
# Note: We keep operators that are part of larger expressions
PURE_OPERATOR_TOKENS: Set[str] = {
    # Single character operators
    "=", "+", "-", "*", "/", "%", "&", "|", "^", "!", "~", "?", ":",
    ",", ";", "{", "}", "(", ")", "[", "]", ".", "<", ">",
    # Two character operators
    "->", "::", "==", "!=", ">=", "<=", "&&", "||", "++", "--",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<", ">>",
    "<<=", ">>=", "->*", ".*",
    # Other noise
    "...",
}

# Joern operator prefixes - these are internal representations
JOERN_OPERATOR_PREFIXES = (
    "<operator>.",
    "<operators>.",
)

# Version tag
NORM_VERSION = "aligned-v2.0-original-cpg"

# ============================================================================
# CORE NORMALIZATION
# ============================================================================

def normalize_for_embedding(s: str) -> str:
    """
    Idempotent, order-stable normalization for original CPG code:
      1) Normalize newlines/CR → spaces; collapse runs of whitespace.
      2) Remove angle-bracket placeholders and known sentinel tokens.
      3) Remove pure operator tokens (keep operators in expressions).
      4) Enforce length window [MIN_LEN, MAX_LEN].
      5) Strip leading/trailing spaces.

    Returns '' if filtered/invalid (callers can drop these rows).
    """
    if not s or not isinstance(s, str):
        return ""

    # 1) Whitespace normalization
    s = s.replace("\r", " ").replace("\n", " ").replace("\t", " ")
    s = WHITESPACE_RE.sub(" ", s).strip()
    if not s:
        return ""

    # 2) Check for Joern operator nodes (like <operator>.assignment)
    # Extract the meaningful part if possible
    for prefix in JOERN_OPERATOR_PREFIXES:
        if s.startswith(prefix):
            # Keep the operator name (assignment, addressOf, etc.)
            op_name = s[len(prefix):]
            if op_name and len(op_name) >= 2:
                return op_name
            return ""

    # Drop strings containing placeholder tokens like "<global>" anywhere.
    for token in ANGLE_PLACEHOLDER_TOKENS:
        if token in s:
            return ""

    # 3) Pure operator token filter (only exact matches)
    if s in PURE_OPERATOR_TOKENS:
        return ""

    # 4) Placeholder filtering
    if s in PLACEHOLDER_SET:
        return ""
    if DROP_IF_ANGLE_BRACKETED and PLACEHOLDER_RE.match(s):
        return ""

    # 5) Length window
    L = len(s)
    if L > MAX_LEN:
        # Truncate rather than drop for very long strings
        s = s[:MAX_LEN]
        L = MAX_LEN

    # 6) Single character check - must be alphanumeric
    if L < 2:
        if not s.isalnum():
            return ""

    return s.strip()


def normalize_code_snippet(s: str) -> str:
    """
    Lighter normalization for code snippets - preserves structure better.
    Use this for CODE properties that contain full expressions.
    """
    if not s or not isinstance(s, str):
        return ""
    
    # Basic whitespace normalization
    s = s.replace("\r", " ").replace("\n", " ").replace("\t", " ")
    s = WHITESPACE_RE.sub(" ", s).strip()
    
    if not s:
        return ""

    # Drop strings containing placeholder tokens like "<global>" anywhere.
    for token in ANGLE_PLACEHOLDER_TOKENS:
        if token in s:
            return ""
    
    # Check placeholders
    if s in PLACEHOLDER_SET:
        return ""
    if DROP_IF_ANGLE_BRACKETED and PLACEHOLDER_RE.match(s):
        return ""
    
    # Length limit
    if len(s) > MAX_LEN:
        s = s[:MAX_LEN]
    
    return s.strip()


def normalize_identifier(s: str) -> str:
    """
    Normalization specifically for identifiers (variable/function names).
    More permissive - keeps underscores, numbers, etc.
    """
    if not s or not isinstance(s, str):
        return ""
    
    s = s.strip()
    
    # Remove Joern operator prefix if present
    for prefix in JOERN_OPERATOR_PREFIXES:
        if s.startswith(prefix):
            s = s[len(prefix):]
            break

    # Check placeholders
    if s in PLACEHOLDER_SET:
        return ""
    if DROP_IF_ANGLE_BRACKETED and PLACEHOLDER_RE.match(s):
        return ""
    for token in ANGLE_PLACEHOLDER_TOKENS:
        if token in s:
            return ""
    
    # Must have at least one alphanumeric
    if not any(c.isalnum() for c in s):
        return ""
    
    return s


def sha256_normalized(s: str) -> str:
    """
    Compute SHA256 over the *normalized* string.
    Must be identical wherever it is used.
    """
    n = normalize_for_embedding(s)
    return hashlib.sha256(n.encode("utf-8", errors="ignore")).hexdigest()


# ============================================================================
# VALIDATION / HELPERS
# ============================================================================

def is_placeholder(s: str) -> bool:
    """Check if string is a placeholder that should be filtered."""
    if not isinstance(s, str):
        return True
    s = s.strip()
    if s in PLACEHOLDER_SET:
        return True
    if DROP_IF_ANGLE_BRACKETED and PLACEHOLDER_RE.match(s):
        return True
    return False


def looks_like_codey(s: str) -> bool:
    """Lightweight length screen (mirrors upstream quick checks)."""
    return isinstance(s, str) and (MIN_LEN <= len(s) <= MAX_LEN)


def is_operator_node(name: str) -> bool:
    """Check if a node name represents a Joern operator."""
    if not name:
        return False
    return name.startswith("<operator>") or name in PURE_OPERATOR_TOKENS


def extract_operator_type(name: str) -> Optional[str]:
    """Extract the operator type from a Joern operator node name."""
    for prefix in JOERN_OPERATOR_PREFIXES:
        if name.startswith(prefix):
            return name[len(prefix):]
    return None


def validate_normalization_consistency(test_strings: Optional[List[str]] = None) -> bool:
    """
    Smoke-test for common edge cases. Returns True if function completes.
    """
    if test_strings is None:
        test_strings = [
            # Real function names (should be kept)
            "strcpy",
            "g_malloc0",
            "xenstore_read_fe_int",
            # Real variable names (should be kept)
            "xen_9pdev",
            "ring_order",
            "num_rings",
            # Joern operators (should extract meaningful part)
            "<operator>.assignment",
            "<operator>.indirectFieldAccess",
            # Pure operators (should be filtered)
            "->",
            "==",
            ";",
            # Code snippets (should be kept)
            "strcpy(buffer, input)",
            "xen_9pdev->rings[i].evtchn",
            # Placeholders (should be filtered)
            "<empty>",
            "<global>",
            "<unknown>",
            "RET",
            # Edge cases
            "x",  # Single alphanumeric - keep
            "*",  # Single operator - filter
            "a" * 5000,  # Very long - truncate
        ]

    print("=" * 100)
    print("TEXT NORMALIZATION TEST (V2 - Original CPGs)")
    print("=" * 100)
    print(f"{'Input':<40} | {'Valid':<6} | {'Normalized':<40}")
    print("-" * 100)
    
    for t in test_strings:
        n = normalize_for_embedding(t)
        display_input = t[:37] + "..." if len(t) > 40 else t
        display_norm = n[:37] + "..." if len(n) > 40 else n
        valid = "✅" if n else "❌"
        print(f"{display_input:<40} | {valid:<6} | {display_norm:<40}")
    
    print("=" * 100)
    return True


def get_normalization_config() -> Dict[str, object]:
    """Expose configuration to external scripts for audit logs."""
    return {
        "min_len": MIN_LEN,
        "max_len": MAX_LEN,
        "drop_angle_bracketed": DROP_IF_ANGLE_BRACKETED,
        "placeholder_set": sorted(list(PLACEHOLDER_SET)),
        "pure_operator_tokens_count": len(PURE_OPERATOR_TOKENS),
        "version": NORM_VERSION,
    }


# ============================================================================
# LEGACY ALIASES (for backward compatibility)
# ============================================================================

def normalize_text(s: str) -> str:
    """Alias for normalize_for_embedding."""
    return normalize_for_embedding(s)

def sha256_text(s: str) -> str:
    """Alias for sha256_normalized."""
    return sha256_normalized(s)


# ============================================================================
# SELF-TEST
# ============================================================================

if __name__ == "__main__":
    print("=== SHARED TEXT NORMALIZATION V2 ===")
    print("Config:", get_normalization_config())
    print()
    validate_normalization_consistency()
