do_local_using_decl (tree decl, tree scope, tree name)
{
  tree oldval, oldtype, newval, newtype;
  tree orig_decl = decl;

  decl = validate_nonmember_using_decl (decl, scope, name);
  if (decl == NULL_TREE)
    return;

  if (building_stmt_list_p ()
      && at_function_scope_p ())
    add_decl_expr (decl);

  oldval = lookup_name_innermost_nonclass_level (name);
  oldtype = lookup_type_current_level (name);

  do_nonmember_using_decl (scope, name, oldval, oldtype, &newval, &newtype);

  if (newval)
    {
      if (is_overloaded_fn (newval))
	{
	  tree fn, term;


	  if (oldval && TREE_CODE (oldval) == OVERLOAD)
	    term = OVL_FUNCTION (oldval);
	  else
	    term = oldval;
	  for (fn = newval; fn && OVL_CURRENT (fn) != term;
	       fn = OVL_NEXT (fn))
	    push_overloaded_decl (OVL_CURRENT (fn),
				  PUSH_LOCAL | PUSH_USING,
				  false);
	}
      else
	push_local_binding (name, newval, PUSH_USING);
    }
  if (newtype)
    {
      push_local_binding (name, newtype, PUSH_USING);
      set_identifier_type_value (name, newtype);
    }


  if (!processing_template_decl)
    cp_emit_debug_info_for_using (orig_decl, current_scope());
}
