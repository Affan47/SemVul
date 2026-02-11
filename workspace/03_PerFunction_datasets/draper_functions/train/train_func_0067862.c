be_tx_compl_get(struct be_tx_obj *txo)
{
	struct be_queue_info *tx_cq = &txo->cq;
	struct be_tx_compl_info *txcp = &txo->txcp;
	struct be_eth_tx_compl *compl = queue_tail_node(tx_cq);

	if (compl->dw[offsetof(struct amap_eth_tx_compl, valid) / 32] == 0)
		return NULL;


	rmb();
	be_dws_le_to_cpu(compl, sizeof(*compl));

	txcp->status = GET_TX_COMPL_BITS(status, compl);
	txcp->end_index = GET_TX_COMPL_BITS(wrb_index, compl);

	compl->dw[offsetof(struct amap_eth_tx_compl, valid) / 32] = 0;
	queue_tail_inc(tx_cq);
	return txcp;
}
