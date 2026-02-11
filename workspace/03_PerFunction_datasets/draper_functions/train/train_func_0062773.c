omp_copy_decl (tree var, copy_body_data *cb)
{
  omp_context *ctx = (omp_context *) cb;
  tree new_var;

  if (TREE_CODE (var) == LABEL_DECL)
    {
      new_var = create_artificial_label (DECL_SOURCE_LOCATION (var));
      DECL_CONTEXT (new_var) = current_function_decl;
      insert_decl_map (&ctx->cb, var, new_var);
      return new_var;
    }

  while (!is_taskreg_ctx (ctx))
    {
      ctx = ctx->outer;
      if (ctx == NULL)
	return var;
      new_var = maybe_lookup_decl (var, ctx);
      if (new_var)
	return new_var;
    }

  if (is_global_var (var) || decl_function_context (var) != ctx->cb.src_fn)
    return var;

  return error_mark_node;
}
