pp_cxx_template_parameter_list (cxx_pretty_printer *pp, tree t)
{
  const int n = TREE_VEC_LENGTH (t);
  int i;
  for (i = 0; i < n; ++i)
    {
      if (i)
	pp_cxx_separate_with (pp, ',');
      pp_cxx_template_parameter (pp, TREE_VEC_ELT (t, i));
    }
}
