tps62360_dcdc_set_voltage_sel(struct regulator_dev *dev,
					 unsigned selector)
{
	struct tps62360_chip *tps = rdev_get_drvdata(dev);
	int ret;
	bool found = false;
	int new_vset_id = tps->curr_vset_id;


	if (tps->valid_gpios)
		found = find_voltage_set_register(tps, selector, &new_vset_id);

	if (!found) {
		ret = regmap_update_bits(tps->regmap, REG_VSET0 + new_vset_id,
				tps->voltage_reg_mask, selector);
		if (ret < 0) {
			dev_err(tps->dev,
				"%s(): register %d update failed with err %d\n",
				 __func__, REG_VSET0 + new_vset_id, ret);
			return ret;
		}
		tps->curr_vset_id = new_vset_id;
		tps->curr_vset_vsel[new_vset_id] = selector;
	}


	if (tps->valid_gpios) {
		gpio_set_value_cansleep(tps->vsel0_gpio, new_vset_id & 0x1);
		gpio_set_value_cansleep(tps->vsel1_gpio,
					(new_vset_id >> 1) & 0x1);
	}
	return 0;
}
