wilc_netdev_init(struct wilc **wilc)
{
	int i;
	perInterface_wlan_t *nic;
	struct net_device *ndev;

	sema_init(&close_exit_sync, 0);


	g_linux_wlan = kzalloc(sizeof(*g_linux_wlan), GFP_KERNEL);
	if (!g_linux_wlan)
		return -ENOMEM;

	*wilc = g_linux_wlan;

	register_inetaddr_notifier(&g_dev_notifier);

	for (i = 0; i < NUM_CONCURRENT_IFC; i++) {

		ndev = alloc_etherdev(sizeof(perInterface_wlan_t));
		if (!ndev) {
			PRINT_ER("Failed to allocate ethernet dev\n");
			return -1;
		}

		nic = netdev_priv(ndev);
		memset(nic, 0, sizeof(perInterface_wlan_t));


		if (i == 0) {
		#if defined(NM73131)
			strcpy(ndev->name, "wilc_eth%d");
		#elif defined(PLAT_CLM9722)
			strcpy(ndev->name, "eth%d");
		#else
			strcpy(ndev->name, "wlan%d");
		#endif
		} else
			strcpy(ndev->name, "p2p%d");

		nic->u8IfIdx = g_linux_wlan->vif_num;
		nic->wilc_netdev = ndev;
		nic->wilc = *wilc;
		g_linux_wlan->vif[g_linux_wlan->vif_num].ndev = ndev;
		g_linux_wlan->vif_num++;
		ndev->netdev_ops = &wilc_netdev_ops;

		{
			struct wireless_dev *wdev;

			wdev = wilc_create_wiphy(ndev);

			#ifdef WILC_SDIO

			SET_NETDEV_DEV(ndev, &local_sdio_func->dev);
			#endif

			if (wdev == NULL) {
				PRINT_ER("Can't register WILC Wiphy\n");
				return -1;
			}


			nic->wilc_netdev->ieee80211_ptr = wdev;
			nic->wilc_netdev->ml_priv = nic;
			wdev->netdev = nic->wilc_netdev;
			nic->netstats.rx_packets = 0;
			nic->netstats.tx_packets = 0;
			nic->netstats.rx_bytes = 0;
			nic->netstats.tx_bytes = 0;

		}

		if (register_netdev(ndev)) {
			PRINT_ER("Device couldn't be registered - %s\n", ndev->name);
			return -1;
		}

		nic->iftype = STATION_MODE;
		nic->mac_opened = 0;

	}

	#ifndef WILC_SDIO
	if (!linux_spi_init(&g_linux_wlan->wilc_spidev)) {
		PRINT_ER("Can't initialize SPI\n");
		return -1;
	}
	g_linux_wlan->wilc_spidev = wilc_spi_dev;
	#else
	g_linux_wlan->wilc_sdio_func = local_sdio_func;
	#endif

	return 0;
}
