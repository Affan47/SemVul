ymf271_write_timer(int chipnum, int data)
{
	int slotnum;
	YMF271Chip *chip;
	YMF271Group *group;
	double period;

	chip = &YMF271[chipnum];

	slotnum = fm_tab[chip->timerreg & 0xf];
	group = &chip->groups[slotnum];

	if ((chip->timerreg & 0xf0) == 0)
	{
		group->sync = data & 0x3;
		group->pfm = data >> 7;
	}
	else
	{
		switch (chip->timerreg)
		{
			case 0x10:
				chip->timerA &= ~0xff;
				chip->timerA |= data;
				break;

			case 0x11:
				chip->timerA &= ~0x300;
				chip->timerA |= (data & 0x3)<<8;
				break;

			case 0x12:
				chip->timerB = data;
				break;

			case 0x13:
				if (data & 1)
				{
					chip->timerAVal = chip->timerA;
				}
				if (data & 2)
				{
					chip->timerBVal = chip->timerB;
				}
				if (data & 4)
				{

					chip->enable |= 4;
				}
				if (data & 8)
				{

					chip->enable |= 8;
				}
				if (data & 0x10)
				{
					chip->irqstate &= ~1;
					chip->status &= ~1;

					if (chip->irq_callback) chip->irq_callback(0);

					period = 384.0 * (1024.0 - (double)chip->timerAVal) / (double)CLOCK;

					timer_adjust(chip->timA, TIME_IN_SEC(period), chipnum, TIME_IN_SEC(period));
				}
				if (data & 0x20)
				{
					chip->irqstate &= ~2;
					chip->status &= ~2;

					if (chip->irq_callback) chip->irq_callback(0);

					period = 6144.0 * (256.0 - (double)chip->timerBVal) / (double)CLOCK;

					timer_adjust(chip->timB, TIME_IN_SEC(period), chipnum, TIME_IN_SEC(period));
				}

				break;
		}
	}
}
