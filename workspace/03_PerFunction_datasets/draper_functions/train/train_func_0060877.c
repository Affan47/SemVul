g_mime_stream_mmap_new (int fd, int prot, int flags)
{
#ifdef HAVE_MMAP
	GMimeStreamMmap *mstream;
	struct stat st;
	gint64 start;
	char *map;

	if ((start = lseek (fd, 0, SEEK_CUR)) == -1)
		return NULL;

	if (fstat (fd, &st) == -1)
		return NULL;

	map = mmap (NULL, st.st_size, prot, flags, fd, 0);
	if (map == MAP_FAILED)
		return NULL;

	mstream = g_object_newv (GMIME_TYPE_STREAM_MMAP, 0, NULL);
	g_mime_stream_construct ((GMimeStream *) mstream, start, -1);
	mstream->owner = TRUE;
	mstream->eos = FALSE;
	mstream->fd = fd;
	mstream->map = map;
	mstream->maplen = st.st_size;

	return (GMimeStream *) mstream;
#else
	return NULL;
#endif
}
