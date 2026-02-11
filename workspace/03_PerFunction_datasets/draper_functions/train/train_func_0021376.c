matround(MATRIX *m, VALUE *v2, VALUE *v3)
{
	VALUE *p, *q;
	long s;
	MATRIX *res;

	s = m->m_size;
	res = matalloc(s);
	*res = *m;
	p = m->m_table;
	q = res->m_table;
	while (s-- > 0)
		roundvalue(p++, v2, v3, q++);
	return res;
}
