__assgn_nonis_param(struct net_t *np, struct expr_t *xrhs,
 struct xstk_t *xsp)
{
 int32 owlen, nwlen;

 owlen = wlen_(np->nwid);
 nwlen = wlen_(xsp->xslen);


 if (np->ntyp == N_REAL)
  {
   memcpy(np->nva.wp, xsp->ap, 2*owlen*WRDBYTES);
   return;
  }
 __my_free((char *) np->nva.wp, 2*WRDBYTES*owlen);
 np->nva.wp = (word32 *) __my_malloc(2*WRDBYTES*nwlen);
 memcpy(np->nva.wp, xsp->ap, 2*nwlen*WRDBYTES);


 if (xsp->xslen != np->nwid)
  {
   np->nwid = xsp->xslen;
   if (np->nu.ct->nx1 != NULL) __free_xtree(np->nu.ct->nx1);
   if (np->nu.ct->nx2 != NULL) __free_xtree(np->nu.ct->nx2);
   if (np->nwid == 1)
    {
     np->n_isavec = FALSE;
     np->nu.ct->nx1 = np->nu.ct->nx2 = NULL;
    }
   else
    {
     np->nu.ct->nx1 = __bld_rng_numxpr((word32) (np->nwid - 1), 0L, WBITS);
     np->nu.ct->nx2 = __bld_rng_numxpr(0L, 0L, WBITS);
     np->n_isavec = TRUE;
    }
  }


 if (xrhs->is_string) np->nu.ct->pstring = TRUE;
 else { np->nu.ct->pstring = FALSE; np->nu.ct->pbase = BDEC; }
}
