efx_sriov_get_vf_config(struct net_device *net_dev, int vf_i,
			    struct ifla_vf_info *ivi)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	if (efx->type->sriov_get_vf_config)
		return efx->type->sriov_get_vf_config(efx, vf_i, ivi);
	else
		return -EOPNOTSUPP;
}
