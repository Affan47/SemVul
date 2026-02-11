dmp_defparams(FILE *f, struct mod_t *mdp)
{
 register int32 i;
 struct dfparam_t *dfpp;
 struct itree_t *itp;

 __pv_stlevel++;
 for (dfpp = __dfphdr; dfpp != NULL; dfpp = dfpp->dfpnxt)
  {
   if (dfpp->in_mdp != mdp) continue;
   __wrap_puts("defparam ", f);
   if (dfpp->dfp_local) __wrap_puts(dfpp->gdfpnam, f);
   else
    {


     itp = __it_roots[dfpp->dfpiis[0]];
     for (i = 0;;)
      {
       if (i > 0) __wrap_putc('.', f);

       __wrap_puts(itp->itip->isym->synam, f);
       if (++i > dfpp->last_dfpi) break;
       itp = &(itp->in_its[dfpp->dfpiis[i]]);
      }
     if (i > 0) __wrap_putc('.', f);
     __wrap_puts(dfpp->targsyp->synam, f);

    }
   __wrap_puts(" = ", f);
   dmp_expr(f, dfpp->dfpxrhs);
   __nl_wrap_puts(";", f);
  }
 __pv_stlevel--;
}
