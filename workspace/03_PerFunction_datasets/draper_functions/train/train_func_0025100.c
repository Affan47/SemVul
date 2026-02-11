qbern(ZVALUE z)
{
	long n, i, k, m, nn, dd;
	NUMBER **p;
	NUMBER *s, *s1, *c, *c1, *t;
	size_t sz;

	if (zisone(z))
		return qlink(&_qneghalf_);

	if (zisodd(z) || z.sign)
		return qlink(&_qzero_);

	if (zge31b(z))
		return NULL;

	n = ztoi(z);

	if (n == 0)

		return qlink(&_qone_);

	m = (n >> 1) - 1;

	if (m < B_num)
		return qlink(B_table[m]);

	if (m >= B_allocnum) {
		k = (m/QALLOCNUM + 1) * QALLOCNUM;
		sz = k * sizeof(NUMBER *);
		if (sz < (size_t) k)
			return NULL;
		if (B_allocnum == 0)
			p = (NUMBER **) malloc(sz);
		else
			p = (NUMBER **) realloc(B_table, sz);
		if (p == NULL)
			return NULL;
		B_allocnum = k;
		B_table = p;
	}
	for (k = B_num; k <= m; k++) {
		nn = 2 * k + 3;
		dd = 1;
		c1 = itoq(nn);
		c = qinv(c1);
		qfree(c1);
		s = qsub(&_qonehalf_, c);
		i = k;
		for (i = 0; i < k; i++) {
			c1 = qmuli(c, nn--);
			qfree(c);
			c = qdivi(c1, dd++);
			qfree(c1);
			c1 = qmuli(c, nn--);
			qfree(c);
			c = qdivi(c1, dd++);
			qfree(c1);
			t = qmul(c, B_table[i]);
			s1 = qsub(s, t);
			qfree(t);
			qfree(s);
			s = s1;
		}
		B_table[k] = s;
		qfree(c);
	}
	B_num = k;
	return qlink(B_table[m]);
}
