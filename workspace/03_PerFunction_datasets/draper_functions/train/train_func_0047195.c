init_out_fp()
{
  if (!out_fp) {
    if (getenv("GCIN_DBG_TMP") || 0) {
      char fname[64];
      sprintf(fname, "/tmp/gcindbg-%d-%d", getuid(), getpid());
      out_fp = fopen(fname, "w");
    }

    if (!out_fp)
      out_fp = stdout;
  }
}
