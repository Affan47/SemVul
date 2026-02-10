efx_sriov_set_vf_spoofchk(struct net_device *net_dev, int vf_i,
			      bool spoofchk)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	if (efx->type->sriov_set_vf_spoofchk)
		return efx->type->sriov_set_vf_spoofchk(efx, vf_i, spoofchk);
	else
		return -EOPNOTSUPP;
}
