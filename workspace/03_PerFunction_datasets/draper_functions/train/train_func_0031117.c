php_sprintf_appendint(char **buffer, int *pos, int *size, long number,
						int width, char padding, int alignment,
						int always_sign)
{
	char numbuf[NUM_BUF_SIZE];
	register unsigned long magn, nmagn;
	register unsigned int i = NUM_BUF_SIZE - 1, neg = 0;

	PRINTF_DEBUG(("sprintf: appendint(%x, %x, %x, %d, %d, '%c', %d)\n",
				  *buffer, pos, size, number, width, padding, alignment));
	if (number < 0) {
		neg = 1;
		magn = ((unsigned long) -(number + 1)) + 1;
	} else {
		magn = (unsigned long) number;
	}


	if(alignment==0 && padding=='0') padding=' ';

	numbuf[i] = '\0';

	do {
		nmagn = magn / 10;

		numbuf[--i] = (unsigned char)(magn - (nmagn * 10)) + '0';
		magn = nmagn;
	}
	while (magn > 0 && i > 0);
	if (neg) {
		numbuf[--i] = '-';
	} else if (always_sign) {
		numbuf[--i] = '+';
	}
	PRINTF_DEBUG(("sprintf: appending %d as \"%s\", i=%d\n",
				  number, &numbuf[i], i));
	php_sprintf_appendstring(buffer, pos, size, &numbuf[i], width, 0,
							 padding, alignment, (NUM_BUF_SIZE - 1) - i,
							 neg, 0, always_sign);
}
