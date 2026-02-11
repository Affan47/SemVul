dln2_irq_bus_unlock(struct irq_data *irqd)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	struct dln2_gpio *dln2 = container_of(gc, struct dln2_gpio, gpio);
	int pin = irqd_to_hwirq(irqd);
	int enabled, unmasked;
	unsigned type;
	int ret;

	enabled = test_bit(pin, dln2->enabled_irqs);
	unmasked = test_bit(pin, dln2->unmasked_irqs);

	if (enabled != unmasked) {
		if (unmasked) {
			type = dln2->irq_type[pin] & DLN2_GPIO_EVENT_MASK;
			set_bit(pin, dln2->enabled_irqs);
		} else {
			type = DLN2_GPIO_EVENT_NONE;
			clear_bit(pin, dln2->enabled_irqs);
		}

		ret = dln2_gpio_set_event_cfg(dln2, pin, type, 0);
		if (ret)
			dev_err(dln2->gpio.dev, "failed to set event\n");
	}

	mutex_unlock(&dln2->irq_lock);
}
