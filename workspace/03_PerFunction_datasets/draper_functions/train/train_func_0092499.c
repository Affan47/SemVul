mwifiex_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	struct sk_buff *new_skb;
	struct mwifiex_txinfo *tx_info;
	bool multicast;

	mwifiex_dbg(priv->adapter, DATA,
		    "data: %lu BSS(%d-%d): Data <= kernel\n",
		    jiffies, priv->bss_type, priv->bss_num);

	if (priv->adapter->surprise_removed) {
		kfree_skb(skb);
		priv->stats.tx_dropped++;
		return 0;
	}
	if (!skb->len || (skb->len > ETH_FRAME_LEN)) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "Tx: bad skb len %d\n", skb->len);
		kfree_skb(skb);
		priv->stats.tx_dropped++;
		return 0;
	}
	if (skb_headroom(skb) < MWIFIEX_MIN_DATA_HEADER_LEN) {
		mwifiex_dbg(priv->adapter, DATA,
			    "data: Tx: insufficient skb headroom %d\n",
			    skb_headroom(skb));

		new_skb =
			skb_realloc_headroom(skb, MWIFIEX_MIN_DATA_HEADER_LEN);
		if (unlikely(!new_skb)) {
			mwifiex_dbg(priv->adapter, ERROR,
				    "Tx: cannot alloca new_skb\n");
			kfree_skb(skb);
			priv->stats.tx_dropped++;
			return 0;
		}
		kfree_skb(skb);
		skb = new_skb;
		mwifiex_dbg(priv->adapter, INFO,
			    "info: new skb headroomd %d\n",
			    skb_headroom(skb));
	}

	tx_info = MWIFIEX_SKB_TXCB(skb);
	memset(tx_info, 0, sizeof(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->pkt_len = skb->len;

	multicast = is_multicast_ether_addr(skb->data);

	if (unlikely(!multicast && skb->sk &&
		     skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS &&
		     priv->adapter->fw_api_ver == MWIFIEX_FW_V15))
		skb = mwifiex_clone_skb_for_tx_status(priv,
						      skb,
					MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS, NULL);


	__net_timestamp(skb);

	if (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->bss_type == MWIFIEX_BSS_TYPE_STA &&
	    !ether_addr_equal_unaligned(priv->cfg_bssid, skb->data)) {
		if (priv->adapter->auto_tdls && priv->check_tdls_tx)
			mwifiex_tdls_check_tx(priv, skb);
	}

	mwifiex_queue_tx_pkt(priv, skb);

	return 0;
}
