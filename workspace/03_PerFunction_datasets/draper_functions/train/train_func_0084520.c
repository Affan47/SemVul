reset_bank(struct denali_nand_info *denali)
{
	uint32_t irq_status;
	uint32_t irq_mask = INTR_STATUS__RST_COMP | INTR_STATUS__TIME_OUT;

	clear_interrupts(denali);

	iowrite32(1 << denali->flash_bank, denali->flash_reg + DEVICE_RESET);

	irq_status = wait_for_irq(denali, irq_mask);

	if (irq_status & INTR_STATUS__TIME_OUT)
		dev_err(denali->dev, "reset bank failed.\n");
}
