compute_new_size(git_vector *v)
{
	size_t new_size = v->_alloc_size;


	if (new_size < MIN_ALLOCSIZE)
		new_size = MIN_ALLOCSIZE;
	else if (new_size <= (SIZE_MAX / 3) * 2)
		new_size += new_size / 2;
	else
		new_size = SIZE_MAX;

	return new_size;
}
