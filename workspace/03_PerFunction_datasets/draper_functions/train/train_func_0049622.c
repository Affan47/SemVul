is_valid_utf8_str(const unsigned char* string, size_t length)
{
	int expect = 0;
	char div = 0;
	size_t pos = 0;

	if (length == 0) return 1;

	for (pos = 0; pos < length; pos++)
	{
		if (expect)
		{
			if ((string[pos] & 0xC0) == 0x80) expect--;
			else return 0;
		}
		else
		{
			if (string[pos] & 0x80)
			{
				for (div = 0x40; div > 0x08; div /= 2)
				{
					if (string[pos] & div) expect++;
					else break;
				}
				if ((string[pos] & div) || (pos+expect >= length)) return 0;
				switch (expect) {
					case 0:
						return 0;
					case 1:

						if (string[pos] < 0xC2) return 0;
						break;
					case 2:

						if ((string[pos] == 0xE0) && (string[pos+1] < 0xA0 )) return 0;

						if ((string[pos] == 0xED) && (string[pos+1] > 0x9F )) return 0;
						break;
					case 3:

						if ((string[pos] == 0xF0) && (string[pos+1] < 0x90 )) return 0;
						if (string[pos] > 0xF4) return 0;
						if ((string[pos] == 0xF4) && (string[pos+1] > 0x8F )) return 0;
						break;
				}
			}
		}
	}
	return 1;
}
