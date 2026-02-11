iwl_mvm_init_mcc(struct iwl_mvm *mvm)
{
	bool tlv_lar;
	bool nvm_lar;
	int retval;
	struct ieee80211_regdomain *regd;
	char mcc[3];

	if (mvm->cfg->device_family == IWL_DEVICE_FAMILY_8000) {
		tlv_lar = fw_has_capa(&mvm->fw->ucode_capa,
				      IWL_UCODE_TLV_CAPA_LAR_SUPPORT);
		nvm_lar = mvm->nvm_data->lar_enabled;
		if (tlv_lar != nvm_lar)
			IWL_INFO(mvm,
				 "Conflict between TLV & NVM regarding enabling LAR (TLV = %s NVM =%s)\n",
				 tlv_lar ? "enabled" : "disabled",
				 nvm_lar ? "enabled" : "disabled");
	}

	if (!iwl_mvm_is_lar_supported(mvm))
		return 0;


	retval = iwl_mvm_init_fw_regd(mvm);
	if (retval != -ENOENT)
		return retval;


	mvm->lar_regdom_set = false;

	regd = iwl_mvm_get_current_regdomain(mvm, NULL);
	if (IS_ERR_OR_NULL(regd))
		return -EIO;

	if (iwl_mvm_is_wifi_mcc_supported(mvm) &&
	    !iwl_mvm_get_bios_mcc(mvm, mcc)) {
		kfree(regd);
		regd = iwl_mvm_get_regdomain(mvm->hw->wiphy, mcc,
					     MCC_SOURCE_BIOS, NULL);
		if (IS_ERR_OR_NULL(regd))
			return -EIO;
	}

	retval = regulatory_set_wiphy_regd_sync_rtnl(mvm->hw->wiphy, regd);
	kfree(regd);
	return retval;
}
