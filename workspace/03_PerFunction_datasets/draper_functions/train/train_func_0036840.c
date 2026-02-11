qib_sdma_process_event(struct qib_pportdata *ppd,
	enum qib_sdma_events event)
{
	unsigned long flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	__qib_sdma_process_event(ppd, event);

	if (ppd->sdma_state.current_state == qib_sdma_state_s99_running)
		qib_verbs_sdma_desc_avail(ppd, qib_sdma_descq_freecnt(ppd));

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
}
