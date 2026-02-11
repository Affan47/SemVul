gen_scheduled_generic_parms_dies (void)
{
  unsigned i;
  tree t;

  if (generic_type_instances == NULL)
    return;

  FOR_EACH_VEC_ELT (tree, generic_type_instances, i, t)
    gen_generic_params_dies (t);
}
