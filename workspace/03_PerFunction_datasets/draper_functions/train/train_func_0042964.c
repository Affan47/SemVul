gimple_call_fnspec (const_gimple stmt)
{
  tree type, attr;

  type = gimple_call_fntype (stmt);
  if (!type)
    return NULL_TREE;

  attr = lookup_attribute ("fn spec", TYPE_ATTRIBUTES (type));
  if (!attr)
    return NULL_TREE;

  return TREE_VALUE (TREE_VALUE (attr));
}
