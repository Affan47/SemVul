dwapb_gpio_add_port(struct dwapb_gpio *gpio,
			       struct dwapb_port_property *pp,
			       unsigned int offs)
{
	struct dwapb_gpio_port *port;
	void __iomem *dat, *set, *dirout;
	int err;

	port = &gpio->ports[offs];
	port->gpio = gpio;
	port->idx = pp->idx;

#ifdef CONFIG_PM_SLEEP
	port->ctx = devm_kzalloc(gpio->dev, sizeof(*port->ctx), GFP_KERNEL);
	if (!port->ctx)
		return -ENOMEM;
#endif

	dat = gpio->regs + GPIO_EXT_PORTA + (pp->idx * GPIO_EXT_PORT_SIZE);
	set = gpio->regs + GPIO_SWPORTA_DR + (pp->idx * GPIO_SWPORT_DR_SIZE);
	dirout = gpio->regs + GPIO_SWPORTA_DDR +
		(pp->idx * GPIO_SWPORT_DDR_SIZE);

	err = bgpio_init(&port->bgc, gpio->dev, 4, dat, set, NULL, dirout,
			 NULL, false);
	if (err) {
		dev_err(gpio->dev, "failed to init gpio chip for %s\n",
			pp->name);
		return err;
	}

#ifdef CONFIG_OF_GPIO
	port->bgc.gc.of_node = pp->node;
#endif
	port->bgc.gc.ngpio = pp->ngpio;
	port->bgc.gc.base = pp->gpio_base;


	if (pp->idx == 0)
		port->bgc.gc.set_debounce = dwapb_gpio_set_debounce;

	if (pp->irq)
		dwapb_configure_irqs(gpio, port, pp);

	err = gpiochip_add(&port->bgc.gc);
	if (err)
		dev_err(gpio->dev, "failed to register gpiochip for %s\n",
			pp->name);
	else
		port->is_registered = true;

	return err;
}
