i40evf_set_coalesce(struct net_device *netdev,
			       struct ethtool_coalesce *ec)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	struct i40e_hw *hw = &adapter->hw;
	struct i40e_vsi *vsi = &adapter->vsi;
	struct i40e_q_vector *q_vector;
	int i;

	if (ec->tx_max_coalesced_frames_irq || ec->rx_max_coalesced_frames_irq)
		vsi->work_limit = ec->tx_max_coalesced_frames_irq;

	if ((ec->rx_coalesce_usecs >= (I40E_MIN_ITR << 1)) &&
	    (ec->rx_coalesce_usecs <= (I40E_MAX_ITR << 1)))
		vsi->rx_itr_setting = ec->rx_coalesce_usecs;

	else
		return -EINVAL;

	if ((ec->tx_coalesce_usecs >= (I40E_MIN_ITR << 1)) &&
	    (ec->tx_coalesce_usecs <= (I40E_MAX_ITR << 1)))
		vsi->tx_itr_setting = ec->tx_coalesce_usecs;
	else if (ec->use_adaptive_tx_coalesce)
		vsi->tx_itr_setting = (I40E_ITR_DYNAMIC |
				       ITR_REG_TO_USEC(I40E_ITR_RX_DEF));
	else
		return -EINVAL;

	if (ec->use_adaptive_rx_coalesce)
		vsi->rx_itr_setting |= I40E_ITR_DYNAMIC;
	else
		vsi->rx_itr_setting &= ~I40E_ITR_DYNAMIC;

	if (ec->use_adaptive_tx_coalesce)
		vsi->tx_itr_setting |= I40E_ITR_DYNAMIC;
	else
		vsi->tx_itr_setting &= ~I40E_ITR_DYNAMIC;

	for (i = 0; i < adapter->num_msix_vectors - NONQ_VECS; i++) {
		q_vector = &adapter->q_vectors[i];
		q_vector->rx.itr = ITR_TO_REG(vsi->rx_itr_setting);
		wr32(hw, I40E_VFINT_ITRN1(0, i), q_vector->rx.itr);
		q_vector->tx.itr = ITR_TO_REG(vsi->tx_itr_setting);
		wr32(hw, I40E_VFINT_ITRN1(1, i), q_vector->tx.itr);
		i40e_flush(hw);
	}

	return 0;
}
