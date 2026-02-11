interlink(struct message *m, long count, int newmail)
{
	int	i;
	long	n;
	struct msort	*ms;
	struct message	*root;
	int	autocollapse = !newmail && !(inhook&2) &&
			value("autocollapse") != NULL;

	ms = smalloc(sizeof *ms * count);
	for (n = 0, i = 0; i < count; i++) {
		if (m[i].m_parent == NULL) {
			if (autocollapse)
				colps(&m[i], 1);
			ms[n].ms_u.ms_long = m[i].m_date;
			ms[n].ms_n = i;
			n++;
		}
	}
	if (n > 0) {
		qsort(ms, n, sizeof *ms, mlonglt);
		root = &m[ms[0].ms_n];
		for (i = 1; i < n; i++) {
			m[ms[i-1].ms_n].m_younger = &m[ms[i].ms_n];
			m[ms[i].ms_n].m_elder = &m[ms[i-1].ms_n];
		}
	} else
		root = &m[0];
	free(ms);
	return root;
}
