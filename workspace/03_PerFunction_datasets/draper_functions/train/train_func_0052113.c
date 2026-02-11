g3d_stream_file_seek(gpointer data, goffset offset,
	GSeekType whence)
{
	G3DStreamFile *sf = (G3DStreamFile *)data;
	int w = SEEK_SET;
	switch(whence) {
		case G_SEEK_SET: w = SEEK_SET; break;
		case G_SEEK_CUR: w = SEEK_CUR; break;
		case G_SEEK_END: w = SEEK_END; break;
	}
	return fseek(sf->f, offset, w);
}
