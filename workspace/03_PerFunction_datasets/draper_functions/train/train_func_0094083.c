find_image ( const char *name ) {
	struct image *image;

	list_for_each_entry ( image, &images, list ) {
		if ( strcmp ( image->name, name ) == 0 )
			return image;
	}

	return NULL;
}
