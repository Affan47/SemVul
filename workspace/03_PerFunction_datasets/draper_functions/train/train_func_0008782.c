__eval_realrealqcol(register struct expr_t *ndp)
{
 double d1;
 register struct xstk_t *xspq, *xsp;
 register struct expr_t *xp;


 xspq = __eval2_xpr(ndp->lu.x);
 memcpy(&d1, xspq->ap, sizeof(double));


 if (d1 != 0.0)
  {
   __pop_xstk();
   xp = ndp->ru.x->lu.x;
   xsp = __eval_xpr(xp);
   if (xp->cnvt_to_real)
    {
     d1 = __cnvt_stk_to_real(xsp, (xp->has_sign == 1));


     memcpy(xsp->ap, &d1, sizeof(double));
    }
   return;
  }

 __pop_xstk();
 xp = ndp->ru.x->ru.x;
 xsp = __eval_xpr(xp);
 if (xp->cnvt_to_real)
  {
   d1 = __cnvt_stk_to_real(xsp, (xp->has_sign == 1));


   memcpy(xsp->ap, &d1, sizeof(double));
  }
}
