__iwl_mvm_unassign_vif_chanctx(struct iwl_mvm *mvm,
					   struct ieee80211_vif *vif,
					   struct ieee80211_chanctx_conf *ctx,
					   bool switching_chanctx)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct ieee80211_vif *disabled_vif = NULL;

	lockdep_assert_held(&mvm->mutex);

	iwl_mvm_remove_time_event(mvm, mvmvif, &mvmvif->time_event_data);

	switch (vif->type) {
	case NL80211_IFTYPE_ADHOC:
		goto out;
	case NL80211_IFTYPE_MONITOR:
		mvmvif->monitor_active = false;
		mvmvif->ps_disabled = false;
		break;
	case NL80211_IFTYPE_AP:

		if (!switching_chanctx || !mvmvif->ap_ibss_active)
			goto out;

		mvmvif->csa_countdown = false;


		iwl_mvm_modify_all_sta_disable_tx(mvm, mvmvif, true);


		rcu_assign_pointer(mvm->csa_tx_blocked_vif, vif);

		mvmvif->ap_ibss_active = false;
		break;
	case NL80211_IFTYPE_STATION:
		if (!switching_chanctx)
			break;

		disabled_vif = vif;

		iwl_mvm_mac_ctxt_changed(mvm, vif, true, NULL);
		break;
	default:
		break;
	}

	iwl_mvm_update_quotas(mvm, false, disabled_vif);
	iwl_mvm_binding_remove_vif(mvm, vif);

out:
	mvmvif->phy_ctxt = NULL;
	iwl_mvm_power_update_mac(mvm);
}
