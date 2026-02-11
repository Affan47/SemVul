cond_unmask_irq(struct irq_desc *desc)
{


	if (!irqd_irq_disabled(&desc->irq_data) &&
	    irqd_irq_masked(&desc->irq_data) && !desc->threads_oneshot)
		unmask_irq(desc);
}
