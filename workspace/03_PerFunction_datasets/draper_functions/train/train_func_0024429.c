has_spurious_elements(__isl_keep isl_map *qc,
	__isl_keep isl_set *dom, __isl_keep isl_set *ran)
{
	isl_set *s;
	int subset;
	unsigned d;

	if (!qc || !dom || !ran)
		return -1;

	d = isl_map_dim(qc, isl_dim_in);

	qc = isl_map_copy(qc);
	qc = set_path_length(qc, 0, 1);
	qc = isl_map_project_out(qc, isl_dim_in, d - 1, 1);
	qc = isl_map_project_out(qc, isl_dim_out, d - 1, 1);

	s = isl_map_domain(isl_map_copy(qc));
	subset = isl_set_is_subset(s, dom);
	isl_set_free(s);
	if (subset < 0)
		goto error;
	if (!subset) {
		isl_map_free(qc);
		return 1;
	}

	s = isl_map_range(qc);
	subset = isl_set_is_subset(s, ran);
	isl_set_free(s);

	return subset < 0 ? -1 : !subset;
error:
	isl_map_free(qc);
	return -1;
}
