fm10k_msix_clean_rings(int __always_unused irq, void *data)
{
	struct fm10k_q_vector *q_vector = data;

	if (q_vector->rx.count || q_vector->tx.count)
		napi_schedule_irqoff(&q_vector->napi);

	return IRQ_HANDLED;
}
