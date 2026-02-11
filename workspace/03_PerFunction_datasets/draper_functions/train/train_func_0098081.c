mpt3sas_transport_port_remove(struct MPT3SAS_ADAPTER *ioc, u64 sas_address,
	u64 sas_address_parent)
{
	int i;
	unsigned long flags;
	struct _sas_port *mpt3sas_port, *next;
	struct _sas_node *sas_node;
	u8 found = 0;
	struct _sas_phy *mpt3sas_phy, *next_phy;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_node = _transport_sas_node_find_by_sas_address(ioc,
	    sas_address_parent);
	if (!sas_node) {
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		return;
	}
	list_for_each_entry_safe(mpt3sas_port, next, &sas_node->sas_port_list,
	    port_list) {
		if (mpt3sas_port->remote_identify.sas_address != sas_address)
			continue;
		found = 1;
		list_del(&mpt3sas_port->port_list);
		goto out;
	}
 out:
	if (!found) {
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		return;
	}

	for (i = 0; i < sas_node->num_phys; i++) {
		if (sas_node->phy[i].remote_identify.sas_address == sas_address)
			memset(&sas_node->phy[i].remote_identify, 0 ,
			    sizeof(struct sas_identify));
	}

	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	list_for_each_entry_safe(mpt3sas_phy, next_phy,
	    &mpt3sas_port->phy_list, port_siblings) {
		if ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
			dev_printk(KERN_INFO, &mpt3sas_port->port->dev,
			    "remove: sas_addr(0x%016llx), phy(%d)\n",
			    (unsigned long long)
			    mpt3sas_port->remote_identify.sas_address,
			    mpt3sas_phy->phy_id);
		mpt3sas_phy->phy_belongs_to_port = 0;
		sas_port_delete_phy(mpt3sas_port->port, mpt3sas_phy->phy);
		list_del(&mpt3sas_phy->port_siblings);
	}
	sas_port_delete(mpt3sas_port->port);
	kfree(mpt3sas_port);
}
