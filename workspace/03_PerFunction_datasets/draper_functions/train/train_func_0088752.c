efi_download_install ( EFI_HANDLE *handle ) {
	EFI_BOOT_SERVICES *bs = efi_systab->BootServices;
	EFI_STATUS efirc;
	int rc;

	efirc = bs->InstallMultipleProtocolInterfaces (
			handle,
			&ipxe_download_protocol_guid,
			&ipxe_download_protocol_interface,
			NULL );
	if ( efirc ) {
		rc = -EEFI ( efirc );
		DBG ( "Could not install download protocol: %s\n",
		      strerror ( rc ) );
		return rc;
	}

	return 0;
}
