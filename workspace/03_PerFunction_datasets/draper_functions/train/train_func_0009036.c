git_vector_sort(git_vector *v)
{
	assert(v);

	if (v->sorted || v->_cmp == NULL)
		return;

	qsort(v->contents, v->length, sizeof(void *), v->_cmp);
	v->sorted = 1;
}
