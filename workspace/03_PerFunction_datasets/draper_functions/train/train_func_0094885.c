i40evf_configure_queues(struct i40evf_adapter *adapter)
{
	struct i40e_virtchnl_vsi_queue_config_info *vqci;
	struct i40e_virtchnl_queue_pair_info *vqpi;
	int pairs = adapter->num_active_queues;
	int i, len;

	if (adapter->current_op != I40E_VIRTCHNL_OP_UNKNOWN) {

		dev_err(&adapter->pdev->dev, "Cannot configure queues, command %d pending\n",
			adapter->current_op);
		return;
	}
	adapter->current_op = I40E_VIRTCHNL_OP_CONFIG_VSI_QUEUES;
	len = sizeof(struct i40e_virtchnl_vsi_queue_config_info) +
		       (sizeof(struct i40e_virtchnl_queue_pair_info) * pairs);
	vqci = kzalloc(len, GFP_KERNEL);
	if (!vqci)
		return;

	vqci->vsi_id = adapter->vsi_res->vsi_id;
	vqci->num_queue_pairs = pairs;
	vqpi = vqci->qpair;


	for (i = 0; i < pairs; i++) {
		vqpi->txq.vsi_id = vqci->vsi_id;
		vqpi->txq.queue_id = i;
		vqpi->txq.ring_len = adapter->tx_rings[i].count;
		vqpi->txq.dma_ring_addr = adapter->tx_rings[i].dma;
		vqpi->txq.headwb_enabled = 1;
		vqpi->txq.dma_headwb_addr = vqpi->txq.dma_ring_addr +
		    (vqpi->txq.ring_len * sizeof(struct i40e_tx_desc));

		vqpi->rxq.vsi_id = vqci->vsi_id;
		vqpi->rxq.queue_id = i;
		vqpi->rxq.ring_len = adapter->rx_rings[i].count;
		vqpi->rxq.dma_ring_addr = adapter->rx_rings[i].dma;
		vqpi->rxq.max_pkt_size = adapter->netdev->mtu
					+ ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN;
		vqpi->rxq.databuffer_size = adapter->rx_rings[i].rx_buf_len;
		if (adapter->flags & I40EVF_FLAG_RX_PS_ENABLED) {
			vqpi->rxq.splithdr_enabled = true;
			vqpi->rxq.hdr_size = I40E_RX_HDR_SIZE;
		}
		vqpi++;
	}

	adapter->aq_required &= ~I40EVF_FLAG_AQ_CONFIGURE_QUEUES;
	i40evf_send_pf_msg(adapter, I40E_VIRTCHNL_OP_CONFIG_VSI_QUEUES,
			   (u8 *)vqci, len);
	kfree(vqci);
}
