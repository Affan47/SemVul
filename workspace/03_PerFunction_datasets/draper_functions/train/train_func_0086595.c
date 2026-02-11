wm8993_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	unsigned int reg;

	reg = snd_soc_read(codec, WM8993_DAC_CTRL);

	if (mute)
		reg |= WM8993_DAC_MUTE;
	else
		reg &= ~WM8993_DAC_MUTE;

	snd_soc_write(codec, WM8993_DAC_CTRL, reg);

	return 0;
}
