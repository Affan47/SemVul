vfy_find_class (vfy_jclass ignore ATTRIBUTE_UNUSED, vfy_string name)
{
  vfy_jclass k;

  k = get_type_from_signature (name);
  if (TREE_CODE (k) == POINTER_TYPE)
    k = TREE_TYPE (k);

  return k;
}
