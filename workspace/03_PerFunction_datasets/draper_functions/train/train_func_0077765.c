fcoe_percpu_clean(struct fc_lport *lport)
{
	struct fcoe_percpu_s *pp;
	struct sk_buff *skb;
	unsigned int cpu;

	for_each_possible_cpu(cpu) {
		pp = &per_cpu(fcoe_percpu, cpu);

		if (!pp->thread || !cpu_online(cpu))
			continue;

		skb = dev_alloc_skb(0);
		if (!skb)
			continue;

		skb->destructor = fcoe_percpu_flush_done;

		spin_lock_bh(&pp->fcoe_rx_list.lock);
		__skb_queue_tail(&pp->fcoe_rx_list, skb);
		if (pp->fcoe_rx_list.qlen == 1)
			wake_up_process(pp->thread);
		spin_unlock_bh(&pp->fcoe_rx_list.lock);

		wait_for_completion(&fcoe_flush_completion);
	}
}
