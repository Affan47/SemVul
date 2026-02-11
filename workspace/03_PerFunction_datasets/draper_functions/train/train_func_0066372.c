gth_file_data_cmp_filesize (GthFileData *a,
			    GthFileData *b)
{
	goffset size_a, size_b;

	size_a = g_file_info_get_size (a->info);
	size_b = g_file_info_get_size (b->info);

	if (size_a < size_b)
		return -1;
	else if (size_a > size_b)
		return 1;
	else
		return 0;
}
