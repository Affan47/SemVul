chk_pthels(struct spcpth_t *pthp)
{
 register int32 pei;
 struct pathel_t *pep;
 struct net_t *np;
 int32 gd_path;

 gd_path = TRUE;
 for (pei = 0; pei <= pthp->last_pein; pei++)
  {
   pep = &(pthp->peins[pei]);
   np = pep->penp;

   if (!np->n_isapthsrc) __misc_terr(__FILE__, __LINE__);


  }
 for (pei = 0; pei <= pthp->last_peout; pei++)
  {
   pep = &(pthp->peouts[pei]);
   np = pep->penp;
   if (np->n_isavec && !np->vec_scalared)
    {
     __gferr(825, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "vectored path destination wire %s illegal - must be scalared",
      np->nsym->synam);
     gd_path = FALSE;
    }


   if (np->ntyp == N_TRIREG)
    {
     __gferr(826, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "path destination wire %s illegal trireg type", np->nsym->synam);
     gd_path = FALSE;
    }
   else if (!np->n_isapthdst
    || (np->nrngrep == NX_DWIR && np->nu.rngdwir->n_delrep != DT_PTHDST))
    {
     __gferr(826, pthp->pthsym->syfnam_ind, pthp->pthsym->sylin_cnt,
      "path destination wire %s illegal - has wire delay", np->nsym->synam);
     gd_path = FALSE;
    }
  }
 return(gd_path);
}
