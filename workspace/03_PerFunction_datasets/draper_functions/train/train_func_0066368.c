main(int argc, const char *argv[]) {
	int fac [10] = {
		1,
		1,
		2,
		6,
		24,
		120,
		720,
		5040,
		40320,
		362880
	};
	int i;
	int sum = 0;;
	int tempi;
	int tempsum;

	for (i = 10; i < 9999999; i++) {
		tempsum = 0;
		tempi = i;
		while (tempi > 0) {
			tempsum += fac[tempi%10];
			tempi /= 10;
		}
		if (tempsum == i) {
			sum += i;
		}
	}
	printf("%d\n", sum);

	return 0;
}
