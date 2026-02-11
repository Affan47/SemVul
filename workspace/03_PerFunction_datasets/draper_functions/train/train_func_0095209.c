rtl_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct rtl8169_private *tp = netdev_priv(dev);

	if ((tp->mac_version == RTL_GIGA_MAC_VER_27 ||
	     tp->mac_version == RTL_GIGA_MAC_VER_28 ||
	     tp->mac_version == RTL_GIGA_MAC_VER_31 ||
	     tp->mac_version == RTL_GIGA_MAC_VER_49 ||
	     tp->mac_version == RTL_GIGA_MAC_VER_50 ||
	     tp->mac_version == RTL_GIGA_MAC_VER_51) &&
	    r8168_check_dash(tp)) {
		rtl8168_driver_stop(tp);
	}

	netif_napi_del(&tp->napi);

	unregister_netdev(dev);

	dma_free_coherent(&tp->pci_dev->dev, sizeof(*tp->counters),
			  tp->counters, tp->counters_phys_addr);

	rtl_release_firmware(tp);

	if (pci_dev_run_wake(pdev))
		pm_runtime_get_noresume(&pdev->dev);


	rtl_rar_set(tp, dev->perm_addr);

	rtl_disable_msi(pdev, tp);
	rtl8169_release_board(pdev, dev, tp->mmio_addr);
}
