qlog(NUMBER *q, NUMBER *epsilon)
{
	int need_new_ln_10 = TRUE;
	NUMBER *ln_q;
	NUMBER *ret;


	if (qiszero(q) || qiszero(epsilon)) {
		math_error("logarithm of 0");

	}


	if (qisint(q) && qispos(q) && !zge8192b(q->num) && ziseven(q->num)) {
		BOOL is_10_power;
		long ilog_10;


		ilog_10 = zlog10(q->num, &is_10_power );
		if (is_10_power == TRUE) {

			return itoq(ilog_10);
		}

	}


	ln_q = qln(q, epsilon);

	if (qiszero(ln_q)) {
		return ln_q;
	}


	if (ln_10_epsilon == NULL) {

		ln_10_epsilon = qcopy(epsilon);
	} else if (qcmp(ln_10_epsilon, epsilon) == TRUE) {

		qfree(ln_10_epsilon);
		ln_10_epsilon = qcopy(epsilon);
	} else if (ln_10 != NULL) {

		need_new_ln_10 = FALSE;
	}


	if (need_new_ln_10 == TRUE) {
		if (ln_10 != NULL) {
			qfree(ln_10);
		}
		ln_10 = qln(&_qten_, ln_10_epsilon);
	}


	ret = qqdiv(ln_q, ln_10);
	qfree(ln_q);
	return ret;
}
