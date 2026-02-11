read_bits(uint8_t* buffer, uint8_t length, int advance) {
	static size_t buffer_idx = 0;

	static uint8_t bits_idx = 0;

	uint8_t old_bits_idx = bits_idx;
	uint8_t old_buffer_idx = buffer_idx;

	uint64_t value = 0;
	uint8_t nbits_available = (8 - bits_idx);
	uint64_t the_mask = 0;

	if (length >= nbits_available) {
		the_mask = create_mask_from_msb(
			length, bits_idx, nbits_available);
		value = buffer[buffer_idx++] & the_mask;
		bits_idx = 0;
		value <<= length - nbits_available;
		value |= read_bits(
			buffer, length - nbits_available, advance);
	} else {
		the_mask = create_mask_from_msb(8, bits_idx, length);
		value = buffer[buffer_idx] & the_mask;
		value >>= (nbits_available - length);
		bits_idx += length;
	}

	if (!advance) {
		buffer_idx = old_buffer_idx;
		bits_idx = old_bits_idx;
	}

	return value;
}
