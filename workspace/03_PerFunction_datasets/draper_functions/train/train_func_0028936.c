file_data(Stream_t *Stream, time_t *date, mt_size_t *size,
		     int *type, int *address)
{
	DeclareThis(SimpleFile_t);

	if(date)
		*date = This->statbuf.st_mtime;
	if(size)
		*size = This->statbuf.st_size;
	if(type)
		*type = S_ISDIR(This->statbuf.st_mode);
	if(address)
		*address = 0;
	return 0;
}
