ipa_free_all_edge_args (void)
{
  int i;
  struct ipa_edge_args *args;

  FOR_EACH_VEC_ELT (ipa_edge_args_t, ipa_edge_args_vector, i, args)
    ipa_free_edge_args_substructures (args);

  VEC_free (ipa_edge_args_t, gc, ipa_edge_args_vector);
  ipa_edge_args_vector = NULL;
}
