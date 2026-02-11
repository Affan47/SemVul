regmap_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	struct regmap *map = d->map;
	const struct regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);

	if (on) {
		if (d->wake_buf)
			d->wake_buf[irq_data->reg_offset / map->reg_stride]
				&= ~irq_data->mask;
		d->wake_count++;
	} else {
		if (d->wake_buf)
			d->wake_buf[irq_data->reg_offset / map->reg_stride]
				|= irq_data->mask;
		d->wake_count--;
	}

	return 0;
}
