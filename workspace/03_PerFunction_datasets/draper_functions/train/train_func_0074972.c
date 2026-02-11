wm8350_dcdc_set_suspend_enable(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int dcdc = rdev_get_id(rdev);
	u16 val;

	switch (dcdc) {
	case WM8350_DCDC_1:
		val = wm8350_reg_read(wm8350, WM8350_DCDC1_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC1_LOW_POWER,
			val | wm8350->pmic.dcdc1_hib_mode);
		break;
	case WM8350_DCDC_3:
		val = wm8350_reg_read(wm8350, WM8350_DCDC3_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC3_LOW_POWER,
			val | wm8350->pmic.dcdc3_hib_mode);
		break;
	case WM8350_DCDC_4:
		val = wm8350_reg_read(wm8350, WM8350_DCDC4_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC4_LOW_POWER,
			val | wm8350->pmic.dcdc4_hib_mode);
		break;
	case WM8350_DCDC_6:
		val = wm8350_reg_read(wm8350, WM8350_DCDC6_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC6_LOW_POWER,
			val | wm8350->pmic.dcdc6_hib_mode);
		break;
	case WM8350_DCDC_2:
	case WM8350_DCDC_5:
	default:
		return -EINVAL;
	}

	return 0;
}
