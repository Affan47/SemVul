applicable0(const problem *p_)
{
     const problem_dft *p = (const problem_dft *) p_;
     return (1
	     && p->sz->rnk == 1
	     && p->vecsz->rnk == 0

	     && X(is_prime)(p->sz->dims[0].n)


	     && p->sz->dims[0].n > 16
	  );
}
