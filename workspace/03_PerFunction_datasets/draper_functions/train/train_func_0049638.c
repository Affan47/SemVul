octeon_console_send_cmd(struct octeon_device *oct, char *cmd_str,
			    u32 wait_hundredths)
{
	u32 len = strlen(cmd_str);

	dev_dbg(&oct->pci_dev->dev, "sending \"%s\" to bootloader\n", cmd_str);

	if (len > BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN - 1) {
		dev_err(&oct->pci_dev->dev, "Command string too long, max length is: %d\n",
			BOOTLOADER_PCI_WRITE_BUFFER_STR_LEN - 1);
		return -1;
	}

	if (octeon_wait_for_bootloader(oct, wait_hundredths) != 0) {
		dev_err(&oct->pci_dev->dev, "Bootloader not ready for command.\n");
		return -1;
	}


	octeon_remote_lock();
	octeon_pci_write_core_mem(oct, BOOTLOADER_PCI_READ_BUFFER_DATA_ADDR,
				  (u8 *)cmd_str, len);
	octeon_write_device_mem32(oct, BOOTLOADER_PCI_READ_BUFFER_LEN_ADDR,
				  len);
	octeon_write_device_mem32(oct, BOOTLOADER_PCI_READ_BUFFER_OWNER_ADDR,
				  OCTEON_PCI_IO_BUF_OWNER_OCTEON);


	if (octeon_wait_for_bootloader(oct, 200) != 0) {
		octeon_remote_unlock();
		dev_err(&oct->pci_dev->dev, "Bootloader did not accept command.\n");
		return -1;
	}
	octeon_remote_unlock();
	return 0;
}
