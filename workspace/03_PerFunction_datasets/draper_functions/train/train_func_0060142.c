ComputeErrorSet( Junction *j, int k, int usePlusBlockBypass)
#else
ComputeErrorSet( j, k, usePlusBlockBypass )
Junction *j;
int k;
int usePlusBlockBypass;
#endif
{
	Junction *alt1;
	set a, rk, f;
	require(j->ntype==nJunction, "ComputeErrorSet: non junction passed");

	f = rk = empty;
	for (alt1=j; alt1!=NULL; alt1 = (Junction *)alt1->p2)
	{
        if (alt1->ignore && ! usePlusBlockBypass) continue;
		REACH(alt1->p1, k, &rk, a);
		require(set_nil(rk), "ComputeErrorSet: rk != nil");
		set_free(rk);
		set_orin(&f, a);
		set_free(a);
	}
	return f;
}
