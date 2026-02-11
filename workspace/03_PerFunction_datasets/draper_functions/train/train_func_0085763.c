efx_pci_remove(struct pci_dev *pci_dev)
{
	struct efx_nic *efx;

	efx = pci_get_drvdata(pci_dev);
	if (!efx)
		return;


	rtnl_lock();
	efx_dissociate(efx);
	dev_close(efx->net_dev);
	efx_disable_interrupts(efx);
	efx->state = STATE_UNINIT;
	rtnl_unlock();

	if (efx->type->sriov_fini)
		efx->type->sriov_fini(efx);

	efx_unregister_netdev(efx);

	efx_mtd_remove(efx);

	efx_pci_remove_main(efx);

	efx_fini_io(efx);
	netif_dbg(efx, drv, efx->net_dev, "shutdown successful\n");

	efx_fini_struct(efx);
	free_netdev(efx->net_dev);

	pci_disable_pcie_error_reporting(pci_dev);
}
