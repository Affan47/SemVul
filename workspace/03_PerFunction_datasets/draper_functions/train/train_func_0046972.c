alloc_netdev ( size_t priv_len ) {
	struct net_device *netdev;
	struct net_device_configurator *configurator;
	struct net_device_configuration *config;
	unsigned int num_configs;
	size_t confs_len;
	size_t total_len;

	num_configs = table_num_entries ( NET_DEVICE_CONFIGURATORS );
	confs_len = ( num_configs * sizeof ( netdev->configs[0] ) );
	total_len = ( sizeof ( *netdev ) + confs_len + priv_len );
	netdev = zalloc ( total_len );
	if ( netdev ) {
		ref_init ( &netdev->refcnt, free_netdev );
		netdev->link_rc = -EUNKNOWN_LINK_STATUS;
		INIT_LIST_HEAD ( &netdev->tx_queue );
		INIT_LIST_HEAD ( &netdev->tx_deferred );
		INIT_LIST_HEAD ( &netdev->rx_queue );
		netdev_settings_init ( netdev );
		config = netdev->configs;
		for_each_table_entry ( configurator, NET_DEVICE_CONFIGURATORS ){
			config->netdev = netdev;
			config->configurator = configurator;
			config->rc = -EUNUSED_CONFIG;
			intf_init ( &config->job, &netdev_config_desc,
				    &netdev->refcnt );
			config++;
		}
		netdev->priv = ( ( ( void * ) netdev ) + sizeof ( *netdev ) +
				 confs_len );
	}
	return netdev;
}
