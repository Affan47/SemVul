bld_bsel_expr(struct net_t *np, int32 ndx)
{
 int32 ndx2;
 struct expr_t *xp, *xpid, *xpndx;

 xpid = __alloc_newxnd();
 xpid->optyp = ID;
 xpid->lu.sy = np->nsym;
 xpid->szu.xclen = __get_netwide(np);

 ndx2 = __unnormalize_ndx(np, ndx);
 xpndx = __bld_rng_numxpr((word32) ndx2, 0L, WBITS);
 xpndx->ibase = BDEC;
 if (ndx != ndx2) xpndx->ind_noth0 = TRUE;


 xp = __alloc_newxnd();
 xp->optyp = LSB;
 xp->szu.xclen = 1;

 xp->lu.x = xpid;
 xp->ru.x = xpndx;
 return(xp);
}
