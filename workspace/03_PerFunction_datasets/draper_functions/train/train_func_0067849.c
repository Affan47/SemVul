__load_mdrwire(register struct net_t *np)
{
 register struct net_pin_t *npp;
 register struct xstk_t *xsp;


 push_xstk_(xsp, np->nwid);

 zero_allbits_(xsp->ap, np->nwid);
 one_allbits_(xsp->bp, np->nwid);


 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {

   if (npp->npproctyp == NP_PROC_FILT
    && npp->npaux->npu.filtitp != __inst_ptr) continue;
   ldcomb_driver(xsp, np, npp);
  }
 return(xsp);
}
