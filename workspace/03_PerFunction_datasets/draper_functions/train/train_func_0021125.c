get_nth_val_ent(struct trie_node *node, int n, int f)
{
  struct record_row *col;
  col = &node->row;
  if (n < 0) {
    return NULL;
  }
  if (n < do_get_nr_values(node)) {
    return &col->vals[n];
  }
  if (f) {
    int i;
    col->vals = realloc(col->vals, sizeof(struct record_val)*(n + 1));
    for (i = col->nr_vals; i < n+1; i++) {
      col->vals[i].type = RT_EMPTY;
    }
    col->nr_vals = n + 1;
    return &col->vals[n];
  }
  return NULL;
}
