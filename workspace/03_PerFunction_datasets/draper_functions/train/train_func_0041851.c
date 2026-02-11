rc5t583_gpio_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct rc5t583_gpio *rc5t583_gpio = to_rc5t583_gpio(gc);

	if (offset < RC5T583_MAX_GPIO)
		return rc5t583_gpio->rc5t583->irq_base +
				RC5T583_IRQ_GPIO0 + offset;
	return -EINVAL;
}
