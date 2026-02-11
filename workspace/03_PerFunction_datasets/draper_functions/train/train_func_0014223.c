iwl_trans_pcie_unref(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	unsigned long flags;

	if (iwlwifi_mod_params.d0i3_disable)
		return;

	spin_lock_irqsave(&trans_pcie->ref_lock, flags);
	IWL_DEBUG_RPM(trans, "ref_counter: %d\n", trans_pcie->ref_count);
	if (WARN_ON_ONCE(trans_pcie->ref_count == 0)) {
		spin_unlock_irqrestore(&trans_pcie->ref_lock, flags);
		return;
	}
	trans_pcie->ref_count--;
	spin_unlock_irqrestore(&trans_pcie->ref_lock, flags);
}
