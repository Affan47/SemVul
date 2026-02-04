#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
graphson_parser.py - V2 GraphSON/CPG Parser and Schema Discovery (Devign/REVEAL/Draper/PrimeVul)

NEW in V2 - SCHEMA DISCOVERY MODE:
  - Scans ALL GraphSON files from manifests
  - Discovers ALL unique node types and edge types across entire dataset
  - Finds all property keys for each node type
  - Generates updated cpg_config.py code
  - Identifies missing types not in current configuration

Features:
- Auto-detects GraphSON schema (TinkerPop format)
- Extracts node/edge types and properties
- Generates human-readable .txt report
- Generates structured .json output
- Provides schema summary and statistics
- Full dataset schema discovery

Usage:
    # Single file analysis (original mode)
    python graphson_parser.py --input /path/to/export.json --output-dir ./analysis
    
    # FULL DATASET SCHEMA DISCOVERY
    python graphson_parser.py --discover \\
        --manifests manifest_train.csv manifest_val.csv manifest_test.csv \\
        --json-roots /path/to/train /path/to/val /path/to/test \\
        --output-dir ./schema_discovery

    # REVEAL preset (uses standard paths if available)
    python graphson_parser.py --discover --dataset reveal

    # DRAPER preset (uses standard paths if available)
    python graphson_parser.py --discover --dataset draper

    # PRIMEVUL preset (uses standard paths if available)
    python graphson_parser.py --discover --dataset primevul
    
Output files:
    - analysis_report.txt      : Human-readable report
    - analysis_data.json       : Structured JSON data
    - schema_summary.json      : Schema detection results
    - discovered_schema.json   : Full schema discovery
    - cpg_config_update.py     : Generated config code
