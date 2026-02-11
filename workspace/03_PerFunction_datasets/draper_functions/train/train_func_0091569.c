copy_modports(void)
{
 register int32 pi;
 register struct mod_pin_t *ompp, *nmpp;
 int32 pnum;

 if ((pnum = __oinst_mod->mpnum) == 0) return;

 __inst_mod->mpins = (struct mod_pin_t *)
  __my_malloc(pnum*sizeof(struct mod_pin_t));

 nmpp = &(__inst_mod->mpins[0]);
 for (pi = 0, ompp = &(__oinst_mod->mpins[0]); pi < pnum; pi++, ompp++, nmpp++)
  {
   *nmpp = *ompp;
   nmpp->mpref = __copy_expr(ompp->mpref);
  }
}
