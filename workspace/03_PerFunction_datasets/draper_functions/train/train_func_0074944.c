TLan_EeReadByte(u16 io_base, u8 ee_addr, u8 * data)
{
	int err;
	int ret = 0;


	TLan_EeSendStart(io_base);
	err = TLan_EeSendByte(io_base, 0xA0, TLAN_EEPROM_ACK);
	if (err) {
		ret = 1;
		goto fail;
	}
	err = TLan_EeSendByte(io_base, ee_addr, TLAN_EEPROM_ACK);
	if (err) {
		ret = 2;
		goto fail;
	}
	TLan_EeSendStart(io_base);
	err = TLan_EeSendByte(io_base, 0xA1, TLAN_EEPROM_ACK);
	if (err) {
		ret = 3;
		goto fail;
	}
	TLan_EeReceiveByte(io_base, data, TLAN_EEPROM_STOP);
      fail:

	return ret;

}
