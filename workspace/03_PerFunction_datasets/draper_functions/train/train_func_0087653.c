lookup_tag (enum tree_code form, tree name,
            cxx_scope *binding_level, int thislevel_only)
{
  struct cp_binding_level *level;


  int allow_template_parms_p = 1;
  bool type_is_anonymous = ANON_AGGRNAME_P (name);

  timevar_push (TV_NAME_LOOKUP);
  for (level = binding_level; level; level = level->level_chain)
    {
      tree tail;
      if (type_is_anonymous && level->type_decls != NULL)
        {
          tree type = binding_table_find_anon_type (level->type_decls, name);


          if (type != NULL)
            POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, type);
        }
      else if (level->kind == sk_namespace)

	for (tail = current_namespace; 1; tail = CP_DECL_CONTEXT (tail))
	  {
            cxx_binding *binding =
              cxx_scope_find_binding_for_name (NAMESPACE_LEVEL (tail), name);
	    tree old;


	    if (thislevel_only && !allow_template_parms_p
		&& binding && binding->value
		&& DECL_CLASS_TEMPLATE_P (binding->value))
	      old = binding->value;
	    else if (binding)
	      old = select_decl (binding, LOOKUP_PREFER_TYPES);
            else
              old = NULL_TREE;

	    if (old)
	      {


		old = TREE_TYPE (old);
		old = follow_tag_typedef (old);
		if (!old)
		  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
		if (TREE_CODE (old) != form
		    && (form == ENUMERAL_TYPE
			|| TREE_CODE (old) == ENUMERAL_TYPE))
		  {
		    error ("`%#D' redeclared as %C", old, form);
		    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
		  }
		POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, old);
	      }
	    if (thislevel_only || tail == global_namespace)
	      POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
	  }
      else if (level->type_decls != NULL)
        {
          binding_entry entry = binding_table_find (level->type_decls, name);
          if (entry != NULL)
            {
              enum tree_code code = TREE_CODE (entry->type);

              if (code != form
                  && (form == ENUMERAL_TYPE || code == ENUMERAL_TYPE))
                {

                  error ("`%#D' redeclared as %C", entry->type, form);
                  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
                }
              POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, entry->type);
            }
	  }
      if (thislevel_only && level->kind != sk_cleanup)
	{
	  if (level->kind == sk_template_parms && allow_template_parms_p)
	    {


	      allow_template_parms_p = 0;
	      continue;
	    }
	  else
	    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
	}
    }
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
}
