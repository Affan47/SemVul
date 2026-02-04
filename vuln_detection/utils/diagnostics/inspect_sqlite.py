#!/usr/bin/env python3
"""
inspect_sqlite.py - Check what tables exist in SQLite
"""

import sqlite3
import sys
from pathlib import Path

def inspect_sqlite(db_path: str):
    """Inspect SQLite database structure."""
    
    path = Path(db_path)
    if not path.exists():
        print(f"❌ File not found: {path}")
        return
    
    print(f"\n{'='*60}")
    print(f"SQLite Database Inspection")
    print(f"{'='*60}")
    print(f"File: {path}")
    print(f"Size: {path.stat().st_size / 1024 / 1024:.2f} MB")
    
    try:
        conn = sqlite3.connect(str(path))
        conn.row_factory = sqlite3.Row
        
        # List all tables
        tables = conn.execute(
            "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;"
        ).fetchall()
        
        print(f"\n📋 Tables found: {len(tables)}")
        for t in tables:
            print(f"   - {t['name']}")
        
        # For each table, show schema and row count
        for t in tables:
            table_name = t['name']
            print(f"\n📊 Table: {table_name}")
            
            # Row count
            count = conn.execute(f"SELECT COUNT(*) FROM '{table_name}'").fetchone()[0]
            print(f"   Rows: {count:,}")
            
            # Schema
            schema = conn.execute(f"PRAGMA table_info('{table_name}')").fetchall()
            print(f"   Columns:")
            for col in schema:
                print(f"      {col['name']:15s} {col['type']:10s} {'PK' if col['pk'] else ''}")
            
            # Sample data
            if count > 0:
                sample = conn.execute(f"SELECT * FROM '{table_name}' LIMIT 1").fetchone()
                print(f"   Sample row keys: {list(sample.keys())}")
                
                # If it has vec/dim columns, show those
                if 'dim' in sample.keys():
                    print(f"   Sample dim: {sample['dim']}")
                if 'sha256' in sample.keys():
                    print(f"   Sample sha256: {sample['sha256'][:32]}...")
        
        conn.close()
        
    except Exception as e:
        print(f"❌ Error: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python inspect_sqlite.py <path_to_sqlite>")
        sys.exit(1)
    
    inspect_sqlite(sys.argv[1])

"""

python inspect_sqlite.py "./Clean_exports/cache_devign_v2/graphcodebert_64d.sqlite"

"""    