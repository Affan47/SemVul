bnr_hash_destroy (struct bnr_hash *hash)
{
  struct bnr_hash_node *node, *next;
  struct bnr_hash_c c;

  if (hash == NULL)
    return -1;

  node = c_bnr_hash_first (hash, &c);
  while (node != NULL)
  {
    char *x = node->name;
    next = c_bnr_hash_next (hash, &c);
    bnr_hash_delete (hash, node->name);
    free (x);
    node = next;
  }

  free (hash->tbl);
  free (hash);

  return 0;
}
