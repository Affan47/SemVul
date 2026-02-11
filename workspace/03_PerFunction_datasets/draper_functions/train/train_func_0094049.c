bzimage_exec ( struct image *image ) {
	struct bzimage_context bzimg;
	const char *cmdline = ( image->cmdline ? image->cmdline : "" );
	int rc;


	if ( ( rc = bzimage_parse_header ( image, &bzimg,
					   image->priv.user ) ) != 0 )
		return rc;
	assert ( bzimg.rm_kernel == image->priv.user );


	if ( ( rc = bzimage_parse_cmdline ( image, &bzimg, cmdline ) ) != 0)
		return rc;


	if ( ( rc = bzimage_set_cmdline ( image, &bzimg, cmdline ) ) != 0 )
		return rc;


	if ( ( rc = bzimage_load_initrds ( image, &bzimg ) ) != 0 )
		return rc;


	bzimage_update_header ( image, &bzimg, bzimg.rm_kernel );


	shutdown ( SHUTDOWN_BOOT );

	DBGC ( image, "bzImage %p jumping to RM kernel at %04x:0000 "
	       "(stack %04x:%04zx)\n", image, ( bzimg.rm_kernel_seg + 0x20 ),
	       bzimg.rm_kernel_seg, bzimg.rm_heap );


	__asm__ __volatile__ ( REAL_CODE ( "movw %w0, %%ds\n\t"
					   "movw %w0, %%es\n\t"
					   "movw %w0, %%fs\n\t"
					   "movw %w0, %%gs\n\t"
					   "movw %w0, %%ss\n\t"
					   "movw %w1, %%sp\n\t"
					   "pushw %w2\n\t"
					   "pushw $0\n\t"
					   "lret\n\t" )
			       : : "r" ( bzimg.rm_kernel_seg ),
			           "r" ( bzimg.rm_heap ),
			           "r" ( bzimg.rm_kernel_seg + 0x20 ) );


	assert ( 0 );

	return -ECANCELED;
}
