tenxpress_set_settings(struct efx_nic *efx, struct ethtool_cmd *ecmd)
{
	if (!ecmd->autoneg)
		return -EINVAL;

	return efx_mdio_set_settings(efx, ecmd);
}
