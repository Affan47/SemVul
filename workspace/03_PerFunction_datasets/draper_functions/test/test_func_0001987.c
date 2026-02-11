applicable0(const S *ego, const problem *p_, const planner *plnr)
{
     const problem_rdft2 *p = (const problem_rdft2 *) p_;
     iodim *d = p->sz->dims;

     if (1
	 && p->vecsz->rnk <= 1
	 && p->sz->rnk == 1


	 && (d[0].n % 2) == 0


	 && (p->kind == R2HC || p->kind == HC2R)

	  ) {
	  INT vl, ivs, ovs;
	  X(tensor_tornk1)(p->vecsz, &vl, &ivs, &ovs);

	  if (X(toobig)(d[0].n) && CONSERVE_MEMORYP(plnr))
	       return 0;


	  if (X(nbuf_redundant)(d[0].n, vl,
				ego->maxnbuf_ndx,
				maxnbufs, NELEM(maxnbufs)))
	       return 0;

	  if (p->r0 != p->cr) {
	       if (p->kind == HC2R) {


		    return (NO_DESTROY_INPUTP(plnr));
	       } else {


		    return (d[0].os > 2);
	       }
	  }


	  if (X(rdft2_inplace_strides(p, RNK_MINFTY)))
	       return 1;

	  if (
	       ((p->vecsz->rnk == 0)
		||
		(X(nbuf)(d[0].n, p->vecsz->dims[0].n,
			 maxnbufs[ego->maxnbuf_ndx])
		 == p->vecsz->dims[0].n)))
	       return 1;
     }

     return 0;
}
