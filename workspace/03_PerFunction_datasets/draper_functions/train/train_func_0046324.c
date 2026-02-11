lam_ssi_boot_base_find_boot_schema(OPT *aod)
{
  char *bhost;
  char *fname;
  char **pathv = 0;
  int pathc = 0;
  int unusedc;
  char **unusedv;


  sfh_argv_add(&pathc, &pathv, "");
  sfh_argv_add(&pathc, &pathv, "$TROLLIUSHOME/etc");
  sfh_argv_add(&pathc, &pathv, "$LAMHOME/etc");
  sfh_argv_add(&pathc, &pathv, LAM_SYSCONFDIR);
  if (lam_ssi_boot_verbose >= 1) {
    int i;
    lam_debug(lam_ssi_boot_did,
	      "base: looking for boot schema in following directories:");
    lam_debug(lam_ssi_boot_did, "base:   <current directory>");
    for (i = 1; i < pathc; ++i)
      lam_debug(lam_ssi_boot_did, "base:   %s", pathv[i]);
  }


  ao_unused(aod, &unusedc, &unusedv);
  if (unusedc == 2) {
    fname = unusedv[1];
  } else if ((fname = getenv("LAMBHOST"))) {
  } else if ((fname = getenv("TROLLIUSBHOST"))) {
  } else {
    fname = DEFFBHOST;
  }
  if (lam_ssi_boot_verbose >= 1) {
    lam_debug(lam_ssi_boot_did, "base: looking for boot schema file:");
    lam_debug(lam_ssi_boot_did, "base:   %s", fname);
  }


  bhost = sfh_path_findv(fname, pathv, R_OK, environ);
  sfh_argv_free(pathv);


  if (lam_ssi_boot_verbose >= 1)
    lam_debug(lam_ssi_boot_did, "base: found boot schema: %s",
	      (bhost != NULL) ? bhost : "Not found!");
  if (bhost == 0)
    show_help("boot", "find-hostfile", fname, NULL);


  return bhost;
}
