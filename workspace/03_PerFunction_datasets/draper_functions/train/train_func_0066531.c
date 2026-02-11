faifa_init(void)
{
	faifa_t *faifa;

	faifa = calloc(1, sizeof(faifa_t));
	if (faifa == NULL)
		goto __error_malloc;

	return faifa;

	free(faifa);
__error_malloc:
	return NULL;
}
