wm831x_on_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_on *wm831x_on;
	int irq = wm831x_irq(wm831x, platform_get_irq(pdev, 0));
	int ret;

	wm831x_on = devm_kzalloc(&pdev->dev, sizeof(struct wm831x_on),
				 GFP_KERNEL);
	if (!wm831x_on) {
		dev_err(&pdev->dev, "Can't allocate data\n");
		return -ENOMEM;
	}

	wm831x_on->wm831x = wm831x;
	INIT_DELAYED_WORK(&wm831x_on->work, wm831x_poll_on);

	wm831x_on->dev = devm_input_allocate_device(&pdev->dev);
	if (!wm831x_on->dev) {
		dev_err(&pdev->dev, "Can't allocate input dev\n");
		ret = -ENOMEM;
		goto err;
	}

	wm831x_on->dev->evbit[0] = BIT_MASK(EV_KEY);
	wm831x_on->dev->keybit[BIT_WORD(KEY_POWER)] = BIT_MASK(KEY_POWER);
	wm831x_on->dev->name = "wm831x_on";
	wm831x_on->dev->phys = "wm831x_on/input0";
	wm831x_on->dev->dev.parent = &pdev->dev;

	ret = request_threaded_irq(irq, NULL, wm831x_on_irq,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				   "wm831x_on",
				   wm831x_on);
	if (ret < 0) {
		dev_err(&pdev->dev, "Unable to request IRQ: %d\n", ret);
		goto err_input_dev;
	}
	ret = input_register_device(wm831x_on->dev);
	if (ret) {
		dev_dbg(&pdev->dev, "Can't register input device: %d\n", ret);
		goto err_irq;
	}

	platform_set_drvdata(pdev, wm831x_on);

	return 0;

err_irq:
	free_irq(irq, wm831x_on);
err_input_dev:
err:
	return ret;
}
