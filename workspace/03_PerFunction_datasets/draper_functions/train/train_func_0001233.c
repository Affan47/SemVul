twl4030_init_irq(struct device *dev, int irq_num)
{
	static struct irq_chip	twl4030_irq_chip;
	int			status, i;
	int			irq_base, irq_end, nr_irqs;
	struct			device_node *node = dev->of_node;


	nr_irqs = TWL4030_PWR_NR_IRQS + TWL4030_CORE_NR_IRQS;

	irq_base = irq_alloc_descs(-1, 0, nr_irqs, 0);
	if (IS_ERR_VALUE(irq_base)) {
		dev_err(dev, "Fail to allocate IRQ descs\n");
		return irq_base;
	}

	irq_domain_add_legacy(node, nr_irqs, irq_base, 0,
			      &irq_domain_simple_ops, NULL);

	irq_end = irq_base + TWL4030_CORE_NR_IRQS;


	status = twl4030_init_sih_modules(twl_irq_line);
	if (status < 0)
		return status;

	twl4030_irq_base = irq_base;


	twl4030_irq_chip = dummy_irq_chip;
	twl4030_irq_chip.name = "twl4030";

	twl4030_sih_irq_chip.irq_ack = dummy_irq_chip.irq_ack;

	for (i = irq_base; i < irq_end; i++) {
		irq_set_chip_and_handler(i, &twl4030_irq_chip,
					 handle_simple_irq);
		irq_set_nested_thread(i, 1);
		activate_irq(i);
	}

	dev_info(dev, "%s (irq %d) chaining IRQs %d..%d\n", "PIH",
			irq_num, irq_base, irq_end);


	status = twl4030_sih_setup(dev, TWL4030_MODULE_INT, irq_end);
	if (status < 0) {
		dev_err(dev, "sih_setup PWR INT --> %d\n", status);
		goto fail;
	}


	status = request_threaded_irq(irq_num, NULL, handle_twl4030_pih,
				      IRQF_ONESHOT,
				      "TWL4030-PIH", NULL);
	if (status < 0) {
		dev_err(dev, "could not claim irq%d: %d\n", irq_num, status);
		goto fail_rqirq;
	}
	enable_irq_wake(irq_num);

	return irq_base;
fail_rqirq:

fail:
	for (i = irq_base; i < irq_end; i++) {
		irq_set_nested_thread(i, 0);
		irq_set_chip_and_handler(i, NULL, NULL);
	}

	return status;
}
