cpu8051_convert_bit_address(uint8_t bit_address, uint8_t *byte_address,
			    uint8_t *bit_number)
{
	if (bit_address > 0x7F) {

		*byte_address = bit_address & 0xF8;
		*bit_number = bit_address & 0x07;
	} else {

		*byte_address = (bit_address >> 3) + 0x20;
		*bit_number = bit_address & 0x07;
	}
}
