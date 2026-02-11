_match_intf_src(const struct intf_entry *entry, void *arg)
{
	struct intf_entry *save = (struct intf_entry *)arg;

	if (entry->intf_addr.addr_type == ADDR_TYPE_IP &&
	    entry->intf_addr.addr_ip == save->intf_addr.addr_ip) {

		if (save->intf_len < entry->intf_len)
			memcpy(save, entry, save->intf_len);
		else
			memcpy(save, entry, entry->intf_len);
		return (1);
	}
	return (0);
}
