wsnode_new (struct wordsplit *wsp, struct wordsplit_node **pnode)
{
  struct wordsplit_node *node = calloc (1, sizeof (*node));
  if (!node)
    return _wsplt_nomem (wsp);
  *pnode = node;
  return 0;
}
