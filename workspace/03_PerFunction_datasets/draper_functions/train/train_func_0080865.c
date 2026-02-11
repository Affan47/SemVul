is_gimple_call_addr (tree t)
{
  return (TREE_CODE (t) == OBJ_TYPE_REF || is_gimple_val (t));
}
