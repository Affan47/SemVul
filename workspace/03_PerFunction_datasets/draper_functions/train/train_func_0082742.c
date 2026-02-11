isl_pw_aff_floor(__isl_take isl_pw_aff *pwaff)
{
	int i;

	pwaff = isl_pw_aff_cow(pwaff);
	if (!pwaff)
		return NULL;
	if (pwaff->n == 0)
		return pwaff;

	for (i = 0; i < pwaff->n; ++i) {
		pwaff->p[i].aff = isl_aff_floor(pwaff->p[i].aff);
		if (!pwaff->p[i].aff)
			return isl_pw_aff_free(pwaff);
	}

	return pwaff;
}
