shared_file_index(const shared_file_t *sf)
{
	shared_file_check(sf);

	g_assert(sf->file_index != 0);
	g_assert(PARTIAL_FILE != sf->file_index || NULL != sf->fi);

	return sf->file_index;
}
