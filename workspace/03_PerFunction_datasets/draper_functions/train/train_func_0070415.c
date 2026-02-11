eepromWriteBlock(uint16_t address, int size) {
	eepromWriteEnable();

	eepromData.buf.cmd = EEPROM_WRITE;
	eepromData.buf.addr[1] = (address&0xff);
	eepromData.buf.addr[0] = (address>>8);

	eepromData.spiFlag = 0;
	spiTransaction(eepromData.spi, &eepromData.buf, &eepromData.buf, size+3);

	while (!eepromData.spiFlag) {
		yield(1);
	}

	do {
		yield(1);
		eepromReadStatus();
	} while (eepromData.status & 0b01);
}
