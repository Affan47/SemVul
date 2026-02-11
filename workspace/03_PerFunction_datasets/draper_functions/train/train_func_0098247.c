g3d_stream_open_file(const gchar *filename, const gchar *mode)
{
	G3DStreamFile *sf;
	struct stat stats;
	guint32 flags = 0;

	sf = g_new0(G3DStreamFile, 1);


	sf->f = fopen(filename, mode);
	if(sf->f == NULL) {
		g_free(sf);
		return NULL;
	}


	if(g_stat(filename, &stats) != 0)
		sf->size = -1;
	sf->size = stats.st_size;

	if(mode[0] == 'r')
		flags |= (1 << G3D_STREAM_READABLE);
	if(mode[0] == 'w')
		flags |= (1 << G3D_STREAM_WRITABLE);

	flags |= (1 << G3D_STREAM_SEEKABLE);

	return g3d_stream_new_custom(flags, filename,
		g3d_stream_file_read, g3d_stream_file_read_line,
		g3d_stream_file_seek, g3d_stream_file_tell,
		g3d_stream_file_size, g3d_stream_file_eof,
		g3d_stream_file_close, sf);
}
