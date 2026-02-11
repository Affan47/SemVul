lam_ssi_rpi_crtcp_init(struct _proc **crtcp_procs, int nprocs,
		       int *max_tag, int *max_cid)
{
#if LAM_WANT_DEBUG
  char prefix[256];
  char suffix[256];
  lam_debug_stream_info_t lds = {0, 0, 0, NULL, NULL, 0, 1, 1, 0, NULL};
#endif


  PUB(short) = lam_ssi_base_param_lookup_int(param_short);
  crtcp_sockbuf = lam_ssi_base_param_lookup_int(param_sockbuf);
  if (crtcp_sockbuf < 0) {
    crtcp_sockbuf = PUB(short);
  }

  if (lam_ssi_verbose >= 0) {
    lam_debug(lam_ssi_did, "crtcp RPI module initializing");
    lam_debug(lam_ssi_did, "rpi:crtcp:short: %d", PUB(short));
    lam_debug(lam_ssi_did, "rpi:crtcp:sockbuf: %d", crtcp_sockbuf);
    lam_debug(lam_ssi_did, "rpi:crtcp:verbose: %d", PUB(verbose));
  }

#if LAM_WANT_DEBUG

  snprintf(prefix, sizeof(prefix), "<n%d/%d/%d>crtcp: ",
           getnodeid(), lam_getpid(), lam_myproc->p_gps.gps_grank);
  snprintf(suffix, sizeof(suffix), "crtcp-rank-%d.txt",
           lam_myproc->p_gps.gps_grank);

  lds.lds_prefix = prefix;
  lds.lds_fl_file_append = 0;
  lds.lds_file_suffix = suffix;
  PUB(did) = lam_debug_open(&lds);
#else
  PUB(did) = -1;
#endif
  PUB(verbose) = lam_ssi_rpi_verbose;

  if (PUB(verbose) >= 10)
    lam_debug(PUB(did), "in crtcp init function");


  if (lam_ssi_rpi_crtcp_addprocs(crtcp_procs, nprocs)) {
    if (PUB(verbose) >= 50)
      lam_debug(PUB(did), "ASYNC%d: addprocs failed", getpid());
    return NULL;
  }


  return &module_actions;
}
