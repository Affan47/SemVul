znprime(ZVALUE z)
{
	FULL n;

	z.sign = 0;


	if (zge32b(z)) {
		return (FULL)1;
	}


	if (zisabsleone(z)) {
		return (FULL)2;
	}


	n = ztofull(z);
	if (n >= MAX_SM_PRIME) {
		return (FULL)0;
	}


	return next_prime(n);
}
