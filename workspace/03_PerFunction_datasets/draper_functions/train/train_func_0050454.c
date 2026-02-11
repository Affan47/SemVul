max14577_charger_reg_init(struct max14577_charger *chg)
{
	struct regmap *rmap = chg->max14577->regmap;
	u8 reg_data;
	int ret;


	reg_data = 0x1 << CDETCTRL1_CHGDETEN_SHIFT;
	max14577_update_reg(rmap, MAX14577_REG_CDETCTRL1,
			CDETCTRL1_CHGDETEN_MASK | CDETCTRL1_CHGTYPMAN_MASK,
			reg_data);


	reg_data = 0x1 << CHGCTRL2_VCHGR_RC_SHIFT;
	reg_data |= 0x1 << CHGCTRL2_MBCHOSTEN_SHIFT;
	max14577_write_reg(rmap, MAX14577_REG_CHGCTRL2, reg_data);


	reg_data = 0x0 << CHGCTRL6_AUTOSTOP_SHIFT;
	max14577_write_reg(rmap, MAX14577_REG_CHGCTRL6, reg_data);

	ret = max14577_init_constant_voltage(chg, chg->pdata->constant_uvolt);
	if (ret)
		return ret;

	ret = max14577_init_eoc(chg, chg->pdata->eoc_uamp);
	if (ret)
		return ret;

	ret = max14577_init_fast_charge(chg, chg->pdata->fast_charge_uamp);
	if (ret)
		return ret;

	ret = max14577_set_fast_charge_timer(chg,
			MAXIM_CHARGER_FAST_CHARGE_TIMER_DEFAULT);
	if (ret)
		return ret;


	switch (chg->pdata->ovp_uvolt) {
	case 7500000:
		reg_data = 0x0;
		break;
	case 6000000:
	case 6500000:
	case 7000000:
		reg_data = 0x1 + (chg->pdata->ovp_uvolt - 6000000) / 500000;
		break;
	default:
		dev_err(chg->dev, "Wrong value for OVP: %u\n",
				chg->pdata->ovp_uvolt);
		return -EINVAL;
	}
	reg_data <<= CHGCTRL7_OTPCGHCVS_SHIFT;
	max14577_write_reg(rmap, MAX14577_REG_CHGCTRL7, reg_data);

	return 0;
}
