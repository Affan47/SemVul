isl_access_info_sort_sources(
	__isl_take isl_access_info *acc)
{
	if (!acc)
		return NULL;
	if (acc->n_must <= 1)
		return acc;

	if (isl_sort(acc->source, acc->n_must, sizeof(struct isl_labeled_map),
		    access_sort_cmp, acc) < 0)
		return isl_access_info_free(acc);

	return acc;
}
