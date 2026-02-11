asd_post_ascb_list(struct asd_ha_struct *asd_ha, struct asd_ascb *ascb,
		       int num)
{
	unsigned long flags;
	LIST_HEAD(list);
	int can_queue;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	can_queue = asd_ha->hw_prof.max_scbs - asd_ha->seq.pending;
	if (can_queue >= num)
		asd_ha->seq.pending += num;
	else
		can_queue = 0;

	if (!can_queue) {
		spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);
		asd_printk("%s: scb queue full\n", pci_name(asd_ha->pcidev));
		return -SAS_QUEUE_FULL;
	}

	asd_swap_head_scb(asd_ha, ascb);

	__list_add(&list, ascb->list.prev, &ascb->list);

	asd_start_scb_timers(&list);

	asd_ha->seq.scbpro += num;
	list_splice_init(&list, asd_ha->seq.pend_q.prev);
	asd_write_reg_dword(asd_ha, SCBPRO, (u32)asd_ha->seq.scbpro);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	return 0;
}
