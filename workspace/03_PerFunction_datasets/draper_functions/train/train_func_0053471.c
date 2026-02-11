Simplify ()
{
	int min = 0, max = m_max - m_min;
	int i, j, imax = max + 1;
	double vmax = m_values[0], minval;
	for (i = 1; i < imax; i++)
		if (m_values[i] > vmax) {
			vmax = m_values[i];
		}
	minval = epsilon * vmax;
	while (m_values[min] < minval)
		min++;
	while (m_values[max] < minval)
		max--;
	IsotopicPattern *pat = new IsotopicPattern (min + m_min, max + m_min);
	pat->m_mono = m_mono;
	pat->m_mono_mass = m_mono_mass;
	vmax /= 100.;
	for (i = min, j = 0; i <= max; i++, j++)
		pat->m_values[j] = m_values[i] / vmax;
	return pat;
}
