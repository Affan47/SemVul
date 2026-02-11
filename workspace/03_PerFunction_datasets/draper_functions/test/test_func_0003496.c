dmp_iports(FILE *f, struct inst_t *ip, struct expr_t **iptab)
{
 register int32 pi;
 register struct mod_pin_t *mpp;
 int32 first_time, pnum;
 struct expr_t *cxp;
 struct mod_t *mdp;

 __wrap_putc('(', f);
 first_time = TRUE;
 mdp = ip->imsym->el.emdp;
 if ((pnum = mdp->mpnum) == 0) { __nl_wrap_puts(");", f); return; }

 mpp = &(mdp->mpins[0]);
 if (ip->ip_explicit)
  {
   for (pi = 0; pi < pnum; pi++, mpp++)
    {
     if (first_time) first_time = FALSE; else __wrap_puts(", ", f);

     cxp = iptab[pi];
     if (mpp->mpsnam != NULL)
      {
       __wrap_putc('.', f);
       __wrap_puts(mpp->mpsnam, f);
       __wrap_putc('(', f);
       dmp_expr(f, cxp);
       __wrap_putc(')', f);
      }
     else dmp_expr(f, cxp);
    }
  }
 else
  {
   for (pi = 0; pi < pnum; pi++)
    {
     if (first_time) first_time = FALSE; else __wrap_puts(", ", f);

     cxp = iptab[pi];
     dmp_expr(f, cxp);
    }
  }
 __nl_wrap_puts(");", f);
}
