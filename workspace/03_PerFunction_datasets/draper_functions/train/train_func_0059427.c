applicable_memcpy_loop(const P *pln, const problem_rdft *p)
{
     return (p->I != p->O
	     && pln->rnk > 0
             && pln->vl > 2 );
}
