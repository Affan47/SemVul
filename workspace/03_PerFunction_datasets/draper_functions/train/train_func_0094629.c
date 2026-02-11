isl_qpolynomial_fold_plain_is_equal(__isl_keep isl_qpolynomial_fold *fold1,
	__isl_keep isl_qpolynomial_fold *fold2)
{
	int i;

	if (!fold1 || !fold2)
		return -1;

	if (fold1->n != fold2->n)
		return 0;


	for (i = 0; i < fold1->n; ++i) {
		int eq = isl_qpolynomial_plain_is_equal(fold1->qp[i], fold2->qp[i]);
		if (eq < 0 || !eq)
			return eq;
	}

	return 1;
}
