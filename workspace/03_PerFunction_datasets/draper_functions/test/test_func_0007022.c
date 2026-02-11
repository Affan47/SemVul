convert_fromutf7(void *ptr,
			    const char *text, size_t cnt)
{
	struct libmail_u_convert_fromimaputf7 *fromutf7=
		(struct libmail_u_convert_fromimaputf7 *)ptr;
	int bits;

	while (cnt)
	{
		if (fromutf7->errflag)
			return fromutf7->errflag;

		if (!fromutf7->seenamp && *text == '&')
		{
			fromutf7->seenamp=1;
			fromutf7->inmod=0;
			fromutf7->modcnt=0;
			++text;
			--cnt;
			continue;
		}

		if (fromutf7->seenamp)
		{
			if (*text == '-')
			{
				convert_fromutf7_add(fromutf7, '&');
				++text;
				--cnt;
				fromutf7->seenamp=0;
				continue;
			}
			fromutf7->seenamp=0;
			fromutf7->inmod=1;
		}

		if (!fromutf7->inmod)
		{


			convert_fromutf7_add(fromutf7,
					     ((uint16_t)*text) & 0xFFFF);
			++text;
			--cnt;
			continue;
		}

		if (*text == '-')
		{

			fromutf7->inmod=0;
			++text;
			--cnt;
			continue;
		}


		bits=mbase64_lookup[(unsigned char)*text];

		++text;
		--cnt;

		if (bits < 0)
		{
			errno=EILSEQ;
			return fromutf7->errflag=-1;
		}

		fromutf7->modbits = (fromutf7->modbits << 6) | bits;
		fromutf7->modcnt += 6;

		if (fromutf7->modcnt >= 16)
		{


			int shiftcnt=fromutf7->modcnt - 16;
			uint32_t v=fromutf7->modbits;

			if (shiftcnt)
				v >>= shiftcnt;

			fromutf7->modcnt -= 16;

			convert_fromutf7_add(fromutf7, v);
		}
	}
	return 0;
}
