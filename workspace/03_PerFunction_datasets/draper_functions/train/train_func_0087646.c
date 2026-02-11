searchByIndex(char * p, int m, char * t) {
    int i, j = 10, k = m - 1, l;
    while (j) {
	j--;


	if (t[m + j] - 48 != j) continue;


	for (i = 0; i < m && p[k - i] == t[i + j]; ++i);


	if (i < m) continue;


	for (l = k; l >= 0; l--)
	    printf("%c", p[l]);

	printf("%d\n", j);
    }
}
