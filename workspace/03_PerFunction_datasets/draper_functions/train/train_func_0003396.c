be_async_grp5_qos_speed_process(struct be_adapter *adapter,
					    struct be_mcc_compl *compl)
{
	struct be_async_event_grp5_qos_link_speed *evt =
			(struct be_async_event_grp5_qos_link_speed *)compl;

	if (adapter->phy.link_speed >= 0 &&
	    evt->physical_port == adapter->port_num)
		adapter->phy.link_speed = le16_to_cpu(evt->qos_link_speed) * 10;
}
