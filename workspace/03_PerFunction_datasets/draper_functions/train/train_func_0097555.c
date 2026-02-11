iwl_mvm_phy_ctxt_changed(struct iwl_mvm *mvm, struct iwl_mvm_phy_ctxt *ctxt,
			     struct cfg80211_chan_def *chandef,
			     u8 chains_static, u8 chains_dynamic)
{
	lockdep_assert_held(&mvm->mutex);

	ctxt->channel = chandef->chan;
	return iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
				      chains_static, chains_dynamic,
				      FW_CTXT_ACTION_MODIFY, 0);
}
