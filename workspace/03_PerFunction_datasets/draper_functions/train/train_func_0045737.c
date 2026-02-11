pci_vpd_write ( struct pci_vpd *vpd, unsigned int address, const void *buf,
		    size_t len ) {
	const uint8_t *bytes = buf;
	uint32_t data;
	size_t skip_len;
	unsigned int i;
	int rc;


	skip_len = ( address & 0x03 );


	for ( address &= ~0x03 ; len ; address += 4 ) {


		if ( skip_len || ( len <= 0x03 ) ) {
			if ( ( rc = pci_vpd_read_dword ( vpd, address,
							 &data ) ) != 0 )
				return rc;
		}


		for ( i = 4 ; i ; i-- ) {
			if ( skip_len ) {
				skip_len--;
			} else if ( len ) {
				data = ( ( data & ~0xff ) | *(bytes++) );
				len--;
			}
			data = ( ( data << 24 ) | ( data >> 8 ) );
		}


		if ( ( rc = pci_vpd_write_dword ( vpd, address, data ) ) != 0 )
			return rc;
	}
	return 0;
}
