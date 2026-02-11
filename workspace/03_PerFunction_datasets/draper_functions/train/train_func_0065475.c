slic_mcast_add_list(struct adapter *adapter, char *address)
{
	struct mcast_address *mcaddr, *mlist;


	mlist = adapter->mcastaddrs;
	while (mlist) {
		if (ether_addr_equal(mlist->address, address))
			return 0;
		mlist = mlist->next;
	}


	mcaddr = kmalloc(sizeof(struct mcast_address), GFP_ATOMIC);
	if (mcaddr == NULL)
		return 1;

	ether_addr_copy(mcaddr->address, address);

	mcaddr->next = adapter->mcastaddrs;
	adapter->mcastaddrs = mcaddr;

	return 0;
}
