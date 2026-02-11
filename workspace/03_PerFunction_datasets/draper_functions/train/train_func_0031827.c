check_instantiated_arg (tree tmpl, tree t, tsubst_flags_t complain)
{
  if (ARGUMENT_PACK_P (t))
    {
      tree vec = ARGUMENT_PACK_ARGS (t);
      int len = TREE_VEC_LENGTH (vec);
      bool result = false;
      int i;

      for (i = 0; i < len; ++i)
	if (check_instantiated_arg (tmpl, TREE_VEC_ELT (vec, i), complain))
	  result = true;
      return result;
    }
  else if (TYPE_P (t))
    {


      tree nt = (cxx_dialect > cxx98 ? NULL_TREE
		 : no_linkage_check (t, false));

      if (nt)
	{


	  if (complain & tf_error)
	    {
	      if (TYPE_ANONYMOUS_P (nt))
		error ("%qT is/uses anonymous type", t);
	      else
		error ("template argument for %qD uses local type %qT",
		       tmpl, t);
	    }
	  return true;
	}


      else if (variably_modified_type_p (t, NULL_TREE))
	{
	  if (complain & tf_error)
	    error ("%qT is a variably modified type", t);
	  return true;
	}
    }


  else if (TREE_TYPE (t)
	   && INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (t))
	   && !TREE_CONSTANT (t))
    {
      if (complain & tf_error)
	error ("integral expression %qE is not constant", t);
      return true;
    }
  return false;
}
