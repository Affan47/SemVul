update_crc(unsigned long crc, unsigned char *buf, int len)
	{
		unsigned long c = crc;
		int n;

		if (!crc_table_computed)
		{
			make_crc_table();
		}

		for (n = 0; n < len; n++)
		{
			c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
		}

		return c;
	}
