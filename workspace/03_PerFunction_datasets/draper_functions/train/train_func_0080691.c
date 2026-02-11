QC_encode(progfuncs_t *progfuncs, int len, int method, char *in, int handle)
{
	int i;
	if (method == 0)
	{
		SafeWrite(handle, in, len);
		return len;
	}
	else if (method == 1)
	{
		for (i = 0; i < len; i++)
			in[i] = in[i] ^ 0xA5;
		SafeWrite(handle, in, len);
		return len;
	}
	else if (method == 2)
	{
#ifdef AVAIL_ZLIB
		char out[8192];

		z_stream strm = {
			in,
			len,
			0,

			out,
			sizeof(out),
			0,

			NULL,
			NULL,

			NULL,
			NULL,
			NULL,

			Z_BINARY,
			0,
			0
		};
		i=0;

		deflateInit(&strm, Z_BEST_COMPRESSION);
		while(deflate(&strm, Z_FINISH) == Z_OK)
		{
			SafeWrite(handle, out, sizeof(out) - strm.avail_out);
			i+=sizeof(out) - strm.avail_out;
			strm.next_out = out;
			strm.avail_out = sizeof(out);
		}
		SafeWrite(handle, out, sizeof(out) - strm.avail_out);
		i+=sizeof(out) - strm.avail_out;
		deflateEnd(&strm);
		return i;
#endif
		Sys_Error("ZLIB compression not supported in this build");
		return 0;
	}

	else
	{
		Sys_Error("Wierd method");
		return 0;
	}
}
