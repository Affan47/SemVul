inverse_modulus(long long e, long long modulus) {
	long long a = e;
	long long b = modulus;

	int x = 0;
	int y = 1;
	int x0 = 1;
	int y0 = 0;

	int q, temp;

	while(b != 0) {
		q = a/b;
		temp = a %b;
		a = b;
		b = temp;

		temp = x;
		x = x0 - q * x;
		x0 = temp;

		temp = y;
		y = y0 - q * y;
		y0 = temp;
	}

	if(x0 < 0)
		x0 += modulus;

	return x0;
}
