db_entry_open(struct cache_entry* e, mode_t modes){
	get_key_path(e, filename_buffer);
	int fd = open(filename_buffer, O_RDWR | modes, S_IRUSR | S_IWUSR);
	if (fd <= 0){
		WARN("Unable to open cache file: %s", filename_buffer);
	}
	return fd;
}
