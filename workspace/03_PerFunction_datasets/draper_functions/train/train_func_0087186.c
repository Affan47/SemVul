pw_multi_aff_product(
	__isl_take isl_pw_multi_aff *pma1, __isl_take isl_pw_multi_aff *pma2)
{
	int i, j, n;
	isl_space *space;
	isl_pw_multi_aff *res;

	if (!pma1 || !pma2)
		goto error;

	n = pma1->n * pma2->n;
	space = isl_space_product(isl_space_copy(pma1->dim),
				  isl_space_copy(pma2->dim));
	res = isl_pw_multi_aff_alloc_size(space, n);

	for (i = 0; i < pma1->n; ++i) {
		for (j = 0; j < pma2->n; ++j) {
			isl_set *domain;
			isl_multi_aff *ma;

			domain = isl_set_product(isl_set_copy(pma1->p[i].set),
						 isl_set_copy(pma2->p[j].set));
			ma = isl_multi_aff_product(
					isl_multi_aff_copy(pma1->p[i].maff),
					isl_multi_aff_copy(pma2->p[i].maff));
			res = isl_pw_multi_aff_add_piece(res, domain, ma);
		}
	}

	isl_pw_multi_aff_free(pma1);
	isl_pw_multi_aff_free(pma2);
	return res;
error:
	isl_pw_multi_aff_free(pma1);
	isl_pw_multi_aff_free(pma2);
	return NULL;
}
