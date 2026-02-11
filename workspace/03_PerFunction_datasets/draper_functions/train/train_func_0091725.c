rem_ref_cm_node(struct nes_cm_core *cm_core,
			   struct nes_cm_node *cm_node)
{
	unsigned long flags;
	struct nes_qp *nesqp;

	if (!cm_node)
		return -EINVAL;

	spin_lock_irqsave(&cm_node->cm_core->ht_lock, flags);
	if (atomic_dec_return(&cm_node->ref_count)) {
		spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);
		return 0;
	}
	list_del(&cm_node->list);
	atomic_dec(&cm_core->ht_node_cnt);
	spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);


	if (!cm_node->accelerated && cm_node->accept_pend) {
		BUG_ON(!cm_node->listener);
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
		BUG_ON(atomic_read(&cm_node->listener->pend_accepts_cnt) < 0);
	}
	WARN_ON(cm_node->send_entry);
	if (cm_node->recv_entry)
		handle_recv_entry(cm_node, 0);
	if (cm_node->listener) {
		mini_cm_dec_refcnt_listen(cm_core, cm_node->listener, 0);
	} else {
		if (cm_node->apbvt_set && cm_node->nesvnic) {
			nes_manage_apbvt(cm_node->nesvnic, cm_node->mapped_loc_port,
					 PCI_FUNC(cm_node->nesvnic->nesdev->pcidev->devfn),
					 NES_MANAGE_APBVT_DEL);
		}
		nes_debug(NES_DBG_NLMSG, "Delete APBVT mapped_loc_port = %04X\n",
					cm_node->mapped_loc_port);
		nes_remove_mapinfo(cm_node->loc_addr, cm_node->loc_port,
			cm_node->mapped_loc_addr, cm_node->mapped_loc_port);
	}

	atomic_dec(&cm_core->node_cnt);
	atomic_inc(&cm_nodes_destroyed);
	nesqp = cm_node->nesqp;
	if (nesqp) {
		nesqp->cm_node = NULL;
		nes_rem_ref(&nesqp->ibqp);
		cm_node->nesqp = NULL;
	}

	kfree(cm_node);
	return 0;
}
