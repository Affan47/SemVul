be_async_link_state_process(struct be_adapter *adapter,
					struct be_mcc_compl *compl)
{
	struct be_async_event_link_state *evt =
			(struct be_async_event_link_state *)compl;


	adapter->phy.link_speed = -1;


	if (!BEx_chip(adapter) &&
	    !(evt->port_link_status & LOGICAL_LINK_STATUS_MASK))
		return;


	if (adapter->flags & BE_FLAGS_LINK_STATUS_INIT)
		be_link_status_update(adapter,
				      evt->port_link_status & LINK_STATUS_MASK);
}
