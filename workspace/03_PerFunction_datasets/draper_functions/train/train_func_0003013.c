aa_features_new_from_string(aa_features **features,
				const char *string, size_t size)
{
	aa_features *f;

	*features = NULL;


	if (size >= STRING_SIZE)
		return ENOBUFS;

	f = calloc(1, sizeof(*f));
	if (!f) {
		errno = ENOMEM;
		return -1;
	}
	aa_features_ref(f);

	memcpy(f->string, string, size);
	f->string[size] = '\0';
	*features = f;

	return 0;
}
