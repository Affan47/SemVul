dump_template_argument_list (tree args, int flags)
{
  int n = get_non_default_template_args_count (args, flags);
  int need_comma = 0;
  int i;

  for (i = 0; i < n; ++i)
    {
      tree arg = TREE_VEC_ELT (args, i);


      if (need_comma
          && (!ARGUMENT_PACK_P (arg)
              || TREE_VEC_LENGTH (ARGUMENT_PACK_ARGS (arg)) > 0))
	pp_separate_with_comma (cxx_pp);

      dump_template_argument (arg, flags);
      need_comma = 1;
    }
}
