chk1_arrinit_expr(struct expr_t *xp, char *paramnam, int32 ai)
{
 if (__expr_has_glb(xp) || !__src_rd_chk_paramexpr(xp, 0))
  {
   __pv_ferr(1025,
    "parameter array initializer cell %s[%d] \"%s\" illegal - parameters and constants only",
    paramnam, ai, __msgexpr_tostr(__xs, xp));

   __free2_xtree(xp);
   xp->szu.xclen = WBITS;
   __set_numval(xp, ALL1W, ALL1W, WBITS);
  }
}
