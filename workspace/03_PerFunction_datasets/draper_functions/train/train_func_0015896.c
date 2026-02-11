sread_app_suspend(struct lam_ssi_rpi_proc *ps)
{
  unsigned int in_nbytes = ps->cp_in_nbytes;

  if (PUB(verbose) >= 40)
    lam_debug(PUB(did),
	      "sread yielding to handler: "
	      "current bookmark rank %d = %u",
	      ps->cp_proc->p_gps.gps_grank, ps->cp_in_nbytes);


  lam_ssi_crmpi.lscrma_app_suspend();

#if 0
  if (PUB(is_sread_in_fast)) {


    if (PUB(verbose) >= 40)
      lam_debug(PUB(did), "_fast sread: returned from yield.");
  } else {
#endif


    if (PUB(verbose) >= 40)
      lam_debug(PUB(did),
		"sread back from handler: "
		"current bookmark rank %d = %u",
		ps->cp_proc->p_gps.gps_grank,
		ps->cp_in_nbytes);

    if (ps->cp_in_nbytes != in_nbytes) {
      if (PUB(verbose) >= 40)
        lam_debug(PUB(did), "sread: something changed -- returning");
      return 1;
    }
    if (PUB(verbose) >= 40)
      lam_debug(PUB(did), "sread: nothing changed -- continuing");
#if 0
  }
#endif

  return 0;
}
