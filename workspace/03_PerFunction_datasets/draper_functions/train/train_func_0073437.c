sgtl5000_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 adcdac_ctrl = SGTL5000_DAC_MUTE_LEFT | SGTL5000_DAC_MUTE_RIGHT;

	snd_soc_update_bits(codec, SGTL5000_CHIP_ADCDAC_CTRL,
			adcdac_ctrl, mute ? adcdac_ctrl : 0);

	return 0;
}
