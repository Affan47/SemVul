"""
DYNAMIC CPG Configuration - V9 (CALL Node Property Priority Fix)

CRITICAL CHANGE in V9:
  - CALL nodes now use NAME first (not CODE) for text extraction
  - This ensures "strcpy" always gets the same embedding regardless of context
  - Previous: CODE="Var1 = strcpy(Var2, Var3)" → different embeddings per usage
  - Now: NAME="strcpy" → consistent embeddings for same function

Schema validated against Devign (27,318 files). REVEAL adds:
  - CAPTURE edge
  - CLOSURE_BINDING node

Current combined schema (Devign + REVEAL):
  - 19 edge types (full mode)
  - 17 edge types (full_filtered mode, recommended)
  - 28 node types discovered
  - 16 semantic node types kept
  - 12 structural node types filtered

All 19 edge types found across Devign + REVEAL:
  REACHING_DEF, AST, EVAL_TYPE, CONTAINS, CFG, POST_DOMINATE, DOMINATE,
  CDG, ARGUMENT, REF, CALL, PARAMETER_LINK, SOURCE_FILE, CONDITION,
  ALIAS_OF, BINDS, RECEIVER, IMPORTS, CAPTURE
"""

import re
import logging
from typing import Set, Dict, List, Optional, Tuple, Any

# ============================================================================
# EDGE TYPE CONFIGURATION (V9 - Complete from Schema Discovery)
# ============================================================================

# All 19 edge types discovered across Devign + REVEAL (sorted by frequency)
FULL_EDGE_TYPES = [
    "REACHING_DEF",  # 17,302,629 edges - Data flow (CRITICAL for vuln detection!)
    "AST",           # 9,087,000 edges - Abstract Syntax Tree structure
    "EVAL_TYPE",     # 7,249,503 edges - Type evaluation edges
    "CFG",           # 5,299,809 edges - Control Flow Graph
    "POST_DOMINATE", # 5,020,925 edges - Post-dominance relation
    "DOMINATE",      # 4,995,846 edges - Dominance relation
    "CDG",           # 3,991,999 edges - Control Dependency Graph
    "ARGUMENT",      # 3,604,010 edges - Function argument edges
    "REF",           # 2,072,854 edges - Reference edges
    "CALL",          # 1,823,980 edges - Function call edges
    "PARAMETER_LINK",# 903,596 edges - Parameter connections
    "CONDITION",     # 158,495 edges - Condition edges (if/while)
    "ALIAS_OF",      # 61,254 edges - Type alias edges
    "BINDS",         # 25,590 edges - Binding edges
    "CAPTURE",       # 103 edges - Closure capture (REVEAL)
    "RECEIVER",      # 5,952 edges - Method receiver
    "IMPORTS",       # 21 edges - Import dependencies
    "CONTAINS",      # 5,968,797 edges - Containment (metadata)
    "SOURCE_FILE",   # 640,952 edges - File relations (metadata)
]

# Simplified 5-class scheme (Original Devign style)
SIMPLIFIED_EDGE_TYPES = ["AST", "CFG", "DFG_READ", "DFG_WRITE", "NCS"]

# Mapping from full edge types to simplified 5-class scheme
FULL_TO_SIMPLIFIED_MAP = {
    # AST-like edges
    "AST": "AST",
    "ARGUMENT": "AST",
    "PARAMETER_LINK": "AST",
    "RECEIVER": "AST",
    "CAPTURE": "AST",
    
    # CFG-like edges  
    "CFG": "CFG",
    "CALL": "CFG",
    "CONDITION": "CFG",
    
    # Data flow - read
    "REF": "DFG_READ",
    "DFG": "DFG_READ",
    "IMPORTS": "DFG_READ",
    
    # Data flow - write/definition
    "REACHING_DEF": "DFG_WRITE",
    
    # Control dependency / dominance
    "DOMINATE": "NCS",
    "POST_DOMINATE": "NCS", 
    "CDG": "NCS",
    
    # Filtered out (set to None)
    "EVAL_TYPE": None,
    "SOURCE_FILE": None,
    "CONTAINS": None,
    "BINDS": None,
    "ALIAS_OF": None,
}

