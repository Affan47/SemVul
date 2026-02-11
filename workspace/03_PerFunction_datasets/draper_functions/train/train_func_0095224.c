get_component_var (tree var, bool imag_p)
{
  size_t decl_index = DECL_UID (var) * 2 + imag_p;
  tree ret = cvc_lookup (decl_index);

  if (ret == NULL)
    {
      ret = create_one_component_var (TREE_TYPE (TREE_TYPE (var)), var,
				      imag_p ? "CI" : "CR",
				      imag_p ? "$imag" : "$real",
				      imag_p ? IMAGPART_EXPR : REALPART_EXPR);
      cvc_insert (decl_index, ret);
    }

  return ret;
}
