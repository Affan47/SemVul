request_world_data(void)
{
	int world = CRAM[0][0x00D] / 4;


	if (extra_version)
	{
		static const UINT8 world_swap[] =
		{
			8, 7, 6, 4, 0, 2, 3, 5, 1, 9
		};

		world = world_swap[world];
	}


	memcpy(CRAM[4] + 2, CROM_BANK4[world].data, CROM_BANK4[world].size);
	memcpy(CRAM[5] + 2, CROM_BANK5[world].data, CROM_BANK5[world].size);
	memcpy(CRAM[7] + 2, CROM_BANK7[world].data, CROM_BANK7[world].size);


	if (extra_version)
	{
		int i;

		for (i = 0; i < 8; i++)
		{
			UINT16 patch = cchip_extra_patch[world][i];

			if (patch != 0)
			{
				CRAM[5][CRAM[5][2] + 22 * i + 18] = patch >> 0;
				CRAM[5][CRAM[5][2] + 22 * i + 19] = patch >> 8;
			}
		}

		memcpy(CRAM[6] + 2, CROM_BANK6_EXTRA, sizeof CROM_BANK6_EXTRA);
	}
	else
	{
		memcpy(CRAM[6] + 2, CROM_BANK6, sizeof CROM_BANK6);
	}
}
