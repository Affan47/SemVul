igb_vlan_promisc_disable(struct igb_adapter *adapter)
{
	u32 i;


	if (!(adapter->flags & IGB_FLAG_VLAN_PROMISC))
		return;


	adapter->flags &= ~IGB_FLAG_VLAN_PROMISC;

	for (i = 0; i < E1000_VLAN_FILTER_TBL_SIZE; i += VFTA_BLOCK_SIZE)
		igb_scrub_vfta(adapter, i);
}
