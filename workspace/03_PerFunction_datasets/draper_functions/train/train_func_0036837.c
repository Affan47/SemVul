applicable0(const solver *ego_, const problem *p_,
		       const planner *plnr)
{
     const S *ego = (const S *) ego_;
     const problem_dft *p = (const problem_dft *) p_;
     return (1
	     && FINITE_RNK(p->vecsz->rnk)


	     && p->sz->rnk > 0

	     && (0


		 || (p->ri == p->ro
		     && !X(tensor_inplace_strides2)(p->sz, p->vecsz)
		     && X(tensor_strides_decrease)(
			  p->sz, p->vecsz,
			  ego->adt->apply == apply_after ?
			  INPLACE_IS : INPLACE_OS))


		 || (p->ri != p->ro && ego->adt->apply == apply_after
		     && !NO_DESTROY_INPUTP(plnr)
		     && X(tensor_min_istride)(p->sz) <= 2
		     && X(tensor_min_ostride)(p->sz) > 2)


		 || (p->ri != p->ro && ego->adt->apply == apply_before
		     && X(tensor_min_ostride)(p->sz) <= 2
		     && X(tensor_min_istride)(p->sz) > 2)
		  )
	  );
}
