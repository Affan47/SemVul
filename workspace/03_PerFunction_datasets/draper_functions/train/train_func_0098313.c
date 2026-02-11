qprecision(NUMBER *q)
{
	long r;

	if (qiszero(q) || qisneg(q)) {
		math_error("Non-positive number for precision");

	}
	r = - qilog2(q);
	return (r < 0 ? 0 : r);
}
