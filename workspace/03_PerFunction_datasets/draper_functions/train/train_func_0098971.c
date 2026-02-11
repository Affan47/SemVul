myri10ge_nvs_read ( struct nvs_device *nvs,
			       unsigned int addr,
			       void *_buf,
			       size_t len )
{
	struct myri10ge_private *priv =
		container_of (nvs, struct myri10ge_private, nvs);
	struct pci_device *pci = myri10ge_pcidev ( myri10ge_netdev ( priv ) );
	unsigned int vs = priv->pci_cap_vs;
	unsigned char *buf = (unsigned char *) _buf;
	unsigned int data;
	unsigned int i, j;

	DBGP ( "myri10ge_nvs_read\n" );


	pci_write_config_byte ( pci, VS_EEPROM_READ_ADDR + 3, addr>>16 );
	pci_write_config_byte ( pci, VS_EEPROM_READ_ADDR + 2, addr>>8 );
	pci_write_config_byte ( pci, VS_EEPROM_READ_ADDR + 1, addr );
	addr++;


	for ( i=0; i<len; ++i,addr++ ) {


		if ( ( addr & 0xff ) == 0 ) {
			if ( ( addr & 0xffff ) == 0 ) {
				pci_write_config_byte ( pci,
							VS_EEPROM_READ_ADDR + 3,
							addr >> 16 );
			}
			pci_write_config_byte ( pci,
					        VS_EEPROM_READ_ADDR + 2,
						addr >> 8 );
		}
		pci_write_config_byte ( pci, VS_EEPROM_READ_ADDR + 1, addr );


		if ( ( i & 3 ) == 3 ) {
			pci_read_config_dword ( pci,
						VS_EEPROM_READ_DATA,
						&data );
			for ( j=0; j<4; j++ ) {
				buf[i-j] = data;
				data >>= 8;
			}
		}
	}


	if ( ( i & 3 ) != 0 ) {
		pci_read_config_dword ( pci, VS_EEPROM_READ_DATA, &data );
		for ( j=1; j<=(i&3); j++ ) {
			buf[i-j] = data;
			data >>= 8;
		}
	}

	DBGP_HDA ( addr - len, _buf, len );
	return 0;
}
