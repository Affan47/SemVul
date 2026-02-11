crtcp_proc_read_extra(struct lam_ssi_rpi_proc *ps)
{
  char sink[512];
  int nread;
  char *bogus;

  do {
    bogus = sink;
    nread = sread(ps, &bogus, &ps->cp_extra, sizeof(sink));
    if (nread <= 0)
      return (nread);
    ps->cp_extra -= nread;
  } while (ps->cp_extra > 0);


  ps->cp_readfn = lam_ssi_rpi_crtcp_proc_read_env;
  return (0);
}
