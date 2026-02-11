skns_rle_decode ( int romoffset, int size )
{
	data8_t *src = memory_region (REGION_GFX1)+ romoffset;
	data8_t *dst = decodebuffer;

	while(size>0) {
		UINT8 code = *src++;
		size -= (code & 0x7f) + 1;
		if(code & 0x80) {
			code &= 0x7f;
			do {
				*dst++ = *src++;
				code--;
			} while(code != 0xff);
		} else {
			UINT8 val = *src++;
			do {
				*dst++ = val;
				code--;
			} while(code != 0xff);
		}
	}
	return src-memory_region (REGION_GFX1);
}
