image_replace ( struct image *replacement ) {
	struct image *image = current_image;
	int rc;


	assert ( replacement->flags & IMAGE_REGISTERED );


	if ( ! image ) {
		rc = -ENOTTY;
		DBGC ( replacement, "IMAGE %s cannot replace non-existent "
		       "image: %s\n", replacement->name, strerror ( rc ) );
		return rc;
	}


	if ( ( rc = image_probe ( replacement ) ) != 0 )
		return rc;


	image_put ( image->replacement );


	image->replacement = image_get ( replacement );
	DBGC ( image, "IMAGE %s will replace self with IMAGE %s\n",
	       image->name, replacement->name );

	return 0;
}
