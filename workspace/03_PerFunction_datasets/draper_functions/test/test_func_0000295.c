et131x_free_busy_send_packets(struct et131x_adapter *adapter)
{
	struct tcb *tcb;
	unsigned long flags;
	u32 freed = 0;
	struct tx_ring *tx_ring = &adapter->tx_ring;


	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

	tcb = tx_ring->send_head;

	while (tcb != NULL && freed < NUM_TCB) {
		struct tcb *next = tcb->next;

		tx_ring->send_head = next;

		if (next == NULL)
			tx_ring->send_tail = NULL;

		tx_ring->used--;

		spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

		freed++;
		free_send_packet(adapter, tcb);

		spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

		tcb = tx_ring->send_head;
	}

	WARN_ON(freed == NUM_TCB);

	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

	tx_ring->used = 0;
}
