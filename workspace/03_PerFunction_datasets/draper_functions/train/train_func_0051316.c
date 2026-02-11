base64_decode(FILE *in, FILE *out)
{
	uint8_t *buf, *outbuf;
	uint32_t holder;
	unsigned int pos, nbytes, num_padding;
	size_t ignore;

	assert((in != NULL) && (out != NULL));

	buf = malloc(DECODE_BUFSIZE);
	if(buf == NULL)
		return -1;
	outbuf = malloc(BUFSIZE);
	if(outbuf == NULL)
		return -1;

	holder = 0;
	pos = 0;
	nbytes = 0;
	num_padding = 0;
	ignore = 0;
	while(!feof(in))
	{
		size_t amt_read;
		unsigned int i;

		amt_read = fread(buf, 1, DECODE_BUFSIZE, in);
		if((amt_read != DECODE_BUFSIZE) && ferror(in))
		{
			free(buf);
			free(outbuf);
			return -1;
		}

		for(i = 0; i < amt_read; i++)
		{
			if(!isbase64(buf[i]))
				continue;
			if(buf[i] == '=')
				++num_padding;
			holder <<= 6;
			holder |= b64tonum[buf[i]];

			if(++nbytes == 4)
			{
				outbuf[pos++] = (holder >> 16) & 0xFF;
				outbuf[pos++] = (holder >> 8) & 0xFF;
				outbuf[pos++] = holder & 0xFF;
				if((pos+3) >= BUFSIZE)
				{
					ignore = fwrite(outbuf, 1, pos, out);
					pos = 0;
				}
				nbytes = 0; holder = 0;
			}
		}
	}


	switch(num_padding)
	{
		case 0:
			ignore = fwrite(outbuf, 1, pos, out);
			break;

		case 1:
			ignore = fwrite(outbuf, 1, pos-1, out);
			break;

		case 2:
			ignore = fwrite(outbuf, 1, pos-2, out);
	}

	free(buf);
	free(outbuf);
	return 0;
}
