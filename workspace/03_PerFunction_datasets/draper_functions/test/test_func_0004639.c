arm_pcs_from_attribute (tree attr)
{
  const struct pcs_attribute_arg *ptr;
  const char *arg;


  if (TREE_VALUE (attr) == NULL_TREE
      || TREE_CODE (TREE_VALUE (attr)) != STRING_CST)
    return ARM_PCS_UNKNOWN;

  arg = TREE_STRING_POINTER (TREE_VALUE (attr));


  for (ptr = pcs_attribute_args; ptr->arg != NULL; ptr++)
    if (streq (arg, ptr->arg))
      return ptr->value;


  return ARM_PCS_UNKNOWN;
}
