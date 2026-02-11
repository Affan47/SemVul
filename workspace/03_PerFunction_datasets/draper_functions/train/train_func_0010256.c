wi_read_double_from_ieee754(void *base, uintptr_t offset) {
	unsigned char	*bytes;
	double			value;
	int32_t			mantissa, exp;
	uint32_t		first, second;

	bytes	= base + offset;
	first	= (((uint32_t) (bytes[0] & 0xFF) << 24) |
			   ((uint32_t) (bytes[1] & 0xFF) << 16) |
			   ((uint32_t) (bytes[2] & 0xFF) <<  8) |
			    (uint32_t) (bytes[3] & 0xFF));
	second	= (((uint32_t) (bytes[4] & 0xFF) << 24) |
			   ((uint32_t) (bytes[5] & 0xFF) << 16) |
			   ((uint32_t) (bytes[6] & 0xFF) <<  8) |
			    (uint32_t) (bytes[7] & 0xFF));

	if(first == 0 && second == 0) {
		value = 0.0;
	} else {
		exp = (first & 0x7FF00000) >> _WI_BYTEORDER_IEEE754_EXP_POSITION;

		if(exp == _WI_BYTEORDER_IEEE754_EXP_MAX) {
			value = HUGE_VAL;
		} else {
			if(exp == 0) {
				mantissa	= (first & 0x000FFFFF);
				value		= ldexp((double) mantissa, exp - _WI_BYTEORDER_IEEE754_EXP_OFFSET - _WI_BYTEORDER_IEEE754_EXP_POSITION + 1);
				value		+= ldexp((double) second,  exp - _WI_BYTEORDER_IEEE754_EXP_OFFSET - _WI_BYTEORDER_IEEE754_EXP_POSITION + 1 - 32);
			} else {
				mantissa	= (first & 0x000FFFFF) + 0x00100000;
				value		= ldexp((double) mantissa, exp - _WI_BYTEORDER_IEEE754_EXP_OFFSET - _WI_BYTEORDER_IEEE754_EXP_POSITION);
				value		+= ldexp((double) second,  exp - _WI_BYTEORDER_IEEE754_EXP_OFFSET - _WI_BYTEORDER_IEEE754_EXP_POSITION - 32);
			}
		}
	}

	if(first & 0x80000000)
		return -value;
	else
		return value;
}
