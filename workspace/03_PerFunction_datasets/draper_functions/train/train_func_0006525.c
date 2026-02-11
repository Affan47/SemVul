isl_inequality_from_aff(__isl_take isl_aff *aff)
{
	int k;
	isl_local_space *ls;
	isl_basic_set *bset;

	if (!aff)
		return NULL;

	ls = isl_aff_get_domain_local_space(aff);
	bset = isl_basic_set_from_local_space(ls);
	bset = isl_basic_set_extend_constraints(bset, 0, 1);
	k = isl_basic_set_alloc_inequality(bset);
	if (k < 0)
		goto error;

	isl_seq_cpy(bset->ineq[k], aff->v->el + 1, aff->v->size - 1);
	isl_aff_free(aff);

	return isl_basic_set_constraint(bset, &bset->ineq[k]);
error:
	isl_aff_free(aff);
	isl_basic_set_free(bset);
	return NULL;
}
