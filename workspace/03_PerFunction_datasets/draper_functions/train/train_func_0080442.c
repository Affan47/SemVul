git_vector_bsearch(git_vector *v, const void *key)
{
	if (v->_cmp == NULL)
		return GIT_ENOTFOUND;

	return git_vector_bsearch2(v, v->_cmp, key);
}
