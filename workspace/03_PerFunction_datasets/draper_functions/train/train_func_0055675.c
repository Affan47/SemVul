pp_cxx_template_argument_list (cxx_pretty_printer *pp, tree t)
{
  int i;
  bool need_comma = false;

  if (t == NULL)
    return;
  for (i = 0; i < TREE_VEC_LENGTH (t); ++i)
    {
      tree arg = TREE_VEC_ELT (t, i);
      tree argpack = NULL_TREE;
      int idx, len = 1;

      if (ARGUMENT_PACK_P (arg))
	{
	  argpack = ARGUMENT_PACK_ARGS (arg);
	  len = TREE_VEC_LENGTH (argpack);
	}

      for (idx = 0; idx < len; idx++)
	{
	  if (argpack)
	    arg = TREE_VEC_ELT (argpack, idx);

	  if (need_comma)
	    pp_cxx_separate_with (pp, ',');
	  else
	    need_comma = true;

	  if (TYPE_P (arg) || (TREE_CODE (arg) == TEMPLATE_DECL
			       && TYPE_P (DECL_TEMPLATE_RESULT (arg))))
	    pp_cxx_type_id (pp, arg);
	  else
	    pp_cxx_expression (pp, arg);
	}
    }
}
