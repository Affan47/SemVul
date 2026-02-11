e100_asf(struct nic *nic)
{

	return (nic->pdev->device >= 0x1050) && (nic->pdev->device <= 0x1057) &&
	   (nic->eeprom[eeprom_config_asf] & eeprom_asf) &&
	   !(nic->eeprom[eeprom_config_asf] & eeprom_gcl) &&
	   ((nic->eeprom[eeprom_smbus_addr] & 0xFF) != 0xFE);
}
