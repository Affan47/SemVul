node_read(int is_compact, FILE *fp) {
  SparseNode n = make_null_node(is_compact);
  size_t nr;

  if (!fp) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "node_read: bad file pointer.\n");
    }
    return n;
  }

  if (n.is_compact) {
    n.compact = (CompactSparseNode *)malloc(sizeof(CompactSparseNode));
    nr = fread(n.compact, sizeof(CompactSparseNode), 1, fp);
    if (!nr) {

      free(n.compact);
      return make_null_node(is_compact);
    }
    n.compact->next = NULL;
    n.compact->prev = NULL;
    return n;
  }

  n.precise = (PreciseSparseNode *)malloc(sizeof(PreciseSparseNode));
  nr = fread(n.precise, sizeof(PreciseSparseNode), 1, fp);
  if (!nr) {

    free(n.precise);
    return make_null_node(is_compact);
  }
  n.precise->next = NULL;
  n.precise->prev = NULL;
  return n;
}
