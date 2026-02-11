embedded_init ( void ) {
	int i;
	struct image *image;
	void *data;
	int rc;


	if ( ! sizeof ( embedded_images ) )
		return;


	for ( i = 0 ; i < ( int ) ( sizeof ( embedded_images ) /
				    sizeof ( embedded_images[0] ) ) ; i++ ) {
		image = &embedded_images[i];


		data = ( ( void * ) image->data );
		image->data = virt_to_user ( data );

		DBG ( "Embedded image \"%s\": %zd bytes at %p\n",
		      image->name, image->len, data );

		if ( ( rc = register_image ( image ) ) != 0 ) {
			DBG ( "Could not register embedded image \"%s\": "
			      "%s\n", image->name, strerror ( rc ) );
			return;
		}
	}


	image = &embedded_images[0];
	if ( ( rc = image_autoload ( image ) ) != 0 ) {
		DBG ( "Could not load embedded image \"%s\": %s\n",
		      image->name, strerror ( rc ) );
		return;
	}
}
