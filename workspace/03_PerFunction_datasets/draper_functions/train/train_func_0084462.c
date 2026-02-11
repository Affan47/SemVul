e100_eeprom_load(struct nic *nic)
{
	u16 addr, addr_len = 8, checksum = 0;


	e100_eeprom_read(nic, &addr_len, 0);
	nic->eeprom_wc = 1 << addr_len;

	for (addr = 0; addr < nic->eeprom_wc; addr++) {
		nic->eeprom[addr] = e100_eeprom_read(nic, &addr_len, addr);
		if (addr < nic->eeprom_wc - 1)
			checksum += le16_to_cpu(nic->eeprom[addr]);
	}


	if (cpu_to_le16(0xBABA - checksum) != nic->eeprom[nic->eeprom_wc - 1]) {
		netif_err(nic, probe, nic->netdev, "EEPROM corrupted\n");
		if (!eeprom_bad_csum_allow)
			return -EAGAIN;
	}

	return 0;
}
