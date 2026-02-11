_php_stream_write_buffer(php_stream *stream, const char *buf, size_t count TSRMLS_DC)
{
	size_t didwrite = 0, towrite, justwrote;


	if (stream->ops->seek && (stream->flags & PHP_STREAM_FLAG_NO_SEEK) == 0 && stream->readpos != stream->writepos) {
		stream->readpos = stream->writepos = 0;

		stream->ops->seek(stream, stream->position, SEEK_SET, &stream->position TSRMLS_CC);
	}


	while (count > 0) {
		towrite = count;
		if (towrite > stream->chunk_size)
			towrite = stream->chunk_size;

		justwrote = stream->ops->write(stream, buf, towrite TSRMLS_CC);


		if ((int)justwrote > 0) {
			buf += justwrote;
			count -= justwrote;
			didwrite += justwrote;


			if (stream->ops->seek && (stream->flags & PHP_STREAM_FLAG_NO_SEEK) == 0) {
				stream->position += justwrote;
			}
		} else {
			break;
		}
	}
	return didwrite;

}
