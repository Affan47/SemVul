hmm2ij_prestate_step2_determine_safe(int n,
				     int nss_max_imin_np1, int nss_min_jmax_np1,
				     int nis_imin_n,
				     int nis_jmax_n,
				     int *safe_imax, int *safe_jmin)
{
  *safe_imax = (nss_max_imin_np1 < nis_imin_n) ?
    nss_max_imin_np1 : nis_imin_n;
  *safe_jmin = (nss_min_jmax_np1 > nis_jmax_n) ?
    nss_min_jmax_np1 : nis_jmax_n;
}
