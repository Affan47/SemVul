init ()
{
  decl_cache = NULL;
  cstat_tail = NULL;
  cur_scope = NULL;
  cur_body = NULL;
  cur_du = new vaul_design_unit (pool->get_work_library(),
				 NULL, lex->filename);

  tree_protect_loc ((tree_base_node **)&decl_cache);

  next_decl_seqno = 0;

  int l = lex->lineno;
  push_scope (mVAUL_TopScope(l, NULL));
  add_decl (mIIR_LibraryClause (l, make_id("work")));
  add_decl (mIIR_LibraryClause (l, make_id("std")));

  std = NULL;

  announced_scope = NULL;
  n_errors = 0;

  max_constrain_depth = -1;
}
