reverse_rotation_order (struct EULER *p, GMT_LONG n)
{
	GMT_LONG i, j;
	struct EULER p_tmp;

	for (i = 0; i < n/2; i++) {
		j = n - i - 1;
		if (i != j) {
			p_tmp = p[i];
			p[i] = p[j];
			p[j] = p_tmp;
		}
	}
}
