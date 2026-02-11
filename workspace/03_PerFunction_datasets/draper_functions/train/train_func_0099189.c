is_volatile_reg(struct device *dev, unsigned int reg)
{
	struct tps65910 *tps65910 = dev_get_drvdata(dev);


	if ((reg >= TPS65910_VIO) && (reg <= TPS65910_VDAC)) {

		if (tps65910_chip_id(tps65910) == TPS65910)
			if ((reg == TPS65911_VDDCTRL_OP) ||
				(reg == TPS65911_VDDCTRL_SR))
				return true;
		return false;
	}
	return true;
}
