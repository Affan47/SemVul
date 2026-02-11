get_mode(char *mode)
{
	int m;

	if (get_int(mode, &m, 0) < 0) {
		fprintf(stderr, "Invalidate mode: %s\n", mode);
		exit(1);
	}

	return m;
}
