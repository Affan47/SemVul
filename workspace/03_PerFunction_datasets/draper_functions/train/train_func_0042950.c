qhypot(NUMBER *q1, NUMBER *q2, NUMBER *epsilon)
{
	NUMBER *tmp1, *tmp2, *tmp3;

	if (qiszero(epsilon)) {
		math_error("Zero epsilon value for hypot");

	}
	if (qiszero(q1))
		return qqabs(q2);
	if (qiszero(q2))
		return qqabs(q1);
	tmp1 = qsquare(q1);
	tmp2 = qsquare(q2);
	tmp3 = qqadd(tmp1, tmp2);
	qfree(tmp1);
	qfree(tmp2);
	tmp1 = qsqrt(tmp3, epsilon, 24L);
	qfree(tmp3);
	return tmp1;
}
