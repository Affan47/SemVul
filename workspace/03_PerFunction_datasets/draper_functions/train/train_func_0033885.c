process_write_bit(bool a)
{
	static uint_8 buf[BUF_SIZE];
	static int current_bit = 0;

	if (fout == 0)
		fout = fopen("test", "wb");

	if (a >> 1)
	{
		int i;
		for (i = 0 ; i <= 7 - (current_bit & 0x07) ; i++)
			buf[current_bit / 8] |= (1 << i);

		for (i = 0 ; i < (current_bit + 7) / 8 ; i++)
		{
			fwrite(&buf[i], 1, 1, fout);
			if (buf[i] == 0xff)
			{
				static uint_8 padding = 0;
				fwrite(&padding, 1, 1, fout);
			}
		}

		current_bit = 0;
		return;
	}

	if ((current_bit & 0x7) == 0) buf[current_bit / 8] = 0;

	buf[current_bit / 8] |= a << (7 - (current_bit & 0x07));
	current_bit++;

	if (current_bit == BUF_SIZE * 8)
	{
		int i;

		current_bit = 0;
		for (i = 0 ; i < BUF_SIZE ; i++)
		{
			fwrite(&buf[i], 1, 1, fout);
			if (buf[i] == 0xff)
			{
				static uint_8 padding = 0;
				fwrite(&padding, 1, 1, fout);
			}
		}
	}
}
