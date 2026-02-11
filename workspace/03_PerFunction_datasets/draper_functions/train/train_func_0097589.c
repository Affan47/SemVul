ti_bandgap_tshut_init(struct ti_bandgap *bgp,
				 struct platform_device *pdev)
{
	int gpio_nr = bgp->tshut_gpio;
	int status;


	status = gpio_request(gpio_nr, "tshut");
	if (status < 0) {
		dev_err(bgp->dev, "Could not request for TSHUT GPIO:%i\n", 86);
		return status;
	}
	status = gpio_direction_input(gpio_nr);
	if (status) {
		dev_err(bgp->dev, "Cannot set input TSHUT GPIO %d\n", gpio_nr);
		return status;
	}

	status = request_irq(gpio_to_irq(gpio_nr), ti_bandgap_tshut_irq_handler,
			     IRQF_TRIGGER_RISING, "tshut", NULL);
	if (status) {
		gpio_free(gpio_nr);
		dev_err(bgp->dev, "request irq failed for TSHUT");
	}

	return 0;
}
