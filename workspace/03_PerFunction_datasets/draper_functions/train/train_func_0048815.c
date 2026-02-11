__reinit_netdrvr_putvrec(struct net_t *np, struct mod_t *mdp)
{
 register int32 bi, di, ii;
 register struct dltevlst_t *dlp, *dlp2, *last_dlp;
 struct vpi_drv_t *vpidrvp;

 for (di = 0;; di++)
  {
   if ((vpidrvp = np->vpi_ndrvs[di]) == NULL) break;


   if (vpidrvp->vpi_drvwp.wp == NULL) __arg_terr(__FILE__, __LINE__);

   putv_drvwp_allocinit(mdp, np, vpidrvp, FALSE);


   for (ii = 0; ii < mdp->flatinum; ii++)
    {

     for (bi = np->nwid - 1; bi >= 0; bi--)
      {
       if ((dlp = vpidrvp->putv_drv_tedlst[ii*np->nwid + bi]) == NULL)
        continue;
       last_dlp = NULL;
       for (dlp2 = dlp; dlp2 != NULL; dlp2 = dlp2->terp) last_dlp = dlp2;

       if (last_dlp != NULL) last_dlp->terp = __dltevfreelst;
       __dltevfreelst = dlp;
       vpidrvp->putv_drv_tedlst[ii*np->nwid + bi] = NULL;
      }
    }
  }
}
