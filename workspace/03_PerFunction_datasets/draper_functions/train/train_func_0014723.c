adv7511_power_on(struct adv7511 *adv7511)
{
	adv7511->current_edid_segment = -1;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER,
			   ADV7511_POWER_POWER_DOWN, 0);
	if (adv7511->i2c_main->irq) {


		regmap_write(adv7511->regmap, ADV7511_REG_INT_ENABLE(0),
			     ADV7511_INT0_EDID_READY);
		regmap_write(adv7511->regmap, ADV7511_REG_INT_ENABLE(1),
			     ADV7511_INT1_DDC_ERROR);
	}


	regmap_update_bits(adv7511->regmap, ADV7511_REG_POWER2,
			   ADV7511_REG_POWER2_HDP_SRC_MASK,
			   ADV7511_REG_POWER2_HDP_SRC_NONE);


	regcache_sync(adv7511->regmap);

	adv7511->powered = true;
}
