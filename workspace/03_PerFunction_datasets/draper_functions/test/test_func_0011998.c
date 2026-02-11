bzimage_set_cmdline ( struct image *image,
				 struct bzimage_context *bzimg,
				 const char *cmdline ) {
	size_t cmdline_len;


	cmdline_len = ( strlen ( cmdline ) + 1 );
	if ( cmdline_len > bzimg->cmdline_size )
		cmdline_len = bzimg->cmdline_size;
	copy_to_user ( bzimg->rm_kernel, bzimg->rm_cmdline,
		       cmdline, cmdline_len );
	DBGC ( image, "bzImage %p command line \"%s\"\n", image, cmdline );

	return 0;
}
