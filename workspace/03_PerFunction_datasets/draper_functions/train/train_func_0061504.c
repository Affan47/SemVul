arizona_map_irq(struct arizona *arizona, int irq)
{
	int ret;

	ret = regmap_irq_get_virq(arizona->aod_irq_chip, irq);
	if (ret < 0)
		ret = regmap_irq_get_virq(arizona->irq_chip, irq);

	return ret;
}
