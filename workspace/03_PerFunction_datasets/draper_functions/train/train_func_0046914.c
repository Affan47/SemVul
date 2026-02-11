qquomod(NUMBER *q1, NUMBER *q2, NUMBER **quo, NUMBER **mod, long rnd)
{
	NUMBER *qq, *qm;
	ZVALUE tmp1, tmp2, tmp3, tmp4;

	if (qiszero(q2)) {
		qq = qlink(&_qzero_);
		qm = qlink(q1);
	} else if (qisint(q1) && qisint(q2)) {
		zdiv(q1->num, q2->num, &tmp1, &tmp2, rnd);
		if (ziszero(tmp1)) {
			zfree(tmp1);
			zfree(tmp2);
			qq = qlink(&_qzero_);
			qm = qlink(q1);
		} else {
			qq = qalloc();
			qq->num = tmp1;
			if (ziszero(tmp2)) {
				zfree(tmp2);
				qm = qlink(&_qzero_);
			} else {
				qm = qalloc();
				qm->num = tmp2;
			}
		}
	} else {
		zmul(q1->num, q2->den, &tmp1);
		zmul(q2->num, q1->den, &tmp2);
		zdiv(tmp1, tmp2, &tmp3, &tmp4, rnd);
		zfree(tmp1);
		zfree(tmp2);
		if (ziszero(tmp3)) {
			zfree(tmp3);
			zfree(tmp4);
			qq = qlink(&_qzero_);
			qm = qlink(q1);
		} else {
			qq = qalloc();
			qq->num = tmp3;
			if (ziszero(tmp4)) {
				zfree(tmp4);
				qm = qlink(&_qzero_);
			} else {
				qm = qalloc();
				zmul(q1->den, q2->den, &tmp1);
				zreduce(tmp4, tmp1, &qm->num, &qm->den);
				zfree(tmp1);
				zfree(tmp4);
			}
		}
	}
	*quo = qq;
	*mod = qm;
	return !qiszero(qm);
}
