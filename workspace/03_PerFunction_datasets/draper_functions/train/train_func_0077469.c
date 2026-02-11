make_netconsole_target(struct config_group *group,
						  const char *name)
{
	unsigned long flags;
	struct netconsole_target *nt;


	nt = kzalloc(sizeof(*nt), GFP_KERNEL);
	if (!nt)
		return ERR_PTR(-ENOMEM);

	nt->np.name = "netconsole";
	strlcpy(nt->np.dev_name, "eth0", IFNAMSIZ);
	nt->np.local_port = 6665;
	nt->np.remote_port = 6666;
	eth_broadcast_addr(nt->np.remote_mac);


	config_item_init_type_name(&nt->item, name, &netconsole_target_type);


	spin_lock_irqsave(&target_list_lock, flags);
	list_add(&nt->list, &target_list);
	spin_unlock_irqrestore(&target_list_lock, flags);

	return &nt->item;
}
