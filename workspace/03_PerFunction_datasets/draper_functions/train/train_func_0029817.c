cp_link(const char *from, const char *to, size_t link_size)
{
	int error = 0;
	ssize_t read_len;
	char *link_data = git__malloc(link_size + 1);
	GITERR_CHECK_ALLOC(link_data);

	read_len = p_readlink(from, link_data, link_size);
	if (read_len != (ssize_t)link_size) {
		giterr_set(GITERR_OS, "Failed to read symlink data for '%s'", from);
		error = -1;
	}
	else {
		link_data[read_len] = '\0';

		if (p_symlink(link_data, to) < 0) {
			giterr_set(GITERR_OS, "Could not symlink '%s' as '%s'",
				link_data, to);
			error = -1;
		}
	}

	git__free(link_data);
	return error;
}
