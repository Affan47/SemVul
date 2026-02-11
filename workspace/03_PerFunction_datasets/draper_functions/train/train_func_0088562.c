wilc_wlan_txq_remove_from_head(void)
{
	struct txq_entry_t *tqe;
	wilc_wlan_dev_t *p = &g_wlan;
	unsigned long flags;

	spin_lock_irqsave(&g_linux_wlan->txq_spinlock, flags);
	if (p->txq_head) {
		tqe = p->txq_head;
		p->txq_head = tqe->next;
		if (p->txq_head)
			p->txq_head->prev = NULL;

		p->txq_entries -= 1;


	} else {
		tqe = NULL;
	}
	spin_unlock_irqrestore(&g_linux_wlan->txq_spinlock, flags);
	return tqe;
}
