iwl_pcie_rxq_restock(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rxq *rxq = &trans_pcie->rxq;
	struct iwl_rx_mem_buffer *rxb;


	if (!test_bit(STATUS_DEVICE_ENABLED, &trans->status))
		return;

	spin_lock(&rxq->lock);
	while ((iwl_rxq_space(rxq) > 0) && (rxq->free_count)) {

		rxb = rxq->queue[rxq->write];
		BUG_ON(rxb && rxb->page);


		rxb = list_first_entry(&rxq->rx_free, struct iwl_rx_mem_buffer,
				       list);
		list_del(&rxb->list);


		rxq->bd[rxq->write] = iwl_pcie_dma_addr2rbd_ptr(rxb->page_dma);
		rxq->queue[rxq->write] = rxb;
		rxq->write = (rxq->write + 1) & RX_QUEUE_MASK;
		rxq->free_count--;
	}
	spin_unlock(&rxq->lock);


	if (rxq->write_actual != (rxq->write & ~0x7)) {
		spin_lock(&rxq->lock);
		iwl_pcie_rxq_inc_wr_ptr(trans);
		spin_unlock(&rxq->lock);
	}
}
