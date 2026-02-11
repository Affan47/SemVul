mkplan(const solver *ego_, const problem *p_, planner *plnr)
{
     const problem_dft *p = (const problem_dft *) p_;
     const S *ego = (const S *) ego_;
     P *pln;
     plan *cld = 0, *cldcpy = 0;

     static const plan_adt padt = {
	  X(dft_solve), awake, print, destroy
     };

     if (!applicable(ego_, p_, plnr))
          return (plan *) 0;

     cldcpy =
	  X(mkplan_d)(plnr,
		      X(mkproblem_dft_d)(X(mktensor_0d)(),
					 X(tensor_append)(p->vecsz, p->sz),
					 p->ri, p->ii, p->ro, p->io));

     if (!cldcpy) goto nada;

     cld = X(mkplan_f_d)(plnr, ego->adt->mkcld(p), NO_BUFFERING, 0, 0);
     if (!cld) goto nada;

     pln = MKPLAN_DFT(P, &padt, ego->adt->apply);
     pln->cld = cld;
     pln->cldcpy = cldcpy;
     pln->slv = ego;
     X(ops_add)(&cld->ops, &cldcpy->ops, &pln->super.super.ops);

     return &(pln->super.super);

 nada:
     X(plan_destroy_internal)(cld);
     X(plan_destroy_internal)(cldcpy);
     return (plan *)0;
}
