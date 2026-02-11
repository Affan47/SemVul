make_odb_dir(void)
{
	if (p_mkdir(odb_dir, 0755) < 0) {
		int err = errno;
		fprintf(stderr, "can't make directory \"%s\"", odb_dir);
		if (err == EEXIST)
			fprintf(stderr, " (already exists)");
		fprintf(stderr, "\n");
		return -1;
	}
	return 0;
}
