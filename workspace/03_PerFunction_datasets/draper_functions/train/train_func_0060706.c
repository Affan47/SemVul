leland_init_eeprom(UINT8 default_val, const UINT16 *data, UINT8 serial_offset, UINT8 serial_type)
{
	static struct EEPROM_interface eeprom_interface =
	{
		6,
		16,
		"110",
		"101",
		"111"
	};
	UINT8 xorval = (serial_type == SERIAL_TYPE_ADD_XOR || serial_type == SERIAL_TYPE_ENCRYPT_XOR) ? 0xff : 0x00;
	UINT32 serial;


	memset(eeprom_data, default_val, sizeof(eeprom_data));


	while (*data != 0xffff)
	{
		int offset = *data++;
		int value = *data++;
		eeprom_data[offset * 2 + 0] = value >> 8;
		eeprom_data[offset * 2 + 1] = value & 0xff;
	}


	serial = 0x12345678;


	switch (serial_type)
	{
		case SERIAL_TYPE_ADD:
		case SERIAL_TYPE_ADD_XOR:
		{
			int i;
			for (i = 0; i < 10; i++)
			{
				int digit;

				if (i >= 8)
					digit = 0;
				else
					digit = ((serial << (i * 4)) >> 28) & 15;
				digit = ('0' + digit) * 2;

				eeprom_data[serial_offset * 2 +  0 + (i ^ 1)] = (digit / 3) ^ xorval;
				eeprom_data[serial_offset * 2 + 10 + (i ^ 1)] = (digit / 3) ^ xorval;
				eeprom_data[serial_offset * 2 + 20 + (i ^ 1)] = (digit - (2 * (digit / 3))) ^ xorval;
			}
			break;
		}

		case SERIAL_TYPE_ENCRYPT:
		case SERIAL_TYPE_ENCRYPT_XOR:
		{
			int d, e, h, l;


			l = (serial >> 24) & 0xff;
			h = (serial >> 16) & 0xff;
			e = (serial >> 8) & 0xff;
			d = serial & 0xff;


			h = ((h ^ 0x2a ^ l) ^ 0xff) + 5;
			d = ((d + 0x2a) ^ e) ^ 0xff;
			l ^= e;
			e ^= 0x2a;


			eeprom_data[serial_offset * 2 + 0] = h ^ xorval;
			eeprom_data[serial_offset * 2 + 1] = l ^ xorval;
			eeprom_data[serial_offset * 2 + 2] = d ^ xorval;
			eeprom_data[serial_offset * 2 + 3] = e ^ xorval;
			break;
		}
	}

	EEPROM_init(&eeprom_interface);
}
