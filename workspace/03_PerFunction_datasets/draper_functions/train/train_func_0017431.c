fill_offset_range(LHALH1Decoder *decoder, uint8_t code,
                              unsigned int mask, unsigned int offset)
{
	unsigned int i;


	for (i = 0; (i & ~mask) == 0; ++i) {
		decoder->offset_lookup[code | i] = (uint8_t) offset;
	}
}
