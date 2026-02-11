unvisit_body (tree fndecl)
{
  struct cgraph_node *cgn = cgraph_get_node (fndecl);

  unmark_visited (&DECL_SAVED_TREE (fndecl));
  unmark_visited (&DECL_SIZE (DECL_RESULT (fndecl)));
  unmark_visited (&DECL_SIZE_UNIT (DECL_RESULT (fndecl)));

  if (cgn)
    for (cgn = cgn->nested; cgn; cgn = cgn->next_nested)
      unvisit_body (cgn->symbol.decl);
}
