efi_image_probe ( struct image *image ) {
	EFI_BOOT_SERVICES *bs = efi_systab->BootServices;
	EFI_HANDLE handle;
	EFI_STATUS efirc;
	int rc;


	if ( ( efirc = bs->LoadImage ( FALSE, efi_image_handle, NULL,
				       user_to_virt ( image->data, 0 ),
				       image->len, &handle ) ) != 0 ) {

		rc = -EEFI_LOAD ( efirc );
		DBGC ( image, "EFIIMAGE %p could not load: %s\n",
		       image, strerror ( rc ) );
		return rc;
	}


	bs->UnloadImage ( handle );

	return 0;
}