# ============================================================================
# CONFIGURATION MODE
# ============================================================================

class EdgeTypeMode:
    """Edge type configuration modes."""
    FULL = "full"                    # Use all 19 edge types
    SIMPLIFIED = "simplified"        # Use 5-class Devign scheme
    FULL_FILTERED = "full_filtered"  # Use 16 types (filter metadata edges)

# Choose your mode here:
DEFAULT_EDGE_MODE = EdgeTypeMode.FULL_FILTERED

# ============================================================================
# NODE CONFIGURATION (V9 - Complete from Schema Discovery)
# ============================================================================

# Nodes to KEEP in the graph (semantic content - have meaningful text)
# Total: 16 semantic node types
CORE_SEMANTIC_NODES = {
    # High frequency - critical for vulnerability detection
    "CALL",              # 1,829,810 nodes - Function calls (strcpy, malloc, etc.)
    "IDENTIFIER",        # 1,567,612 nodes - Variable/function names
    "BLOCK",             # 723,396 nodes - Code blocks
    "METHOD",            # 524,900 nodes - Function definitions
    "LITERAL",           # 472,697 nodes - Numbers, strings
    "FIELD_IDENTIFIER",  # 459,746 nodes - Struct field access
    "TYPE_DECL",         # 405,029 nodes - Type declarations
    "LOCAL",             # 284,174 nodes - Local variable declarations
    "CONTROL_STRUCTURE", # 239,960 nodes - if/while/for
    "JUMP_TARGET",       # 52,451 nodes - Jump targets (goto labels)
    "RETURN",            # 49,346 nodes - Return statements
    "METHOD_REF",        # 25,665 nodes - Method references
    
    # Low frequency but semantic
    "UNKNOWN",           # 4,039 nodes - Parser couldn't identify (has CODE)
    "MEMBER",            # 2 nodes - Class members (has CODE, NAME)
    "IMPORT",            # 21 nodes - Import statements (has CODE)
    "DEPENDENCY",        # 21 nodes - External dependencies (has NAME)
}

# Nodes to DISCARD (metadata/structural - no useful semantic text)
# Total: 12 structural node types
CORE_STRUCTURAL_NODES = {
    "METHOD_PARAMETER_IN",   # 903,596 nodes - Parameter metadata
    "METHOD_PARAMETER_OUT",  # 903,596 nodes - Parameter metadata
    "METHOD_RETURN",         # 524,900 nodes - Always "RET"
    "TYPE",                  # 348,731 nodes - Type nodes (in EVAL_TYPE edges)
    "FILE",                  # 110,932 nodes - File metadata
    "NAMESPACE_BLOCK",       # 110,932 nodes - Namespace metadata
    "NAMESPACE",             # 27,318 nodes - Namespace metadata
    "META_DATA",             # 27,318 nodes - Parser metadata
    "BINDING",               # 25,590 nodes - Binding metadata
    "CLOSURE_BINDING",       # 103 nodes - Closure binding metadata (REVEAL)
    "MODIFIER",              # 18,391 nodes - Access modifiers
    "TYPE_REF",              # 14,055 nodes - Type references
    "COMMENT",               # (if present) - Comments
    "ANNOTATION",            # (if present) - Annotations
}

# ============================================================================
# DYNAMIC EDGE MAPPING
# ============================================================================

