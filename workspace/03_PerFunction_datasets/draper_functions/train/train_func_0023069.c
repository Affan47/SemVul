__emit_1showvar(struct net_t *np, struct gref_t *grp)
{
 register int32 i, bi;
 register struct net_pin_t *npp;
 int32 arrwid, obwid;
 i_tev_ndx tevpi, *teviarr;
 char s1[RECLEN], s2[RECLEN];


 if (np->n_isaparam) return;

 __cur_sofs = 0;

 __bld_showvars_prefix(s1, np, grp);

 if (np->ntyp == N_EVENT)
  { __cvsim_msg("%s **event**\n", s1); goto disp_drvs; }


 if (np->n_isarr)
  {
   __adds(" [");
   arrwid = __get_arrwide(np);

   if (arrwid > 4) obwid = 4; else obwid = arrwid;
   for (i = 0; i < obwid; i++)
    {
     if (i != 0) __adds(", ");
     __var_tostr(s2, np, i, i, BBIN);
     __adds(s2);
    }
   if (arrwid > obwid)
    { sprintf(__xs, ", ... <%d more>", arrwid - obwid); __adds(__xs); }
   __adds("]");
  }


 else __disp_var(np, -1, -1, BHEX, '?');
 __cvsim_msg("%s = %s\n", s1, __exprline);
 __cur_sofs = 0;


 if (np->nrngrep == NX_DWIR)
  {


   teviarr = &(np->nu.rngdwir->wschd_pbtevs[np->nwid*__inum]);
   if (np->n_isavec)
    {
     __cvsim_msg("   Per bit wire with delay scheduled values:\n");
     for (bi = np->nwid - 1; bi >= 0; bi--)
      {
       if ((tevpi = teviarr[bi]) != -1)
        {

         __cvsim_msg("    [%d] %s\n", __unnormalize_ndx(np, bi),
          __bld_valofsched(s1, &(__tevtab[tevpi])));
        }
      }
    }
   else if ((tevpi = teviarr[0]) != -1)
    {
    __cvsim_msg("scalar wire scheduled %s\n",
      __bld_valofsched(s1, &(__tevtab[tevpi])));
    }
  }


disp_drvs:

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  emit1_driver(np, npp, FALSE);

 for (npp = np->nlds; npp != NULL; npp = npp->npnxt) emit1_load(np, npp);
 __cur_sofs = 0;
}
