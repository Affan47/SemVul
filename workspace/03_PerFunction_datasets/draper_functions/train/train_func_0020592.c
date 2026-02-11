pmic_arb_chained_irq(struct irq_desc *desc)
{
	struct spmi_pmic_arb_dev *pa = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	void __iomem *intr = pa->intr;
	int first = pa->min_apid >> 5;
	int last = pa->max_apid >> 5;
	u32 status;
	int i, id;

	chained_irq_enter(chip, desc);

	for (i = first; i <= last; ++i) {
		status = readl_relaxed(intr +
				      pa->ver_ops->owner_acc_status(pa->ee, i));
		while (status) {
			id = ffs(status) - 1;
			status &= ~(1 << id);
			periph_interrupt(pa, id + i * 32);
		}
	}

	chained_irq_exit(chip, desc);
}
