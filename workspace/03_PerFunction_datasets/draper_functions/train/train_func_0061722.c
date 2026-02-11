git_vector_search(size_t *at_pos, const git_vector *v, const void *entry)
{
	return git_vector_search2(at_pos, v, v->_cmp ? v->_cmp : strict_comparison, entry);
}
