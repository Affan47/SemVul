nic_add_nic_iface(nic_t *nic, nic_interface_t *nic_iface)
{
	nic_interface_t *current, *prev;


	current = nic_find_nic_iface(nic, nic_iface->protocol,
				     nic_iface->vlan_id, nic_iface->iface_num,
				     nic_iface->request_type);
	if (current) {
		LOG_DEBUG(PFX "%s: nic interface for VLAN: %d, protocol: %d"
			  " already exist", nic->log_name, nic_iface->vlan_id,
			  nic_iface->protocol);
		return 0;
	}

	prev = NULL;
	current = nic->nic_iface;
	while (current != NULL) {
		if (current->protocol == nic_iface->protocol) {

			nic_iface->vlan_next = current;
			nic_iface->next = current->next;
			current->next = NULL;
			if (prev)
				prev->next = nic_iface;
			else
				nic->nic_iface = nic_iface;
			goto done;
		}
		prev = current;
		current = current->next;
	}
	nic_iface->next = nic->nic_iface;
	nic->nic_iface = nic_iface;
done:

	nic_iface->parent = nic;
	memcpy(&nic_iface->ustack.uip_ethaddr.addr, nic->mac_addr, ETH_ALEN);
	nic->num_of_nic_iface++;

	LOG_INFO(PFX "%s: Added nic interface for VLAN: %d, protocol: %d",
		 nic->log_name, nic_iface->vlan_id, nic_iface->protocol);

	return 0;
}
