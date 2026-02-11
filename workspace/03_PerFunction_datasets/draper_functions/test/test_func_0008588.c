pre_gcse (struct edge_list *edge_list)
{
  unsigned int i;
  int did_insert, changed;
  struct expr **index_map;
  struct expr *expr;


  index_map = XCNEWVEC (struct expr *, expr_hash_table.n_elems);
  for (i = 0; i < expr_hash_table.size; i++)
    for (expr = expr_hash_table.table[i]; expr; expr = expr->next_same_hash)
      index_map[expr->bitmap_index] = expr;


  changed = pre_delete ();
  did_insert = pre_edge_insert (edge_list, index_map);


  pre_insert_copies ();
  if (did_insert)
    {
      commit_edge_insertions ();
      changed = 1;
    }

  free (index_map);
  return changed;
}
