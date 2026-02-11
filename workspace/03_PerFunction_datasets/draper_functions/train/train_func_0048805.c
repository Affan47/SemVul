cx_check_missing_mem_inits (tree fun, tree body, bool complain)
{
  bool bad;
  tree field;
  unsigned i, nelts;
  tree ctype;

  if (TREE_CODE (body) != CONSTRUCTOR)
    return false;

  nelts = CONSTRUCTOR_NELTS (body);
  ctype = DECL_CONTEXT (fun);
  field = TYPE_FIELDS (ctype);

  if (TREE_CODE (ctype) == UNION_TYPE)
    {
      if (nelts == 0 && next_initializable_field (field))
	{
	  if (complain)
	    error ("%<constexpr%> constructor for union %qT must "
		   "initialize exactly one non-static data member", ctype);
	  return true;
	}
      return false;
    }

  bad = false;
  for (i = 0; i <= nelts; ++i)
    {
      tree index;
      if (i == nelts)
	index = NULL_TREE;
      else
	{
	  index = CONSTRUCTOR_ELT (body, i)->index;

	  if (TREE_CODE (index) != FIELD_DECL
	      || DECL_ARTIFICIAL (index))
	    continue;
	}
      for (; field != index; field = DECL_CHAIN (field))
	{
	  tree ftype;
	  if (TREE_CODE (field) != FIELD_DECL
	      || (DECL_C_BIT_FIELD (field) && !DECL_NAME (field))
	      || DECL_ARTIFICIAL (field))
	    continue;
	  ftype = strip_array_types (TREE_TYPE (field));
	  if (type_has_constexpr_default_constructor (ftype))
	    {


	      gcc_checking_assert (!TYPE_HAS_COMPLEX_DFLT (ftype)
				   || errorcount != 0);
	      continue;
	    }
	  if (!complain)
	    return true;
	  error ("uninitialized member %qD in %<constexpr%> constructor",
		 field);
	  bad = true;
	}
      if (field == NULL_TREE)
	break;
      field = DECL_CHAIN (field);
    }

  return bad;
}
