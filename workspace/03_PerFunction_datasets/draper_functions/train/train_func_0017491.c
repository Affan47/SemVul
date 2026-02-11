relation_digraph (relation r, relation_node size, bitsetv *function)
{
  relation_node i;

  infinity = size + 2;
  INDEX = xcalloc (size + 1, sizeof *INDEX);
  VERTICES = xnmalloc (size + 1, sizeof *VERTICES);
  top = 0;

  R = r;
  F = *function;

  for (i = 0; i < size; i++)
    if (INDEX[i] == 0 && R[i])
      traverse (i);

  free (INDEX);
  free (VERTICES);

  *function = F;
}
