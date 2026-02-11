replace_phis_by_defined_names (VEC (chain_p, heap) *chains)
{
  chain_p chain;
  dref a;
  unsigned i, j;

  FOR_EACH_VEC_ELT (chain_p, chains, i, chain)
    FOR_EACH_VEC_ELT (dref, chain->refs, j, a)
      {
	if (gimple_code (a->stmt) == GIMPLE_PHI)
	  {
	    a->name_defined_by_phi = PHI_RESULT (a->stmt);
	    a->stmt = NULL;
	  }
      }
}
