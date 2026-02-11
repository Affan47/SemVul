nd_1bit_concat(struct expr_t *lhsx)
{
 register struct expr_t *catndp;

 if (lhsx->optyp == LCB)
  {
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    chk_getpat_nonscal(catndp->lu.x);
   return;
  }
 __sgferr(800,
  "$getpattern continous assign lvalue must be concatenate of scalar wires");
}
