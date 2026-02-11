ath6kl_mgmt_powersave_ap(struct ath6kl_vif *vif,
				     u32 id,
				     u32 freq,
				     u32 wait,
				     const u8 *buf,
				     size_t len,
				     bool *more_data,
				     bool no_cck)
{
	struct ieee80211_mgmt *mgmt;
	struct ath6kl_sta *conn;
	bool is_psq_empty = false;
	struct ath6kl_mgmt_buff *mgmt_buf;
	size_t mgmt_buf_size;
	struct ath6kl *ar = vif->ar;

	mgmt = (struct ieee80211_mgmt *) buf;
	if (is_multicast_ether_addr(mgmt->da))
		return false;

	conn = ath6kl_find_sta(vif, mgmt->da);
	if (!conn)
		return false;

	if (conn->sta_flags & STA_PS_SLEEP) {
		if (!(conn->sta_flags & STA_PS_POLLED)) {

			mgmt_buf_size = len + sizeof(struct ath6kl_mgmt_buff);
			mgmt_buf = kmalloc(mgmt_buf_size, GFP_KERNEL);
			if (!mgmt_buf)
				return false;

			INIT_LIST_HEAD(&mgmt_buf->list);
			mgmt_buf->id = id;
			mgmt_buf->freq = freq;
			mgmt_buf->wait = wait;
			mgmt_buf->len = len;
			mgmt_buf->no_cck = no_cck;
			memcpy(mgmt_buf->buf, buf, len);
			spin_lock_bh(&conn->psq_lock);
			is_psq_empty = skb_queue_empty(&conn->psq) &&
					(conn->mgmt_psq_len == 0);
			list_add_tail(&mgmt_buf->list, &conn->mgmt_psq);
			conn->mgmt_psq_len++;
			spin_unlock_bh(&conn->psq_lock);


			if (is_psq_empty)
				ath6kl_wmi_set_pvb_cmd(ar->wmi, vif->fw_vif_idx,
						       conn->aid, 1);
			return true;
		}


		spin_lock_bh(&conn->psq_lock);
		if (!skb_queue_empty(&conn->psq) || (conn->mgmt_psq_len != 0))
			*more_data = true;
		spin_unlock_bh(&conn->psq_lock);
	}

	return false;
}
