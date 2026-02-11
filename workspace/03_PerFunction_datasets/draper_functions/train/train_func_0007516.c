unlzma_main(int argc UNUSED_PARAM, char **argv)
{
	IF_LZMA(int opts =) getopt32(argv, "cfvqdt");
# if ENABLE_LZMA

	if (applet_name[2] == 'm' && !(opts & (OPT_DECOMPRESS|OPT_TEST)))
		bb_show_usage();
# endif

	if (applet_name[2] == 'c')
		option_mask32 |= OPT_STDOUT;

	argv += optind;
	return bbunpack(argv, unpack_lzma_stream, make_new_name_generic, "lzma");
}
