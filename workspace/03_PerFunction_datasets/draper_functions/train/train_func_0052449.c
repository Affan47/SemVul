cdce925_pll_calculate_rate(unsigned long parent_rate,
	u16 n, u16 m)
{
	if ((!m || !n) || (m == n))
		return parent_rate;
	return mult_frac(parent_rate, (unsigned long)n, (unsigned long)m);
}
