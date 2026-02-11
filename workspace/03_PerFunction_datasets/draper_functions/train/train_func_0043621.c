main(int argc, const char *argv[]) {
	uint64_t sum = 0;
	uint32_t i;
	int number_truncatable = 0;


	increase_size();


	numbers[0] = NOT_PRIME;
	numbers[1] = NOT_PRIME;
	i = 2;
	while (number_truncatable < 11) {

		int n = i;
		if (is_truncatable_prime(i)) {
			sum += n;
			printf("Truncatable: %u\n", i);
			number_truncatable++;
		}

		i += n;
		while(i < max) {
			numbers[i] = NOT_PRIME;
			i += n;
		}

		n++;
		while (n < max && numbers[n] == NOT_PRIME) {
			n++;
		}
		i = n;
		if (i >= max) {
			increase_size();
		}
	}

	printf("sum: %lld\n", sum);
	printf("n: %d\n", number_truncatable);
	return 0;
}
