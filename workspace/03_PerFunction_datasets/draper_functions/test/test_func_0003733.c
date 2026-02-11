ARCH_define_output(const char *path)
{
	STR_free(ARCH_output);

	if (path && *path != '/')
		path = FILE_cat(FILE_get_current_dir(), path, NULL);

  ARCH_output = STR_copy(path);
}
