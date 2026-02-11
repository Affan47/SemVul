apol_policy_path_compare(const apol_policy_path_t * a, const apol_policy_path_t * b)
{
	int cmp;
	if (a == NULL || b == NULL) {
		errno = EINVAL;
		return 0;
	}
	if ((cmp = a->path_type - b->path_type) != 0) {
		return cmp;
	}
	if ((cmp = strcmp(a->base, b->base)) != 0) {
		return cmp;
	}
	if (a->path_type == APOL_POLICY_PATH_TYPE_MODULAR) {

		size_t i;
		cmp = apol_vector_compare(a->modules, b->modules, apol_str_strcmp, NULL, &i);
		if (cmp != 0) {
			return cmp;
		}
	}
	return 0;
}
