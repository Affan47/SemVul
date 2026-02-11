entropy_collect_environ(SHA1Context *ctx)
{
	extern char **environ;
	size_t i, j;
	const char *str[RANDOM_SHUFFLE_MAX];

	for (i = 0, j = 0; NULL != environ[i]; i++) {
		str[j++] = environ[i];
		if (RANDOM_SHUFFLE_MAX == j) {
			entropy_array_string_collect(ctx, str, RANDOM_SHUFFLE_MAX);
			j = 0;
		}
	}
	if (j != 0)
		entropy_array_string_collect(ctx, str, j);
	sha1_feed_ulong(ctx, i);
}
