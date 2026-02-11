iwl_mvm_tdls_channel_switch(struct ieee80211_hw *hw,
			    struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta, u8 oper_class,
			    struct cfg80211_chan_def *chandef,
			    struct sk_buff *tmpl_skb, u32 ch_sw_tm_ie)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_sta *mvmsta;
	unsigned int delay;
	int ret;

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_TDLS(mvm, "TDLS channel switch with %pM ch %d width %d\n",
		       sta->addr, chandef->chan->center_freq, chandef->width);


	if (mvm->tdls_cs.peer.sta_id != IWL_MVM_STATION_COUNT) {
		IWL_DEBUG_TDLS(mvm,
			       "Existing peer. Can't start switch with %pM\n",
			       sta->addr);
		ret = -EBUSY;
		goto out;
	}

	ret = iwl_mvm_tdls_config_channel_switch(mvm, vif,
						 TDLS_SEND_CHAN_SW_REQ,
						 sta->addr, sta->tdls_initiator,
						 oper_class, chandef, 0, 0, 0,
						 tmpl_skb, ch_sw_tm_ie);
	if (ret)
		goto out;


	mvm->tdls_cs.peer.skb = skb_copy(tmpl_skb, GFP_KERNEL);
	if (!mvm->tdls_cs.peer.skb) {
		ret = -ENOMEM;
		goto out;
	}

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	mvm->tdls_cs.peer.sta_id = mvmsta->sta_id;
	mvm->tdls_cs.peer.chandef = *chandef;
	mvm->tdls_cs.peer.initiator = sta->tdls_initiator;
	mvm->tdls_cs.peer.op_class = oper_class;
	mvm->tdls_cs.peer.ch_sw_tm_ie = ch_sw_tm_ie;


	delay = 2 * TU_TO_MS(vif->bss_conf.dtim_period *
			     vif->bss_conf.beacon_int);
	mod_delayed_work(system_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jiffies(delay));

out:
	mutex_unlock(&mvm->mutex);
	return ret;
}
