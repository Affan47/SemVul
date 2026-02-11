gpio_keys_setup_key(struct platform_device *pdev,
				struct input_dev *input,
				struct gpio_button_data *bdata,
				const struct gpio_keys_button *button)
{
	const char *desc = button->desc ? button->desc : "gpio_keys";
	struct device *dev = &pdev->dev;
	irq_handler_t isr;
	unsigned long irqflags;
	int irq;
	int error;

	bdata->input = input;
	bdata->button = button;
	spin_lock_init(&bdata->lock);

	if (gpio_is_valid(button->gpio)) {

		error = devm_gpio_request_one(&pdev->dev, button->gpio,
					      GPIOF_IN, desc);
		if (error < 0) {
			dev_err(dev, "Failed to request GPIO %d, error %d\n",
				button->gpio, error);
			return error;
		}

		if (button->debounce_interval) {
			error = gpio_set_debounce(button->gpio,
					button->debounce_interval * 1000);

			if (error < 0)
				bdata->software_debounce =
						button->debounce_interval;
		}

		if (button->irq) {
			bdata->irq = button->irq;
		} else {
			irq = gpio_to_irq(button->gpio);
			if (irq < 0) {
				error = irq;
				dev_err(dev,
					"Unable to get irq number for GPIO %d, error %d\n",
					button->gpio, error);
				return error;
			}
			bdata->irq = irq;
		}

		INIT_DELAYED_WORK(&bdata->work, gpio_keys_gpio_work_func);

		isr = gpio_keys_gpio_isr;
		irqflags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;

	} else {
		if (!button->irq) {
			dev_err(dev, "No IRQ specified\n");
			return -EINVAL;
		}
		bdata->irq = button->irq;

		if (button->type && button->type != EV_KEY) {
			dev_err(dev, "Only EV_KEY allowed for IRQ buttons.\n");
			return -EINVAL;
		}

		bdata->release_delay = button->debounce_interval;
		setup_timer(&bdata->release_timer,
			    gpio_keys_irq_timer, (unsigned long)bdata);

		isr = gpio_keys_irq_isr;
		irqflags = 0;
	}

	input_set_capability(input, button->type ?: EV_KEY, button->code);


	error = devm_add_action(&pdev->dev, gpio_keys_quiesce_key, bdata);
	if (error) {
		dev_err(&pdev->dev,
			"failed to register quiesce action, error: %d\n",
			error);
		return error;
	}


	if (!button->can_disable)
		irqflags |= IRQF_SHARED;

	error = devm_request_any_context_irq(&pdev->dev, bdata->irq,
					     isr, irqflags, desc, bdata);
	if (error < 0) {
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			bdata->irq, error);
		return error;
	}

	return 0;
}
