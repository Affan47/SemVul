snd_opl3_reset(struct snd_opl3 * opl3)
{
	unsigned short opl3_reg;

	unsigned short reg_side;
	unsigned char voice_offset;

	int max_voices, i;

	max_voices = (opl3->hardware < OPL3_HW_OPL3) ?
		MAX_OPL2_VOICES : MAX_OPL3_VOICES;

	for (i = 0; i < max_voices; i++) {

		if (i < MAX_OPL2_VOICES) {

			reg_side = OPL3_LEFT;
			voice_offset = i;
		} else {

			reg_side = OPL3_RIGHT;
			voice_offset = i - MAX_OPL2_VOICES;
		}
		opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + snd_opl3_regmap[voice_offset][0]);
		opl3->command(opl3, opl3_reg, OPL3_TOTAL_LEVEL_MASK);
		opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + snd_opl3_regmap[voice_offset][1]);
		opl3->command(opl3, opl3_reg, OPL3_TOTAL_LEVEL_MASK);

		opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
		opl3->command(opl3, opl3_reg, 0x00);
	}

	opl3->max_voices = MAX_OPL2_VOICES;
	opl3->fm_mode = SNDRV_DM_FM_MODE_OPL2;

	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TEST, OPL3_ENABLE_WAVE_SELECT);
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION, 0x00);
	opl3->rhythm = 0;
}
