malloc_init(void)
{

	if (malloc_initialized == false)
		return (malloc_init_hard());

	return (false);
}
