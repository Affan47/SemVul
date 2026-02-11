loose_backend__stream_free(git_odb_stream *_stream)
{
	loose_writestream *stream = (loose_writestream *)_stream;

	if (!stream->finished)
		git_filebuf_cleanup(&stream->fbuf);

	free(stream);
}
