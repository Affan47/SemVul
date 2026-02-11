gcd_euler (int n1, int n2)
{
	int buf;
	if (n1 < n2) {
		buf = n1;
		n1 = n2;
		n2 = buf;
	}
	while (1) {
		if (n2 == 0)
			return n1;
		buf = n1 % n2;
		n1 = n2;
		n2 = buf;
	}
}
