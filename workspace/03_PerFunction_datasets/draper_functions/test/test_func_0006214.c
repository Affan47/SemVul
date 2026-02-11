mount_idemp(const char *path, const char *into)
{
	char *real = realpath(path, NULL);
	if (real == NULL) {
		printf("%s is not a directory\n", path);
		return 1;
	}
	char *unreal = malloc(strlen(into)+strlen(real)+2);
	sprintf(unreal, "%s/%s", into, real);

	if (!is_dir(real)) {
		printf("%s is not a directory\n", real);
		return 1;
	}

	if (mount(real, unreal, NULL, MS_BIND, NULL) != 0) {
		perror("mounting writable tree failed");
		return 1;
	}

	return 0;
}
