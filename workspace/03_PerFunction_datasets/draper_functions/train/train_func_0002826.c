ucs2stat_mtime(const ucs2_char_t *filename)
{
	int ret = 0;
	struct stat st;
	char *mbs_path = ucs2dupmbs(filename);

	if (mbs_path) {
		path_decode(mbs_path);
		ret = stat(mbs_path, &st);
		free(mbs_path);
		if (ret == 0) {
			return st.st_mtime;
		}
	}
	return 0;
}
