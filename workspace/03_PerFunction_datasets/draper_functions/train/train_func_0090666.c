nbi_exec ( struct image *image ) {
	struct imgheader imgheader;
	int may_return;
	int rc;

	copy_from_user ( &imgheader, image->priv.user, 0,
			 sizeof ( imgheader ) );


	if ( ( rc = nbi_prepare_dhcp ( image ) ) != 0 )
		return rc;


	may_return = NBI_PROGRAM_RETURNS ( imgheader.flags );
	if ( ! may_return )
		shutdown ( SHUTDOWN_BOOT );


	if ( NBI_LINEAR_EXEC_ADDR ( imgheader.flags ) ) {
		rc = nbi_boot32 ( image, &imgheader );
	} else {
	        rc = nbi_boot16 ( image, &imgheader );
	}

	if ( ! may_return ) {

		DBGC ( image, "NBI %p returned %d from non-returnable image\n",
		       image, rc  );
		while ( 1 ) {}
	}

	DBGC ( image, "NBI %p returned %d\n", image, rc );

	return rc;
}
