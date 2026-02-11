max77693_muic_irq_work(struct work_struct *work)
{
	struct max77693_muic_info *info = container_of(work,
			struct max77693_muic_info, irq_work);
	int irq_type = -1;
	int i, ret = 0;

	if (!info->edev)
		return;

	mutex_lock(&info->mutex);

	for (i = 0; i < ARRAY_SIZE(muic_irqs); i++)
		if (info->irq == muic_irqs[i].virq)
			irq_type = muic_irqs[i].irq;

	ret = regmap_bulk_read(info->max77693->regmap_muic,
			MAX77693_MUIC_REG_STATUS1, info->status, 2);
	if (ret) {
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		return;
	}

	switch (irq_type) {
	case MAX77693_MUIC_IRQ_INT1_ADC:
	case MAX77693_MUIC_IRQ_INT1_ADC_LOW:
	case MAX77693_MUIC_IRQ_INT1_ADC_ERR:
	case MAX77693_MUIC_IRQ_INT1_ADC1K:


		ret = max77693_muic_adc_handler(info);
		break;
	case MAX77693_MUIC_IRQ_INT2_CHGTYP:
	case MAX77693_MUIC_IRQ_INT2_CHGDETREUN:
	case MAX77693_MUIC_IRQ_INT2_DCDTMR:
	case MAX77693_MUIC_IRQ_INT2_DXOVP:
	case MAX77693_MUIC_IRQ_INT2_VBVOLT:
	case MAX77693_MUIC_IRQ_INT2_VIDRM:

		ret = max77693_muic_chg_handler(info);
		break;
	case MAX77693_MUIC_IRQ_INT3_EOC:
	case MAX77693_MUIC_IRQ_INT3_CGMBC:
	case MAX77693_MUIC_IRQ_INT3_OVP:
	case MAX77693_MUIC_IRQ_INT3_MBCCHG_ERR:
	case MAX77693_MUIC_IRQ_INT3_CHG_ENABLED:
	case MAX77693_MUIC_IRQ_INT3_BAT_DET:
		break;
	default:
		dev_err(info->dev, "muic interrupt: irq %d occurred\n",
				irq_type);
		mutex_unlock(&info->mutex);
		return;
	}

	if (ret < 0)
		dev_err(info->dev, "failed to handle MUIC interrupt\n");

	mutex_unlock(&info->mutex);
}
