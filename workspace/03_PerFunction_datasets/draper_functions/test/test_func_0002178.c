search_filename_similar(const char *filename, const char *query)
{
	char *filename_canonic;
	bool result;

	filename_canonic = UNICODE_CANONIZE(filename);

	result = NULL != is_strprefix(filename_canonic, query);

	if (filename_canonic != filename)
		hfree(filename_canonic);

	return result;
}
