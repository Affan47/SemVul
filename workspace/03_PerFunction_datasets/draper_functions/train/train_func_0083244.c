get_alias_set (t)
     tree t;
{
  HOST_WIDE_INT set;


  if (! flag_strict_aliasing || t == error_mark_node
      || (! TYPE_P (t)
	  && (TREE_TYPE (t) == 0 || TREE_TYPE (t) == error_mark_node)))
    return 0;


  if (! TYPE_P (t))
    {
      tree inner = t;
      tree placeholder_ptr = 0;


      STRIP_NOPS (t);
      set = (*lang_hooks.get_alias_set) (t);
      if (set != -1)
	return set;


      while (TREE_CODE (inner) == PLACEHOLDER_EXPR
	     || handled_component_p (inner))
	{
	  if (TREE_CODE (inner) == PLACEHOLDER_EXPR)
	    inner = find_placeholder (inner, &placeholder_ptr);
	  else
	    inner = TREE_OPERAND (inner, 0);

	  STRIP_NOPS (inner);
	}


      if (TREE_CODE (inner) == INDIRECT_REF)
	{
	  tree decl = find_base_decl (TREE_OPERAND (inner, 0));

	  if (decl && DECL_POINTER_ALIAS_SET_KNOWN_P (decl))
	    {

	      if (DECL_POINTER_ALIAS_SET (decl) == -2)
		{
		  tree pointed_to_type = TREE_TYPE (TREE_TYPE (decl));


		  HOST_WIDE_INT pointed_to_alias_set
		    = get_alias_set (pointed_to_type);

		  if (pointed_to_alias_set == 0)

		    DECL_POINTER_ALIAS_SET (decl) = 0;
		  else if (AGGREGATE_TYPE_P (pointed_to_type))


		    DECL_POINTER_ALIAS_SET (decl)
		      = pointed_to_alias_set;
		  else
		    {
		      DECL_POINTER_ALIAS_SET (decl) = new_alias_set ();
		      record_alias_subset (pointed_to_alias_set,
					   DECL_POINTER_ALIAS_SET (decl));
		    }
		}


	      return DECL_POINTER_ALIAS_SET (decl);
	    }


	  else if (TREE_CODE (TREE_TYPE (inner)) == VOID_TYPE)
	    return 0;
	}


      placeholder_ptr = 0;
      while (TREE_CODE (t) == PLACEHOLDER_EXPR
	     || (handled_component_p (t) && ! can_address_p (t)))
	{
	  if (TREE_CODE (t) == PLACEHOLDER_EXPR)
	    t = find_placeholder (t, &placeholder_ptr);
	  else
	    t = TREE_OPERAND (t, 0);

	  STRIP_NOPS (t);
	}


      if (TREE_CODE (t) == VAR_DECL
	  && DECL_RTL_SET_P (t) && GET_CODE (DECL_RTL (t)) == MEM)
	return MEM_ALIAS_SET (DECL_RTL (t));


      t = TREE_TYPE (t);
    }


  t = TYPE_MAIN_VARIANT (t);
  if (TYPE_ALIAS_SET_KNOWN_P (t))
    return TYPE_ALIAS_SET (t);


  set = (*lang_hooks.get_alias_set) (t);
  if (set != -1)
    return set;


  else if (TREE_CODE (t) == FUNCTION_TYPE)
    set = 0;


  else if (TREE_CODE (t) == VECTOR_TYPE)
    set = get_alias_set (TREE_TYPE (t));

  else

    set = new_alias_set ();

  TYPE_ALIAS_SET (t) = set;


  if (AGGREGATE_TYPE_P (t) || TREE_CODE (t) == COMPLEX_TYPE)
    record_component_aliases (t);

  return set;
}
