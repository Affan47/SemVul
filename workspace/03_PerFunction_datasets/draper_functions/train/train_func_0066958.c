ath10k_tx_h_add_p2p_noa_ie(struct ath10k *ar,
				       struct ieee80211_vif *vif,
				       struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ath10k_vif *arvif = ath10k_vif_to_arvif(vif);


	if (arvif->vdev_type != WMI_VDEV_TYPE_AP ||
	    arvif->vdev_subtype != WMI_VDEV_SUBTYPE_P2P_GO)
		return;

	if (unlikely(ieee80211_is_probe_resp(hdr->frame_control))) {
		spin_lock_bh(&ar->data_lock);
		if (arvif->u.ap.noa_data)
			if (!pskb_expand_head(skb, 0, arvif->u.ap.noa_len,
					      GFP_ATOMIC))
				memcpy(skb_put(skb, arvif->u.ap.noa_len),
				       arvif->u.ap.noa_data,
				       arvif->u.ap.noa_len);
		spin_unlock_bh(&ar->data_lock);
	}
}
