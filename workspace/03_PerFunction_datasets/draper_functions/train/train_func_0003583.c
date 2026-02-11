isl_qpolynomial_pow(__isl_take isl_qpolynomial *qp,
	unsigned power)
{
	qp = isl_qpolynomial_cow(qp);

	if (!qp)
		return NULL;

	qp->upoly = isl_upoly_pow(qp->upoly, power);
	if (!qp->upoly)
		goto error;

	return qp;
error:
	isl_qpolynomial_free(qp);
	return NULL;
}
