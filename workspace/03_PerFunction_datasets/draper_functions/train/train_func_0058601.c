apol_vector_compare(const apol_vector_t * a, const apol_vector_t * b, apol_vector_comp_func * cmp, void *data, size_t * i)
{
	int compval;
	if (a == NULL || b == NULL || i == NULL) {
		errno = EINVAL;
		return 0;
	}
	size_t a_len = apol_vector_get_size(a);
	size_t b_len = apol_vector_get_size(b);
	for (*i = 0; *i < a_len && *i < b_len; (*i)++) {
		if (cmp != NULL) {
			compval = cmp(a->array[*i], b->array[*i], data);
		} else {
			compval = (int)((char *)a->array[*i] - (char *)b->array[*i]);
		}
		if (compval != 0) {
			return compval;
		}
	}
	if (a_len == b_len) {
		return 0;
	} else if (a_len < b_len) {
		return -1;
	} else {
		return 1;
	}
}
