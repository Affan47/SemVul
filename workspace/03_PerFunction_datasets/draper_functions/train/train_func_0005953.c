gzip_main(int argc, char **argv)
#else
int gzip_main(int argc UNUSED_PARAM, char **argv)
#endif
{
	unsigned opt;

#if ENABLE_FEATURE_GZIP_LONG_OPTIONS
	applet_long_options = gzip_longopts;
#endif

	opt = getopt32(argv, "cfv" IF_GUNZIP("dt") "q123456789n");
#if ENABLE_GUNZIP
	if (opt & 0x18)
		return gunzip_main(argc, argv);
#endif
	option_mask32 &= 0x7;


	argv += optind;

	SET_PTR_TO_GLOBALS((char *)xzalloc(sizeof(struct globals)+sizeof(struct globals2))
			+ sizeof(struct globals));


	ALLOC(uch, G1.l_buf, INBUFSIZ);
	ALLOC(uch, G1.outbuf, OUTBUFSIZ);
	ALLOC(ush, G1.d_buf, DIST_BUFSIZE);
	ALLOC(uch, G1.window, 2L * WSIZE);
	ALLOC(ush, G1.prev, 1L << BITS);


	global_crc32_table = crc32_filltable(NULL, 0);

	return bbunpack(argv, pack_gzip, append_ext, "gz");
}