"""

import json
import argparse
import csv
import importlib.util
import os
import sys
from pathlib import Path
from collections import defaultdict, Counter
from typing import Any, Dict, List, Optional, Tuple, Set
from datetime import datetime
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor, as_completed
import multiprocessing

# TQDM (graceful fallback)
try:
    from tqdm import tqdm
except ImportError:
    def tqdm(iterable=None, *a, **k):
        return iterable if iterable is not None else range(0)


# =============================================================================
# DEFAULTS + DATASET PRESETS
# =============================================================================

DEFAULT_CPG_CONFIG_PATH = Path(
    "./Clean_exports/cpg_config.py"
)

DEFAULT_COMPARE_CONFIG = {
    "semantic_nodes": {
        "CALL",
        "IDENTIFIER",
        "BLOCK",
        "METHOD",
        "LITERAL",
        "FIELD_IDENTIFIER",
        "TYPE_DECL",
        "LOCAL",
        "CONTROL_STRUCTURE",
        "JUMP_TARGET",
        "RETURN",
        "METHOD_REF",
        "UNKNOWN",
        "MEMBER",
        "IMPORT",
        "DEPENDENCY",
    },
    "structural_nodes": {
        "METHOD_PARAMETER_IN",
        "METHOD_PARAMETER_OUT",
        "METHOD_RETURN",
        "TYPE",
        "FILE",
        "NAMESPACE_BLOCK",
        "NAMESPACE",
        "META_DATA",
        "BINDING",
        "MODIFIER",
        "TYPE_REF",
        "COMMENT",
        "ANNOTATION",
    },
    "edge_types": {
        "REACHING_DEF",
        "AST",
        "EVAL_TYPE",
        "CFG",
        "POST_DOMINATE",
        "DOMINATE",
        "CDG",
        "ARGUMENT",
        "REF",
        "CALL",
        "PARAMETER_LINK",
        "CONDITION",
        "ALIAS_OF",
        "BINDS",
        "RECEIVER",
        "IMPORTS",
        "CONTAINS",
        "SOURCE_FILE",
    },
    "source": "builtin",
}

DATASET_PRESETS = {
    "reveal": {
        "manifests": [
            Path(
                "./workspace/"
                "03_PerFunction_datasets/reveal_functions/manifest_train.csv"
            ),
            Path(
                "./workspace/"
                "03_PerFunction_datasets/reveal_functions/manifest_validation.csv"
            ),
            Path(
                "./workspace/"
                "03_PerFunction_datasets/reveal_functions/manifest_test.csv"
            ),
        ],
        "json_roots": [
            Path(
                "./CPGs/"
                "reveal_functions/train"
            ),
            Path(
                "./CPGs/"
                "reveal_functions/validation"
            ),
            Path(
                "./CPGs/"
                "reveal_functions/test"
            ),
        ],
        "scan_dir": Path(
            "./CPGs/reveal_functions"
        ),
        "output_dir": Path(
            "./Clean_exports/"
            "schema_discovery_reveal"
        ),
        "config_path": DEFAULT_CPG_CONFIG_PATH,
    },
    "devign": {
        "manifests": [
            Path(
                "./workspace/"
                "03_PerFunction_datasets/original_devign_functions/manifest_train.csv"
            ),
            Path(
                "./workspace/"
                "03_PerFunction_datasets/original_devign_functions/manifest_validation.csv"
            ),
            Path(
                "./workspace/"
                "03_PerFunction_datasets/original_devign_functions/manifest_test.csv"
            ),
        ],
        "json_roots": [
            Path(
                "./CPGs/"
                "original_devign_functions/train"
            ),
            Path(
                "./CPGs/"
                "original_devign_functions/validation"
            ),
            Path(
                "./CPGs/"
                "original_devign_functions/test"
            ),
        ],
        "scan_dir": Path(
            "./CPGs/original_devign_functions"
        ),
        "output_dir": Path(
            "./Clean_exports/"
            "schema_discovery_devign"
        ),
        "config_path": DEFAULT_CPG_CONFIG_PATH,
    },
    "draper": {
        "manifests": [
            Path(
                "./workspace/"
                "03_PerFunction_datasets/draper_functions/manifest_train.csv"
            ),
            Path(
                "./workspace/"
                "03_PerFunction_datasets/draper_functions/manifest_validation.csv"
            ),
            Path(
                "./workspace/"
                "03_PerFunction_datasets/draper_functions/manifest_test.csv"
            ),
        ],
        "json_roots": [
            Path(
                "./CPGs/"
                "draper_functions/train"
            ),
            Path(
                "./CPGs/"
                "draper_functions/validation"
            ),
            Path(
                "./CPGs/"
                "draper_functions/test"
            ),
        ],
        "scan_dir": Path(
            "./CPGs/draper_functions"
        ),
        "output_dir": Path(
            "./Clean_exports/"
            "schema_discovery_draper"
        ),
        "config_path": DEFAULT_CPG_CONFIG_PATH,
    },
    "primevul": {
        "manifests": [
            Path(
                "./workspace/03_PerFunction_datasets/"
                "primevul_functions/manifest_train.csv"
            ),
            Path(
                "./workspace/03_PerFunction_datasets/"
                "primevul_functions/manifest_validation.csv"
            ),
            Path(
                "./workspace/03_PerFunction_datasets/"
                "primevul_functions/manifest_test.csv"
            ),
        ],
        "json_roots": [
            Path(
                "./CPGs/"
                "primevul_functions/train"
            ),
            Path(
                "./CPGs/"
                "primevul_functions/validation"
            ),
            Path(
                "./CPGs/"
                "primevul_functions/test"
            ),
        ],
        "scan_dir": Path(
            "./CPGs/primevul_functions"
        ),
        "output_dir": Path(
            "./Clean_exports/"
            "schema_discovery_primevul"
        ),
        "config_path": DEFAULT_CPG_CONFIG_PATH,
    },
}


def load_compare_config(config_path: Optional[Path]) -> Optional[Dict[str, Any]]:
    if not config_path:
        return None
    if not config_path.exists():
        return None
    try:
        spec = importlib.util.spec_from_file_location("cpg_config_dynamic", str(config_path))
        if spec is None or spec.loader is None:
            return None
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
    except Exception:
        return None

    semantic = set(getattr(module, "CORE_SEMANTIC_NODES", []) or [])
    structural = set(getattr(module, "CORE_STRUCTURAL_NODES", []) or [])

    edge_types: Set[str] = set()
    if hasattr(module, "FULL_EDGE_TYPES"):
        edge_types = set(getattr(module, "FULL_EDGE_TYPES"))
    elif hasattr(module, "get_edge_types"):
        try:
            edge_types = set(module.get_edge_types("full"))
        except Exception:
            edge_types = set()

    if not semantic and not structural and not edge_types:
        return None

    return {
        "semantic_nodes": semantic,
        "structural_nodes": structural,
        "edge_types": edge_types,
        "source": str(config_path),
    }


# =============================================================================
# GRAPHSON PARSER CLASS
# =============================================================================

class GraphSONParser:
    """Parse and analyze TinkerPop GraphSON files from Joern."""
    
    def __init__(self, json_path: Path):
        self.json_path = Path(json_path)
        self.raw_data = None
        self.vertices = []
        self.edges = []
        self.schema = {
            "node_types": defaultdict(lambda: {"count": 0, "properties": set()}),
            "edge_types": defaultdict(lambda: {"count": 0, "properties": set()}),
            "property_types": {},
        }
        self.parsed_nodes = []
        self.parsed_edges = []
        
    def load(self) -> bool:
        """Load the JSON file."""
        try:
            with open(self.json_path, 'r', encoding='utf-8') as f:
                self.raw_data = json.load(f)
            return True
        except Exception as e:
            return False
    
    def _unwrap_value(self, obj: Any) -> Any:
        """Recursively unwrap TinkerPop typed values."""
        if obj is None:
            return None
            
        if isinstance(obj, dict):
            if "@value" in obj:
                inner = obj["@value"]
                return self._unwrap_value(inner)
            else:
                return {k: self._unwrap_value(v) for k, v in obj.items()}
        
        elif isinstance(obj, list):
            return [self._unwrap_value(item) for item in obj]
        
        else:
            return obj
    
    def _extract_property_value(self, prop_data: Any) -> Any:
        """Extract the actual value from a property structure."""
        unwrapped = self._unwrap_value(prop_data)
        
        if isinstance(unwrapped, dict):
            for key in ['value', '@value']:
                if key in unwrapped:
                    return self._extract_property_value(unwrapped[key])
            return unwrapped
        
        elif isinstance(unwrapped, list):
            if len(unwrapped) == 1:
                return unwrapped[0]
            return unwrapped
        
        return unwrapped
    
    def _parse_vertex(self, vertex: Dict) -> Dict:
        """Parse a single vertex into a clean structure."""
        unwrapped = self._unwrap_value(vertex)
        
        node = {
            "id": unwrapped.get("id"),
            "label": unwrapped.get("label", "UNKNOWN"),
            "properties": {},
        }
        
        props = unwrapped.get("properties", {})
        for prop_name, prop_data in props.items():
            value = self._extract_property_value(prop_data)
            node["properties"][prop_name] = value
            
            if value is not None:
                self.schema["property_types"][prop_name] = type(value).__name__
        
        label = node["label"]
        self.schema["node_types"][label]["count"] += 1
        self.schema["node_types"][label]["properties"].update(node["properties"].keys())
        
        return node
    
    def _parse_edge(self, edge: Dict) -> Dict:
        """Parse a single edge into a clean structure."""
        unwrapped = self._unwrap_value(edge)
        
        parsed = {
            "id": unwrapped.get("id"),
            "label": unwrapped.get("label", "UNKNOWN"),
            "source_id": unwrapped.get("outV"),
            "source_label": unwrapped.get("outVLabel", ""),
            "target_id": unwrapped.get("inV"),
            "target_label": unwrapped.get("inVLabel", ""),
            "properties": {},
        }
        
        props = unwrapped.get("properties", {})
        for prop_name, prop_data in props.items():
            value = self._extract_property_value(prop_data)
            parsed["properties"][prop_name] = value
        
        label = parsed["label"]
        self.schema["edge_types"][label]["count"] += 1
        self.schema["edge_types"][label]["properties"].update(parsed["properties"].keys())
        
        return parsed
    
    def parse(self) -> bool:
        """Parse the loaded GraphSON data."""
        if self.raw_data is None:
            return False
        
        data = self._unwrap_value(self.raw_data)
        
        if isinstance(data, dict):
            self.vertices = data.get("vertices", [])
            self.edges = data.get("edges", [])
        elif isinstance(data, list):
            for item in data:
                if isinstance(item, dict):
                    if "vertices" in item:
                        self.vertices = item["vertices"]
                    if "edges" in item:
                        self.edges = item["edges"]
        
        for v in self.vertices:
            parsed = self._parse_vertex(v)
            self.parsed_nodes.append(parsed)
        
        for e in self.edges:
            parsed = self._parse_edge(e)
            self.parsed_edges.append(parsed)
        
        return True
    
    def get_schema_summary(self) -> Dict:
        """Generate a schema summary."""
        node_types = {}
        for ntype, info in self.schema["node_types"].items():
            node_types[ntype] = {
                "count": info["count"],
                "properties": sorted(list(info["properties"])),
            }
        
        edge_types = {}
        for etype, info in self.schema["edge_types"].items():
            edge_types[etype] = {
                "count": info["count"],
                "properties": sorted(list(info["properties"])),
            }
        
        return {
            "file": str(self.json_path),
            "total_nodes": len(self.parsed_nodes),
            "total_edges": len(self.parsed_edges),
            "node_types": node_types,
            "edge_types": edge_types,
            "property_types": self.schema["property_types"],
        }
    
    def get_nodes_by_type(self, node_type: str) -> List[Dict]:
        """Get all nodes of a specific type."""
        return [n for n in self.parsed_nodes if n["label"] == node_type]
    
    def build_node_map(self) -> Dict:
        """Build a map from node ID to node data."""
        return {n["id"]: n for n in self.parsed_nodes}
    
    def generate_text_report(self) -> str:
        """Generate human-readable text report."""
        lines = []
        lines.append("=" * 80)
        lines.append("GRAPHSON ANALYSIS REPORT")
        lines.append("=" * 80)
        lines.append(f"File: {self.json_path}")
        lines.append(f"Generated: {datetime.now().isoformat()}")
        lines.append("")
        
        lines.append("-" * 80)
        lines.append("STATISTICS")
        lines.append("-" * 80)
        lines.append(f"Total Nodes: {len(self.parsed_nodes)}")
        lines.append(f"Total Edges: {len(self.parsed_edges)}")
        lines.append(f"Node Types: {len(self.schema['node_types'])}")
        lines.append(f"Edge Types: {len(self.schema['edge_types'])}")
        lines.append("")
        
        lines.append("-" * 80)
        lines.append("NODE TYPES")
        lines.append("-" * 80)
        for ntype, info in sorted(self.schema["node_types"].items(),
                                   key=lambda x: x[1]["count"], reverse=True):
            lines.append(f"\n{ntype}: {info['count']} nodes")
            lines.append(f"  Properties: {sorted(list(info['properties']))}")
        lines.append("")
        
        lines.append("-" * 80)
        lines.append("EDGE TYPES")
        lines.append("-" * 80)
        for etype, info in sorted(self.schema["edge_types"].items(),
                                   key=lambda x: x[1]["count"], reverse=True):
            lines.append(f"\n{etype}: {info['count']} edges")
            if info['properties']:
                lines.append(f"  Properties: {sorted(list(info['properties']))}")
        lines.append("")
        
        lines.append("=" * 80)
        lines.append("END OF REPORT")
        lines.append("=" * 80)
        
        return "\n".join(lines)
    
    def generate_json_data(self) -> Dict:
        """Generate structured JSON output."""
        call_info = []
        for node in self.get_nodes_by_type("CALL"):
            call_info.append({
                "id": node["id"],
                "name": node["properties"].get("NAME", ""),
                "code": node["properties"].get("CODE", ""),
                "line_number": node["properties"].get("LINE_NUMBER"),
            })
        
        edge_list = []
        for edge in self.parsed_edges:
            edge_list.append({
                "source": edge["source_id"],
                "target": edge["target_id"],
                "type": edge["label"],
                "source_type": edge["source_label"],
                "target_type": edge["target_label"],
            })
        
        return {
            "file": str(self.json_path),
            "parsed_at": datetime.now().isoformat(),
            "statistics": {
                "total_nodes": len(self.parsed_nodes),
                "total_edges": len(self.parsed_edges),
                "node_types": len(self.schema["node_types"]),
                "edge_types": len(self.schema["edge_types"]),
            },
            "schema": self.get_schema_summary(),
            "call_nodes": call_info,
            "all_nodes": self.parsed_nodes,
            "all_edges": edge_list,
        }


# =============================================================================
# SCHEMA DISCOVERY - SCAN ALL FILES
# =============================================================================

def parse_single_file_for_schema(json_path: str) -> Optional[Dict]:
    """
    Parse a single GraphSON file and return schema info.
    Used for parallel processing.
    """
    try:
        parser = GraphSONParser(Path(json_path))
        if not parser.load():
            return None
        if not parser.parse():
            return None
        
        # Convert sets to lists for serialization
        node_types = {}
        for ntype, info in parser.schema["node_types"].items():
            node_types[ntype] = {
                "count": info["count"],
                "properties": list(info["properties"]),
            }
        
        edge_types = {}
        for etype, info in parser.schema["edge_types"].items():
            edge_types[etype] = {
                "count": info["count"],
                "properties": list(info["properties"]),
            }
        
        return {
            "file": str(json_path),
            "num_nodes": len(parser.parsed_nodes),
            "num_edges": len(parser.parsed_edges),
            "node_types": node_types,
            "edge_types": edge_types,
        }
    except Exception as e:
        return {"file": str(json_path), "error": str(e)}


class SchemaDiscovery:
    """
    Discover ALL node types and edge types across the entire dataset.
    """
    
    def __init__(self, output_dir: Path = None, config_path: Optional[Path] = None):
        self.output_dir = output_dir or Path("./schema_discovery")
        self.output_dir.mkdir(parents=True, exist_ok=True)

        loaded_config = load_compare_config(config_path) if config_path else None
        self.current_config = loaded_config or DEFAULT_COMPARE_CONFIG
        self.current_config_source = self.current_config.get("source", "builtin")
        
        # Aggregated schema
        self.all_node_types: Dict[str, Dict] = defaultdict(lambda: {
            "total_count": 0,
            "file_count": 0,
            "properties": set(),
            "sample_files": [],
        })
        self.all_edge_types: Dict[str, Dict] = defaultdict(lambda: {
            "total_count": 0,
            "file_count": 0,
            "properties": set(),
            "sample_files": [],
        })
        
        # Statistics
        self.total_files = 0
        self.processed_files = 0
        self.failed_files = 0
        self.total_nodes = 0
        self.total_edges = 0
        
        # Track largest graphs (might have more types)
        self.largest_graphs: List[Dict] = []
    
    def collect_json_files(
        self,
        manifests: List[Path],
        json_roots: List[Path],
    ) -> List[Path]:
        """Collect all GraphSON files from manifests."""
        json_files = []
        
        for manifest_path, root_dir in zip(manifests, json_roots):
            if not manifest_path.exists():
                print(f"[WARN] Manifest not found: {manifest_path}")
                continue
            if not root_dir.exists():
                print(f"[WARN] Root not found: {root_dir}")
                continue
            
            print(f"[INFO] Reading manifest: {manifest_path.name}")
            
            with manifest_path.open("r", encoding="utf-8") as f:
                reader = csv.DictReader(f)
                for row in reader:
                    graph_path = (
                        row.get("graph_json_path")
                        or row.get("export_json_path")
                        or row.get("graphson_path")
                    )
                    if graph_path:
                        cand = Path(graph_path)
                        if not cand.is_absolute():
                            cand = root_dir / cand
                        if cand.exists():
                            json_files.append(cand)
                            continue
                    # Try multiple possible column names
                    func_id = (row.get("func_id") or row.get("id") or 
                               row.get("function_id") or row.get("sample_id"))
                    if not func_id:
                        continue
                    
                    # Strip file extension if present (e.g., "test_func_0000001.c" -> "test_func_0000001")
                    func_id_clean = func_id.rsplit('.', 1)[0] if '.' in func_id else func_id
                    
                    # Try common export paths (with both original and cleaned func_id)
                    candidates = [
                        root_dir / "exports" / func_id_clean / "export_all" / "export.json",
                        root_dir / "exports" / func_id_clean / "export.json",
                        root_dir / "exports" / func_id / "export_all" / "export.json",
                        root_dir / "exports" / func_id / "export.json",
                        root_dir / func_id_clean / "export_all" / "export.json",
                        root_dir / func_id_clean / "export.json",
                        root_dir / func_id / "export_all" / "export.json",
                        root_dir / func_id / "export.json",
                    ]
                    
                    for cand in candidates:
                        if cand.exists():
                            json_files.append(cand)
                            break
        
        print(f"[INFO] Found {len(json_files)} GraphSON files")
        return json_files
    
    def scan_directory(self, directory: Path, pattern: str = "**/export.json") -> List[Path]:
        """Scan a directory for GraphSON files."""
        json_files = list(directory.glob(pattern))
        print(f"[INFO] Found {len(json_files)} files matching '{pattern}' in {directory}")
        return json_files
    
    def _merge_schema_result(self, result: Dict):
        """Merge a single file's schema into the aggregated schema."""
        if "error" in result:
            self.failed_files += 1
            return
        
        self.processed_files += 1
        self.total_nodes += result.get("num_nodes", 0)
        self.total_edges += result.get("num_edges", 0)
        
        # Track largest graphs
        graph_size = result.get("num_nodes", 0) + result.get("num_edges", 0)
        if len(self.largest_graphs) < 20 or graph_size > self.largest_graphs[-1].get("size", 0):
            self.largest_graphs.append({
                "file": result["file"],
                "size": graph_size,
                "nodes": result.get("num_nodes", 0),
                "edges": result.get("num_edges", 0),
                "node_types": list(result.get("node_types", {}).keys()),
                "edge_types": list(result.get("edge_types", {}).keys()),
            })
            self.largest_graphs.sort(key=lambda x: -x["size"])
            self.largest_graphs = self.largest_graphs[:20]
        
        # Merge node types
        for ntype, info in result.get("node_types", {}).items():
            self.all_node_types[ntype]["total_count"] += info.get("count", 0)
            self.all_node_types[ntype]["file_count"] += 1
            self.all_node_types[ntype]["properties"].update(info.get("properties", []))
            
            # Keep sample files
            if len(self.all_node_types[ntype]["sample_files"]) < 3:
                self.all_node_types[ntype]["sample_files"].append(result["file"])
        
        # Merge edge types
        for etype, info in result.get("edge_types", {}).items():
            self.all_edge_types[etype]["total_count"] += info.get("count", 0)
            self.all_edge_types[etype]["file_count"] += 1
            self.all_edge_types[etype]["properties"].update(info.get("properties", []))
            
            if len(self.all_edge_types[etype]["sample_files"]) < 3:
                self.all_edge_types[etype]["sample_files"].append(result["file"])
    
    def discover_schema(
        self,
        json_files: List[Path],
        max_workers: int = None,
        show_progress: bool = True,
    ):
        """Scan all files and discover the complete schema."""
        self.total_files = len(json_files)
        
        if max_workers is None:
            max_workers = min(8, multiprocessing.cpu_count())
        
        print(f"\n[DISCOVERY] Scanning {len(json_files)} files with {max_workers} workers...")
        
        # Process files in parallel (fallback to threads if process pool is not permitted)
        file_paths = [str(f) for f in json_files]
        executor_cls = ProcessPoolExecutor
        executor_note = "process"

        try:
            executor = executor_cls(max_workers=max_workers)
        except PermissionError:
            executor_cls = ThreadPoolExecutor
            executor_note = "thread"
            executor = executor_cls(max_workers=max_workers)
            print("[WARN] Process pool not permitted; falling back to threads.")

        with executor:
            futures = {executor.submit(parse_single_file_for_schema, fp): fp for fp in file_paths}

            iterator = as_completed(futures)
            if show_progress:
                iterator = tqdm(iterator, total=len(futures), desc=f"Scanning ({executor_note})")

            for future in iterator:
                try:
                    result = future.result(timeout=60)
                    if result:
                        self._merge_schema_result(result)
                except Exception:
                    self.failed_files += 1
        
        print(f"\n[DISCOVERY] Complete!")
        print(f"  Files processed: {self.processed_files}/{self.total_files}")
        print(f"  Failed files: {self.failed_files}")
        print(f"  Total nodes: {self.total_nodes:,}")
        print(f"  Total edges: {self.total_edges:,}")
        print(f"  Unique node types: {len(self.all_node_types)}")
        print(f"  Unique edge types: {len(self.all_edge_types)}")
    
    def get_discovered_schema(self) -> Dict:
        """Get the complete discovered schema."""
        # Convert sets to sorted lists
        node_types = {}
        for ntype, info in sorted(self.all_node_types.items()):
            node_types[ntype] = {
                "total_count": info["total_count"],
                "file_count": info["file_count"],
                "properties": sorted(list(info["properties"])),
                "sample_files": info["sample_files"],
            }
        
        edge_types = {}
        for etype, info in sorted(self.all_edge_types.items()):
            edge_types[etype] = {
                "total_count": info["total_count"],
                "file_count": info["file_count"],
                "properties": sorted(list(info["properties"])),
                "sample_files": info["sample_files"],
            }
        
        return {
            "discovery_timestamp": datetime.now().isoformat(),
            "statistics": {
                "total_files": self.total_files,
                "processed_files": self.processed_files,
                "failed_files": self.failed_files,
                "total_nodes": self.total_nodes,
                "total_edges": self.total_edges,
                "unique_node_types": len(node_types),
                "unique_edge_types": len(edge_types),
            },
            "node_types": node_types,
            "edge_types": edge_types,
            "largest_graphs": self.largest_graphs,
        }
    
    def compare_with_config(self, current_config: Dict = None) -> Dict:
        """Compare discovered schema with current cpg_config.py settings."""
        if current_config is None:
            current_config = self.current_config or DEFAULT_COMPARE_CONFIG

        semantic_nodes = set(current_config.get("semantic_nodes", []))
        structural_nodes = set(current_config.get("structural_nodes", []))
        edge_types = set(current_config.get("edge_types", []))
        config_source = current_config.get("source", self.current_config_source)
        
        discovered_nodes = set(self.all_node_types.keys())
        discovered_edges = set(self.all_edge_types.keys())
        
        known_nodes = semantic_nodes | structural_nodes
        known_edges = edge_types
        
        missing_nodes = discovered_nodes - known_nodes
        missing_edges = discovered_edges - known_edges
        
        # Classify missing nodes as semantic or structural based on heuristics
        semantic_candidates = set()
        structural_candidates = set()
        
        for node in missing_nodes:
            info = self.all_node_types[node]
            props = info["properties"]
            
            # Heuristic: nodes with CODE/NAME properties are likely semantic
            if "CODE" in props or "NAME" in props:
                semantic_candidates.add(node)
            else:
                structural_candidates.add(node)
        
        return {
            "discovered_nodes": sorted(discovered_nodes),
            "discovered_edges": sorted(discovered_edges),
            "missing_nodes": sorted(missing_nodes),
            "missing_edges": sorted(missing_edges),
            "semantic_candidates": sorted(semantic_candidates),
            "structural_candidates": sorted(structural_candidates),
            "known_nodes": sorted(known_nodes),
            "known_edges": sorted(known_edges),
            "config_source": config_source,
        }
    
    def generate_config_update(self) -> str:
        """Generate Python code to update cpg_config.py with discovered types."""
        comparison = self.compare_with_config()
        
        lines = []
        lines.append('"""')
        lines.append("AUTO-GENERATED CPG CONFIG UPDATE")
        lines.append(f"Generated: {datetime.now().isoformat()}")
        lines.append(f"Files scanned: {self.processed_files}")
        lines.append(f"Total nodes: {self.total_nodes:,}")
        lines.append(f"Total edges: {self.total_edges:,}")
        lines.append('"""')
        lines.append("")
        
        # All discovered edge types with counts
        lines.append("# " + "=" * 70)
        lines.append("# DISCOVERED EDGE TYPES (sorted by frequency)")
        lines.append("# " + "=" * 70)
        lines.append("")
        lines.append("DISCOVERED_EDGE_TYPES = [")
        
        edge_items = sorted(
            self.all_edge_types.items(),
            key=lambda x: -x[1]["total_count"]
        )
        for etype, info in edge_items:
            count = info["total_count"]
            file_count = info["file_count"]
            lines.append(f'    "{etype}",  # {count:,} edges in {file_count:,} files')
        lines.append("]")
        lines.append("")
        
        # Missing edge types
        if comparison["missing_edges"]:
            lines.append("# NEW EDGE TYPES NOT IN CURRENT CONFIG:")
            for etype in comparison["missing_edges"]:
                info = self.all_edge_types[etype]
                lines.append(f'#   "{etype}": {info["total_count"]:,} occurrences')
            lines.append("")
        
        # All discovered node types
        lines.append("# " + "=" * 70)
        lines.append("# DISCOVERED NODE TYPES (sorted by frequency)")
        lines.append("# " + "=" * 70)
        lines.append("")
        
        # Semantic nodes (have CODE or NAME)
        lines.append("# Nodes with semantic content (have CODE/NAME properties):")
        lines.append("DISCOVERED_SEMANTIC_NODES = {")
        
        semantic_nodes = []
        structural_nodes = []
        
        for ntype, info in sorted(self.all_node_types.items(), key=lambda x: -x[1]["total_count"]):
            props = info["properties"]
            if "CODE" in props or "NAME" in props:
                semantic_nodes.append((ntype, info))
            else:
                structural_nodes.append((ntype, info))
        
        for ntype, info in semantic_nodes:
            count = info["total_count"]
            props = sorted(list(info["properties"]))[:5]  # First 5 props
            props_str = ", ".join(props)
            lines.append(f'    "{ntype}",  # {count:,} nodes | props: {props_str}')
        lines.append("}")
        lines.append("")
        
        # Structural nodes
        lines.append("# Nodes without semantic content (metadata/structural):")
        lines.append("DISCOVERED_STRUCTURAL_NODES = {")
        for ntype, info in structural_nodes:
            count = info["total_count"]
            props = sorted(list(info["properties"]))[:5]
            props_str = ", ".join(props) if props else "(no properties)"
            lines.append(f'    "{ntype}",  # {count:,} nodes | props: {props_str}')
        lines.append("}")
        lines.append("")
        
        # Missing nodes
        if comparison["missing_nodes"]:
            lines.append("# " + "=" * 70)
            lines.append("# NEW NODE TYPES NOT IN CURRENT CONFIG")
            lines.append("# " + "=" * 70)
            lines.append("")
            
            if comparison["semantic_candidates"]:
                lines.append("# Likely SEMANTIC (add to CORE_SEMANTIC_NODES):")
                for ntype in comparison["semantic_candidates"]:
                    info = self.all_node_types[ntype]
                    props = sorted(list(info["properties"]))
                    lines.append(f'#   "{ntype}": {info["total_count"]:,} nodes')
                    lines.append(f'#       Properties: {props}')
                lines.append("")
            
            if comparison["structural_candidates"]:
                lines.append("# Likely STRUCTURAL (add to CORE_STRUCTURAL_NODES):")
                for ntype in comparison["structural_candidates"]:
                    info = self.all_node_types[ntype]
                    props = sorted(list(info["properties"]))
                    lines.append(f'#   "{ntype}": {info["total_count"]:,} nodes')
                    lines.append(f'#       Properties: {props}')
                lines.append("")
        
        # Generate LABEL_TO_PROPERTY_KEYS
        lines.append("# " + "=" * 70)
        lines.append("# PROPERTY KEYS FOR EACH NODE TYPE")
        lines.append("# " + "=" * 70)
        lines.append("")
        lines.append("DISCOVERED_LABEL_TO_PROPERTY_KEYS = {")
        
        # Priority order for properties
        priority_props = ["CODE", "NAME", "FULL_NAME", "METHOD_FULL_NAME", "SIGNATURE",
                         "TYPE_FULL_NAME", "CANONICAL_NAME", "CONTROL_STRUCTURE_TYPE"]
        
        for ntype, info in sorted(self.all_node_types.items()):
            props = list(info["properties"])
            
            # Sort: priority props first, then alphabetical
            def prop_sort_key(p):
                if p in priority_props:
                    return (0, priority_props.index(p))
                return (1, p)
            
            props = sorted(props, key=prop_sort_key)
            
            # Take most useful properties (up to 5)
            useful_props = [p for p in props if p in priority_props][:4]
            if not useful_props:
                useful_props = props[:3]
            
            if useful_props:
                props_str = ", ".join(f'"{p}"' for p in useful_props)
                lines.append(f'    "{ntype}": ({props_str}),')
        
        lines.append("}")
        lines.append("")
        
        # Summary
        lines.append("# " + "=" * 70)
        lines.append("# SUMMARY")
        lines.append("# " + "=" * 70)
        lines.append(f"# Total unique edge types: {len(self.all_edge_types)}")
        lines.append(f"# Total unique node types: {len(self.all_node_types)}")
        lines.append(f"#   - Semantic: {len(semantic_nodes)}")
        lines.append(f"#   - Structural: {len(structural_nodes)}")
        lines.append(f"# Missing edge types: {len(comparison['missing_edges'])}")
        lines.append(f"# Missing node types: {len(comparison['missing_nodes'])}")
        
        return "\n".join(lines)
    
    def save_results(self):
        """Save all discovery results to files."""
        # Full schema JSON
        schema_path = self.output_dir / "discovered_schema.json"
        with open(schema_path, "w", encoding="utf-8") as f:
            json.dump(self.get_discovered_schema(), f, indent=2, default=str)
        print(f"✅ Full schema: {schema_path}")
        
        # Comparison with current config
        comparison_path = self.output_dir / "config_comparison.json"
        with open(comparison_path, "w", encoding="utf-8") as f:
            json.dump(self.compare_with_config(), f, indent=2, default=str)
        print(f"✅ Config comparison: {comparison_path}")
        
        # Generated config code
        config_path = self.output_dir / "cpg_config_update.py"
        config_code = self.generate_config_update()
        with open(config_path, "w", encoding="utf-8") as f:
            f.write(config_code)
        print(f"✅ Config update code: {config_path}")
        
        # Human-readable summary
        summary_path = self.output_dir / "discovery_summary.txt"
        with open(summary_path, "w", encoding="utf-8") as f:
            f.write(self._generate_summary_report())
        print(f"✅ Summary report: {summary_path}")
    
    def _generate_summary_report(self) -> str:
        """Generate a human-readable summary report."""
        lines = []
        lines.append("=" * 80)
        lines.append("SCHEMA DISCOVERY REPORT")
        lines.append("=" * 80)
        lines.append(f"Generated: {datetime.now().isoformat()}")
        lines.append("")
        
        lines.append("-" * 80)
        lines.append("STATISTICS")
        lines.append("-" * 80)
        lines.append(f"Files scanned:    {self.processed_files:,} / {self.total_files:,}")
        lines.append(f"Failed files:     {self.failed_files:,}")
        lines.append(f"Total nodes:      {self.total_nodes:,}")
        lines.append(f"Total edges:      {self.total_edges:,}")
        lines.append(f"Unique node types: {len(self.all_node_types)}")
        lines.append(f"Unique edge types: {len(self.all_edge_types)}")
        lines.append(f"Config source:    {self.current_config_source}")
        lines.append("")
        
        # Edge types
        lines.append("-" * 80)
        lines.append("ALL EDGE TYPES (sorted by frequency)")
        lines.append("-" * 80)
        for etype, info in sorted(self.all_edge_types.items(), key=lambda x: -x[1]["total_count"]):
            lines.append(f"  {etype:25s}: {info['total_count']:>12,} edges in {info['file_count']:>8,} files")
        lines.append("")
        
        # Node types
        lines.append("-" * 80)
        lines.append("ALL NODE TYPES (sorted by frequency)")
        lines.append("-" * 80)
        for ntype, info in sorted(self.all_node_types.items(), key=lambda x: -x[1]["total_count"]):
            props = sorted(list(info["properties"]))[:6]
            props_str = ", ".join(props)
            lines.append(f"  {ntype:25s}: {info['total_count']:>12,} nodes")
            lines.append(f"      Properties: {props_str}")
        lines.append("")
        
        # Comparison
        comparison = self.compare_with_config()
        
        if comparison["missing_edges"]:
            lines.append("-" * 80)
            lines.append("⚠️  NEW EDGE TYPES (not in cpg_config.py)")
            lines.append("-" * 80)
            for etype in comparison["missing_edges"]:
                info = self.all_edge_types[etype]
                lines.append(f"  {etype}: {info['total_count']:,} occurrences")
            lines.append("")
        
        if comparison["missing_nodes"]:
            lines.append("-" * 80)
            lines.append("⚠️  NEW NODE TYPES (not in cpg_config.py)")
            lines.append("-" * 80)
            for ntype in comparison["missing_nodes"]:
                info = self.all_node_types[ntype]
                props = sorted(list(info["properties"]))
                category = "SEMANTIC" if "CODE" in props or "NAME" in props else "STRUCTURAL"
                lines.append(f"  {ntype}: {info['total_count']:,} nodes [{category}]")
                lines.append(f"      Properties: {props}")
            lines.append("")
        
        # Largest graphs
        lines.append("-" * 80)
        lines.append("LARGEST GRAPHS (might have rare types)")
        lines.append("-" * 80)
        for i, graph in enumerate(self.largest_graphs[:10], 1):
            lines.append(f"  {i}. {graph['nodes']} nodes, {graph['edges']} edges")
            lines.append(f"     File: {graph['file']}")
            lines.append(f"     Node types: {', '.join(graph['node_types'][:10])}")
            lines.append(f"     Edge types: {', '.join(graph['edge_types'][:10])}")
        lines.append("")
        
        lines.append("=" * 80)
        lines.append("END OF REPORT")
        lines.append("=" * 80)
        
        return "\n".join(lines)


