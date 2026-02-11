qquo(NUMBER *q1, NUMBER *q2, long rnd)
{
	ZVALUE tmp, tmp1, tmp2;
	NUMBER *q;

	if (qiszero(q1) || qiszero(q2))
		return qlink(&_qzero_);
	if (qisint(q1) && qisint(q2)) {
		zquo(q1->num, q2->num, &tmp, rnd);
	} else {
		zmul(q1->num, q2->den, &tmp1);
		zmul(q2->num, q1->den, &tmp2);
		zquo(tmp1, tmp2, &tmp, rnd);
		zfree(tmp1);
		zfree(tmp2);
	}
	if (ziszero(tmp)) {
		zfree(tmp);
		return qlink(&_qzero_);
	}
	q = qalloc();
	q->num = tmp;
	return q;
}
