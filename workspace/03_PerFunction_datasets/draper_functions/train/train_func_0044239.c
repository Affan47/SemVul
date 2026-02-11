ssdv_outbits(ssdv_t *s, uint16_t bits, uint8_t length)
{
	uint8_t b;

	if(length)
	{
		s->outbits <<= length;
		s->outbits |= bits & ((1 << length) - 1);
		s->outlen += length;
	}

	while(s->outlen >= 8 && s->out_len > 0)
	{
		b = s->outbits >> (s->outlen - 8);


		*(s->outp++) = b;
		s->outlen -= 8;
		s->out_len--;


		if(s->out_stuff && b == 0xFF)
		{
			s->outbits &= (1 << s->outlen) - 1;
			s->outlen += 8;
		}
	}

	return(s->out_len ? SSDV_OK : SSDV_BUFFER_FULL);
}
