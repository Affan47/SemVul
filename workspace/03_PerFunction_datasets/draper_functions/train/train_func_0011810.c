create_tmp_from_val (tree val, bool is_formal)
{

  tree type = TYPE_MAIN_VARIANT (TREE_TYPE (val));
  tree var = create_tmp_var (type, get_name (val));
  if (is_formal
      && (TREE_CODE (TREE_TYPE (var)) == COMPLEX_TYPE
	  || TREE_CODE (TREE_TYPE (var)) == VECTOR_TYPE))
    DECL_GIMPLE_REG_P (var) = 1;
  return var;
}
