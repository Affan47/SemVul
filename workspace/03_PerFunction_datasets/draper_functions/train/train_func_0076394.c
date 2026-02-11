fp_buftofp(const unsigned char *buf,
    unsigned intbits, unsigned fltbits,
    unsigned shift)
{
	unsigned long long value = 0, precision = 0;
	unsigned long long *ints[] = { &precision,
				       &value };
	unsigned int bits[] = { 6,
				intbits + fltbits };

	unsigned o, ibit, i;
	for (o = 0, ibit = 8 - (shift % 8), i = shift / 8; o < 2;) {
		if (ibit > bits[o]) {
			*ints[o] = *ints[o] | ((buf[i] >> (ibit - bits[o])) & ((1ULL << bits[o]) - 1));
			ibit -= bits[o];
			o++;
		} else {
			*ints[o] = *ints[o] | ((buf[i] & ((1ULL << ibit) - 1)) << (bits[o] - ibit));
			bits[o] -= ibit;
			ibit = 8;
			i++;
		}
	}


	if (precision > intbits)
		precision -= intbits;
	else
		precision = intbits;

	int negative = !!(value & (1ULL << (intbits + fltbits - 1)));
	if (negative) value = (~value + 1) & ((1ULL << (intbits + fltbits - 1)) - 1);
	struct fp_number result = {
		.integer = { value >> fltbits, intbits },
		.fraction = { value & ((1ULL << fltbits) - 1), fltbits, precision }
	};
	if (negative) result.integer.value = -result.integer.value;

	return result;
}
