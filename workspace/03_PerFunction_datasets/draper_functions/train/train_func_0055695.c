add_function_candidate (struct z_candidate **candidates,
			tree fn, tree ctype, tree arglist,
			tree access_path, tree conversion_path,
			int flags)
{
  tree parmlist = TYPE_ARG_TYPES (TREE_TYPE (fn));
  int i, len;
  tree convs;
  tree parmnode, argnode;
  tree orig_arglist;
  int viable = 1;


  if (DECL_ANTICIPATED (fn))
    return NULL;


  if (DECL_CONSTRUCTOR_P (fn))
    {
      parmlist = skip_artificial_parms_for (fn, parmlist);
      orig_arglist = arglist;
      arglist = skip_artificial_parms_for (fn, arglist);
    }
  else
    orig_arglist = arglist;

  len = list_length (arglist);
  convs = make_tree_vec (len);


  parmnode = parmlist;
  for (i = 0; i < len; ++i)
    {
      if (parmnode == NULL_TREE || parmnode == void_list_node)
	break;
      parmnode = TREE_CHAIN (parmnode);
    }

  if (i < len && parmnode)
    viable = 0;


  else if (!sufficient_parms_p (parmnode))
    viable = 0;

  if (! viable)
    goto out;


  parmnode = parmlist;
  argnode = arglist;

  for (i = 0; i < len; ++i)
    {
      tree arg = TREE_VALUE (argnode);
      tree argtype = lvalue_type (arg);
      tree t;
      int is_this;

      if (parmnode == void_list_node)
	break;

      is_this = (i == 0 && DECL_NONSTATIC_MEMBER_FUNCTION_P (fn)
		 && ! DECL_CONSTRUCTOR_P (fn));

      if (parmnode)
	{
	  tree parmtype = TREE_VALUE (parmnode);


	  if (ctype && is_this)
	    {
	      parmtype
		= build_qualified_type (ctype,
					TYPE_QUALS (TREE_TYPE (parmtype)));
	      parmtype = build_pointer_type (parmtype);
	    }

	  t = implicit_conversion (parmtype, argtype, arg, flags);
	}
      else
	{
	  t = build1 (IDENTITY_CONV, argtype, arg);
	  ICS_ELLIPSIS_FLAG (t) = 1;
	}

      if (t && is_this)
	ICS_THIS_FLAG (t) = 1;

      TREE_VEC_ELT (convs, i) = t;
      if (! t)
	{
	  viable = 0;
	  break;
	}

      if (ICS_BAD_FLAG (t))
	viable = -1;

      if (parmnode)
	parmnode = TREE_CHAIN (parmnode);
      argnode = TREE_CHAIN (argnode);
    }

 out:
  return add_candidate (candidates, fn, orig_arglist, convs, access_path,
			conversion_path, viable);
}
