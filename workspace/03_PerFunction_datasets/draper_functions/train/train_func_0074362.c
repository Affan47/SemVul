treahunt_decode(void)
{
	int A;
	unsigned char *rom = memory_region(REGION_CPU1);
	int diff = memory_region_length(REGION_CPU1) / 2;
	int data;


	memory_set_opcode_base(0,rom+diff);


	for (A = 0; A < 0x4000; A++)
	{
		data = rom[A];

		if (A & 0x1000)
		{

			rom[A+diff] =
				 ((data & 0x01) << 7) |
				 ((data & 0x02) << 3) |
				 ((data & 0x04) << 4) |
				  (data & 0x28) |
				 ((data & 0x10) >> 3) |
				 ((data & 0x40) >> 4) |
				 ((data & 0x80) >> 7);

			if ((A & 0x04) == 0)

				rom[A+diff] ^= 0x81;
		}
		else
		{

			rom[A+diff] =
					(~data & 0x81) |
					((data & 0x02) << 3) |
					((data & 0x04) << 4) |
					 (data & 0x28) |
					((data & 0x10) >> 3) |
					((data & 0x40) >> 4);
		}
	}
}
