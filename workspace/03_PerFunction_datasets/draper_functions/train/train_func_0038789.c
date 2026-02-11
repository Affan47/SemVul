eepromWriteStatus(int8_t status) {
	eepromData.buf.cmd = EEPROM_WRSR;
	*(uint8_t *)&eepromData.buf.addr = status;

	eepromData.spiFlag = 0;
	spiTransaction(eepromData.spi, &eepromData.buf, &eepromData.buf, 2);

	while (!eepromData.spiFlag) {
		yield(1);
	}

	yield(5);
}
