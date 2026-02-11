twl6040_can_write_to_chip(struct snd_soc_codec *codec,
				  unsigned int reg)
{
	struct twl6040_data *priv = snd_soc_codec_get_drvdata(codec);

	switch (reg) {
	case TWL6040_REG_HSLCTL:
	case TWL6040_REG_HSRCTL:
	case TWL6040_REG_EARCTL:

		return priv->dl1_unmuted;
	case TWL6040_REG_HFLCTL:
	case TWL6040_REG_HFRCTL:
		return priv->dl2_unmuted;
	default:
		return 1;
	}
}