def get_edge_types(mode: str = None) -> List[str]:
    """Get the list of edge types based on mode."""
    mode = mode or DEFAULT_EDGE_MODE
    
    if mode == EdgeTypeMode.FULL:
        return FULL_EDGE_TYPES
    elif mode == EdgeTypeMode.SIMPLIFIED:
        return SIMPLIFIED_EDGE_TYPES
    elif mode == EdgeTypeMode.FULL_FILTERED:
        # Full types but exclude metadata edges
        return [e for e in FULL_EDGE_TYPES 
                if e not in ("CONTAINS", "SOURCE_FILE")]
    else:
        return SIMPLIFIED_EDGE_TYPES


def map_edge_type(raw_edge: str, mode: str = None) -> Optional[str]:
    """Map a raw Joern edge type to the configured scheme."""
    mode = mode or DEFAULT_EDGE_MODE
    
    if mode == EdgeTypeMode.SIMPLIFIED:
        return FULL_TO_SIMPLIFIED_MAP.get(raw_edge)
    
    elif mode == EdgeTypeMode.FULL:
        if raw_edge in FULL_EDGE_TYPES:
            return raw_edge
        return _classify_unknown_edge(raw_edge)
    
    elif mode == EdgeTypeMode.FULL_FILTERED:
        if raw_edge in ("CONTAINS", "SOURCE_FILE"):
            return None
        if raw_edge in FULL_EDGE_TYPES:
            return raw_edge
        return _classify_unknown_edge(raw_edge)
    
    return None


def _classify_unknown_edge(edge_label: str) -> Optional[str]:
    """Classify unknown edge types based on patterns."""
    edge_upper = edge_label.upper()
    
    if "AST" in edge_upper or "ARGUMENT" in edge_upper:
        return "AST"
    if "CFG" in edge_upper or "FLOW" in edge_upper:
        return "CFG"
    if "DEF" in edge_upper or "WRITE" in edge_upper:
        return "REACHING_DEF"
    if "REF" in edge_upper or "READ" in edge_upper or "USE" in edge_upper:
        return "REF"
    if "DOMINATE" in edge_upper or "CDG" in edge_upper:
        return "CDG"
    if "TYPE" in edge_upper or "ALIAS" in edge_upper:
        return "EVAL_TYPE"
    if "RECEIVER" in edge_upper:
        return "RECEIVER"
    if "IMPORT" in edge_upper:
        return "IMPORTS"
    
    return None


# ============================================================================
# EDGE TYPE INDEX MAPPING (for PyG)
# ============================================================================

def get_edge_type_to_index(mode: str = None) -> Dict[str, int]:
    """Get mapping from edge type string to integer index."""
    edge_types = get_edge_types(mode)
    return {et: i for i, et in enumerate(edge_types)}


def get_index_to_edge_type(mode: str = None) -> Dict[int, str]:
    """Get mapping from integer index to edge type string."""
    edge_types = get_edge_types(mode)
    return {i: et for i, et in enumerate(edge_types)}


# ============================================================================
# NODE PROPERTY EXTRACTION (V9 - CRITICAL: CALL uses NAME first!)
# ============================================================================

