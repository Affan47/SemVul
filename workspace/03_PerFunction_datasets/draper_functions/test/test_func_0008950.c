sm501_gpio_remove(struct sm501_devdata *sm)
{
	struct sm501_gpio *gpio = &sm->gpio;

	if (!sm->gpio.registered)
		return;

	gpiochip_remove(&gpio->low.gpio);
	gpiochip_remove(&gpio->high.gpio);

	iounmap(gpio->regs);
	release_resource(gpio->regs_res);
	kfree(gpio->regs_res);
}
