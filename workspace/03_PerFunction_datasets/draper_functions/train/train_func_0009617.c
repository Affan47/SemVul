generic_readline(G3DStream *stream, gchar *buf, gsize size)
{
	gint32 i;

	for(i = 0; i < (size - 1); i ++) {
		if(g3d_stream_eof(stream))
			return NULL;
		if(g3d_stream_read(stream, buf + i, 1) <= 0)
			return NULL;
		if(buf[i] == '\n') {
			buf[i + 1] = '\0';
			return buf;
		}
	}
	buf[size - 1] = '\0';
	return buf;
}
