cchip_timer(int dummy)
{
	if (CRAM[1][0x100] == 1)
	{
		request_round_data();

		CRAM[1][0x100] = 0xFF;
	}

	if (CRAM[5][0x000] == 1)
	{
		request_world_data();

		CRAM[5][0x000] = 0xFF;
	}

	if (CRAM[1][0x149] == 1)
	{
		request_goalin_data();

		CRAM[1][0x149] = 0xFF;
	}

	coin_lockout_w(1, CRAM[0][8] & 0x80);
	coin_lockout_w(0, CRAM[0][8] & 0x40);
	coin_counter_w(1, CRAM[0][8] & 0x20);
	coin_counter_w(0, CRAM[0][8] & 0x10);

	CRAM[0][3] = readinputport(2);
	CRAM[0][4] = readinputport(3);
	CRAM[0][5] = readinputport(4);
	CRAM[0][6] = readinputport(5);
}
