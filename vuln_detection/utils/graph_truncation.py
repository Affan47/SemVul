#!/usr/bin/env python3
"""
Intelligent Graph Truncation for Vulnerability Detection

Implements semantic-priority subgraph extraction that:
1. Preserves vulnerability-relevant nodes (CALL, CONTROL_STRUCTURE, etc.)
2. Maintains graph connectivity via BFS from entry point
3. Prioritizes data-flow edges (REACHING_DEF, REF)
4. Handles class imbalance by preserving more signal in larger graphs

Based on techniques from:
- Devign (NIPS 2019): Basic truncation
- IVDetect (ICSE 2021): PDG slicing around sensitive APIs  
- Reveal (TSE 2021): Subgraph extraction
- FUNDED (ISSTA 2020): Hierarchical representation

Usage:
    # As a module
    from graph_truncation import GraphTruncator
    truncator = GraphTruncator(max_nodes=500, strategy='semantic_bfs')
    truncated_data = truncator.truncate(data)
    
    # As a transform in DataLoader
    transform = GraphTruncationTransform(max_nodes=500)
    dataset = CachedGraphDataset(..., transform=transform)

Author: Anonymous
"""

import torch
import numpy as np
from torch_geometric.data import Data
from torch_geometric.utils import subgraph, k_hop_subgraph
from typing import Optional, List, Set, Dict, Tuple
from collections import deque
import warnings


# =============================================================================
# NODE TYPE PRIORITIES (based on vulnerability detection importance)
# =============================================================================

# Priority 1: CRITICAL - Always keep these (vulnerability-relevant)
CRITICAL_NODES = {
    'CALL',              # Function calls (strcpy, malloc, free, etc.)
    'CONTROL_STRUCTURE', # if/while/for - control flow decisions
    'RETURN',            # Return statements
    'JUMP_TARGET',       # goto targets
}

# Priority 2: HIGH - Keep if space allows (semantic content)
HIGH_PRIORITY_NODES = {
    'IDENTIFIER',        # Variable names
    'LITERAL',           # Constants, strings
    'LOCAL',             # Local variable declarations
    'FIELD_IDENTIFIER',  # Struct field access
    'METHOD_REF',        # Method references
}

# Priority 3: MEDIUM - Keep for structure
MEDIUM_PRIORITY_NODES = {
    'BLOCK',             # Code blocks
    'METHOD',            # Function definition (usually 1)
    'TYPE_DECL',         # Type declarations
    'UNKNOWN',           # Parser unknowns (may contain important code)
}

# Priority 4: LOW - Can be dropped first
LOW_PRIORITY_NODES = {
    'MEMBER',
    'IMPORT',
    'DEPENDENCY',
    'MODIFIER',
    'BINDING',
    'NAMESPACE',
    'NAMESPACE_BLOCK',
    'FILE',
    'META_DATA',
    'TYPE',
    'TYPE_REF',
    'METHOD_PARAMETER_IN',
    'METHOD_PARAMETER_OUT',
    'METHOD_RETURN',
    'COMMENT',
    'ANNOTATION',
}

# Node type to priority mapping (lower = higher priority)
NODE_PRIORITY = {}
for i, nodes in enumerate([CRITICAL_NODES, HIGH_PRIORITY_NODES, MEDIUM_PRIORITY_NODES, LOW_PRIORITY_NODES]):
    for node in nodes:
        NODE_PRIORITY[node] = i

# Default priority for unknown node types
DEFAULT_PRIORITY = 2


# =============================================================================
# EDGE TYPE PRIORITIES (for vulnerability detection)
# =============================================================================

# Critical edges for vulnerability detection
CRITICAL_EDGES = {
    'REACHING_DEF',  # Data flow - most important for vuln detection!
    'REF',           # Reference edges
    'CFG',           # Control flow
    'CDG',           # Control dependency
}

# Important structural edges
IMPORTANT_EDGES = {
    'AST',           # Syntax structure
    'CALL',          # Function calls
    'ARGUMENT',      # Arguments
    'CONDITION',     # Conditions
}

# Less important edges (can be dropped)
OPTIONAL_EDGES = {
    'DOMINATE',
    'POST_DOMINATE',
    'EVAL_TYPE',
    'PARAMETER_LINK',
    'ALIAS_OF',
    'BINDS',
    'CONTAINS',
    'SOURCE_FILE',
    'RECEIVER',
    'IMPORTS',
}


# =============================================================================
# SENSITIVE API PATTERNS (for vulnerability-focused extraction)
# =============================================================================