LABEL_TO_PROPERTY_KEYS = {
    # ═══════════════════════════════════════════════════════════════════════
    # CRITICAL CHANGE IN V9: CALL now uses NAME first, not CODE!
    # 
    # Before (V8): CODE="Var1 = strcpy(Var2, Var3)" → different embeddings
    # After (V9):  NAME="strcpy" → consistent embeddings for same function
    #
    # This is essential for vulnerability detection because:
    #   - strcpy, malloc, free, etc. should have IDENTICAL embeddings
    #   - regardless of how they're called in different contexts
    # ═══════════════════════════════════════════════════════════════════════
    "CALL": ("NAME", "METHOD_FULL_NAME", "CODE", "SIGNATURE"),  # NAME FIRST!
    
    # Other high priority semantic nodes (unchanged)
    "IDENTIFIER": ("NAME", "CODE", "TYPE_FULL_NAME"),  # NAME first for identifiers too
    "LITERAL": ("CODE", "TYPE_FULL_NAME"),
    "FIELD_IDENTIFIER": ("CANONICAL_NAME", "CODE"),  # Canonical name preferred
    "METHOD": ("NAME", "FULL_NAME", "SIGNATURE", "CODE"),  # NAME first
    "METHOD_REF": ("METHOD_FULL_NAME", "CODE", "TYPE_FULL_NAME"),
    "CONTROL_STRUCTURE": ("CONTROL_STRUCTURE_TYPE", "CODE"),  # Type first (IF, WHILE, FOR)
    "BLOCK": ("CODE", "TYPE_FULL_NAME"),
    "RETURN": ("CODE",),
    "LOCAL": ("NAME", "CODE", "TYPE_FULL_NAME"),  # NAME first for locals
    "JUMP_TARGET": ("NAME", "CODE"),  # NAME first for labels
    "TYPE_DECL": ("NAME", "FULL_NAME", "CODE"),  # NAME first
    
    # New semantic nodes
    "UNKNOWN": ("CODE", "TYPE_FULL_NAME"),
    "MEMBER": ("NAME", "CODE", "TYPE_FULL_NAME"),  # NAME first
    "IMPORT": ("IMPORTED_ENTITY", "CODE"),  # What's imported
    "DEPENDENCY": ("NAME", "VERSION"),  # Dependency name
    
    # Structural nodes (for reference, usually filtered)
    "METHOD_PARAMETER_IN": ("NAME", "CODE", "TYPE_FULL_NAME"),
    "METHOD_PARAMETER_OUT": ("NAME", "CODE", "TYPE_FULL_NAME"),
    "METHOD_RETURN": ("TYPE_FULL_NAME", "CODE"),
    "TYPE": ("NAME", "FULL_NAME"),
    "TYPE_REF": ("TYPE_FULL_NAME", "CODE"),
    "FILE": ("NAME", "CODE"),
    "NAMESPACE": ("NAME", "CODE"),
    "NAMESPACE_BLOCK": ("NAME", "FULL_NAME", "CODE"),
    "BINDING": ("NAME", "METHOD_FULL_NAME", "SIGNATURE"),
    "MODIFIER": ("MODIFIER_TYPE", "CODE"),
    "META_DATA": ("LANGUAGE", "VERSION"),
}

FALLBACK_PROPERTY_KEYS = ("NAME", "CODE", "FULL_NAME")  # NAME first as fallback


def get_property_keys_for_label(node_label: str) -> Tuple[str, ...]:
    """Get property keys to extract text from a node type."""
    return LABEL_TO_PROPERTY_KEYS.get(node_label, FALLBACK_PROPERTY_KEYS)


# ============================================================================
# NODE FILTERING
# ============================================================================

def should_include_node_type(node_label: str) -> bool:
    """Determine if a node type should be included in the graph."""
    if node_label in CORE_SEMANTIC_NODES:
        return True
    if node_label in CORE_STRUCTURAL_NODES:
        return False
    
    label_upper = node_label.upper()
    
    exclude_patterns = [
        r".*_POSITION$", r".*_LOCATION$", r"^COMMENT$", 
        r"^ANNOTATION$"
    ]
    for pattern in exclude_patterns:
        if re.match(pattern, label_upper):
            return False
    
    include_patterns = [
        r".*CALL.*", r".*IDENTIFIER.*", r".*LITERAL.*",
        r".*TYPE_DECL.*", r".*FIELD.*", r".*CONTROL.*", r".*BLOCK.*",
        r".*LOCAL.*", r".*RETURN.*", r".*JUMP.*", r".*MEMBER.*",
        r".*IMPORT.*", r".*UNKNOWN.*"
    ]
    for pattern in include_patterns:
        if re.match(pattern, label_upper):
            return True
    
    return False


# ============================================================================
# SECURITY-SENSITIVE API CATEGORIES (NEW in V9)
# ============================================================================

