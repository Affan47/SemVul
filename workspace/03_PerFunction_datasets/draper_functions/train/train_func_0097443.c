truth_type_for (tree type)
{
  if (TREE_CODE (type) == VECTOR_TYPE)
    {
      tree elem = lang_hooks.types.type_for_size
        (GET_MODE_BITSIZE (TYPE_MODE (TREE_TYPE (type))), 0);
      return build_opaque_vector_type (elem, TYPE_VECTOR_SUBPARTS (type));
    }
  else
    return boolean_type_node;
}