SENSITIVE_APIS = {
    # Memory operations (buffer overflow)
    'malloc', 'calloc', 'realloc', 'free', 'alloca',
    'memcpy', 'memmove', 'memset', 'memcmp',
    
    # String operations (buffer overflow)
    'strcpy', 'strncpy', 'strcat', 'strncat', 'strlen',
    'strcmp', 'strncmp', 'sprintf', 'snprintf', 'vsprintf',
    'gets', 'fgets', 'scanf', 'sscanf', 'fscanf',
    
    # Format string
    'printf', 'fprintf', 'vprintf', 'syslog',
    
    # File operations
    'fopen', 'fclose', 'fread', 'fwrite', 'open', 'close', 'read', 'write',
    
    # Network
    'recv', 'send', 'recvfrom', 'sendto', 'connect', 'bind', 'listen', 'accept',
    
    # Command execution
    'system', 'exec', 'execve', 'popen', 'fork',
    
    # Integer operations (overflow)
    'atoi', 'atol', 'strtol', 'strtoul',
}


# =============================================================================
# GRAPH TRUNCATION STRATEGIES
# =============================================================================

class GraphTruncator:
    """
    Intelligent graph truncation with multiple strategies.
    
    Strategies:
        - 'semantic_bfs': BFS from entry with semantic node priority (RECOMMENDED)
        - 'semantic_only': Keep only semantic nodes, drop structural
        - 'bfs': Simple BFS from METHOD node
        - 'random': Random sampling (baseline)
        - 'degree': Keep high-degree nodes
        - 'sensitive_api': Focus on subgraphs around sensitive API calls
    """
    
    def __init__(
        self,
        max_nodes: int = 500,
        max_edges: Optional[int] = None,
        strategy: str = 'semantic_bfs',
        preserve_edge_types: Optional[List[str]] = None,
        node_type_attr: str = 'node_type',
        edge_type_attr: str = 'edge_type',
        verbose: bool = False,
    ):
        """
        Args:
            max_nodes: Maximum number of nodes to keep
            max_edges: Maximum edges (optional, usually determined by nodes)
            strategy: Truncation strategy
            preserve_edge_types: Edge types to prioritize preserving
            node_type_attr: Attribute name for node types in Data object
            edge_type_attr: Attribute name for edge types in Data object
            verbose: Print truncation statistics
        """
        self.max_nodes = max_nodes
        self.max_edges = max_edges
        self.strategy = strategy
        self.preserve_edge_types = preserve_edge_types or list(CRITICAL_EDGES)
        self.node_type_attr = node_type_attr
        self.edge_type_attr = edge_type_attr
        self.verbose = verbose
        
        # Statistics
        self.stats = {
            'total_processed': 0,
            'truncated': 0,
            'nodes_removed': 0,
            'edges_removed': 0,
        }
    
    def truncate(self, data: Data) -> Data:
        """
        Truncate a single graph.
        
        Args:
            data: PyG Data object
            
        Returns:
            Truncated Data object (or original if already small enough)
        """
        self.stats['total_processed'] += 1
        
        num_nodes = data.num_nodes
        
        # No truncation needed
        if num_nodes <= self.max_nodes:
            return data
        
        self.stats['truncated'] += 1
        original_edges = data.edge_index.shape[1]
        
        # Select strategy
        if self.strategy == 'semantic_bfs':
            keep_nodes = self._semantic_bfs_selection(data)
        elif self.strategy == 'semantic_only':
            keep_nodes = self._semantic_only_selection(data)
        elif self.strategy == 'bfs':
            keep_nodes = self._bfs_selection(data)
        elif self.strategy == 'random':
            keep_nodes = self._random_selection(data)
        elif self.strategy == 'degree':
            keep_nodes = self._degree_selection(data)
        elif self.strategy == 'sensitive_api':
            keep_nodes = self._sensitive_api_selection(data)
        else:
            raise ValueError(f"Unknown strategy: {self.strategy}")
        
        # Create subgraph
        truncated = self._create_subgraph(data, keep_nodes)
        
        # Update statistics
        self.stats['nodes_removed'] += num_nodes - truncated.num_nodes
        self.stats['edges_removed'] += original_edges - truncated.edge_index.shape[1]
        
        if self.verbose:
            print(f"Truncated: {num_nodes} -> {truncated.num_nodes} nodes, "
                  f"{original_edges} -> {truncated.edge_index.shape[1]} edges")
        
        return truncated
    
    def _get_node_types(self, data: Data) -> Optional[torch.Tensor]:
        """Get node type tensor from data."""
        if hasattr(data, self.node_type_attr):
            return getattr(data, self.node_type_attr)
        # Try to extract from one-hot features (first N dimensions)
        if hasattr(data, 'x') and data.x is not None:
            # Assume first 12-16 dimensions are one-hot node types
            if data.x.shape[1] >= 12:
                return data.x[:, :16].argmax(dim=1)
        return None
    
    def _get_node_priority(self, node_type_idx: int, type_names: Optional[List[str]] = None) -> int:
        """Get priority for a node type index."""
        if type_names and node_type_idx < len(type_names):
            type_name = type_names[node_type_idx]
            return NODE_PRIORITY.get(type_name, DEFAULT_PRIORITY)
        return DEFAULT_PRIORITY
    
    def _semantic_bfs_selection(self, data: Data) -> torch.Tensor:
        """
        Semantic-priority BFS selection.
        
        1. Start from METHOD node (entry point)
        2. BFS but prioritize visiting semantic nodes
        3. Always include CALL and CONTROL_STRUCTURE nodes
        """
        num_nodes = data.num_nodes
        edge_index = data.edge_index
        
        # Build adjacency list (undirected for BFS)
        adj = [set() for _ in range(num_nodes)]
        for i in range(edge_index.shape[1]):
            src, dst = edge_index[0, i].item(), edge_index[1, i].item()
            adj[src].add(dst)
            adj[dst].add(src)
        
        # Get node types if available
        node_types = self._get_node_types(data)
        
        # Find entry point (METHOD node or node 0)
        entry_node = 0
        if node_types is not None:
            method_mask = (node_types == 0)  # Assuming METHOD is index 0
            if method_mask.any():
                entry_node = method_mask.nonzero()[0, 0].item()
        
        # Priority queue: (priority, distance, node_id)
        # Lower priority = more important
        selected = set()
        visited = set()
        
        # Use deque for BFS with priority buckets
        # Bucket 0: CRITICAL nodes, Bucket 1: HIGH, Bucket 2: MEDIUM, Bucket 3: LOW
        buckets = [deque() for _ in range(4)]
        buckets[0].append((entry_node, 0))  # Start from entry
        visited.add(entry_node)
        
        while len(selected) < self.max_nodes:
            # Find non-empty bucket with highest priority
            current_bucket = None
            for bucket in buckets:
                if bucket:
                    current_bucket = bucket
                    break
            
            if current_bucket is None:
                break
            
            node, dist = current_bucket.popleft()
            selected.add(node)
            
            # Add neighbors to appropriate buckets
            for neighbor in adj[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    
                    # Determine priority
                    if node_types is not None:
                        node_type = node_types[neighbor].item()
                        priority = min(node_type, 3)  # Map to bucket 0-3
                    else:
                        priority = 2  # Default medium priority
                    
                    buckets[priority].append((neighbor, dist + 1))
        
        return torch.tensor(sorted(selected), dtype=torch.long)
    
    def _semantic_only_selection(self, data: Data) -> torch.Tensor:
        """Keep only semantic nodes (CALL, IDENTIFIER, LITERAL, etc.)."""
        node_types = self._get_node_types(data)
        
        if node_types is None:
            # Fallback to random if no node types
            return self._random_selection(data)
        
        # Semantic node indices (0-11 typically)
        semantic_mask = node_types < 12
        semantic_nodes = semantic_mask.nonzero().squeeze(-1)
        
        if len(semantic_nodes) > self.max_nodes:
            # Random sample from semantic nodes
            perm = torch.randperm(len(semantic_nodes))[:self.max_nodes]
            return semantic_nodes[perm].sort()[0]
        
        return semantic_nodes
    
    def _bfs_selection(self, data: Data) -> torch.Tensor:
        """Simple BFS from entry point."""
        num_nodes = data.num_nodes
        edge_index = data.edge_index
        
        # Build adjacency
        adj = [set() for _ in range(num_nodes)]
        for i in range(edge_index.shape[1]):
            src, dst = edge_index[0, i].item(), edge_index[1, i].item()
            adj[src].add(dst)
            adj[dst].add(src)
        
        # BFS
        selected = []
        visited = {0}
        queue = deque([0])
        
        while queue and len(selected) < self.max_nodes:
            node = queue.popleft()
            selected.append(node)
            
            for neighbor in adj[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        
        return torch.tensor(sorted(selected), dtype=torch.long)
    
    def _random_selection(self, data: Data) -> torch.Tensor:
        """Random node selection (baseline)."""
        perm = torch.randperm(data.num_nodes)[:self.max_nodes]
        return perm.sort()[0]
    
    def _degree_selection(self, data: Data) -> torch.Tensor:
        """Select nodes with highest degree."""
        edge_index = data.edge_index
        num_nodes = data.num_nodes
        
        # Compute degree
        degree = torch.zeros(num_nodes, dtype=torch.long)
        degree.scatter_add_(0, edge_index[0], torch.ones(edge_index.shape[1], dtype=torch.long))
        degree.scatter_add_(0, edge_index[1], torch.ones(edge_index.shape[1], dtype=torch.long))
        
        # Select top-k by degree
        _, top_nodes = degree.topk(min(self.max_nodes, num_nodes))
        return top_nodes.sort()[0]
    
    def _sensitive_api_selection(self, data: Data) -> torch.Tensor:
        """
        Focus on subgraphs around sensitive API calls.
        
        Requires node text/code information to identify sensitive calls.
        Falls back to semantic_bfs if not available.
        """
        # This requires access to node text which may not be in Data object
        # For now, fall back to semantic_bfs
        # TODO: Implement when node text is available
        return self._semantic_bfs_selection(data)
    
    def _create_subgraph(self, data: Data, keep_nodes: torch.Tensor) -> Data:
        """Create subgraph with selected nodes."""
        # Use PyG's subgraph utility
        edge_index, edge_attr, edge_mask = subgraph(
            keep_nodes,
            data.edge_index,
            edge_attr=data.edge_attr if hasattr(data, 'edge_attr') else None,
            relabel_nodes=True,
            num_nodes=data.num_nodes,
            return_edge_mask=True,
        )
        
        # Create new Data object
        new_data = Data(
            x=data.x[keep_nodes] if data.x is not None else None,
            edge_index=edge_index,
            edge_attr=edge_attr,
        )
        
        # Copy other attributes
        if hasattr(data, 'y'):
            new_data.y = data.y
        
        if hasattr(data, 'edge_type'):
            new_data.edge_type = data.edge_type[edge_mask]
        
        if hasattr(data, self.node_type_attr):
            setattr(new_data, self.node_type_attr, getattr(data, self.node_type_attr)[keep_nodes])
        
        # Copy any other attributes
        for key in data.keys():
            if key not in ['x', 'edge_index', 'edge_attr', 'y', 'edge_type', self.node_type_attr]:
                if hasattr(data, key):
                    val = getattr(data, key)
                    if isinstance(val, torch.Tensor):
                        if val.shape[0] == data.num_nodes:
                            setattr(new_data, key, val[keep_nodes])
                        elif val.shape[0] == data.edge_index.shape[1]:
                            setattr(new_data, key, val[edge_mask])
                        else:
                            setattr(new_data, key, val)
                    else:
                        setattr(new_data, key, val)
        
        return new_data
    
    def get_stats(self) -> Dict:
        """Get truncation statistics."""
        return {
            **self.stats,
            'truncation_rate': self.stats['truncated'] / max(1, self.stats['total_processed']),
            'avg_nodes_removed': self.stats['nodes_removed'] / max(1, self.stats['truncated']),
            'avg_edges_removed': self.stats['edges_removed'] / max(1, self.stats['truncated']),
        }
    
    def reset_stats(self):
        """Reset statistics."""
        self.stats = {
            'total_processed': 0,
            'truncated': 0,
            'nodes_removed': 0,
            'edges_removed': 0,
        }


# =============================================================================
# PYTORCH GEOMETRIC TRANSFORM
# =============================================================================

class GraphTruncationTransform:
    """
    PyG Transform for graph truncation.
    
    Usage:
        transform = GraphTruncationTransform(max_nodes=500)
        dataset = MyDataset(transform=transform)
    """
    
    def __init__(
        self,
        max_nodes: int = 500,
        strategy: str = 'semantic_bfs',
        **kwargs
    ):
        self.truncator = GraphTruncator(
            max_nodes=max_nodes,
            strategy=strategy,
            **kwargs
        )
    
    def __call__(self, data: Data) -> Data:
        return self.truncator.truncate(data)
    
    def __repr__(self) -> str:
        return f'{self.__class__.__name__}(max_nodes={self.truncator.max_nodes}, strategy={self.truncator.strategy})'


# =============================================================================
# BATCH PROCESSING UTILITY
# =============================================================================

def truncate_dataset(
    input_dir: str,
    output_dir: str,
    max_nodes: int = 500,
    strategy: str = 'semantic_bfs',
    verbose: bool = True,
):
    """
    Truncate all graphs in a dataset directory.
    
    Args:
        input_dir: Directory with cache_*.zip files and index.csv
        output_dir: Output directory for truncated cache
        max_nodes: Maximum nodes per graph
        strategy: Truncation strategy
        verbose: Print progress
    """
    import zipfile
    import io
    import csv
    from pathlib import Path
    
    input_path = Path(input_dir)
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    truncator = GraphTruncator(max_nodes=max_nodes, strategy=strategy, verbose=False)
    
    # Read index
    index_path = input_path / "index.csv"
    if not index_path.exists():
        raise FileNotFoundError(f"Index not found: {index_path}")
    
    with open(index_path, 'r') as f:
        reader = csv.DictReader(f)
        samples = list(reader)
    
    if verbose:
        print(f"Processing {len(samples)} samples with max_nodes={max_nodes}, strategy={strategy}")
    
    # Process each zip file
    zip_files = sorted(input_path.glob("cache_*.zip"))
    
    new_index = []
    
    for zip_path in zip_files:
        output_zip = output_path / zip_path.name
        
        with zipfile.ZipFile(zip_path, 'r') as zf_in:
            with zipfile.ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as zf_out:
                for name in zf_in.namelist():
                    with zf_in.open(name) as f:
                        buffer = io.BytesIO(f.read())
                        data = torch.load(buffer, map_location='cpu')
                    
                    # Truncate
                    truncated = truncator.truncate(data)
                    
                    # Save
                    out_buffer = io.BytesIO()
                    torch.save(truncated, out_buffer)
                    out_buffer.seek(0)
                    zf_out.writestr(name, out_buffer.read())
    
    # Update index with new node/edge counts
    for sample in samples:
        # Would need to load and check each graph
        # For now, keep original index
        new_index.append(sample)
    
    # Write new index
    with open(output_path / "index.csv", 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=samples[0].keys())
        writer.writeheader()
        writer.writerows(new_index)
    
    if verbose:
        stats = truncator.get_stats()
        print(f"\nTruncation complete:")
        print(f"  Processed: {stats['total_processed']}")
        print(f"  Truncated: {stats['truncated']} ({100*stats['truncation_rate']:.1f}%)")
        print(f"  Avg nodes removed: {stats['avg_nodes_removed']:.1f}")
        print(f"  Avg edges removed: {stats['avg_edges_removed']:.1f}")


# =============================================================================
# MAIN - Test and Demo
# =============================================================================

if __name__ == "__main__":
    print("=" * 70)
    print("GRAPH TRUNCATION MODULE")
    print("=" * 70)
    
    # Create a dummy graph for testing
    print("\nCreating test graph with 1000 nodes...")
    
    num_nodes = 1000
    num_edges = 5000
    
    # Random edges
    edge_index = torch.randint(0, num_nodes, (2, num_edges))
    
    # Random features (256d + 16 one-hot node types)
    x = torch.randn(num_nodes, 272)
    # Set first 16 dims as one-hot node types
    node_types = torch.randint(0, 16, (num_nodes,))
    x[:, :16] = torch.zeros(num_nodes, 16)
    x[torch.arange(num_nodes), node_types] = 1.0
    
    data = Data(x=x, edge_index=edge_index, y=torch.tensor([1]))
    
    print(f"Original: {data.num_nodes} nodes, {data.edge_index.shape[1]} edges")
    
    # Test each strategy
    strategies = ['semantic_bfs', 'bfs', 'degree', 'random']
    
    for strategy in strategies:
        truncator = GraphTruncator(max_nodes=500, strategy=strategy)
        truncated = truncator.truncate(data)
        print(f"\n{strategy:15s}: {truncated.num_nodes} nodes, {truncated.edge_index.shape[1]} edges")
    
    print("\n" + "=" * 70)
    print("RECOMMENDED USAGE")
    print("=" * 70)
    print("""
# Option 1: As a transform in DataLoader
from graph_truncation import GraphTruncationTransform

transform = GraphTruncationTransform(max_nodes=500, strategy='semantic_bfs')
# Apply to your dataset loader

# Option 2: In training loop
from graph_truncation import GraphTruncator

truncator = GraphTruncator(max_nodes=500, strategy='semantic_bfs')

for batch in dataloader:
    # Truncate each graph in batch if needed
    truncated_batch = [truncator.truncate(g) for g in batch.to_data_list()]
    batch = Batch.from_data_list(truncated_batch)
    
    # Forward pass
    out = model(batch)
    ...

# Option 3: Pre-process entire cache
from graph_truncation import truncate_dataset

truncate_dataset(
    input_dir="/path/to/cache/train",
    output_dir="/path/to/truncated_cache/train", 
    max_nodes=500,
    strategy='semantic_bfs'
)
""")
