find_bb_for_arg (gimple phi, tree def)
{
  size_t i;
  bool foundone = false;
  basic_block result = NULL;
  for (i = 0; i < gimple_phi_num_args (phi); i++)
    if (PHI_ARG_DEF (phi, i) == def)
      {
	if (foundone)
	  return NULL;
	foundone = true;
	result = gimple_phi_arg_edge (phi, i)->src;
      }
  return result;
}
