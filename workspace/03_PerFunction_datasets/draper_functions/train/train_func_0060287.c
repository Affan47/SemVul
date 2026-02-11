ipwireless_network_create(struct ipw_hardware *hw)
{
	struct ipw_network *network =
		kzalloc(sizeof(struct ipw_network), GFP_ATOMIC);

	if (!network)
		return NULL;

	spin_lock_init(&network->lock);
	mutex_init(&network->close_lock);

	network->hardware = hw;

	INIT_WORK(&network->work_go_online, do_go_online);
	INIT_WORK(&network->work_go_offline, do_go_offline);

	ipwireless_associate_network(hw, network);

	return network;
}
