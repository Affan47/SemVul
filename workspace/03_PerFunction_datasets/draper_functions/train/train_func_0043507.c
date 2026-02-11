nextprime(long n)
{
	const long	primes[] = {
			509, 1021, 2039, 4093, 8191, 16381, 32749, 65521,
			131071, 262139, 524287, 1048573, 2097143, 4194301,
			8388593, 16777213, 33554393, 67108859, 134217689,
			268435399, 536870909, 1073741789, 2147483647
		};
	long	mprime = 7;
	int	i;

	for (i = 0; i < sizeof primes / sizeof *primes; i++)
		if ((mprime = primes[i]) >= (n < 65536 ? n*4 :
					n < 262144 ? n*2 : n))
			break;
	if (i == sizeof primes / sizeof *primes)
		mprime = n;
	return mprime;
}
