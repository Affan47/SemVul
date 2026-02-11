bcf_min_diff(const bcf1_t *b)
{
	int i, min = 1<<30;
	const bcf_ginfo_t *PL;
	for (i = 0; i < b->n_gi; ++i)
		if (b->gi[i].fmt == bcf_str2int("PL", 2)) break;
	if (i == b->n_gi) return -1;
	PL = b->gi + i;
	for (i = 0; i < b->n_smpl; ++i) {
		int m1, m2, j;
		const uint8_t *p = (uint8_t*)PL->data;
		m1 = m2 = 1<<30;
		for (j = 0; j < PL->len; ++j) {
			if ((int)p[j] < m1) m2 = m1, m1 = p[j];
			else if ((int)p[j] < m2) m2 = p[j];
		}
		min = min < m2 - m1? min : m2 - m1;
	}
	return min;
}
