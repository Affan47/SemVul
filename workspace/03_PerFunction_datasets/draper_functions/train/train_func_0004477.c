rhash_byte_to_base32(char* dest, const unsigned char* src, unsigned len, int upper_case)
{
	const char a = (upper_case ? 'A' : 'a');
	unsigned shift = 0;
	unsigned char word;
	const unsigned char* e = src + len;
	while(src < e) {
		if(shift > 3) {
			word = (*src & (0xFF >> shift));
			shift = (shift + 5) % 8;
			word <<= shift;
			if(src + 1 < e)
				word |= *(src + 1) >> (8 - shift);
			++src;
		} else {
			shift = (shift + 5) % 8;
			word = ( *src >> ( (8 - shift)&7 ) ) & 0x1F;
			if(shift == 0) src++;
		}
		*dest++ = ( word < 26 ? word + a : word + '2' - 26 );
	}
	*dest = '\0';
}
