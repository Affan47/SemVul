pglz_decompress(const PGLZ_Header *source, char *dest)
{
	const unsigned char *sp;
	const unsigned char *srcend;
	unsigned char *dp;
	unsigned char *destend;

	sp = ((const unsigned char *) source) + sizeof(PGLZ_Header);
	srcend = ((const unsigned char *) source) + VARSIZE(source);
	dp = (unsigned char *) dest;
	destend = dp + source->rawsize;

	while (sp < srcend && dp < destend)
	{


		unsigned char ctrl = *sp++;
		int			ctrlc;

		for (ctrlc = 0; ctrlc < 8 && sp < srcend; ctrlc++)
		{
			if (ctrl & 1)
			{


				int32		len;
				int32		off;

				len = (sp[0] & 0x0f) + 3;
				off = ((sp[0] & 0xf0) << 4) | sp[1];
				sp += 2;
				if (len == 18)
					len += *sp++;


				if (dp + len > destend)
				{
					dp += len;
					break;
				}


				while (len--)
				{
					*dp = dp[-off];
					dp++;
				}
			}
			else
			{


				if (dp >= destend)
					break;

				*dp++ = *sp++;
			}


			ctrl >>= 1;
		}
	}


	if (dp != destend || sp != srcend)
		elog(ERROR, "compressed data is corrupt");


}