# These are used by vulnerability detection models to identify risky patterns
SECURITY_SENSITIVE_APIS = {
    # Buffer operations (buffer overflow risks)
    "BUFFER": {
        "strcpy", "strcat", "sprintf", "vsprintf", "gets", "scanf",
        "strncpy", "strncat", "snprintf", "vsnprintf", "sscanf",
    },
    
    # Memory management (use-after-free, double-free, memory leaks)
    "MEMORY": {
        "malloc", "calloc", "realloc", "free", "alloca",
        "kmalloc", "kfree", "vmalloc", "vfree",
    },
    
    # Memory copy/set (buffer overflow, info disclosure)
    "MEMCPY": {
        "memcpy", "memmove", "memset", "memcmp", "bcopy", "bzero",
    },
    
    # Format string (format string vulnerabilities)
    "FORMAT": {
        "printf", "fprintf", "sprintf", "snprintf", "vprintf",
        "vfprintf", "vsprintf", "vsnprintf", "syslog",
    },
    
    # File operations (path traversal, race conditions)
    "FILE": {
        "open", "fopen", "read", "write", "close", "fclose",
        "fread", "fwrite", "lseek", "fseek", "stat", "fstat",
        "access", "chmod", "chown", "unlink", "remove", "rename",
    },
    
    # Command execution (command injection)
    "COMMAND": {
        "system", "exec", "execl", "execle", "execlp", "execv",
        "execve", "execvp", "popen", "pclose", "fork", "vfork",
    },
    
    # Integer operations (integer overflow)
    "INTEGER": {
        "atoi", "atol", "atoll", "strtol", "strtoll", "strtoul",
        "strtoull", "abs", "labs", "llabs",
    },
    
    # Network operations (various network vulnerabilities)
    "NETWORK": {
        "socket", "bind", "listen", "accept", "connect",
        "send", "recv", "sendto", "recvfrom", "sendmsg", "recvmsg",
        "read", "write", "select", "poll",
    },
    
    # Taint sources (user input entry points)
    "TAINT_SOURCE": {
        "recv", "recvfrom", "recvmsg", "read", "fread", "fgets",
        "gets", "scanf", "fscanf", "sscanf", "getenv", "getc",
        "fgetc", "getchar", "getline", "getdelim",
    },
}

def get_api_category(func_name: str) -> Optional[str]:
    """Get the security category of an API function."""
    func_lower = func_name.lower() if func_name else ""
    for category, apis in SECURITY_SENSITIVE_APIS.items():
        if func_lower in apis or func_name in apis:
            return category
    return None

def is_security_sensitive(func_name: str) -> bool:
    """Check if a function is security-sensitive."""
    return get_api_category(func_name) is not None


# ============================================================================
# CPG CONFIG CLASS
# ============================================================================

class CPGConfig:
    """Configuration class for CPG processing."""
    
    def __init__(self, 
                 edge_mode: str = DEFAULT_EDGE_MODE,
                 discovery_mode: str = "conservative",
                 enable_logging: bool = True,
                 logger: logging.Logger = None):
        
        self.edge_mode = edge_mode
        self.discovery_mode = discovery_mode
        self.enable_logging = enable_logging
        self.logger = logger or logging.getLogger(__name__)
        
        self.discovered_nodes: Set[str] = set()
        self.discovered_edges: Set[str] = set()
        
        self._build_config()
    
    def _build_config(self):
        self.node_whitelist = set(CORE_SEMANTIC_NODES)
        self.edge_types = get_edge_types(self.edge_mode)
        self.edge_to_index = get_edge_type_to_index(self.edge_mode)
        self.label_to_keys = dict(LABEL_TO_PROPERTY_KEYS)
    
    def should_include_node_type(self, node_label: str) -> bool:
        result = should_include_node_type(node_label)
        if result and node_label not in CORE_SEMANTIC_NODES:
            self.discovered_nodes.add(node_label)
        return result
    
    def map_edge_type(self, raw_edge: str) -> Optional[str]:
        result = map_edge_type(raw_edge, self.edge_mode)
        if result and raw_edge not in FULL_EDGE_TYPES:
            self.discovered_edges.add(raw_edge)
        return result
    
    def get_edge_index(self, edge_type: str) -> Optional[int]:
        mapped = self.map_edge_type(edge_type)
        if mapped:
            return self.edge_to_index.get(mapped)
        return None
    
    def get_property_keys_for_label(self, node_label: str) -> Tuple[str, ...]:
        return get_property_keys_for_label(node_label)
    
    def get_num_edge_types(self) -> int:
        return len(self.edge_types)
    
    def report_discoveries(self) -> Dict[str, Any]:
        return {
            "edge_mode": self.edge_mode,
            "edge_types": self.edge_types,
            "num_edge_types": len(self.edge_types),
            "discovered_nodes": list(self.discovered_nodes),
            "discovered_edges": list(self.discovered_edges),
        }


