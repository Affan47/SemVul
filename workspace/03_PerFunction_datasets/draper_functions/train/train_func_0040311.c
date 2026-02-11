file_data(struct lib_context *lc, const char *handler,
	  char *path, void *data, size_t size)
{
	int ret = 0;
	char *name;

	if ((name = _name(lc, path, "dat"))) {
		log_notice(lc, "writing metadata file \"%s\"", name);
		ret = write_file(lc, handler, name, data, size, 0);
		dbg_free(name);
	}

	return ret;
}
