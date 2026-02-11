git_vector_verify_sorted(const git_vector *v)
{
	size_t i;

	if (!git_vector_is_sorted(v))
		return -1;

	for (i = 1; i < v->length; ++i) {
		if (v->_cmp(v->contents[i - 1], v->contents[i]) > 0)
			return -1;
	}

	return 0;
}
