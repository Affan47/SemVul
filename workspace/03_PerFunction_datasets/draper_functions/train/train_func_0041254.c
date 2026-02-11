m_hess_hash_search(col,row,value,tid)
int row,col;
REAL value;
int tid;
{
  struct hess_entry *e;
  int spot;
  struct hess_entry *hashtab;
  int tab_size = m_table_size[tid];

  if ( row > col ) return;

  if ( m_hashcount[tid] >= m_max_fill[tid] ) m_hess_hash_expand();
  hashtab = m_hashtable[tid];


  spot = hash(row,col) % tab_size;
  e = hashtab + spot;
  while ( e->row != HASHEMPTY )
  { if ( (e->row == row) && (e->col == col) )
     { e->value += value; return;
     }
     spot++;
     if ( spot >= tab_size ) spot -= tab_size;
     e = hashtab + spot;
     m_hash_extraprobes++;
  }

  e->col = col; e->row = row;  m_hashcount[tid]++;
  e->value = value;
}
