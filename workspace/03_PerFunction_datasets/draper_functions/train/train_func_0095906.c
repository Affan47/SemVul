fm6_miter_next(fmsmem_i *m)
{
	m->tmpvec[0].n = m->tmpvec[1].n = m->match.n = 0;
	if (m->start >= m->len || m->start < 0) return -1;
	m->start = fm6_smem1_core(m->e, m->len, m->q, m->start, &m->match, 0, &m->tmpvec[0], &m->tmpvec[1]);
	return m->start;
}
