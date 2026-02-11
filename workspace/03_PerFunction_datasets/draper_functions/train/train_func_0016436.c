UnionBlock3(b_type B1, b_type B2, b_type UB)

{
	long	j;
	for(j=0;j<B1->nint;j++)
		UB->i[j] = B1->i[j] | B2->i[j];
}
