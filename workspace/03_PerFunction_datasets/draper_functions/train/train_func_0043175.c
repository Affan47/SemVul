hesiod_free_list(void *context, char **list) {
	char **p;

	UNUSED(context);

	for (p = list; *p; p++)
		free(*p);
	free(list);
}
