conversion_null_warnings (tree totype, tree expr, tree fn, int argnum)
{

  if (expr == null_node && TREE_CODE (totype) != BOOLEAN_TYPE
      && ARITHMETIC_TYPE_P (totype))
    {
      if (fn)
	warning_at (input_location, OPT_Wconversion_null,
		    "passing NULL to non-pointer argument %P of %qD",
		    argnum, fn);
      else
	warning_at (input_location, OPT_Wconversion_null,
		    "converting to non-pointer type %qT from NULL", totype);
    }


  else if (TREE_CODE (TREE_TYPE (expr)) == BOOLEAN_TYPE
	   && TYPE_PTR_P (totype))
    {
      if (fn)
	warning_at (input_location, OPT_Wconversion_null,
		    "converting %<false%> to pointer type for argument %P "
		    "of %qD", argnum, fn);
      else
	warning_at (input_location, OPT_Wconversion_null,
		    "converting %<false%> to pointer type %qT", totype);
    }
}
