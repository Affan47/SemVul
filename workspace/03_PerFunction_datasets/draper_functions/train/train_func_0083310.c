InsertGlobal(int in_ref, void *in_data) {
	if (ext_data_map.find(in_ref) == ext_data_map.end())
		return -1;

	ext_data_map[in_ref] = in_data;

	return 1;
}
