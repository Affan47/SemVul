array_free(struct array *a)
{
	__lock(a);
	if (a->a_arr)
		free(a->a_arr);
	a->a_arr = NULL;
	a->a_size = 0;
	a->a_items = 0;
	__unlock(a);
}
