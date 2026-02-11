scsiback_irq_fn(int irq, void *dev_id)
{
	struct vscsibk_info *info = dev_id;

	if (info->ring_error)
		return IRQ_HANDLED;

	while (scsiback_do_cmd_fn(info))
		cond_resched();

	return IRQ_HANDLED;
}
