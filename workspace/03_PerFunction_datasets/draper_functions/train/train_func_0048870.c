git_vector_init(git_vector *v, unsigned int initial_size, git_vector_cmp cmp)
{
	assert(v);

	memset(v, 0x0, sizeof(git_vector));

	if (initial_size == 0)
		initial_size = minimum_size;

	v->_alloc_size = initial_size;
	v->_cmp = cmp;

	v->length = 0;
	v->sorted = 1;

	v->contents = git__malloc(v->_alloc_size * sizeof(void *));
	if (v->contents == NULL)
		return GIT_ENOMEM;

	return GIT_SUCCESS;
}
