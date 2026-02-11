take_address_of (tree obj, tree type, edge entry, htab_t decl_address,
		 gimple_stmt_iterator *gsi)
{
  int uid;
  void **dslot;
  struct int_tree_map ielt, *nielt;
  tree *var_p, name, addr;
  gimple stmt;
  gimple_seq stmts;


  obj = unshare_expr (obj);
  for (var_p = &obj;
       handled_component_p (*var_p);
       var_p = &TREE_OPERAND (*var_p, 0))
    continue;


  if (DECL_P (*var_p))
    *var_p = build_simple_mem_ref (build_fold_addr_expr (*var_p));


  uid = DECL_UID (TREE_OPERAND (TREE_OPERAND (*var_p, 0), 0));
  ielt.uid = uid;
  dslot = htab_find_slot_with_hash (decl_address, &ielt, uid, INSERT);
  if (!*dslot)
    {
      if (gsi == NULL)
	return NULL;
      addr = TREE_OPERAND (*var_p, 0);
      const char *obj_name
	= get_name (TREE_OPERAND (TREE_OPERAND (*var_p, 0), 0));
      if (obj_name)
	name = make_temp_ssa_name (TREE_TYPE (addr), NULL, obj_name);
      else
	name = make_ssa_name (TREE_TYPE (addr), NULL);
      stmt = gimple_build_assign (name, addr);
      gsi_insert_on_edge_immediate (entry, stmt);

      nielt = XNEW (struct int_tree_map);
      nielt->uid = uid;
      nielt->to = name;
      *dslot = nielt;
    }
  else
    name = ((struct int_tree_map *) *dslot)->to;


  TREE_OPERAND (*var_p, 0) = name;
  if (gsi == NULL)
    return build_fold_addr_expr_with_type (obj, type);

  name = force_gimple_operand (build_addr (obj, current_function_decl),
			       &stmts, true, NULL_TREE);
  if (!gimple_seq_empty_p (stmts))
    gsi_insert_seq_before (gsi, stmts, GSI_SAME_STMT);

  if (!useless_type_conversion_p (type, TREE_TYPE (name)))
    {
      name = force_gimple_operand (fold_convert (type, name), &stmts, true,
				   NULL_TREE);
      if (!gimple_seq_empty_p (stmts))
	gsi_insert_seq_before (gsi, stmts, GSI_SAME_STMT);
    }

  return name;
}
