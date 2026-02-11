snd_device_name_free_hint(void **hints)
{
	char **h;

	if (hints == NULL)
		return 0;
	h = (char **)hints;
	while (*h) {
		free(*h);
		h++;
	}
	free(hints);
	return 0;
}
