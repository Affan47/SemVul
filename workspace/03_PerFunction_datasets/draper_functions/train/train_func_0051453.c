simple_ogg_page__get_at(FLAC__StreamEncoder *encoder, FLAC__uint64 position, ogg_page *page, FLAC__StreamEncoderSeekCallback seek_callback, FLAC__StreamEncoderReadCallback read_callback, void *client_data)
{
	static const unsigned OGG_HEADER_FIXED_PORTION_LEN = 27;
	static const unsigned OGG_MAX_HEADER_LEN = 27 + 255;
	FLAC__byte crc[4];
	FLAC__StreamEncoderSeekStatus seek_status;

	FLAC__ASSERT(page->header == 0);
	FLAC__ASSERT(page->header_len == 0);
	FLAC__ASSERT(page->body == 0);
	FLAC__ASSERT(page->body_len == 0);


	if(0 == seek_callback)
		return false;
	if((seek_status = seek_callback((FLAC__StreamEncoder*)encoder, position, client_data)) != FLAC__STREAM_ENCODER_SEEK_STATUS_OK) {
		if(seek_status == FLAC__STREAM_ENCODER_SEEK_STATUS_ERROR)
			encoder->protected_->state = FLAC__STREAM_ENCODER_CLIENT_ERROR;
		return false;
	}


	if(0 == (page->header = safe_malloc_(OGG_MAX_HEADER_LEN))) {
		encoder->protected_->state = FLAC__STREAM_ENCODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}


	if(!full_read_(encoder, page->header, OGG_HEADER_FIXED_PORTION_LEN, read_callback, client_data))
		return false;

	page->header_len = OGG_HEADER_FIXED_PORTION_LEN + page->header[26];


	if(
		memcmp(page->header, "OggS", 4) ||
		(page->header[5] & 0x01) ||
		memcmp(page->header+6, "\0\0\0\0\0\0\0\0", 8) ||
		page->header[26] == 0
	) {
		encoder->protected_->state = FLAC__STREAM_ENCODER_OGG_ERROR;
		return false;
	}


	if(!full_read_(encoder, page->header + OGG_HEADER_FIXED_PORTION_LEN, page->header[26], read_callback, client_data))
		return false;

	{
		unsigned i;


		for(i = 0; i < (unsigned)page->header[26] - 1; i++) {
			if(page->header[i + OGG_HEADER_FIXED_PORTION_LEN] != 255) {
				encoder->protected_->state = FLAC__STREAM_ENCODER_OGG_ERROR;
				return false;
			}
		}

		page->body_len = 255 * i + page->header[i + OGG_HEADER_FIXED_PORTION_LEN];
	}


	if(0 == (page->body = safe_malloc_(page->body_len))) {
		encoder->protected_->state = FLAC__STREAM_ENCODER_MEMORY_ALLOCATION_ERROR;
		return false;
	}


	if(!full_read_(encoder, page->body, page->body_len, read_callback, client_data))
		return false;


	memcpy(crc, page->header+22, 4);
	ogg_page_checksum_set(page);
	if(memcmp(crc, page->header+22, 4)) {
		encoder->protected_->state = FLAC__STREAM_ENCODER_OGG_ERROR;
		return false;
	}

	return true;
}
