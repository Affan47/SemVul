do_truncate_row (struct trie_node* node, int n)
{
  int i;
  if (n < node->row.nr_vals) {
    for (i = n; i < node->row.nr_vals; i++) {
      free_val_contents(node->row.vals + i);
    }
    node->row.vals = realloc(node->row.vals,
				sizeof(struct record_val)* n);
    node->row.nr_vals = n;
  }
}
