reschedule_1caev(i_tev_ndx tevpi, word64 cadel,
 word64 newtim, struct xstk_t *schd_xsp)
{
 struct tev_t *tevp;
 struct conta_t *cap;

 tevp = &(__tevtab[tevpi]);

 cap = tevp->tu.tecap;
 if (cadel == 0ULL)
  {

   __newval_rescheds++;

   __st_perinst_val(cap->schd_drv_wp, schd_xsp->xslen, schd_xsp->ap,
    schd_xsp->bp);
   return;
  }

 tevp->te_cancel = TRUE;
 __inertial_cancels++;

 schedule_1caev(cap, cadel, newtim, schd_xsp);
}
