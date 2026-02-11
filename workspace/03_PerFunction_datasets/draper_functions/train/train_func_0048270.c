eltorito_load_disk ( struct image *image,
				struct eltorito_boot_entry *boot_entry ) {
	unsigned long start = ( boot_entry->start * ISO9660_BLKSIZE );
	unsigned long length = ( boot_entry->length * ISO9660_BLKSIZE );
	unsigned int load_segment;
	userptr_t buffer;
	int rc;


	if ( image->len < ( start + length ) ) {
		DBGC ( image, "ElTorito %p virtual disk lies outside image\n",
		       image );
		return -ENOEXEC;
	}
	DBGC ( image, "ElTorito %p virtual disk at %#lx+%#lx\n",
	       image, start, length );


	load_segment = boot_entry->load_segment;
	buffer = real_to_user ( load_segment, ( load_segment ? 0 : 0x7c00 ) );


	if ( ( rc = prep_segment ( buffer, length, length ) ) != 0 ) {
		DBGC ( image, "ElTorito %p could not prepare segment: %s\n",
		       image, strerror ( rc ) );
		return rc;
	}


	memcpy_user ( buffer, 0, image->data, start, length );

	return 0;
}
