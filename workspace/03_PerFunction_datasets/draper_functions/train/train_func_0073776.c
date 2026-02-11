libmpq__huffman_get_8bit(struct huffman_input_stream_s *is) {


	uint32_t one_byte;


	if (is->bits <= 8) {
		is->bit_buf |= *(uint16_t *)is->in_buf << is->bits;
		is->in_buf  += sizeof(int16_t);
		is->bits    += 16;
	}


	one_byte      = (is->bit_buf & 0xFF);
	is->bit_buf >>= 8;
	is->bits     -= 8;


	return one_byte;
}
