nes_read16_eeprom(void __iomem *addr, u16 offset)
{
	writel(NES_EEPROM_READ_REQUEST + (offset >> 1),
			(void __iomem *)addr + NES_EEPROM_COMMAND);

	do {
	} while (readl((void __iomem *)addr + NES_EEPROM_COMMAND) &
			NES_EEPROM_READ_REQUEST);

	return readw((void __iomem *)addr + NES_EEPROM_DATA);
}
