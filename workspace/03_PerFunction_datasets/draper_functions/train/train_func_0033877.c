make_table() {
	int i, j, k;
	tablelen = 0;
	if (verbose)
		printf("%d\nSorting\n", n);
	nn = maxnum;
	if (keylen < nn)
		nn = keylen;
	for (j=0; j<256; j++) {
		int max = 0;
		k = -1;
		for (i=0; i<=nn; i++) {
			if (numbers[i] > max) {
				k = i;
				max = numbers[i];
			}
		}
		if (k == -1) {
			nn = j;
			break;
		}
		numbers[k]=0;
		table[j] = k;
		if (k > tablelen)
			tablelen = k;
	}
	free(numbers);
	if (nn > 256)
		nn = 256;
}
