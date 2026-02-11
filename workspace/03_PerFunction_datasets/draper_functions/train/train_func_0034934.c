ymf271_pcm_update(int num, INT16 **outputs, int length)
{
	int i, j;
	INT32 mix[48000*2];
	INT32 *mixp;
	INT16 sample = 0;
	YMF271Chip *chip = &YMF271[num];
	YMF271Slot *slot;
	const UINT8 *rombase;

	memset(mix, 0, sizeof(mix[0])*length*2);

	rombase = chip->rom;

	for (j = 0; j < 48; j++)
	{
		slot = &chip->slots[j];
		mixp = &mix[0];

		if (slot->active && slot->waveform == 7)
		{
			for (i = 0; i < length; i++)
			{
				if (slot->bits == 8)
				{
					sample = rombase[slot->startaddr + (slot->stepptr>>16)]<<8;
				}
				else
				{
					if (slot->stepptr & 1)
						sample = rombase[slot->startaddr + (slot->stepptr>>17)*3 + 2]<<8 | ((rombase[slot->startaddr + (slot->stepptr>>17)*3 + 1] << 4) & 0xf0);
					else
						sample = rombase[slot->startaddr + (slot->stepptr>>17)*3]<<8 | (rombase[slot->startaddr + (slot->stepptr>>17)*3 + 1] & 0xf0);
				}

				*mixp++ += (sample * volume[slot->tl])>>16;
				*mixp++ += (sample * volume[slot->tl])>>16;

				slot->stepptr += slot->step;
				if ((slot->stepptr>>16) > slot->endaddr)
				{

					slot->stepptr &= 0xffff;
					slot->stepptr |= (slot->loopaddr<<16);
				}
			}
		}
	}

	mixp = &mix[0];
	for (i = 0; i < length; i++)
	{
		outputs[0][i] = (*mixp++)>>4;
		outputs[1][i] = (*mixp++)>>4;
	}
}
