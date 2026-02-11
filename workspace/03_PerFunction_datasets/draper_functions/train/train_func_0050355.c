optimize_inline_calls (fn)
     tree fn;
{
  inline_data id;
  tree prev_fn;


  if (errorcount || sorrycount)
    return;


  memset (&id, 0, sizeof (id));


  VARRAY_TREE_INIT (id.fns, 32, "fns");
  VARRAY_PUSH_TREE (id.fns, fn);

  prev_fn = NULL_TREE;
  if (current_function_decl)
    {
      VARRAY_PUSH_TREE (id.fns, current_function_decl);
      prev_fn = current_function_decl;
    }

  prev_fn = ((*lang_hooks.tree_inlining.add_pending_fn_decls)
	     (&id.fns, prev_fn));


  VARRAY_TREE_INIT (id.target_exprs, 32, "target_exprs");


  VARRAY_TREE_INIT (id.inlined_fns, 32, "inlined_fns");


  id.first_inlined_fn = VARRAY_ACTIVE_SIZE (id.fns);


  id.tree_pruner = htab_create (37, htab_hash_pointer,
				htab_eq_pointer, NULL);
  expand_calls_inline (&DECL_SAVED_TREE (fn), &id);


  htab_delete (id.tree_pruner);
  if (DECL_LANG_SPECIFIC (fn))
    {
      tree ifn = make_tree_vec (VARRAY_ACTIVE_SIZE (id.inlined_fns));

      if (VARRAY_ACTIVE_SIZE (id.inlined_fns))
	memcpy (&TREE_VEC_ELT (ifn, 0), &VARRAY_TREE (id.inlined_fns, 0),
		VARRAY_ACTIVE_SIZE (id.inlined_fns) * sizeof (tree));
      DECL_INLINED_FNS (fn) = ifn;
    }
}
