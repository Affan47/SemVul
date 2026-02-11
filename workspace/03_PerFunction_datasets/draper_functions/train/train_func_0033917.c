find_block (const void *v1, const void *v2)
{
  const union tree_node *b1 = (const union tree_node *) v1;
  tree b2 = *((const tree *) v2);
  char *p1 = (char *) b1;
  char *p2 = (char *) BLOCK_ABSTRACT_ORIGIN (b2);

  if (p1 == p2)
    return 0;
  return p1 < p2 ? -1 : 1;
}
