vf610_adc_cfg_post_set(struct vf610_adc *info)
{
	struct vf610_adc_feature *adc_feature = &info->adc_feature;
	int cfg_data = 0;
	int gc_data = 0;

	switch (adc_feature->clk_sel) {
	case VF610_ADCIOC_ALTCLK_SET:
		cfg_data |= VF610_ADC_ALTCLK_SEL;
		break;
	case VF610_ADCIOC_ADACK_SET:
		cfg_data |= VF610_ADC_ADACK_SEL;
		break;
	default:
		break;
	}


	cfg_data |= VF610_ADC_ADLPC_EN;


	cfg_data |= VF610_ADC_ADHSC_EN;


	switch (adc_feature->vol_ref) {
	case VF610_ADCIOC_VR_VREF_SET:
		break;
	case VF610_ADCIOC_VR_VALT_SET:
		cfg_data |= VF610_ADC_REFSEL_VALT;
		break;
	case VF610_ADCIOC_VR_VBG_SET:
		cfg_data |= VF610_ADC_REFSEL_VBG;
		break;
	default:
		dev_err(info->dev, "error voltage reference\n");
	}


	if (adc_feature->ovwren)
		cfg_data |= VF610_ADC_OVWREN;

	writel(cfg_data, info->regs + VF610_REG_ADC_CFG);
	writel(gc_data, info->regs + VF610_REG_ADC_GC);
}
