efx_mdio_check_mmds(struct efx_nic *efx, unsigned int mmd_mask)
{
	int mmd = 0, probe_mmd, devs1, devs2;
	u32 devices;


	probe_mmd = (mmd_mask & MDIO_DEVS_PHYXS) ? MDIO_MMD_PHYXS :
	    __ffs(mmd_mask);


	devs1 = efx_mdio_read(efx, probe_mmd, MDIO_DEVS1);
	devs2 = efx_mdio_read(efx, probe_mmd, MDIO_DEVS2);
	if (devs1 < 0 || devs2 < 0) {
		netif_err(efx, hw, efx->net_dev,
			  "failed to read devices present\n");
		return -EIO;
	}
	devices = devs1 | (devs2 << 16);
	if ((devices & mmd_mask) != mmd_mask) {
		netif_err(efx, hw, efx->net_dev,
			  "required MMDs not present: got %x, wanted %x\n",
			  devices, mmd_mask);
		return -ENODEV;
	}
	netif_vdbg(efx, hw, efx->net_dev, "Devices present: %x\n", devices);


	while (mmd_mask) {
		if ((mmd_mask & 1) && efx_mdio_check_mmd(efx, mmd))
			return -EIO;
		mmd_mask = mmd_mask >> 1;
		mmd++;
	}

	return 0;
}
