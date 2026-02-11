lam_ssi_rpi_sysv_init(struct _proc **procs, int nprocs,
		      int *maxtag, int *maxcid)
{


  lam_ssi_rpi_sysv_poll_yield =
    lam_ssi_base_param_lookup_int(param_poll_yield);
  lam_ssi_rpi_sysv_short =
    lam_ssi_base_param_lookup_int(param_short);
  lam_ssi_rpi_sysv_poolsize =
    lam_ssi_base_param_lookup_int(param_poolsize);
  lam_ssi_rpi_sysv_maxalloc =
    lam_ssi_base_param_lookup_int(param_maxalloc);

  lam_ssi_rpi_tcp_short =
    lam_ssi_base_param_lookup_int(param_tcp_short);
  tcp_sockbuf = lam_ssi_base_param_lookup_int(param_tcp_sockbuf);
  if (tcp_sockbuf < 0) {
    tcp_sockbuf = lam_ssi_rpi_tcp_short;
  }

  lam_ssi_rpi_sysv_maxalloc = lam_ssi_rpi_sysv_maxalloc >> LAM_LOG_ALIGN;

  if (lam_ssi_rpi_verbose >= 0) {
    lam_debug(lam_ssi_rpi_did, "sysv: module initializing");
    lam_debug(lam_ssi_rpi_did, "sysv:pollyield: %d",
	      lam_ssi_rpi_sysv_poll_yield);
    lam_debug(lam_ssi_rpi_did, "sysv:short: %d bytes",
	      lam_ssi_rpi_sysv_short);
    lam_debug(lam_ssi_rpi_did, "sysv:shmpoolsize: %d bytes",
	      lam_ssi_rpi_sysv_poolsize);
    lam_debug(lam_ssi_rpi_did, "sysv:shmmaxalloc: %d bytes",
	      lam_ssi_rpi_sysv_maxalloc);
    lam_debug(lam_ssi_rpi_did, "tcp:short: %d bytes",
	      lam_ssi_rpi_tcp_short);
    lam_debug(lam_ssi_rpi_did, "tcp:sockbuf: %d bytes", tcp_sockbuf);
  }


  if (lam_ssi_rpi_sysv_addprocs(procs, nprocs))
    return NULL;

  return &module_actions;
}
