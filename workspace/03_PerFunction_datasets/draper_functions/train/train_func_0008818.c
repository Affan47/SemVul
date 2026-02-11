scan_omp_parallel (gimple_stmt_iterator *gsi, omp_context *outer_ctx)
{
  omp_context *ctx;
  tree name;
  gimple stmt = gsi_stmt (*gsi);


  if (optimize > 0
      && empty_body_p (gimple_omp_body (stmt))
      && find_omp_clause (gimple_omp_parallel_clauses (stmt),
			  OMP_CLAUSE_COPYIN) == NULL)
    {
      gsi_replace (gsi, gimple_build_nop (), false);
      return;
    }

  ctx = new_omp_context (stmt, outer_ctx);
  taskreg_contexts.safe_push (ctx);
  if (taskreg_nesting_level > 1)
    ctx->is_nested = true;
  ctx->field_map = splay_tree_new (splay_tree_compare_pointers, 0, 0);
  ctx->default_kind = OMP_CLAUSE_DEFAULT_SHARED;
  ctx->record_type = lang_hooks.types.make_type (RECORD_TYPE);
  name = create_tmp_var_name (".omp_data_s");
  name = build_decl (gimple_location (stmt),
		     TYPE_DECL, name, ctx->record_type);
  DECL_ARTIFICIAL (name) = 1;
  DECL_NAMELESS (name) = 1;
  TYPE_NAME (ctx->record_type) = name;
  create_omp_child_function (ctx, false);
  gimple_omp_parallel_set_child_fn (stmt, ctx->cb.dst_fn);

  scan_sharing_clauses (gimple_omp_parallel_clauses (stmt), ctx);
  scan_omp (gimple_omp_body_ptr (stmt), ctx);

  if (TYPE_FIELDS (ctx->record_type) == NULL)
    ctx->record_type = ctx->receiver_decl = NULL;
}
