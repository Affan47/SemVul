FLAC__bitreader_read_raw_uint32(FLAC__BitReader *br, FLAC__uint32 *val, unsigned bits)
{
	FLAC__ASSERT(0 != br);
	FLAC__ASSERT(0 != br->buffer);

	FLAC__ASSERT(bits <= 32);
	FLAC__ASSERT((br->capacity*FLAC__BITS_PER_WORD) * 2 >= bits);
	FLAC__ASSERT(br->consumed_words <= br->words);


	FLAC__ASSERT(FLAC__BITS_PER_WORD >= 32);

	if(bits == 0) {
		*val = 0;
		return true;
	}

	while((br->words-br->consumed_words)*FLAC__BITS_PER_WORD + br->bytes*8 - br->consumed_bits < bits) {
		if(!bitreader_read_from_client_(br))
			return false;
	}
	if(br->consumed_words < br->words) {

		if(br->consumed_bits) {

			const unsigned n = FLAC__BITS_PER_WORD - br->consumed_bits;
			const uint32_t word = br->buffer[br->consumed_words];
			if(bits < n) {
				*val = (word & (FLAC__WORD_ALL_ONES >> br->consumed_bits)) >> (n-bits);
				br->consumed_bits += bits;
				return true;
			}
			*val = word & (FLAC__WORD_ALL_ONES >> br->consumed_bits);
			bits -= n;
			crc16_update_word_(br, word);
			br->consumed_words++;
			br->consumed_bits = 0;
			if(bits) {
				*val <<= bits;
				*val |= (br->buffer[br->consumed_words] >> (FLAC__BITS_PER_WORD-bits));
				br->consumed_bits = bits;
			}
			return true;
		}
		else {
			const uint32_t word = br->buffer[br->consumed_words];
			if(bits < FLAC__BITS_PER_WORD) {
				*val = word >> (FLAC__BITS_PER_WORD-bits);
				br->consumed_bits = bits;
				return true;
			}

			*val = word;
			crc16_update_word_(br, word);
			br->consumed_words++;
			return true;
		}
	}
	else {


		if(br->consumed_bits) {

			FLAC__ASSERT(br->consumed_bits + bits <= br->bytes*8);
			*val = (br->buffer[br->consumed_words] & (FLAC__WORD_ALL_ONES >> br->consumed_bits)) >> (FLAC__BITS_PER_WORD-br->consumed_bits-bits);
			br->consumed_bits += bits;
			return true;
		}
		else {
			*val = br->buffer[br->consumed_words] >> (FLAC__BITS_PER_WORD-bits);
			br->consumed_bits += bits;
			return true;
		}
	}
}
