mono_decimal_from_number (void *from, MonoDecimal *target)
{
	MonoNumber *number = (MonoNumber *) from;
	uint16_t* p = number->digits;
	MonoDecimal d;
	int e = number->scale;
	g_assert(number != NULL);
	g_assert(target != NULL);

	d.reserved = 0;
	DECIMAL_SIGNSCALE(d) = 0;
	DECIMAL_HI32(d) = 0;
	DECIMAL_LO32(d) = 0;
	DECIMAL_MID32(d) = 0;
	g_assert(p != NULL);
	if (!*p) {


		if (e > 0) {
			e = 0;
		}
	} else {
		if (e > DECIMAL_PRECISION) return 0;
		while ((e > 0 || (*p && e > -28)) && (DECIMAL_HI32(d) < 0x19999999 || (DECIMAL_HI32(d) == 0x19999999 && (DECIMAL_MID32(d) < 0x99999999 || (DECIMAL_MID32(d) == 0x99999999 && (DECIMAL_LO32(d) < 0x99999999 || (DECIMAL_LO32(d) == 0x99999999 && *p <= '5'))))))) {
			DecMul10(&d);
			if (*p)
				DecAddInt32(&d, *p++ - '0');
			e--;
		}
		if (*p++ >= '5') {
			gboolean round = TRUE;
			if (*(p-1) == '5' && *(p-2) % 2 == 0) {

				int count = 20;
				while (*p == '0' && count != 0) {
					p++;
					count--;
				}
				if (*p == '\0' || count == 0)
					round = FALSE;
			}

			if (round) {
				DecAddInt32(&d, 1);
				if ((DECIMAL_HI32(d) | DECIMAL_MID32(d) | DECIMAL_LO32(d)) == 0) {
					DECIMAL_HI32(d) = 0x19999999;
					DECIMAL_MID32(d) = 0x99999999;
					DECIMAL_LO32(d) = 0x9999999A;
					e++;
				}
			}
		}
	}
	if (e > 0)
		return 0;
	if (e <= -DECIMAL_PRECISION) {


		DECIMAL_SIGNSCALE(d) = 0;
		DECIMAL_HI32(d) = 0;
		DECIMAL_LO32(d) = 0;
		DECIMAL_MID32(d) = 0;
		DECIMAL_SCALE(d) = (DECIMAL_PRECISION - 1);
	} else {
		DECIMAL_SCALE(d) = (uint8_t)(-e);
	}

	DECIMAL_SIGN(d) = number->sign? DECIMAL_NEG: 0;
	*target = d;
	return 1;
}
