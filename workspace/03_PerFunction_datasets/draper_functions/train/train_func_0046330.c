file_data_ref_debug(const gchar *file, gint line, FileData *fd)
#else
FileData *file_data_ref(FileData *fd)
#endif
{
	if (fd == NULL) return NULL;
#ifdef DEBUG_FILEDATA
	if (fd->magick != 0x12345678)
		DEBUG_0("fd magick mismatch at %s:%d", file, line);
#endif
	g_assert(fd->magick == 0x12345678);
	fd->ref++;

#ifdef DEBUG_FILEDATA
	DEBUG_2("file_data_ref (%d): '%s' @ %s:%d", fd->ref, fd->path, file, line);
#else
	DEBUG_2("file_data_ref (%d): '%s'", fd->ref, fd->path);
#endif
	return fd;
}
