rt5645_enable_push_button_irq(struct snd_soc_codec *codec,
	bool enable)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);

	if (enable) {
		snd_soc_dapm_force_enable_pin(dapm, "ADC L power");
		snd_soc_dapm_force_enable_pin(dapm, "ADC R power");
		snd_soc_dapm_sync(dapm);

		snd_soc_update_bits(codec,
					RT5645_INT_IRQ_ST, 0x8, 0x8);
		snd_soc_update_bits(codec,
					RT5650_4BTN_IL_CMD2, 0x8000, 0x8000);
		snd_soc_read(codec, RT5650_4BTN_IL_CMD1);
		pr_debug("%s read %x = %x\n", __func__, RT5650_4BTN_IL_CMD1,
			snd_soc_read(codec, RT5650_4BTN_IL_CMD1));
	} else {
		snd_soc_update_bits(codec, RT5650_4BTN_IL_CMD2, 0x8000, 0x0);
		snd_soc_update_bits(codec, RT5645_INT_IRQ_ST, 0x8, 0x0);

		snd_soc_dapm_disable_pin(dapm, "ADC L power");
		snd_soc_dapm_disable_pin(dapm, "ADC R power");
		snd_soc_dapm_sync(dapm);
	}
}
