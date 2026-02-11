sp_hash_search ARGS4((S,row,col,value),
struct linsys *S,
int row, int col,
REAL value)
{
  struct sp_entry *e;
  int spot;


  if ( value == 0.0 ) return;

  if ( S->hashcount >= S->max_fill )
     sp_hash_expand(S);


  spot = sp_hash(row,col) % S->table_size;
  e = S->hashtable + spot;
  while ( e->row != HASHEMPTY )
  { if ( (e->row == row) && (e->col == col) )
    { e->value += value;
      return;
    }
    spot++;
    if ( spot >= S->table_size ) spot -= S->table_size;
    e = S->hashtable + spot;
    S->hash_extraprobes++;
  }

  e->col = col; e->row = row;  S->hashcount++;
  e->value = value;

}
