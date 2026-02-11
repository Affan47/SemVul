mc13xxx_common_init(struct device *dev)
{
	struct mc13xxx_platform_data *pdata = dev_get_platdata(dev);
	struct mc13xxx *mc13xxx = dev_get_drvdata(dev);
	u32 revision;
	int i, ret;

	mc13xxx->dev = dev;

	ret = mc13xxx_reg_read(mc13xxx, MC13XXX_REVISION, &revision);
	if (ret)
		return ret;

	mc13xxx->variant->print_revision(mc13xxx, revision);

	ret = mc13xxx_reg_rmw(mc13xxx, MC13XXX_PWRCTRL,
			MC13XXX_PWRCTRL_WDIRESET, MC13XXX_PWRCTRL_WDIRESET);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(mc13xxx->irqs); i++) {
		mc13xxx->irqs[i].reg_offset = i / MC13XXX_IRQ_PER_REG;
		mc13xxx->irqs[i].mask = BIT(i % MC13XXX_IRQ_PER_REG);
	}

	mc13xxx->irq_chip.name = dev_name(dev);
	mc13xxx->irq_chip.status_base = MC13XXX_IRQSTAT0;
	mc13xxx->irq_chip.mask_base = MC13XXX_IRQMASK0;
	mc13xxx->irq_chip.ack_base = MC13XXX_IRQSTAT0;
	mc13xxx->irq_chip.irq_reg_stride = MC13XXX_IRQSTAT1 - MC13XXX_IRQSTAT0;
	mc13xxx->irq_chip.init_ack_masked = true;
	mc13xxx->irq_chip.use_ack = true;
	mc13xxx->irq_chip.num_regs = MC13XXX_IRQ_REG_CNT;
	mc13xxx->irq_chip.irqs = mc13xxx->irqs;
	mc13xxx->irq_chip.num_irqs = ARRAY_SIZE(mc13xxx->irqs);

	ret = regmap_add_irq_chip(mc13xxx->regmap, mc13xxx->irq, IRQF_ONESHOT,
				  0, &mc13xxx->irq_chip, &mc13xxx->irq_data);
	if (ret)
		return ret;

	mutex_init(&mc13xxx->lock);

	if (mc13xxx_probe_flags_dt(mc13xxx) < 0 && pdata)
		mc13xxx->flags = pdata->flags;

	if (pdata) {
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-regulator",
			&pdata->regulators, sizeof(pdata->regulators));
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-led",
				pdata->leds, sizeof(*pdata->leds));
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-pwrbutton",
				pdata->buttons, sizeof(*pdata->buttons));
		if (mc13xxx->flags & MC13XXX_USE_CODEC)
			mc13xxx_add_subdevice_pdata(mc13xxx, "%s-codec",
				pdata->codec, sizeof(*pdata->codec));
		if (mc13xxx->flags & MC13XXX_USE_TOUCHSCREEN)
			mc13xxx_add_subdevice_pdata(mc13xxx, "%s-ts",
				&pdata->touch, sizeof(pdata->touch));
	} else {
		mc13xxx_add_subdevice(mc13xxx, "%s-regulator");
		mc13xxx_add_subdevice(mc13xxx, "%s-led");
		mc13xxx_add_subdevice(mc13xxx, "%s-pwrbutton");
		if (mc13xxx->flags & MC13XXX_USE_CODEC)
			mc13xxx_add_subdevice(mc13xxx, "%s-codec");
		if (mc13xxx->flags & MC13XXX_USE_TOUCHSCREEN)
			mc13xxx_add_subdevice(mc13xxx, "%s-ts");
	}

	if (mc13xxx->flags & MC13XXX_USE_ADC)
		mc13xxx_add_subdevice(mc13xxx, "%s-adc");

	if (mc13xxx->flags & MC13XXX_USE_RTC)
		mc13xxx_add_subdevice(mc13xxx, "%s-rtc");

	return 0;
}
