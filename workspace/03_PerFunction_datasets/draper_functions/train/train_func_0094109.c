chv_config_get(struct pinctrl_dev *pctldev, unsigned pin,
			  unsigned long *config)
{
	struct chv_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	unsigned long flags;
	u32 ctrl0, ctrl1;
	u16 arg = 0;
	u32 term;

	raw_spin_lock_irqsave(&chv_lock, flags);
	ctrl0 = readl(chv_padreg(pctrl, pin, CHV_PADCTRL0));
	ctrl1 = readl(chv_padreg(pctrl, pin, CHV_PADCTRL1));
	raw_spin_unlock_irqrestore(&chv_lock, flags);

	term = (ctrl0 & CHV_PADCTRL0_TERM_MASK) >> CHV_PADCTRL0_TERM_SHIFT;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (term)
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		if (!(ctrl0 & CHV_PADCTRL0_TERM_UP))
			return -EINVAL;

		switch (term) {
		case CHV_PADCTRL0_TERM_20K:
			arg = 20000;
			break;
		case CHV_PADCTRL0_TERM_5K:
			arg = 5000;
			break;
		case CHV_PADCTRL0_TERM_1K:
			arg = 1000;
			break;
		}

		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (!term || (ctrl0 & CHV_PADCTRL0_TERM_UP))
			return -EINVAL;

		switch (term) {
		case CHV_PADCTRL0_TERM_20K:
			arg = 20000;
			break;
		case CHV_PADCTRL0_TERM_5K:
			arg = 5000;
			break;
		}

		break;

	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (!(ctrl1 & CHV_PADCTRL1_ODEN))
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE: {
		u32 cfg;

		cfg = ctrl0 & CHV_PADCTRL0_GPIOCFG_MASK;
		cfg >>= CHV_PADCTRL0_GPIOCFG_SHIFT;
		if (cfg != CHV_PADCTRL0_GPIOCFG_HIZ)
			return -EINVAL;

		break;
	}

	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);
	return 0;
}
