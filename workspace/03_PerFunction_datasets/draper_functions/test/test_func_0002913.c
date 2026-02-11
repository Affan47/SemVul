lp8788_init_dvs(struct platform_device *pdev,
			struct lp8788_buck *buck, enum lp8788_buck_id id)
{
	struct lp8788_platform_data *pdata = buck->lp->pdata;
	u8 mask[] = { LP8788_BUCK1_DVS_SEL_M, LP8788_BUCK2_DVS_SEL_M };
	u8 val[]  = { LP8788_BUCK1_DVS_PIN, LP8788_BUCK2_DVS_PIN };
	u8 default_dvs_mode[] = { LP8788_BUCK1_DVS_I2C, LP8788_BUCK2_DVS_I2C };


	if (id > BUCK2)
		return 0;


	if (!pdata)
		goto set_default_dvs_mode;

	if ((id == BUCK1 && !pdata->buck1_dvs) ||
		(id == BUCK2 && !pdata->buck2_dvs))
		goto set_default_dvs_mode;

	if (lp8788_dvs_gpio_request(pdev, buck, id))
		goto set_default_dvs_mode;

	return lp8788_update_bits(buck->lp, LP8788_BUCK_DVS_SEL, mask[id],
				val[id]);

set_default_dvs_mode:
	return lp8788_update_bits(buck->lp, LP8788_BUCK_DVS_SEL, mask[id],
				  default_dvs_mode[id]);
}
