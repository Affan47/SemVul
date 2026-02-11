extractPermuationAndSignChanges(IntegerVector const &v, IntegerVector &permutation, IntegerVector &signChanges)
{
	int n=v.size()/2;
	permutation=IntegerVector(n);
	signChanges=IntegerVector(n);

	for(int i=0;i<n;i++)
	{
		permutation[i]=v[i]%n;
		if(v[i]<n)
			signChanges[i]=1;
		else
			signChanges[i]=-1;
	}
}
