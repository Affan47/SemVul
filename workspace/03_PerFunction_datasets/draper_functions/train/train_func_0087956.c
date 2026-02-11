add_hte_node(struct nes_cm_core *cm_core, struct nes_cm_node *cm_node)
{
	unsigned long flags;
	struct list_head *hte;

	if (!cm_node || !cm_core)
		return -EINVAL;

	nes_debug(NES_DBG_CM, "Adding Node %p to Active Connection HT\n",
		  cm_node);

	spin_lock_irqsave(&cm_core->ht_lock, flags);


	hte = &cm_core->connected_nodes;
	list_add_tail(&cm_node->list, hte);
	atomic_inc(&cm_core->ht_node_cnt);

	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	return 0;
}
