mkcldrn_gcd(const problem_rdft *p, planner *plnr, P *ego)
{
     INT n = ego->nd, m = ego->md, d = ego->d;
     INT vl = ego->vl;
     R *buf = (R *)MALLOC(sizeof(R) * ego->nbuf, BUFFERS);
     INT num_el = n*m*d*vl;

     if (n > 1) {
	  ego->cld1 = X(mkplan_d)(plnr,
				  X(mkproblem_rdft_0_d)(
				       X(mktensor_3d)(n, d*m*vl, m*vl,
						      d, m*vl, n*m*vl,
						      m*vl, 1, 1),
				       TAINT(p->I, num_el), buf));
	  if (!ego->cld1)
	       goto nada;
	  X(ops_madd)(d, &ego->cld1->ops, &ego->super.super.ops,
		      &ego->super.super.ops);
	  ego->super.super.ops.other += num_el * d * 2;
     }

     ego->cld2 = X(mkplan_d)(plnr,
			     X(mkproblem_rdft_0_d)(
				  X(mktensor_3d)(d, d*n*m*vl, n*m*vl,
						 d, n*m*vl, d*n*m*vl,
						 n*m*vl, 1, 1),
				  p->I, p->I));
     if (!ego->cld2)
	  goto nada;
     X(ops_add2)(&ego->cld2->ops, &ego->super.super.ops);

     if (m > 1) {
	  ego->cld3 = X(mkplan_d)(plnr,
				  X(mkproblem_rdft_0_d)(
				       X(mktensor_3d)(d*n, m*vl, vl,
						      m, vl, d*n*vl,
						      vl, 1, 1),
				       TAINT(p->I, num_el), buf));
	  if (!ego->cld3)
	       goto nada;
	  X(ops_madd2)(d, &ego->cld3->ops, &ego->super.super.ops);
	  ego->super.super.ops.other += num_el * d * 2;
     }

     X(ifree)(buf);
     return 1;

 nada:
     X(ifree)(buf);
     return 0;
}
