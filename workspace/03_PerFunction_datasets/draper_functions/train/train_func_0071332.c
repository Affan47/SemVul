entropy_array_shuffle(void *ary, size_t len, size_t elem_size)
{
	g_assert(ary != NULL);
	g_assert(size_is_non_negative(len));
	g_assert(size_is_positive(elem_size));

	if (len > RANDOM_SHUFFLE_MAX)
		s_carp("%s: cannot shuffle %zu items without bias", G_STRFUNC, len);

	shuffle_with((random_fn_t) entropy_rand31, ary, len, elem_size);
}
