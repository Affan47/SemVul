clear_access_vars (void)
{
  memset (VEC_address (tree, access_vars), 0,
          VEC_length (tree, access_vars) * sizeof(tree));
}
