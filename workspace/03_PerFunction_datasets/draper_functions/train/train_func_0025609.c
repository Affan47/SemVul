primes(int** ps, int n)
{
	int i, j, count;
	char* s = malloc(n);

	count = eratosthenes_sieve(s, n);

	*ps = malloc(count * sizeof(int));

	for (i = 2, j = 0; i < n; ++i) {
		if (s[i]) {
			(*ps)[j] = i;
			j++;
		}
	}

	free(s);

	return count;
}
