check_instantiated_args (tree tmpl, tree args, tsubst_flags_t complain)
{
  int ix, len = DECL_NTPARMS (tmpl);
  bool result = false;

  for (ix = 0; ix != len; ix++)
    {
      tree t = TREE_VEC_ELT (args, ix);

      if (TYPE_P (t))
	{


	  tree nt = no_linkage_check (t);

	  if (nt)
	    {
	      if (!(complain & tf_error))
		;
	      else if (TYPE_ANONYMOUS_P (nt))
		error ("`%T' uses anonymous type", t);
	      else
		error ("`%T' uses local type `%T'", t, nt);
	      result = true;
	    }


	  else if (variably_modified_type_p (t))
	    {
	      if (complain & tf_error)
		error ("`%T' is a variably modified type", t);
	      result = true;
	    }
	}


      else if (TREE_TYPE (t)
	       && INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (t))
	       && !TREE_CONSTANT (t))
	{
	  if (complain & tf_error)
	    error ("integral expression `%E' is not constant", t);
	  result = true;
	}
    }
  if (result && complain & tf_error)
    error ("  trying to instantiate `%D'", tmpl);
  return result;
}
