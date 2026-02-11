has_function_state (struct cgraph_node *node)
{
  if (!funct_state_vec
      || VEC_length (funct_state, funct_state_vec) <= (unsigned int)node->uid)
    return false;
  return VEC_index (funct_state, funct_state_vec, node->uid) != NULL;
}
