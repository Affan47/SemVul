lha_basic_reader_read_compressed(LHABasicReader *reader, void *buf,
                                        size_t buf_len)
{
	size_t bytes;

	if (reader->eof || reader->curr_file_remaining == 0) {
		return 0;
	}


	if (buf_len > reader->curr_file_remaining) {
		bytes = reader->curr_file_remaining;
	} else {
		bytes = buf_len;
	}

	if (!lha_input_stream_read(reader->stream, buf, bytes)) {
		reader->eof = 1;
		return 0;
	}


	reader->curr_file_remaining -= bytes;

	return bytes;
}
