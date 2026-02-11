mathash(MATRIX *m, QCKHASH val)
{
	long skip;
	long i;
	VALUE *vp;


	val += V_MAT;
	quasi_fnv(m->m_dim, val);
	quasi_fnv(m->m_size, val);


	for (i = m->m_dim - 1; i >= 0; i--) {
		quasi_fnv(m->m_min[i], val);
		quasi_fnv(m->m_max[i], val);
	}


	vp = m->m_table;
	for (i = 0; ((i < m->m_size) && (i < 16)); i++) {
		val = hashvalue(vp++, val);
	}


	i = 16;
	if (i < m->m_size) {
		vp = (VALUE *)&m->m_table[i];
		skip = (m->m_size / 11) + 1;
		while (i < m->m_size) {
			val = hashvalue(vp, val);
			i += skip;
			vp += skip;
		}
	}
	return val;
}
