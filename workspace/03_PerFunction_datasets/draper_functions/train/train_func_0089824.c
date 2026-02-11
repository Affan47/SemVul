setReadAheadBufferSize(uint16_t size) {
	if(read_ahead_buffer) {

		read_ahead_len -= read_ahead_ofs;
		read_ahead_ofs = 0;
		memmove(read_ahead_buffer,read_ahead_buffer+read_ahead_ofs,read_ahead_len);

		if(read_ahead_len > size)
			ThrowInternalError("truncating the read-ahead buffer would lose %d buffered bytes",read_ahead_len);

		if(size) {
			if(uint8_t* tmp = (uint8_t*)realloc(read_ahead_buffer,size)) {
				read_ahead_buffer = tmp;
				read_ahead_maxlen = size;
			}
		} else {
			free(read_ahead_buffer);
			read_ahead_buffer = NULL;
		}
	} else if(size) {
		read_ahead_ofs = 0;
		read_ahead_len = 0;
		read_ahead_maxlen = size;
		read_ahead_buffer = (uint8_t*)malloc(size);
	}
}
