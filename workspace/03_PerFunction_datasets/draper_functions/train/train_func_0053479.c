InitCompressorZlib(CompressorState *cs, int level)
{
	z_streamp			zp;

	zp = cs->zp = (z_streamp) malloc(sizeof(z_stream));
	if (cs->zp == NULL)
		die_horribly(NULL, modulename, "out of memory\n");
	zp->zalloc = Z_NULL;
	zp->zfree = Z_NULL;
	zp->opaque = Z_NULL;


	cs->zlibOut = (char *) malloc(ZLIB_OUT_SIZE + 1);
	cs->zlibOutSize = ZLIB_OUT_SIZE;

	if (cs->zlibOut == NULL)
		die_horribly(NULL, modulename, "out of memory\n");

	if (deflateInit(zp, level) != Z_OK)
		die_horribly(NULL, modulename,
					 "could not initialize compression library: %s\n",
					 zp->msg);


	zp->next_out = (void *) cs->zlibOut;
	zp->avail_out = cs->zlibOutSize;
}
