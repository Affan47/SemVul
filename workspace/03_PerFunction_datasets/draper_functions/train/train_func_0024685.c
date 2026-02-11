push_inner_scope_r (tree outer, tree inner)
{
  tree prev;

  if (outer == inner
      || (TREE_CODE (inner) != NAMESPACE_DECL && !CLASS_TYPE_P (inner)))
    return;

  prev = CP_DECL_CONTEXT (TREE_CODE (inner) == NAMESPACE_DECL ? inner : TYPE_NAME (inner));
  if (outer != prev)
    push_inner_scope_r (outer, prev);
  if (TREE_CODE (inner) == NAMESPACE_DECL)
    {
      cp_binding_level *save_template_parm = 0;


      while (current_binding_level->kind == sk_template_parms)
	{
	  cp_binding_level *b = current_binding_level;
	  current_binding_level = b->level_chain;
	  b->level_chain = save_template_parm;
	  save_template_parm = b;
	}

      resume_scope (NAMESPACE_LEVEL (inner));
      current_namespace = inner;


      while (save_template_parm)
	{
	  cp_binding_level *b = save_template_parm;
	  save_template_parm = b->level_chain;
	  b->level_chain = current_binding_level;
	  current_binding_level = b;
	}
    }
  else
    pushclass (inner);
}
