YMZ280B_state_save_update_step(void)
{
	int i,j;
	for (i = 0; i < chip_num; i++)
	{
		for (j = 0; j < 8; j++)
		{
			struct YMZ280BChip *chip = &ymz280b[i];
			struct YMZ280BVoice *voice = &chip->voice[j];
			update_step(chip, voice);
		}
	}
}
