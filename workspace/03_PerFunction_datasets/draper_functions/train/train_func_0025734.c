hmm2ij_state_step4_update_safe_holders(int v, int n, int imin_v, int jmax_v, int *nss_max_imin,
				       int *nss_min_jmax)
{
  if(imin_v > nss_max_imin[n])
    nss_max_imin[n] = imin_v;
  if(jmax_v < nss_min_jmax[n])
    nss_min_jmax[n] = jmax_v;
}