# ============================================================================
# GLOBAL INSTANCE & BACKWARD COMPATIBILITY
# ============================================================================

_global_config = CPGConfig(edge_mode=DEFAULT_EDGE_MODE)

NODE_LABEL_WHITELIST = _global_config.node_whitelist
LABEL_TO_KEYS = _global_config.label_to_keys
DEVIGN_EDGE_MAP = FULL_TO_SIMPLIFIED_MAP
DEVIGN_ORDER = SIMPLIFIED_EDGE_TYPES

def map_edge_type_to_devign(edge_label: str) -> Optional[str]:
    return map_edge_type(edge_label, EdgeTypeMode.SIMPLIFIED)

def track_edge_frequency(*args): pass
def track_node_type_stats(*args): pass
def auto_promote_discovered_edges(*args): return False
def auto_promote_discovered_nodes(*args): return False
def get_promotable_edges(): return {}
def get_promotable_nodes(): return {"semantic": set(), "structural": set()}
def get_discovery_report(): return _global_config.report_discoveries()

def configure_cpg(edge_mode: str = None, 
                  discovery_mode: str = "conservative",
                  enable_logging: bool = True,
                  logger: logging.Logger = None):
    global _global_config
    _global_config = CPGConfig(
        edge_mode=edge_mode or DEFAULT_EDGE_MODE,
        discovery_mode=discovery_mode,
        enable_logging=enable_logging,
        logger=logger
    )
    return _global_config

configure_discovery = configure_cpg


# ============================================================================
# UTILITY FUNCTIONS
# ============================================================================

def print_edge_config():
    print("=" * 60)
    print("CPG EDGE TYPE CONFIGURATION (V9)")
    print("=" * 60)
    print(f"\nMode: {DEFAULT_EDGE_MODE}")
    print(f"\nEdge Types ({len(get_edge_types())}):")
    for i, et in enumerate(get_edge_types()):
        print(f"  {i}: {et}")
    print()


def print_node_config():
    print("=" * 60)
    print("CPG NODE TYPE CONFIGURATION (V9)")
    print("=" * 60)
    print(f"\nSemantic Nodes (KEEP): {len(CORE_SEMANTIC_NODES)}")
    for n in sorted(CORE_SEMANTIC_NODES):
        print(f"  ✅ {n}")
    print(f"\nStructural Nodes (DISCARD): {len(CORE_STRUCTURAL_NODES)}")
    for n in sorted(CORE_STRUCTURAL_NODES):
        print(f"  ❌ {n}")
    print()


def print_property_priority():
    """Print property extraction priority for each node type."""
    print("=" * 70)
    print("NODE PROPERTY EXTRACTION PRIORITY (V9)")
    print("=" * 70)
    print("\n⚠️  CRITICAL CHANGE: CALL nodes now use NAME first, not CODE!")
    print()
    for label in sorted(LABEL_TO_PROPERTY_KEYS.keys()):
        keys = LABEL_TO_PROPERTY_KEYS[label]
        if label in CORE_SEMANTIC_NODES:
            marker = "✅"
        elif label in CORE_STRUCTURAL_NODES:
            marker = "❌"
        else:
            marker = "  "
        print(f"  {marker} {label:25}: {keys}")
    print()


