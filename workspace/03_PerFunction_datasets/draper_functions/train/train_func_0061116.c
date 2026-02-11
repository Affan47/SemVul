git_vector_sort(git_vector *v)
{
	assert(v);

	if (v->_cmp != NULL)
		qsort(v->contents, v->length, sizeof(void *), v->_cmp);
}
