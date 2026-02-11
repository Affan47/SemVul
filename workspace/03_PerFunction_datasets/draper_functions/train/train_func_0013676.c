text_path_cat(char *pathname, size_t size, const char *dirname, const char *basename)
{
	if (dirname)
	{
		pathname = text_ncopy(pathname, dirname, size) - 1;
		while (*pathname == '/')
		{
			pathname--;
		}

		pathname++;
	}

	*pathname++ = '/';

	if (basename)
	{
		return text_ncopy(pathname, text_skip_char(basename, '/'), size);
	}

	*pathname = 0;

	return pathname;
}
