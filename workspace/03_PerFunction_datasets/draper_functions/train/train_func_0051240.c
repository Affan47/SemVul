__reschedule_1wev(i_tev_ndx tevpi, word32 newval, word64 ndel,
 word64 newtim, i_tev_ndx *itevpi)
{
 struct tenp_t *tenp;
 struct tev_t *tevp;

 tevp = &(__tevtab[tevpi]);

 if (ndel == 0ULL)
  {

   __newval_rescheds++;
   tevp->outv = (byte) newval;
   return;
  }
 tenp = tevp->tu.tenp;

 __schedule_1wev(tenp->tenu.np, tenp->nbi, (int32) tevp->tetyp, ndel,
  newtim, newval, itevpi, (int32) tevp->te_trdecay);
 __cancel_1wev(tevp);
}
