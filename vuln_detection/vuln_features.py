#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
vuln_features.py - Vulnerability-Aware Node Feature Extraction (Stage 1)

This module extracts 32-dimensional vulnerability-specific features for each node,
designed to capture patterns that distinguish vulnerable from safe code.

Based on research findings:
  - CALL nodes with security-sensitive APIs have INFINITE lift for vulnerability
  - Edge types have lift ~1.0 (non-discriminative)
  - Buffer/memory/format APIs are the strongest vulnerability indicators

Feature Dimensions (32 total):
  [0-7]:   Security API category one-hot (8 categories)
  [8-15]:  Operation type indicators (array, pointer, size check, etc.)
  [16-23]: Data type and vulnerability pattern indicators
  [24-31]: Taint source/sink indicators

Usage:
    from vuln_features import VulnFeatureExtractor
    
    extractor = VulnFeatureExtractor()
    features = extractor.extract_node_features(node_code, node_type)
    # Returns: np.ndarray of shape (32,)
"""

import re
import numpy as np
from typing import Dict, List, Optional, Set, Tuple

# ═══════════════════════════════════════════════════════════════════════════════
# SECURITY-SENSITIVE API TAXONOMY
# Based on CWE classifications and your diagnostic findings
# ═══════════════════════════════════════════════════════════════════════════════

SECURITY_API_TAXONOMY = {
    # Category 0: Buffer Operations - Unsafe (CWE-119, CWE-120, CWE-121)
    'BUFFER_UNSAFE': {
        'apis': ['strcpy', 'strcat', 'sprintf', 'vsprintf', 'gets', 'scanf', 
                 'sscanf', 'fscanf', 'vscanf', 'vfscanf', 'vsscanf'],
        'cwe': ['CWE-119', 'CWE-120', 'CWE-121', 'CWE-122'],
        'risk': 'high',
    },
    
    # Category 1: Buffer Operations - Bounded (safer but still risky)
    'BUFFER_BOUNDED': {
        'apis': ['strncpy', 'strncat', 'snprintf', 'vsnprintf', 'fgets', 
                 'memcpy', 'memmove', 'memset', 'bcopy', 'bzero'],
        'cwe': ['CWE-119', 'CWE-120'],
        'risk': 'medium',
    },
    
    # Category 2: Memory Allocation (CWE-401, CWE-415, CWE-416)
    'MEMORY_ALLOC': {
        'apis': ['malloc', 'calloc', 'realloc', 'alloca', 'valloc', 
                 'pvalloc', 'memalign', 'aligned_alloc', 'posix_memalign',
                 'new', 'new[]'],
        'cwe': ['CWE-401', 'CWE-122', 'CWE-789'],
        'risk': 'medium',
    },
    
    # Category 3: Memory Deallocation (CWE-415, CWE-416)
    'MEMORY_FREE': {
        'apis': ['free', 'cfree', 'delete', 'delete[]', 'realloc'],
        'cwe': ['CWE-415', 'CWE-416', 'CWE-761'],
        'risk': 'high',
    },
    
    # Category 4: Format String (CWE-134)
    'FORMAT_STRING': {
        'apis': ['printf', 'fprintf', 'sprintf', 'snprintf', 'vprintf',
                 'vfprintf', 'vsprintf', 'vsnprintf', 'syslog', 'setproctitle',
                 'err', 'verr', 'errx', 'verrx', 'warn', 'vwarn', 'warnx', 'vwarnx'],
        'cwe': ['CWE-134'],
        'risk': 'high',
    },
    
    # Category 5: Command/Code Injection (CWE-78, CWE-77)
    'COMMAND_EXEC': {
        'apis': ['system', 'popen', 'exec', 'execl', 'execle', 'execlp',
                 'execv', 'execve', 'execvp', 'execvpe', 'wordexp',
                 'fork', 'vfork', 'clone', 'eval', 'dlopen', 'dlsym'],
        'cwe': ['CWE-78', 'CWE-77', 'CWE-676'],
        'risk': 'critical',
    },
    
    # Category 6: Integer Operations (CWE-190, CWE-191, CWE-681)
    'INTEGER_OPS': {
        'apis': ['atoi', 'atol', 'atoll', 'strtol', 'strtoll', 'strtoul',
                 'strtoull', 'strtoimax', 'strtoumax', 'wcstol', 'wcstoll'],
        'cwe': ['CWE-190', 'CWE-191', 'CWE-681', 'CWE-194', 'CWE-195'],
        'risk': 'medium',
    },
    
    # Category 7: File/IO Operations (CWE-22, CWE-73, CWE-367)
    'FILE_IO': {
        'apis': ['fopen', 'freopen', 'open', 'creat', 'openat', 'fread',
                 'fwrite', 'read', 'write', 'pread', 'pwrite', 'readv',
                 'writev', 'fclose', 'close', 'rename', 'unlink', 'remove',
                 'mkdir', 'rmdir', 'chdir', 'chmod', 'chown', 'link', 'symlink',
                 'access', 'stat', 'lstat', 'fstat'],
        'cwe': ['CWE-22', 'CWE-73', 'CWE-367', 'CWE-377'],
        'risk': 'medium',
    },
}

# Flatten for quick lookup
ALL_SECURITY_APIS: Dict[str, Tuple[int, str]] = {}
for cat_idx, (cat_name, cat_data) in enumerate(SECURITY_API_TAXONOMY.items()):
    for api in cat_data['apis']:
        ALL_SECURITY_APIS[api.lower()] = (cat_idx, cat_name)

# ═══════════════════════════════════════════════════════════════════════════════
# TAINT SOURCES AND SINKS
# ═══════════════════════════════════════════════════════════════════════════════

TAINT_SOURCES = {
    # User Input
    'recv', 'recvfrom', 'recvmsg', 'read', 'fread', 'fgets', 'gets',
    'getchar', 'getc', 'fgetc', 'getline', 'getdelim',
    # Network
    'accept', 'accept4', 'gethostbyname', 'gethostbyaddr',
    # Environment
    'getenv', 'secure_getenv',
    # Arguments
    'argv', 'main',  # Special handling for main args
    # Scanf family
    'scanf', 'fscanf', 'sscanf', 'vscanf', 'vfscanf', 'vsscanf',
}

TAINT_SINKS = {
    # Buffer overflow sinks
    'strcpy', 'strcat', 'sprintf', 'gets', 'memcpy', 'memmove',
    # Command injection sinks
    'system', 'popen', 'exec', 'execl', 'execle', 'execlp', 'execv', 
    'execve', 'execvp', 'wordexp',
    # Format string sinks
    'printf', 'fprintf', 'sprintf', 'syslog',
    # SQL injection (if applicable)
    'mysql_query', 'mysql_real_query', 'sqlite3_exec', 'PQexec',
    # Memory sinks
    'free', 'realloc',
    # File path sinks
    'fopen', 'open', 'freopen', 'openat',
}

# ═══════════════════════════════════════════════════════════════════════════════
# VULNERABILITY PATTERN REGEX
# ═══════════════════════════════════════════════════════════════════════════════

VULN_PATTERNS = {
    # Array access without bounds check
    'array_access': re.compile(r'\[.*\]'),
    # Pointer arithmetic
    'ptr_arithmetic': re.compile(r'[\+\-]\s*\d+|\+\+|--'),
    # Pointer dereference
    'ptr_deref': re.compile(r'\*\s*[a-zA-Z_]|\-\>'),
    # Address-of operator
    'address_of': re.compile(r'&\s*[a-zA-Z_]'),
    # Size/length variables (positive indicator - bounds checking)
    'size_var': re.compile(r'\b(size|len|length|count|num|n|sz|cb)\b', re.I),
    # Buffer variables
    'buffer_var': re.compile(r'\b(buf|buffer|data|str|string|ptr|mem|dst|src)\b', re.I),
    # Loop constructs (iteration over buffers)
    'loop': re.compile(r'\b(for|while|do)\b'),
    # Null check (positive indicator)
    'null_check': re.compile(r'(!=\s*NULL|==\s*NULL|!\s*[a-zA-Z_]|\bNULL\b)', re.I),
    # Comparison operators (bounds checking)
    'comparison': re.compile(r'[<>]=?|==|!='),
    # Sizeof operator (positive indicator)
    'sizeof': re.compile(r'\bsizeof\b'),
    # Cast operations (type confusion risk)
    'cast': re.compile(r'\(\s*(char|int|void|unsigned|signed|long|short|size_t|uint\d+_t|int\d+_t)\s*\*?\s*\)'),
}

# ═══════════════════════════════════════════════════════════════════════════════
# DATA TYPE PATTERNS
# ═══════════════════════════════════════════════════════════════════════════════

DATA_TYPE_PATTERNS = {
    'char_type': re.compile(r'\bchar\b'),
    'int_type': re.compile(r'\b(int|long|short)\b'),
    'unsigned': re.compile(r'\bunsigned\b'),
    'pointer': re.compile(r'\*'),
    'size_t': re.compile(r'\bsize_t\b'),
    'void_ptr': re.compile(r'\bvoid\s*\*'),
}


# ═══════════════════════════════════════════════════════════════════════════════
# FEATURE EXTRACTOR CLASS
# ═══════════════════════════════════════════════════════════════════════════════

class VulnFeatureExtractor:
    """
    Extracts 32-dimensional vulnerability-aware features from node code.
    
    Feature vector structure:
        [0-7]:   Security API category (one-hot, 8 dims)
        [8-11]:  Operation indicators (array, pointer, sizeof, increment)
        [12-15]: Control flow context (control_struct, conditional, loop, return)
        [16-19]: Data type indicators (char, int, unsigned, pointer)
        [20-23]: Vulnerability pattern flags (null_check, comparison, size_var, buffer_var)
        [24-27]: Taint indicators (is_source, is_buffer_sink, is_cmd_sink, is_format_sink)
        [28-31]: Special flags (has_cast, in_loop_body, has_sizeof, is_call_node)
    """
    
    FEATURE_DIM = 32
    
    def __init__(self, verbose: bool = False):
        self.verbose = verbose
        self._stats = {
            'total_nodes': 0,
            'nodes_with_api': 0,
            'taint_sources': 0,
            'taint_sinks': 0,
            'api_categories': {cat: 0 for cat in SECURITY_API_TAXONOMY.keys()},
        }
    
    def extract_node_features(
        self, 
        node_code: str, 
        node_type: str,
        context_code: Optional[str] = None,
    ) -> np.ndarray:
        """
        Extract vulnerability features for a single node.
        
        Args:
            node_code: The code text of the node
            node_type: The node type (CALL, IDENTIFIER, CONTROL_STRUCTURE, etc.)
            context_code: Optional surrounding context for better analysis
        
        Returns:
            np.ndarray of shape (32,) with float32 features
        """
        features = np.zeros(self.FEATURE_DIM, dtype=np.float32)
        self._stats['total_nodes'] += 1
        
        if not node_code:
            # Mark as CALL node if applicable
            if node_type == 'CALL':
                features[31] = 1.0
            return features
        
        code_lower = node_code.lower()
        
        # ─────────────────────────────────────────────────────────────────────
        # [0-7] Security API Category (one-hot)
        # ─────────────────────────────────────────────────────────────────────
        api_found = self._extract_api_category(code_lower, features)
        if api_found:
            self._stats['nodes_with_api'] += 1
        
        # ─────────────────────────────────────────────────────────────────────
        # [8-11] Operation Type Indicators
        # ─────────────────────────────────────────────────────────────────────
        features[8] = 1.0 if VULN_PATTERNS['array_access'].search(node_code) else 0.0
        features[9] = 1.0 if (VULN_PATTERNS['ptr_deref'].search(node_code) or 
                              VULN_PATTERNS['address_of'].search(node_code)) else 0.0
        features[10] = 1.0 if VULN_PATTERNS['sizeof'].search(node_code) else 0.0
        features[11] = 1.0 if VULN_PATTERNS['ptr_arithmetic'].search(node_code) else 0.0
        
        # ─────────────────────────────────────────────────────────────────────
        # [12-15] Control Flow Context
        # ─────────────────────────────────────────────────────────────────────
        features[12] = 1.0 if node_type == 'CONTROL_STRUCTURE' else 0.0
        features[13] = 1.0 if 'if' in code_lower or '?' in node_code else 0.0
        features[14] = 1.0 if VULN_PATTERNS['loop'].search(node_code) else 0.0
        features[15] = 1.0 if 'return' in code_lower else 0.0
        
        # ─────────────────────────────────────────────────────────────────────
        # [16-19] Data Type Indicators
        # ─────────────────────────────────────────────────────────────────────
        features[16] = 1.0 if DATA_TYPE_PATTERNS['char_type'].search(node_code) else 0.0
        features[17] = 1.0 if DATA_TYPE_PATTERNS['int_type'].search(node_code) else 0.0
        features[18] = 1.0 if DATA_TYPE_PATTERNS['unsigned'].search(node_code) else 0.0
        features[19] = 1.0 if (DATA_TYPE_PATTERNS['pointer'].search(node_code) and 
                               node_type in ['LOCAL', 'IDENTIFIER', 'TYPE_DECL']) else 0.0
        
        # ─────────────────────────────────────────────────────────────────────
        # [20-23] Vulnerability Pattern Flags
        # ─────────────────────────────────────────────────────────────────────
        features[20] = 1.0 if VULN_PATTERNS['null_check'].search(node_code) else 0.0
        features[21] = 1.0 if VULN_PATTERNS['comparison'].search(node_code) else 0.0
        features[22] = 1.0 if VULN_PATTERNS['size_var'].search(node_code) else 0.0
        features[23] = 1.0 if VULN_PATTERNS['buffer_var'].search(node_code) else 0.0
        
        # ─────────────────────────────────────────────────────────────────────
        # [24-27] Taint Source/Sink Indicators
        # ─────────────────────────────────────────────────────────────────────
        is_source, is_buffer_sink, is_cmd_sink, is_format_sink = self._check_taint(code_lower)
        features[24] = 1.0 if is_source else 0.0
        features[25] = 1.0 if is_buffer_sink else 0.0
        features[26] = 1.0 if is_cmd_sink else 0.0
        features[27] = 1.0 if is_format_sink else 0.0
        
        if is_source:
            self._stats['taint_sources'] += 1
        if is_buffer_sink or is_cmd_sink or is_format_sink:
            self._stats['taint_sinks'] += 1
        
        # ─────────────────────────────────────────────────────────────────────
        # [28-31] Special Flags
        # ─────────────────────────────────────────────────────────────────────
        features[28] = 1.0 if VULN_PATTERNS['cast'].search(node_code) else 0.0
        features[29] = 0.0  # Reserved for in_loop_body (needs context)
        features[30] = 1.0 if 'sizeof' in code_lower else 0.0
        features[31] = 1.0 if node_type == 'CALL' else 0.0
        
        return features
    
    def _extract_api_category(self, code_lower: str, features: np.ndarray) -> bool:
        """Extract security API category and set one-hot encoding."""
        for api, (cat_idx, cat_name) in ALL_SECURITY_APIS.items():
            # Match whole word (not substring)
            if re.search(rf'\b{re.escape(api)}\b', code_lower):
                features[cat_idx] = 1.0
                self._stats['api_categories'][cat_name] += 1
                return True
        return False
    
    def _check_taint(self, code_lower: str) -> Tuple[bool, bool, bool, bool]:
        """Check if code contains taint sources or sinks."""
        is_source = False
        is_buffer_sink = False
        is_cmd_sink = False
        is_format_sink = False
        
        for src in TAINT_SOURCES:
            if re.search(rf'\b{re.escape(src)}\b', code_lower):
                is_source = True
                break
        
        # Buffer overflow sinks
        buffer_sinks = {'strcpy', 'strcat', 'sprintf', 'gets', 'memcpy', 'memmove'}
        for sink in buffer_sinks:
            if re.search(rf'\b{re.escape(sink)}\b', code_lower):
                is_buffer_sink = True
                break
        
        # Command injection sinks
        cmd_sinks = {'system', 'popen', 'exec', 'execl', 'execle', 'execlp', 
                     'execv', 'execve', 'execvp'}
        for sink in cmd_sinks:
            if re.search(rf'\b{re.escape(sink)}\b', code_lower):
                is_cmd_sink = True
                break
        
        # Format string sinks
        format_sinks = {'printf', 'fprintf', 'sprintf', 'syslog'}
        for sink in format_sinks:
            if re.search(rf'\b{re.escape(sink)}\b', code_lower):
                is_format_sink = True
                break
        
        return is_source, is_buffer_sink, is_cmd_sink, is_format_sink
    
    def get_stats(self) -> Dict:
        """Return extraction statistics."""
        return self._stats.copy()
    
    def reset_stats(self):
        """Reset statistics counters."""
        self._stats = {
            'total_nodes': 0,
            'nodes_with_api': 0,
            'taint_sources': 0,
            'taint_sinks': 0,
            'api_categories': {cat: 0 for cat in SECURITY_API_TAXONOMY.keys()},
        }
    
    @staticmethod
    def get_feature_names() -> List[str]:
        """Return human-readable feature names."""
        return [
            # [0-7] API categories
            'api_buffer_unsafe', 'api_buffer_bounded', 'api_memory_alloc', 
            'api_memory_free', 'api_format_string', 'api_command_exec',
            'api_integer_ops', 'api_file_io',
            # [8-11] Operation indicators
            'op_array_access', 'op_pointer', 'op_sizeof', 'op_increment',
            # [12-15] Control flow
            'cf_control_struct', 'cf_conditional', 'cf_loop', 'cf_return',
            # [16-19] Data types
            'dt_char', 'dt_int', 'dt_unsigned', 'dt_pointer',
            # [20-23] Vulnerability patterns
            'vp_null_check', 'vp_comparison', 'vp_size_var', 'vp_buffer_var',
            # [24-27] Taint indicators
            'taint_source', 'taint_sink_buffer', 'taint_sink_cmd', 'taint_sink_format',
            # [28-31] Special flags
            'has_cast', 'in_loop_body', 'has_sizeof', 'is_call_node',
        ]


# ═══════════════════════════════════════════════════════════════════════════════
# GRAPH-LEVEL FEATURE AGGREGATION
# ═══════════════════════════════════════════════════════════════════════════════

class GraphVulnFeatureAggregator:
    """
    Aggregates node-level vulnerability features to graph-level.
    
    Provides summary statistics that can be used alongside GNN output:
    - Count of each API category
    - Presence of taint source -> sink paths
    - Risk score based on API composition
    """
    
    def __init__(self):
        self.node_extractor = VulnFeatureExtractor()
    
    def aggregate_graph_features(
        self, 
        node_features: np.ndarray,
        node_types: Optional[List[str]] = None,
    ) -> Dict[str, float]:
        """
        Aggregate node features to graph-level statistics.
        
        Args:
            node_features: Array of shape (num_nodes, 32)
            node_types: Optional list of node type strings
        
        Returns:
            Dictionary of graph-level statistics
        """
        if node_features.shape[0] == 0:
            return self._empty_stats()
        
        stats = {}
        
        # API category counts (normalized by graph size)
        num_nodes = node_features.shape[0]
        for i, cat in enumerate(SECURITY_API_TAXONOMY.keys()):
            stats[f'api_{cat.lower()}_ratio'] = node_features[:, i].sum() / num_nodes
            stats[f'api_{cat.lower()}_count'] = int(node_features[:, i].sum())
        
        # Taint indicators
        stats['has_taint_source'] = float(node_features[:, 24].max())
        stats['has_taint_sink_buffer'] = float(node_features[:, 25].max())
        stats['has_taint_sink_cmd'] = float(node_features[:, 26].max())
        stats['has_taint_sink_format'] = float(node_features[:, 27].max())
        stats['has_any_taint_sink'] = float(max(
            stats['has_taint_sink_buffer'],
            stats['has_taint_sink_cmd'],
            stats['has_taint_sink_format']
        ))
        
        # Potential taint flow (source AND sink present)
        stats['potential_taint_flow'] = float(
            stats['has_taint_source'] and stats['has_any_taint_sink']
        )
        
        # Risk score (weighted combination of risk factors)
        risk_score = (
            2.0 * stats['api_buffer_unsafe_ratio'] +
            2.0 * stats['api_command_exec_ratio'] +
            1.5 * stats['api_format_string_ratio'] +
            1.0 * stats['api_memory_free_ratio'] +
            0.5 * stats['api_memory_alloc_ratio'] +
            3.0 * stats['potential_taint_flow']
        )
        stats['risk_score'] = risk_score
        
        # CALL node statistics
        call_mask = node_features[:, 31] > 0.5
        stats['num_call_nodes'] = int(call_mask.sum())
        stats['call_node_ratio'] = call_mask.sum() / num_nodes
        
        return stats
    
    def _empty_stats(self) -> Dict[str, float]:
        """Return empty statistics dictionary."""
        stats = {}
        for cat in SECURITY_API_TAXONOMY.keys():
            stats[f'api_{cat.lower()}_ratio'] = 0.0
            stats[f'api_{cat.lower()}_count'] = 0
        stats.update({
            'has_taint_source': 0.0,
            'has_taint_sink_buffer': 0.0,
            'has_taint_sink_cmd': 0.0,
            'has_taint_sink_format': 0.0,
            'has_any_taint_sink': 0.0,
            'potential_taint_flow': 0.0,
            'risk_score': 0.0,
            'num_call_nodes': 0,
            'call_node_ratio': 0.0,
        })
        return stats


# ═══════════════════════════════════════════════════════════════════════════════
# TESTING
# ═══════════════════════════════════════════════════════════════════════════════

if __name__ == "__main__":
    print("=" * 70)
    print("VULNERABILITY FEATURE EXTRACTOR TEST")
    print("=" * 70)
    
    extractor = VulnFeatureExtractor(verbose=True)
    
    # Test cases
    test_cases = [
        ("strcpy(dest, src)", "CALL"),
        ("malloc(size)", "CALL"),
        ("free(ptr)", "CALL"),
        ("system(cmd)", "CALL"),
        ("printf(fmt, args)", "CALL"),
        ("if (ptr != NULL)", "CONTROL_STRUCTURE"),
        ("char buffer[256]", "LOCAL"),
        ("int i = 0", "LOCAL"),
        ("recv(sock, buf, len, 0)", "CALL"),
        ("fgets(buf, sizeof(buf), stdin)", "CALL"),
        ("x = arr[i]", "IDENTIFIER"),
        ("ptr++", "IDENTIFIER"),
        ("(char *)malloc(n)", "CALL"),
    ]
    
    print("\nFeature extraction results:")
    print("-" * 70)
    
    feature_names = VulnFeatureExtractor.get_feature_names()
    
    for code, node_type in test_cases:
        features = extractor.extract_node_features(code, node_type)
        
        # Find active features
        active = [(feature_names[i], features[i]) for i in range(32) if features[i] > 0]
        
        print(f"\n{node_type:20s} | {code}")
        if active:
            print(f"  Active features: {active}")
        else:
            print(f"  No vulnerability features detected")
    
    print("\n" + "-" * 70)
    print("Extraction Statistics:")
    print(extractor.get_stats())
    
    # Test graph aggregation
    print("\n" + "=" * 70)
    print("GRAPH AGGREGATION TEST")
    print("=" * 70)
    
    # Simulate a graph with multiple nodes
    aggregator = GraphVulnFeatureAggregator()
    
    node_features = np.array([
        extractor.extract_node_features(code, ntype) 
        for code, ntype in test_cases
    ])
    
    graph_stats = aggregator.aggregate_graph_features(node_features)
    print("\nGraph-level statistics:")
    for k, v in sorted(graph_stats.items()):
        if isinstance(v, float):
            print(f"  {k}: {v:.4f}")
        else:
            print(f"  {k}: {v}")
