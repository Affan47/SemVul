germainSanity(unsigned rem, unsigned div, unsigned order)
{
	unsigned mul = 1;

	rem %= div;
	if (!rem)
		printf("bn div by %u!\n", div);
	while (order--) {
		rem += rem+1;
		if (rem >= div)
			rem -= div;
		mul += mul;
		if (!rem)
			printf("%u*bn+%u div by %u!\n", mul, mul-1, div);
	}
}
