mt6397_irq_init(struct mt6397_chip *mt6397)
{
	int ret;

	mutex_init(&mt6397->irqlock);


	regmap_write(mt6397->regmap, MT6397_INT_CON0, 0x0);
	regmap_write(mt6397->regmap, MT6397_INT_CON1, 0x0);

	mt6397->irq_domain = irq_domain_add_linear(mt6397->dev->of_node,
		MT6397_IRQ_NR, &mt6397_irq_domain_ops, mt6397);
	if (!mt6397->irq_domain) {
		dev_err(mt6397->dev, "could not create irq domain\n");
		return -ENOMEM;
	}

	ret = devm_request_threaded_irq(mt6397->dev, mt6397->irq, NULL,
		mt6397_irq_thread, IRQF_ONESHOT, "mt6397-pmic", mt6397);
	if (ret) {
		dev_err(mt6397->dev, "failed to register irq=%d; err: %d\n",
			mt6397->irq, ret);
		return ret;
	}

	return 0;
}
