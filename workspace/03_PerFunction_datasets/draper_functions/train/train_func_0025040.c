num_eq(struct num a, struct num b)
{
	if (a.exponent != b.exponent)
		return 0;
	if (a.exponent && a.type != b.type) {
		if (a.type == nt_mil)
			return mil_to_mm(a.n, a.exponent) == b.n;
		else
			return a.n == mil_to_mm(b.n, b.exponent);
	}
	return a.n == b.n;
}
