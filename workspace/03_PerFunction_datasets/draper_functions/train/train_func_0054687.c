__eval_assign_rhsexpr(register struct expr_t *xrhs,
 register struct expr_t *xlhs)
{
 register struct xstk_t *xsp;

 xsp = __eval_xpr(xrhs);
 if (xlhs->is_real)
  {

   if (!xrhs->is_real) __cnv_stk_fromreg_toreal(xsp, (xrhs->has_sign == 1));
  }
 else
  {

   if (xrhs->is_real) __cnv_stk_fromreal_toreg32(xsp);


   if (xsp->xslen > xlhs->szu.xclen) __narrow_sizchg(xsp, xlhs->szu.xclen);
   else if (xsp->xslen < xlhs->szu.xclen)
    {
     if (xrhs->has_sign) __sgn_xtnd_widen(xsp, xlhs->szu.xclen);
     else __sizchg_widen(xsp, xlhs->szu.xclen);
    }
  }
 return(xsp);
}
