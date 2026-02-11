adv7511_set_colormap(struct adv7511 *adv7511, bool enable,
				 const uint16_t *coeff,
				 unsigned int scaling_factor)
{
	unsigned int i;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(1),
			   ADV7511_CSC_UPDATE_MODE, ADV7511_CSC_UPDATE_MODE);

	if (enable) {
		for (i = 0; i < 12; ++i) {
			regmap_update_bits(adv7511->regmap,
					   ADV7511_REG_CSC_UPPER(i),
					   0x1f, coeff[i] >> 8);
			regmap_write(adv7511->regmap,
				     ADV7511_REG_CSC_LOWER(i),
				     coeff[i] & 0xff);
		}
	}

	if (enable)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(0),
				   0xe0, 0x80 | (scaling_factor << 5));
	else
		regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(0),
				   0x80, 0x00);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_CSC_UPPER(1),
			   ADV7511_CSC_UPDATE_MODE, 0);
}
