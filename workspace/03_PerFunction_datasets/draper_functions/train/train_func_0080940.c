qperm(NUMBER *q1, NUMBER *q2)
{
	NUMBER *r;
	NUMBER *qtmp1, *qtmp2;
	long i;

	if (qisfrac(q2)) {
		math_error("Non-integral second arg for permutation");

	}
	if (qiszero(q2))
		return qlink(&_qone_);
	if (qisone(q2))
		return qlink(q1);
	if (qisint(q1) && !qisneg(q1)) {
		if (qrel(q2, q1) > 0)
			return qlink(&_qzero_);
		if (qispos(q2)) {
			r = qalloc();
			zperm(q1->num, q2->num, &r->num);
			return r;
		}
	}
	if (zge31b(q2->num)) {
		math_error("Too large arg2 for permutation");

	}
	i = qtoi(q2);
	if (i > 0) {
		q1 = qlink(q1);
		r = qlink(q1);
		while (--i > 0) {
			qtmp1 = qdec(q1);
			qtmp2 = qmul(r, qtmp1);
			qfree(q1);
			q1 = qtmp1;
			qfree(r);
			r = qtmp2;
		}
		qfree(q1);
		return r;
	}
	i = -i;
	qtmp1 = qinc(q1);
	r = qinv(qtmp1);
	while (--i > 0) {
		qtmp2 = qinc(qtmp1);
		qfree(qtmp1);
		qtmp1 = qqdiv(r, qtmp2);
		qfree(r);
		r = qtmp1;
		qtmp1 = qtmp2;
	}
	qfree(qtmp1);
	return r;
}
