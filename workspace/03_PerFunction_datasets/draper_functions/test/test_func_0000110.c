enic_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);

	if (netdev) {
		struct enic *enic = netdev_priv(netdev);

		cancel_work_sync(&enic->reset);
		cancel_work_sync(&enic->change_mtu_work);
		unregister_netdev(netdev);
		enic_dev_deinit(enic);
		vnic_dev_close(enic->vdev);
#ifdef CONFIG_PCI_IOV
		if (enic_sriov_enabled(enic)) {
			pci_disable_sriov(pdev);
			enic->priv_flags &= ~ENIC_SRIOV_ENABLED;
		}
#endif
		kfree(enic->pp);
		vnic_dev_unregister(enic->vdev);
		enic_iounmap(enic);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		free_netdev(netdev);
	}
}