# =============================================================================
# MAIN
# =============================================================================

def apply_dataset_defaults(args) -> None:
    if not args.dataset:
        return
    preset = DATASET_PRESETS.get(args.dataset)
    if not preset:
        return

    if args.output_dir is None and preset.get("output_dir"):
        args.output_dir = preset["output_dir"]
    if args.config_path is None and preset.get("config_path"):
        args.config_path = preset["config_path"]

    if not args.scan_dir and not args.manifests and not args.json_roots:
        args.manifests = preset.get("manifests", [])
        args.json_roots = preset.get("json_roots", [])

    if not args.scan_dir and not args.manifests and preset.get("scan_dir"):
        args.scan_dir = preset["scan_dir"]


def main():
    parser = argparse.ArgumentParser(
        description="Parse and analyze GraphSON/CPG export files",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # Single file analysis
    python graphson_parser.py --input /path/to/export.json --output-dir ./analysis
    
    # Full dataset schema discovery
    python graphson_parser.py --discover \\
        --manifests manifest_train.csv manifest_val.csv manifest_test.csv \\
        --json-roots /path/to/train /path/to/val /path/to/test \\
        --output-dir ./schema_discovery

    # REVEAL preset (uses standard paths if available)
    python graphson_parser.py --discover --dataset reveal
    
    # Directory scan (all export.json files)
    python graphson_parser.py --discover \\
        --scan-dir /path/to/cpgs \\
        --output-dir ./schema_discovery
"""
    )
    
    # Single file mode
    parser.add_argument(
        "--input", "-i", type=Path, default=None,
        help="Path to single export.json (GraphSON file)"
    )
    
    # Discovery mode
    parser.add_argument(
        "--discover", action="store_true",
        help="Enable full dataset schema discovery mode"
    )
    parser.add_argument(
        "--dataset", type=str, default=None, choices=sorted(DATASET_PRESETS.keys()),
        help="Use dataset preset paths (reveal, devign, draper, or primevul)"
    )
    parser.add_argument(
        "--manifests", nargs="+", type=Path, default=[],
        help="Manifest CSV files (for discovery mode)"
    )
    parser.add_argument(
        "--json-roots", nargs="+", type=Path, default=[],
        help="Root directories for JSON files (for discovery mode)"
    )
    parser.add_argument(
        "--scan-dir", type=Path, default=None,
        help="Directory to scan for export.json files (alternative to manifests)"
    )
    
    # Common options
    parser.add_argument(
        "--output-dir", "-o", type=Path, default=None,
        help="Output directory"
    )
    parser.add_argument(
        "--config-path", type=Path, default=None,
        help="Path to cpg_config.py for schema comparison"
    )
    parser.add_argument(
        "--prefix", "-p", type=str, default="analysis",
        help="Output file prefix (default: 'analysis')"
    )
    parser.add_argument(
        "--workers", "-w", type=int, default=None,
        help="Number of parallel workers (default: auto)"
    )
    parser.add_argument(
        "--max-files", type=int, default=None,
        help="Maximum files to process (for testing)"
    )
    
    args = parser.parse_args()
    apply_dataset_defaults(args)
    
    # Determine mode
    if args.discover:
        # Schema discovery mode
        if args.output_dir:
            output_dir = args.output_dir
        else:
            output_dir = Path("./schema_discovery")
        
        print(f"\n{'='*60}")
        print("SCHEMA DISCOVERY MODE")
        print(f"{'='*60}")
        print(f"Output: {output_dir}")
        
        discovery = SchemaDiscovery(output_dir, config_path=args.config_path)
        
        # Collect files
        if args.scan_dir:
            json_files = discovery.scan_directory(args.scan_dir)
        elif args.manifests and args.json_roots:
            if len(args.manifests) != len(args.json_roots):
                print("Error: Number of manifests must match number of json-roots")
                return 1
            json_files = discovery.collect_json_files(args.manifests, args.json_roots)
        else:
            print("Error: Either --scan-dir or (--manifests and --json-roots) required")
            return 1
        
        if not json_files:
            print("No JSON files found!")
            return 1
        
        # Limit files if requested
        if args.max_files:
            json_files = json_files[:args.max_files]
            print(f"[INFO] Limited to {args.max_files} files")
        
        # Run discovery
        discovery.discover_schema(json_files, max_workers=args.workers)
        
        # Save results
        print("\n[SAVING] Generating output files...")
        discovery.save_results()
        
        # Print quick summary
        comparison = discovery.compare_with_config()
        
        print(f"\n{'='*60}")
        print("DISCOVERY COMPLETE")
        print(f"{'='*60}")
        
        if comparison["missing_edges"]:
            print(f"\n⚠️  {len(comparison['missing_edges'])} NEW EDGE TYPES found:")
            for etype in comparison["missing_edges"]:
                info = discovery.all_edge_types[etype]
                print(f"    - {etype}: {info['total_count']:,} occurrences")
        
        if comparison["missing_nodes"]:
            print(f"\n⚠️  {len(comparison['missing_nodes'])} NEW NODE TYPES found:")
            for ntype in comparison["missing_nodes"]:
                info = discovery.all_node_types[ntype]
                print(f"    - {ntype}: {info['total_count']:,} nodes")
        
        if not comparison["missing_edges"] and not comparison["missing_nodes"]:
            print("\n✅ All discovered types are already in cpg_config.py!")
        
        print(f"\nOutput files in: {output_dir}")
        
    elif args.input:
        # Single file analysis mode (original behavior)
        if args.output_dir:
            output_dir = args.output_dir
        else:
            output_dir = args.input.parent
        
        output_dir.mkdir(parents=True, exist_ok=True)
        
        print(f"\n{'='*60}")
        print("GRAPHSON PARSER")
        print(f"{'='*60}")
        print(f"Input: {args.input}")
        print(f"Output: {output_dir}")
        
        parser_obj = GraphSONParser(args.input)
        
        if not parser_obj.load():
            print("❌ Failed to load file")
            return 1
        
        if not parser_obj.parse():
            print("❌ Failed to parse file")
            return 1
        
        print(f"Found {len(parser_obj.parsed_nodes)} nodes and {len(parser_obj.parsed_edges)} edges")
        
        # Generate outputs
        print("\nGenerating outputs...")
        
        txt_path = output_dir / f"{args.prefix}_report.txt"
        txt_content = parser_obj.generate_text_report()
        txt_path.write_text(txt_content, encoding='utf-8')
        print(f"✅ Text report: {txt_path}")
        
        json_path = output_dir / f"{args.prefix}_data.json"
        json_content = parser_obj.generate_json_data()
        with open(json_path, 'w', encoding='utf-8') as f:
            json.dump(json_content, f, indent=2, default=str)
        print(f"✅ JSON data: {json_path}")
        
        schema_path = output_dir / f"{args.prefix}_schema.json"
        schema_content = parser_obj.get_schema_summary()
        with open(schema_path, 'w', encoding='utf-8') as f:
            json.dump(schema_content, f, indent=2, default=str)
        print(f"✅ Schema summary: {schema_path}")
        
        # Print quick summary
        print(f"\n{'='*60}")
        print("QUICK SUMMARY")
        print(f"{'='*60}")
        
        print("\nNode Types:")
        for ntype, info in sorted(parser_obj.schema["node_types"].items(),
                                   key=lambda x: x[1]["count"], reverse=True)[:10]:
            print(f"  {ntype:25s}: {info['count']}")
        
        print("\nEdge Types:")
        for etype, info in sorted(parser_obj.schema["edge_types"].items(),
                                   key=lambda x: x[1]["count"], reverse=True)[:10]:
            print(f"  {etype:25s}: {info['count']}")
        
    else:
        print("Error: Either --input (single file) or --discover (schema discovery) required")
        parser.print_help()
        return 1
    
    print(f"\n{'='*60}")
    print("DONE")
    print(f"{'='*60}")
    
    return 0


if __name__ == "__main__":
    exit(main())

    
"""
USAGE EXAMPLES:



# 2. Full dataset schema discovery with manifests (REVEAL)
python graphson_parser.py --discover \
    --manifests \
        "./workspace/03_PerFunction_datasets/reveal_functions/manifest_train.csv" \
        "./workspace/03_PerFunction_datasets/reveal_functions/manifest_validation.csv" \
        "./workspace/03_PerFunction_datasets/reveal_functions/manifest_test.csv" \
    --json-roots \
        "./CPGs/reveal_functions/train" \
        "./CPGs/reveal_functions/validation" \
        "./CPGs/reveal_functions/test" \
    --output-dir "./schema_discovery_reveal" \
    --workers 8

# 3. Directory scan (simpler alternative)
python graphson_parser.py --discover \\
    --scan-dir "./CPGs/reveal_functions" \\
    --output-dir "./schema_discovery_reveal"

# 4. Quick test with limited files
python graphson_parser.py --discover \\
    --scan-dir "/path/to/cpgs" \\
    --max-files 100 \\
    --output-dir "./test_discovery"
"""
