applicable0(const hc2c_solver *ego, const problem *p_, planner *plnr)
{
     const problem_rdft2 *p = (const problem_rdft2 *) p_;
     INT r;

     return (1
	     && p->sz->rnk == 1
	     && p->vecsz->rnk <= 1

	     && (
		  (p->kind == R2HC)
		  ||


		  (p->kind == HC2R &&
		   (p->r0 == p->cr || !NO_DESTROY_INPUTP(plnr))))

	     && ((r = X(choose_radix)(ego->r, p->sz->dims[0].n)) > 0)
	     && p->sz->dims[0].n > r);
}
