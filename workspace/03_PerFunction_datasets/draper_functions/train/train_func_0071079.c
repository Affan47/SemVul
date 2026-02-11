prep_event_dctrl(struct delctrl_t *dctp)
{
 register struct expr_t *xp;
 struct expr_t *evx;
 struct paramlst_t *pmp;


 pmp = dctp->dc_du.pdels;
 evx = pmp->plxndp;

 __my_free((char *) pmp, sizeof(struct paramlst_t));
 dctp->dc_du.d1x = evx;
 dctp->dc_delrep = DT_1X;


 if (evx == NULL)
  {
   __sgfwarn(3139,
    "implicit event control - no events in statement - will never trigger");
   return;
  }

 if (evx->optyp != OPEVOR && evx->optyp != OPEVCOMMAOR)
  { bld_ev_dces(evx, dctp); return; }


 for (xp = evx;;)
  {
   bld_ev_dces(xp->ru.x, dctp);
   if (xp->lu.x->optyp != OPEVOR && xp->lu.x->optyp != OPEVCOMMAOR)
    {

     bld_ev_dces(xp->lu.x, dctp);
     break;
    }
   xp = xp->lu.x;
  }
}
