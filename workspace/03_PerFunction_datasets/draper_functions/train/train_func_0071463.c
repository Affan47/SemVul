msort_with_tmp(void *b, size_t n, size_t s, cmp_fn_t cmp, char *t)
{
	char *tmp;
	char *b1, *b2;
	size_t n1, n2;

	if (n <= 1)
		return;

	n1 = n / 2;
	n2 = n - n1;
	b1 = b;
	b2 = ptr_add_offset(b, n1 * s);

	msort_with_tmp(b1, n1, s, cmp, t);
	msort_with_tmp(b2, n2, s, cmp, t);

	tmp = t;

	if (s == OPSIZ && op_aligned(b1)) {
		op_t *otmp = (op_t *) tmp;
		op_t *ob1 = (op_t *) b1;
		op_t *ob2 = (op_t *) b2;


		while (n1 > 0 && n2 > 0) {
			if ((*cmp)(ob1, ob2) <= 0) {
				--n1;
				*otmp++ = *ob1++;
			} else {
				--n2;
				*otmp++ = *ob2++;
			}
		}

		tmp = (char *) otmp;
		b1 = (char *) ob1;
		b2 = (char *) ob2;
	} else {
		while (n1 > 0 && n2 > 0) {
			if ((*cmp) (b1, b2) <= 0) {
				tmp = mempcpy(tmp, b1, s);
				b1 += s;
				--n1;
			} else {
				tmp = mempcpy(tmp, b2, s);
				b2 += s;
				--n2;
			}
		}
	}

	if (n1 > 0)
		memcpy(tmp, b1, n1 * s);

	memcpy(b, t, (n - n2) * s);
}
