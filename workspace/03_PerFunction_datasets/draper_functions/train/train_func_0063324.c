emutls_decl (tree decl)
{
  struct varpool_node *var;
  unsigned int i;

  i = emutls_index (decl);
  var = VEC_index (varpool_node_ptr, control_vars, i);
  return var->decl;
}
