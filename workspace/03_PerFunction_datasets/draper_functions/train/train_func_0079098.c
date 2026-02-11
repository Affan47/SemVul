ixgbe_set_vf_macvlan(struct ixgbe_adapter *adapter,
				int vf, int index, unsigned char *mac_addr)
{
	struct list_head *pos;
	struct vf_macvlans *entry;

	if (index <= 1) {
		list_for_each(pos, &adapter->vf_mvs.l) {
			entry = list_entry(pos, struct vf_macvlans, l);
			if (entry->vf == vf) {
				entry->vf = -1;
				entry->free = true;
				entry->is_macvlan = false;
				ixgbe_del_mac_filter(adapter,
						     entry->vf_macvlan, vf);
			}
		}
	}


	if (!index)
		return 0;

	entry = NULL;

	list_for_each(pos, &adapter->vf_mvs.l) {
		entry = list_entry(pos, struct vf_macvlans, l);
		if (entry->free)
			break;
	}


	if (!entry || !entry->free)
		return -ENOSPC;

	entry->free = false;
	entry->is_macvlan = true;
	entry->vf = vf;
	memcpy(entry->vf_macvlan, mac_addr, ETH_ALEN);

	ixgbe_add_mac_filter(adapter, mac_addr, vf);

	return 0;
}
