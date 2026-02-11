free_htc_packet_container(struct htc_target *target,
				      struct htc_packet *packet)
{
	struct list_head *lh;

	spin_lock_bh(&target->rx_lock);

	if (target->pipe.htc_packet_pool == NULL) {
		target->pipe.htc_packet_pool = packet;
		packet->list.next = NULL;
	} else {
		lh = (struct list_head *) target->pipe.htc_packet_pool;
		packet->list.next = lh;
		target->pipe.htc_packet_pool = packet;
	}

	spin_unlock_bh(&target->rx_lock);
}
