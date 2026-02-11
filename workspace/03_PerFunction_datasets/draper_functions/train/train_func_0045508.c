var_can_have_subvars (const_tree v)
{

  if (TREE_THIS_VOLATILE (v))
    return false;


  if (!DECL_P (v))
    return false;

  return type_can_have_subvars (TREE_TYPE (v));
}
