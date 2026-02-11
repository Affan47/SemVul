acpi_gpiochip_free_interrupts(struct gpio_chip *chip)
{
	struct acpi_gpio_chip *acpi_gpio;
	struct acpi_gpio_event *event, *ep;
	acpi_handle handle;
	acpi_status status;

	if (!chip->dev || !chip->to_irq)
		return;

	handle = ACPI_HANDLE(chip->dev);
	if (!handle)
		return;

	status = acpi_get_data(handle, acpi_gpio_chip_dh, (void **)&acpi_gpio);
	if (ACPI_FAILURE(status))
		return;

	list_for_each_entry_safe_reverse(event, ep, &acpi_gpio->events, node) {
		struct gpio_desc *desc;

		free_irq(event->irq, event);
		desc = event->desc;
		if (WARN_ON(IS_ERR(desc)))
			continue;
		gpiochip_unlock_as_irq(chip, event->pin);
		gpiochip_free_own_desc(desc);
		list_del(&event->node);
		kfree(event);
	}
}
