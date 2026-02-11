ensure_segment_validity(const char *name)
{
	const char *current = name;
	char prev = '\0';
	const int lock_len = (int)strlen(GIT_FILELOCK_EXTENSION);
	int segment_len;

	if (*current == '.')
		return -1;

	for (current = name; ; current++) {
		if (*current == '\0' || *current == '/')
			break;

		if (!is_valid_ref_char(*current))
			return -1;

		if (prev == '.' && *current == '.')
			return -1;

		if (prev == '@' && *current == '{')
			return -1;

		prev = *current;
	}

	segment_len = (int)(current - name);


	if (segment_len >= lock_len &&
		!memcmp(current - lock_len, GIT_FILELOCK_EXTENSION, lock_len))
			return -1;

	return segment_len;
}
