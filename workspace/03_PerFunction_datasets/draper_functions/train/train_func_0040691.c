wl12xx_cmd_build_null_data(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct sk_buff *skb = NULL;
	int size;
	void *ptr;
	int ret = -ENOMEM;


	if (wlvif->bss_type == BSS_TYPE_IBSS) {
		size = sizeof(struct wl12xx_null_data_template);
		ptr = NULL;
	} else {
		skb = ieee80211_nullfunc_get(wl->hw,
					     wl12xx_wlvif_to_vif(wlvif));
		if (!skb)
			goto out;
		size = skb->len;
		ptr = skb->data;
	}

	ret = wl1271_cmd_template_set(wl, wlvif->role_id,
				      CMD_TEMPL_NULL_DATA, ptr, size, 0,
				      wlvif->basic_rate);

out:
	dev_kfree_skb(skb);
	if (ret)
		wl1271_warning("cmd buld null data failed %d", ret);

	return ret;

}
