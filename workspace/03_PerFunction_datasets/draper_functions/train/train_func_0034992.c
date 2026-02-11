IsLucasProbablePrime(const Integer &n)
{
	if (n <= 1)
		return false;

	if (n.IsEven())
		return n==2;

	assert(n>2);

	Integer b=3;
	unsigned int i=0;
	int j;

	while ((j=Jacobi(b.Squared()-4, n)) == 1)
	{
		if (++i==64 && n.IsSquare())
			return false;
		++b; ++b;
	}

	if (j==0)
		return false;
	else
		return Lucas(n+1, b, n)==2;
}
