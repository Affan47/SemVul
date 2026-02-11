myri10ge_nvs_write ( struct nvs_device *nvs,
				unsigned int addr,
				const void *_buf,
				size_t len )
{
	struct myri10ge_private *priv =
		container_of (nvs, struct myri10ge_private, nvs);
	struct pci_device *pci = myri10ge_pcidev ( myri10ge_netdev ( priv ) );
	unsigned int vs = priv->pci_cap_vs;
	const unsigned char *buf = (const unsigned char *)_buf;
	unsigned int i;
	uint8 verify;

	DBGP ( "nvs_write " );
	DBGP_HDA ( addr, _buf, len );


	DBGP ( "erasing " );
	pci_write_config_dword ( pci, VS_EEPROM_WRITE, ( addr << 8 ) | 0xff );


	DBGP ( "waiting " );
	pci_read_config_byte ( pci, VS_EEPROM_READ_DATA, &verify );
	while ( verify != 0xff ) {
		pci_write_config_byte ( pci, VS_EEPROM_READ_ADDR + 1, addr );
		pci_read_config_byte ( pci, VS_EEPROM_READ_DATA, &verify );
	}


	DBGP ( "writing " );
	pci_write_config_byte ( pci, VS_MODE, VS_MODE_EEPROM_STREAM_WRITE );
	pci_write_config_dword ( pci, VS_ADDR, addr );
	for (i=0; i<len; i++, addr++)
		pci_write_config_byte ( pci, VS_DATA, buf[i] );
	pci_write_config_dword ( pci, VS_ADDR, 0xffffffff );
	pci_write_config_byte ( pci, VS_MODE, 0 );

	DBGP ( "done\n" );
	return 0;
}
