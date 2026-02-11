mkplan(const solver *ego_, const problem *p_, planner *plnr)
{
     const problem_rdft *p;
     const S *ego = (const S *) ego_;
     P *pln;
     int retval;

     static const plan_adt padt = {
	  X(rdft_solve), X(null_awake), print, X(plan_null_destroy)
     };

     UNUSED(plnr);

     if (!applicable(ego, p_))
          return (plan *) 0;

     p = (const problem_rdft *) p_;
     pln = MKPLAN_RDFT(P, &padt, ego->apply);

     retval = fill_iodim(pln, p);
     (void)retval;
     A(retval);
     A(pln->vl > 0);
     pln->nam = ego->nam;


     X(ops_other)(2 * X(tensor_sz)(p->vecsz), &pln->super.super.ops);
     return &(pln->super.super);
}
