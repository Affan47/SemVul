phantom_get_free(void)
{
	unsigned int i;

	for (i = 0; i < PHANTOM_MAX_MINORS; i++)
		if (phantom_devices[i] == 0)
			break;

	return i;
}
