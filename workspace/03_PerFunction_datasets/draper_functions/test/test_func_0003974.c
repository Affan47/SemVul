__assign_1mdrwire(register struct net_t *np)
{
 register struct xstk_t *xsp;
 register byte *sbp;
 int32 sbi;
 byte *abp;
 word32 *app, *bpp;


 sbp = NULL;

 if (np->n_stren)
  {

   xsp = __stload_mdrwire(np);
   sbp = (byte *) xsp->ap;


   if (np->frc_assgn_allocated
    && !__correct_forced_newwireval(np, xsp->ap, xsp->bp))
    { __pop_xstk(); return; }

   get_stwire_addr_(abp, np);


   if (np->ntyp == N_TRIREG)
    {
     for (sbi = 0; sbi < np->nwid; sbi++)
      {
       if (sbp[sbi] == ST_HIZ)
        sbp[sbi] = (byte) ((abp[sbi] & 3) | __cap_to_stren[np->n_capsiz]);
      }
    }
   if (memcmp(abp, sbp, np->nwid) != 0)
    {
     memcpy(abp, sbp, np->nwid);
     __lhs_changed = TRUE;
    }
  }
 else
  {


   xsp = __load_mdrwire(np);

   if (np->frc_assgn_allocated
    && !__correct_forced_newwireval(np, xsp->ap, xsp->bp))
    { __pop_xstk(); return; }


   __ld_addr(&app, &bpp, np);
   if (np->nwid <= WBITS)
    { if (app[0] == xsp->ap[0] && bpp[0] == xsp->bp[0]) goto done; }
   else
    {
     if (cmp_vval_(app, xsp->ap, np->nwid) == 0
      && cmp_vval_(bpp, xsp->bp, np->nwid) == 0) goto done;
    }
   __st_val(np, xsp->ap, xsp->bp);
   __lhs_changed = TRUE;
  }

done:
 if (__ev_tracing)
  {
   char s1[RECLEN];

   if (np->n_stren) strcpy(s1, " strength"); else strcpy(s1, "");
   __tr_msg(" drivers of%s wire %s combined", s1, np->nsym->synam);
   if (__lhs_changed)
    {
     if (np->n_stren) __st_regab_tostr(__xs, sbp, np->nwid);
     else __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE);
     __tr_msg(" and assigned value %s\n", __xs);
    }
   else __tr_msg(" value unchanged\n");
  }
 if (__lhs_changed) record_nchg_(np);
 __pop_xstk();
}
