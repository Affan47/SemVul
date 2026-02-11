resize_vector(git_vector *v)
{
	v->_alloc_size = ((unsigned int)(v->_alloc_size * resize_factor)) + 1;
	if (v->_alloc_size < minimum_size)
		v->_alloc_size = minimum_size;

	v->contents = git__realloc(v->contents, v->_alloc_size * sizeof(void *));
	GITERR_CHECK_ALLOC(v->contents);

	return 0;
}
