i40e_fcoe_disable(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	struct i40e_fcoe *fcoe = &pf->fcoe;

	if (!(pf->flags & I40E_FLAG_FCOE_ENABLED)) {
		netdev_err(netdev, "device does not support FCoE\n");
		return -ENODEV;
	}
	if (vsi->type != I40E_VSI_FCOE)
		return -EBUSY;

	if (!atomic_dec_and_test(&fcoe->refcnt))
		return -EINVAL;

	netdev_info(netdev, "FCoE disabled\n");

	return 0;
}
