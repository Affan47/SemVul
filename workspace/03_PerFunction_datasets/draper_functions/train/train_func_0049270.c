_gcry_ecc_update_curve_param (const char *name,
                              enum gcry_mpi_ec_models *model,
                              enum ecc_dialects *dialect,
                              gcry_mpi_t *p, gcry_mpi_t *a, gcry_mpi_t *b,
                              gcry_mpi_t *g, gcry_mpi_t *n)
{
  int idx;

  idx = find_domain_parms_idx (name);
  if (idx < 0)
    return GPG_ERR_UNKNOWN_CURVE;

  if (g)
    {
      char *buf;
      size_t len;

      len = 4;
      len += strlen (domain_parms[idx].g_x+2);
      len += strlen (domain_parms[idx].g_y+2);
      len++;
      buf = xtrymalloc (len);
      if (!buf)
        return gpg_err_code_from_syserror ();
      strcpy (stpcpy (stpcpy (buf, "0x04"), domain_parms[idx].g_x+2),
              domain_parms[idx].g_y+2);
      _gcry_mpi_release (*g);
      *g = scanval (buf);
      xfree (buf);
    }
  if (model)
    *model = domain_parms[idx].model;
  if (dialect)
    *dialect = domain_parms[idx].dialect;
  if (p)
    {
      _gcry_mpi_release (*p);
      *p = scanval (domain_parms[idx].p);
    }
  if (a)
    {
      _gcry_mpi_release (*a);
      *a = scanval (domain_parms[idx].a);
    }
  if (b)
    {
      _gcry_mpi_release (*b);
      *b = scanval (domain_parms[idx].b);
    }
  if (n)
    {
      _gcry_mpi_release (*n);
      *n = scanval (domain_parms[idx].n);
    }
  return 0;
}
