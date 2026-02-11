mkplan(const solver *ego_, const problem *p_, planner *plnr)
{
     const problem_rdft2 *p;
     plan *cldcpy = (plan *) 0;
     P *pln;

     static const plan_adt padt = {
	  X(rdft2_solve), awake, print, destroy
     };

     UNUSED(ego_);

     if (!applicable(p_))
          return (plan *) 0;

     p = (const problem_rdft2 *) p_;

     if (p->kind == HC2R) {
	  cldcpy = X(mkplan_d)(plnr,
			       X(mkproblem_rdft_0_d)(
				    X(tensor_copy)(p->vecsz),
				    p->cr, p->r0));
	  if (!cldcpy) return (plan *) 0;
     }

     pln = MKPLAN_RDFT2(P, &padt,
			p->kind == R2HC ?
			(p->r0 == p->cr ? apply_r2hc_inplace : apply_r2hc)
			: apply_hc2r);

     if (p->kind == R2HC)
	  X(tensor_tornk1)(p->vecsz, &pln->vl, &pln->ivs, &pln->ovs);
     pln->cldcpy = cldcpy;

     if (p->kind == R2HC) {

	  X(ops_other)(3 * pln->vl, &pln->super.super.ops);
     }
     else {
	  pln->super.super.ops = cldcpy->ops;
     }

     return &(pln->super.super);
}
