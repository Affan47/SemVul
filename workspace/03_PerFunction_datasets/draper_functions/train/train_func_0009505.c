ath5k_add_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct ath5k_hw *ah = hw->priv;
	int ret;
	struct ath5k_vif *avf = (void *)vif->drv_priv;

	mutex_lock(&ah->lock);

	if ((vif->type == NL80211_IFTYPE_AP ||
	     vif->type == NL80211_IFTYPE_ADHOC)
	    && (ah->num_ap_vifs + ah->num_adhoc_vifs) >= ATH_BCBUF) {
		ret = -ELNRNG;
		goto end;
	}


	if (ah->num_adhoc_vifs ||
	    (ah->nvifs && vif->type == NL80211_IFTYPE_ADHOC)) {
		ATH5K_ERR(ah, "Only one single ad-hoc interface is allowed.\n");
		ret = -ELNRNG;
		goto end;
	}

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
		avf->opmode = vif->type;
		break;
	default:
		ret = -EOPNOTSUPP;
		goto end;
	}

	ah->nvifs++;
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "add interface mode %d\n", avf->opmode);


	if ((avf->opmode == NL80211_IFTYPE_AP) ||
	    (avf->opmode == NL80211_IFTYPE_ADHOC) ||
	    (avf->opmode == NL80211_IFTYPE_MESH_POINT)) {
		int slot;

		WARN_ON(list_empty(&ah->bcbuf));
		avf->bbuf = list_first_entry(&ah->bcbuf, struct ath5k_buf,
					     list);
		list_del(&avf->bbuf->list);

		avf->bslot = 0;
		for (slot = 0; slot < ATH_BCBUF; slot++) {
			if (!ah->bslot[slot]) {
				avf->bslot = slot;
				break;
			}
		}
		BUG_ON(ah->bslot[avf->bslot] != NULL);
		ah->bslot[avf->bslot] = vif;
		if (avf->opmode == NL80211_IFTYPE_AP)
			ah->num_ap_vifs++;
		else if (avf->opmode == NL80211_IFTYPE_ADHOC)
			ah->num_adhoc_vifs++;
		else if (avf->opmode == NL80211_IFTYPE_MESH_POINT)
			ah->num_mesh_vifs++;
	}


	ath5k_hw_set_lladdr(ah, vif->addr);

	ath5k_update_bssid_mask_and_opmode(ah, vif);
	ret = 0;
end:
	mutex_unlock(&ah->lock);
	return ret;
}
