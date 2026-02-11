nccf_inq_lvl_sigma(int ncid, char *name, nc_type *xtypep, size_t *lenp,
		   int *ps_varidp, int *ptop_varidp, int *lvl_dimidp,
		   int *lvl_varidp)
{
   int termids[FT_SIGMA_TERMS];
   int ret;


   if ((ret = inq_vert_var(ncid, STD_SIGMA, FT_SIGMA_TERMS, FT_SIGMA_FORMAT,
			   termids, name, xtypep, lenp, lvl_dimidp, lvl_varidp)))
      return ret;


   if (ps_varidp)
      *ps_varidp = termids[1];
   if (ptop_varidp)
      *ptop_varidp = termids[2];

   return CF_NOERR;
}
