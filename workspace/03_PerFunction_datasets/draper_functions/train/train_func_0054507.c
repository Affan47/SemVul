expand_template_argument_pack (tree args)
{
  tree result_args = NULL_TREE;
  int in_arg, out_arg = 0, nargs = args ? TREE_VEC_LENGTH (args) : 0;
  int num_result_args = -1;
  int non_default_args_count = -1;


  for (in_arg = 0; in_arg < nargs; ++in_arg)
    {
      tree arg = TREE_VEC_ELT (args, in_arg);
      if (arg == NULL_TREE)
	return args;
      if (ARGUMENT_PACK_P (arg))
        {
          int num_packed = TREE_VEC_LENGTH (ARGUMENT_PACK_ARGS (arg));
          if (num_result_args < 0)
            num_result_args = in_arg + num_packed;
          else
            num_result_args += num_packed;
        }
      else
        {
          if (num_result_args >= 0)
            num_result_args++;
        }
    }


  if (num_result_args < 0)
    return args;


  result_args = make_tree_vec (num_result_args);
  if (NON_DEFAULT_TEMPLATE_ARGS_COUNT (args))
    non_default_args_count =
      GET_NON_DEFAULT_TEMPLATE_ARGS_COUNT (args);
  for (in_arg = 0; in_arg < nargs; ++in_arg)
    {
      tree arg = TREE_VEC_ELT (args, in_arg);
      if (ARGUMENT_PACK_P (arg))
        {
          tree packed = ARGUMENT_PACK_ARGS (arg);
          int i, num_packed = TREE_VEC_LENGTH (packed);
          for (i = 0; i < num_packed; ++i, ++out_arg)
            TREE_VEC_ELT (result_args, out_arg) = TREE_VEC_ELT(packed, i);
	  if (non_default_args_count > 0)
	    non_default_args_count += num_packed - 1;
        }
      else
        {
          TREE_VEC_ELT (result_args, out_arg) = arg;
          ++out_arg;
        }
    }
  if (non_default_args_count >= 0)
    SET_NON_DEFAULT_TEMPLATE_ARGS_COUNT (result_args, non_default_args_count);
  return result_args;
}
