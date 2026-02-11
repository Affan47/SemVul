CRC32(const char* sz)
	{
		uint32 crc = 0xffffffff;

		while (*sz != 0)
		{
			crc = (crc >> 8) ^ kCRCTable[(crc & 0xFF) ^ (uint8)(*sz++)];
		}

		return (crc32) (crc ^ 0xffffffff);
	}
