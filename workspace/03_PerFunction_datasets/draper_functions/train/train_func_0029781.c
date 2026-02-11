iwl_pcie_txq_check_wrptrs(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i;

	for (i = 0; i < trans->cfg->base_params->num_of_queues; i++) {
		struct iwl_txq *txq = &trans_pcie->txq[i];

		spin_lock_bh(&txq->lock);
		if (trans_pcie->txq[i].need_update) {
			iwl_pcie_txq_inc_wr_ptr(trans, txq);
			trans_pcie->txq[i].need_update = false;
		}
		spin_unlock_bh(&txq->lock);
	}
}
