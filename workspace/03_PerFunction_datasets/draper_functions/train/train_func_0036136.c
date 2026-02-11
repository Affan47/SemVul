lha_basic_reader_next_file(LHABasicReader *reader)
{


	if (reader->curr_file != NULL) {
		lha_file_header_free(reader->curr_file);
		reader->curr_file = NULL;

		lha_input_stream_skip(reader->stream,
		                      reader->curr_file_remaining);
	}

	if (reader->eof) {
		return NULL;
	}


	reader->curr_file = lha_file_header_read(reader->stream);

	if (reader->curr_file == NULL) {
		reader->eof = 1;
		return NULL;
	}

	reader->curr_file_remaining = reader->curr_file->compressed_length;

	return reader->curr_file;
}
