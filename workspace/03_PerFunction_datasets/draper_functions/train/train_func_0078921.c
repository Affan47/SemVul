immed_vpibit_drv_assign(struct net_t *np, int32 di, int32 bi,
 word32 *ap, word32 *bp)
{
 byte *sbp, *sbp2;
 struct vpi_drv_t *vpidrvp;
 struct xstk_t *xsp;

 vpidrvp = np->vpi_ndrvs[di];

 if (bi == -1) __vpi_terr(__FILE__, __LINE__);


 if (np->n_stren)
  {
   sbp = (byte *) ap;
   sbp2 = &(vpidrvp->vpi_drvwp.bp[__inum*np->nwid + bi]);
   sbp2[0] = sbp[0];
  }

 else
  {
   push_xstk_(xsp, np->nwid);
   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_drvwp, np->nwid);
   __lhsbsel(xsp->ap, bi, ap[0]);
   __lhsbsel(xsp->bp, bi, bp[0]);
   __st_perinst_val(vpidrvp->vpi_drvwp, np->nwid, xsp->ap, xsp->bp);
   __pop_xstk();
  }


 if (np->ntraux != NULL)
  {


   if (__update_tran_harddrvs(np)) __eval_tran_bits(np);
  }
 else
  {
   if (np->nrngrep == NX_DWIR) __sched_1mdrwire(np);
   else __assign_1mdrwire(np);
  }
}
