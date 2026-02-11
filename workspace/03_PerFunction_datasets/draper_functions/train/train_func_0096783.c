efi_file_close ( EFI_FILE_PROTOCOL *this ) {
	struct efi_file *file = container_of ( this, struct efi_file, file );


	if ( ! file->image )
		return 0;


	DBGC ( file, "EFIFILE %s closed\n", efi_file_name ( file ) );
	image_put ( file->image );
	free ( file );

	return 0;
}