def print_summary():
    """Print a complete summary of the configuration."""
    print("=" * 70)
    print("CPG CONFIGURATION V9 - CALL NODE FIX")
    print("=" * 70)
    print(f"\nBased on scan of 27,318 GraphSON files")
    print(f"Total nodes in dataset: 9,654,228")
    print(f"Total edges in dataset: 68,213,212")
    print()
    
    print("-" * 70)
    print("CRITICAL CHANGE IN V9")
    print("-" * 70)
    print("CALL nodes now use NAME first instead of CODE!")
    print("  Before: CODE='Var1 = strcpy(Var2, Var3)' → inconsistent embeddings")
    print("  After:  NAME='strcpy' → consistent embeddings for same function")
    print()
    
    print("-" * 70)
    print("EDGE TYPES")
    print("-" * 70)
    print(f"Full mode:          {len(FULL_EDGE_TYPES)} edge types")
    print(f"Full filtered mode: {len([e for e in FULL_EDGE_TYPES if e not in ('CONTAINS', 'SOURCE_FILE')])} edge types")
    print(f"Simplified mode:    {len(SIMPLIFIED_EDGE_TYPES)} edge types")
    print()
    
    print("-" * 70)
    print("NODE TYPES")
    print("-" * 70)
    print(f"Semantic nodes:    {len(CORE_SEMANTIC_NODES)} types (KEEP)")
    print(f"Structural nodes:  {len(CORE_STRUCTURAL_NODES)} types (DISCARD)")
    print()
    
    print("-" * 70)
    print("SECURITY-SENSITIVE APIs")
    print("-" * 70)
    for category, apis in SECURITY_SENSITIVE_APIS.items():
        print(f"  {category:12}: {len(apis)} functions")
    print()


if __name__ == "__main__":
    print_summary()
    print()
    print_property_priority()
    print()
    print_edge_config()
    print_node_config()
    
    print("=" * 60)
    print("EDGE MAPPING TEST")
    print("=" * 60)
    test_edges = ["AST", "CFG", "REACHING_DEF", "EVAL_TYPE", "CDG", 
                  "DOMINATE", "ARGUMENT", "CALL", "CONTAINS", "ALIAS_OF",
                  "RECEIVER", "IMPORTS"]
    
    for edge in test_edges:
        mapped = map_edge_type(edge)
        idx = _global_config.get_edge_index(edge)
        print(f"  {edge:20} -> {str(mapped):15} (index: {idx})")
    
    print("\n" + "=" * 60)
    print("NODE FILTERING TEST")
    print("=" * 60)
    test_nodes = ["CALL", "IDENTIFIER", "METHOD_RETURN", "METHOD_PARAMETER_IN", 
                  "RETURN", "BLOCK", "FILE", "COMMENT", "JUMP_TARGET", "MODIFIER",
                  "UNKNOWN", "MEMBER", "IMPORT", "DEPENDENCY"]
    
    for node in test_nodes:
        included = should_include_node_type(node)
        status = "✅ KEEP" if included else "❌ DISCARD"
        print(f"  {node:25} -> {status}")
    
    print("\n" + "=" * 60)
    print("SECURITY API TEST")
    print("=" * 60)
    test_apis = ["strcpy", "malloc", "free", "printf", "system", "read", "write",
                 "qemu_opt_get", "unknown_func"]
    
    for api in test_apis:
        category = get_api_category(api)
        is_sensitive = is_security_sensitive(api)
        status = f"⚠️  {category}" if is_sensitive else "   (not sensitive)"
        print(f"  {api:20} -> {status}")
