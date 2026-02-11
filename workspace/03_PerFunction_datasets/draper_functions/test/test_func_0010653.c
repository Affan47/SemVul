wlcore_event_beacon_loss(struct wl1271 *wl, unsigned long roles_bitmap)
{


	struct wl12xx_vif *wlvif;
	struct ieee80211_vif *vif;
	int delay = wl->conf.conn.synch_fail_thold *
				wl->conf.conn.bss_lose_timeout;

	wl1271_info("Beacon loss detected. roles:0x%lx", roles_bitmap);

	wl12xx_for_each_wlvif_sta(wl, wlvif) {
		if (wlvif->role_id == WL12XX_INVALID_ROLE_ID ||
		    !test_bit(wlvif->role_id , &roles_bitmap))
			continue;

		vif = wl12xx_wlvif_to_vif(wlvif);


		if (wlvif->p2p) {
			ieee80211_connection_loss(vif);
			continue;
		}


		ieee80211_queue_delayed_work(wl->hw,
					     &wlvif->connection_loss_work,
					     msecs_to_jiffies(delay));

		ieee80211_cqm_beacon_loss_notify(vif, GFP_KERNEL);
	}
}
