mp_check_pin_attr(int irq, struct irq_alloc_info *info)
{
	struct mp_chip_data *data = irq_get_chip_data(irq);


	if (irq < nr_legacy_irqs() && data->count == 1) {
		if (info->ioapic_trigger != data->trigger)
			mp_register_handler(irq, info->ioapic_trigger);
		data->entry.trigger = data->trigger = info->ioapic_trigger;
		data->entry.polarity = data->polarity = info->ioapic_polarity;
	}

	return data->trigger == info->ioapic_trigger &&
	       data->polarity == info->ioapic_polarity;
}
