omp_check_private (struct gimplify_omp_ctx *ctx, tree decl)
{
  splay_tree_node n;

  do
    {
      ctx = ctx->outer_context;
      if (ctx == NULL)
	return !(is_global_var (decl)

		 || lang_hooks.decls.omp_privatize_by_reference (decl));

      n = splay_tree_lookup (ctx->variables, (splay_tree_key) decl);
      if (n != NULL)
	return (n->value & GOVD_SHARED) == 0;
    }
  while (ctx->region_type == ORT_WORKSHARE);
  return false;
}
