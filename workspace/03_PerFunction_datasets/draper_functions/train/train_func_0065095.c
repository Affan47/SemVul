hermon_reset ( struct hermon *hermon ) {
	struct pci_device *pci = hermon->pci;
	struct pci_config_backup backup;
	static const uint8_t backup_exclude[] =
		PCI_CONFIG_BACKUP_EXCLUDE ( 0x58, 0x5c );


	pci_backup ( pci, &backup, backup_exclude );
	writel ( HERMON_RESET_MAGIC,
		 ( hermon->config + HERMON_RESET_OFFSET ) );
	mdelay ( HERMON_RESET_WAIT_TIME_MS );
	pci_restore ( pci, &backup, backup_exclude );


	hermon->toggle = 0;
}
