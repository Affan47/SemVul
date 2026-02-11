i40evf_netpoll(struct net_device *netdev)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	int q_vectors = adapter->num_msix_vectors - NONQ_VECS;
	int i;


	if (test_bit(__I40E_DOWN, &adapter->vsi.state))
		return;

	for (i = 0; i < q_vectors; i++)
		i40evf_msix_clean_rings(0, &adapter->q_vectors[i]);
}
