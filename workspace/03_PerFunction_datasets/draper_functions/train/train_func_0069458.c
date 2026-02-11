DeflateCompressorZlib(ArchiveHandle *AH, CompressorState *cs, bool flush)
{
	z_streamp	zp = cs->zp;
	char	   *out = cs->zlibOut;
	int			res = Z_OK;

	while (cs->zp->avail_in != 0 || flush)
	{
		res = deflate(zp, flush ? Z_FINISH : Z_NO_FLUSH);
		if (res == Z_STREAM_ERROR)
			die_horribly(AH, modulename,
						 "could not compress data: %s\n", zp->msg);
		if ((flush && (zp->avail_out < cs->zlibOutSize))
			|| (zp->avail_out == 0)
			|| (zp->avail_in != 0)
			)
		{


			if (zp->avail_out < cs->zlibOutSize)
			{


				size_t len = cs->zlibOutSize - zp->avail_out;
				if (cs->writeF(AH, out, len) != len)
					die_horribly(AH, modulename,
								 "could not write to output file: %s\n",
								 strerror(errno));
			}
			zp->next_out = (void *) out;
			zp->avail_out = cs->zlibOutSize;
		}

		if (res == Z_STREAM_END)
			break;
	}
}
