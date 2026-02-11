matadd(MATRIX *m1, MATRIX *m2)
{
	int dim;

	long min1, min2, max1, max2, index;
	VALUE *v1, *v2, *vres;
	MATRIX *res;
	MATRIX tmp;

	if (m1->m_dim != m2->m_dim) {
		math_error("Incompatible matrix dimensions for add");

	}
	tmp.m_dim = m1->m_dim;
	tmp.m_size = m1->m_size;
	for (dim = 0; dim < m1->m_dim; dim++) {
		min1 = m1->m_min[dim];
		max1 = m1->m_max[dim];
		min2 = m2->m_min[dim];
		max2 = m2->m_max[dim];
		if ((min1 && min2 && (min1 != min2)) ||
		    ((max1-min1) != (max2-min2))) {
			math_error("Incompatible matrix bounds for add");

		}
		tmp.m_min[dim] = (min1 ? min1 : min2);
		tmp.m_max[dim] = tmp.m_min[dim] + (max1 - min1);
	}
	res = matalloc(m1->m_size);
	*res = tmp;
	v1 = m1->m_table;
	v2 = m2->m_table;
	vres = res->m_table;
	for (index = m1->m_size; index > 0; index--)
		addvalue(v1++, v2++, vres++);
	return res;
}
