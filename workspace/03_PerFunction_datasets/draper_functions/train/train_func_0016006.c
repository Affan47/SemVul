u16_normalize(uint16_t u16, unsigned char* out, const ssize_t limit)
{
	assert(limit > 0 && "u16_normalize must be called with positive limit");

	if(!u16) {
		return out;
	}

	if(u16 < 0xff) {
		assert((uint8_t)u16 != 0);
		*out++ = (uint8_t)u16;
	} else if (u16 == 0x3002 || u16 == 0xFF0E || u16 == 0xFE52) {

                *out++ = '.';
        } else {
                size_t i;

		if(limit <=  8) {

			return NULL;
		}


		out[0] = '&';
		out[1] = '#';
		out[2] = 'x';
		out[7] = ';';
		for(i=6; i >= 3; --i) {
			out[i] = tohex[u16 & 0xf];
			u16 >>= 4;
		}
		out += 8;
	}
	return out;
}
