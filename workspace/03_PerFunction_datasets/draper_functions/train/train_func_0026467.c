cs_dump (CSPARSE *parse, void *ctx, CSOUTFUNC cb)
{
  CSTREE *node;
  char buf[4096];

  if (parse->tree == NULL)
    return nerr_raise (NERR_ASSERT, "No parse tree exists");

  node = parse->tree;
  return nerr_pass (dump_node (parse, node, 0, ctx, cb, buf, sizeof(buf)));
}
