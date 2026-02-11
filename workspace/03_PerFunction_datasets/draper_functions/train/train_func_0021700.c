htcpld_setup_chip_irq(
		struct platform_device *pdev,
		int chip_index)
{
	struct htcpld_data *htcpld;
	struct htcpld_chip *chip;
	unsigned int irq, irq_end;


	htcpld = platform_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];


	irq_end = chip->irq_start + chip->nirqs;
	for (irq = chip->irq_start; irq < irq_end; irq++) {
		irq_set_chip_and_handler(irq, &htcpld_muxed_chip,
					 handle_simple_irq);
		irq_set_chip_data(irq, chip);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	}

	return 0;
}
