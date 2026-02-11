open_file(BDRVVVFATState* s,mapping_t* mapping)
{
    if(!mapping)
	return -1;
    if(!s->current_mapping ||
	    strcmp(s->current_mapping->path,mapping->path)) {

	int fd = open(mapping->path, O_RDONLY | O_BINARY | O_LARGEFILE);
	if(fd<0)
	    return -1;
	vvfat_close_current_file(s);
	s->current_fd = fd;
	s->current_mapping = mapping;
    }
    return 0;
}
