test_root(unsigned int a, unsigned int b)
{
	while (1) {
		if (a < b)
			return 0;
		if (a == b)
			return 1;
		if (a % b)
			return 0;
		a = a / b;
	}
}
