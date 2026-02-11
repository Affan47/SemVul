ali15x3_setup(struct pci_dev *ALI15X3_dev)
{
	u16 a;
	unsigned char temp;


	pci_read_config_byte(ALI15X3_dev, SMBATPC, &temp);
	if (temp & ALI15X3_LOCK) {
		temp &= ~ALI15X3_LOCK;
		pci_write_config_byte(ALI15X3_dev, SMBATPC, temp);
	}


	pci_read_config_word(ALI15X3_dev, SMBBA, &ali15x3_smba);
	ali15x3_smba &= (0xffff & ~(ALI15X3_SMB_IOSIZE - 1));
	if (ali15x3_smba == 0 && force_addr == 0) {
		dev_err(&ALI15X3_dev->dev, "ALI15X3_smb region uninitialized "
			"- upgrade BIOS or use force_addr=0xaddr\n");
		return -ENODEV;
	}

	if(force_addr)
		ali15x3_smba = force_addr & ~(ALI15X3_SMB_IOSIZE - 1);

	if (acpi_check_region(ali15x3_smba, ALI15X3_SMB_IOSIZE,
			      ali15x3_driver.name))
		return -EBUSY;

	if (!request_region(ali15x3_smba, ALI15X3_SMB_IOSIZE,
			    ali15x3_driver.name)) {
		dev_err(&ALI15X3_dev->dev,
			"ALI15X3_smb region 0x%x already in use!\n",
			ali15x3_smba);
		return -ENODEV;
	}

	if(force_addr) {
		dev_info(&ALI15X3_dev->dev, "forcing ISA address 0x%04X\n",
			ali15x3_smba);
		if (PCIBIOS_SUCCESSFUL != pci_write_config_word(ALI15X3_dev,
								SMBBA,
								ali15x3_smba))
			goto error;
		if (PCIBIOS_SUCCESSFUL != pci_read_config_word(ALI15X3_dev,
								SMBBA, &a))
			goto error;
		if ((a & ~(ALI15X3_SMB_IOSIZE - 1)) != ali15x3_smba) {

			dev_err(&ALI15X3_dev->dev,
				"force address failed - not supported?\n");
			goto error;
		}
	}

	pci_read_config_byte(ALI15X3_dev, SMBCOM, &temp);
	if ((temp & 1) == 0) {
		dev_info(&ALI15X3_dev->dev, "enabling SMBus device\n");
		pci_write_config_byte(ALI15X3_dev, SMBCOM, temp | 0x01);
	}


	pci_read_config_byte(ALI15X3_dev, SMBHSTCFG, &temp);
	if ((temp & 1) == 0) {
		dev_info(&ALI15X3_dev->dev, "enabling SMBus controller\n");
		pci_write_config_byte(ALI15X3_dev, SMBHSTCFG, temp | 0x01);
	}


	pci_write_config_byte(ALI15X3_dev, SMBCLK, 0x20);


	pci_read_config_byte(ALI15X3_dev, SMBREV, &temp);
	dev_dbg(&ALI15X3_dev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&ALI15X3_dev->dev, "iALI15X3_smba = 0x%X\n", ali15x3_smba);

	return 0;
error:
	release_region(ali15x3_smba, ALI15X3_SMB_IOSIZE);
	return -ENODEV;
}
