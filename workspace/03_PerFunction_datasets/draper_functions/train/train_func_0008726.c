push_using_directive_1 (tree used)
{
  tree ud = current_binding_level->using_directives;
  tree iter, ancestor;


  if (purpose_member (used, ud) != NULL_TREE)
    return NULL_TREE;

  ancestor = namespace_ancestor (current_decl_namespace (), used);
  ud = current_binding_level->using_directives;
  ud = tree_cons (used, ancestor, ud);
  current_binding_level->using_directives = ud;


  for (iter = DECL_NAMESPACE_USING (used); iter; iter = TREE_CHAIN (iter))
    push_using_directive (TREE_PURPOSE (iter));

  return ud;
}
