import torch
import zipfile
import io
from pathlib import Path
from collections import Counter

cache_dir = Path("./Clean_exports/cache_devign_v2")
dataset = "unixcoder_768d_full"
signature = "1ac872fe7f1a6442"

# Corrected path - using cache_train.zip
zip_path = cache_dir / dataset / signature / "train" / "cache_train.zip"

edge_type_counts = Counter()

with zipfile.ZipFile(zip_path, 'r') as zf:
    pt_files = sorted([n for n in zf.namelist() if n.endswith('.pt')])[:100]
    
    for pt_name in pt_files:
        with zf.open(pt_name) as f:
            data = torch.load(io.BytesIO(f.read()), map_location='cpu')
        
        # Check edge_type attribute
        if hasattr(data, 'edge_type'):
            edge_types = data.edge_type.numpy()
        elif hasattr(data, 'edge_attr'):
            edge_types = data.edge_attr.numpy()
        else:
            print(f"No edge_type or edge_attr in {pt_name}")
            continue
            
        for et in edge_types:
            edge_type_counts[int(et)] += 1

print("\nEdge Type Distribution in Cache:")
print("="*50)
for idx in sorted(edge_type_counts.keys()):
    print(f"  Index {idx:2d}: {edge_type_counts[idx]:>10,} edges")

print(f"\nTotal unique edge types: {len(edge_type_counts)}")
print(f"Present indices: {sorted(edge_type_counts.keys())}")
missing = set(range(18)) - set(edge_type_counts.keys())
print(f"Missing indices: {sorted(missing)}")


### python diagnose_edge_types.py
################################################################################