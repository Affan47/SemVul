match_sms_folder_mt(gn_memory_type mt)
{
	int i;
	for (i = 0; (s40_30_mt_mappings[i].type != mt) && (s40_30_mt_mappings[i].path != NULL); i++);
	if (s40_30_mt_mappings[i].path == NULL)
		return -1;
	else
		return i;
}
