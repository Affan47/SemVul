wil_reset(struct wil6210_priv *wil, bool load_fw)
{
	int rc;

	wil_dbg_misc(wil, "%s()\n", __func__);

	WARN_ON(!mutex_is_locked(&wil->mutex));
	WARN_ON(test_bit(wil_status_napi_en, wil->status));

	if (debug_fw) {
		static const u8 mac[ETH_ALEN] = {
			0x00, 0xde, 0xad, 0x12, 0x34, 0x56,
		};
		struct net_device *ndev = wil_to_ndev(wil);

		ether_addr_copy(ndev->perm_addr, mac);
		ether_addr_copy(ndev->dev_addr, ndev->perm_addr);
		return 0;
	}

	if (wil->hw_version == HW_VER_UNKNOWN)
		return -ENODEV;

	set_bit(wil_status_resetting, wil->status);

	cancel_work_sync(&wil->disconnect_worker);
	wil6210_disconnect(wil, NULL, WLAN_REASON_DEAUTH_LEAVING, false);
	wil_bcast_fini(wil);


	bitmap_zero(wil->status, wil_status_last);

	if (wil->scan_request) {
		wil_dbg_misc(wil, "Abort scan_request 0x%p\n",
			     wil->scan_request);
		del_timer_sync(&wil->scan_timer);
		cfg80211_scan_done(wil->scan_request, true);
		wil->scan_request = NULL;
	}

	wil_mask_irq(wil);

	wmi_event_flush(wil);

	flush_workqueue(wil->wq_service);
	flush_workqueue(wil->wmi_wq);

	wil_bl_crash_info(wil, false);
	rc = wil_target_reset(wil);
	wil_rx_fini(wil);
	if (rc) {
		wil_bl_crash_info(wil, true);
		return rc;
	}

	rc = wil_get_bl_info(wil);
	if (rc == -EAGAIN && !load_fw)
		rc = 0;
	if (rc)
		return rc;

	if (load_fw) {
		wil_info(wil, "Use firmware <%s> + board <%s>\n", WIL_FW_NAME,
			 WIL_FW2_NAME);

		wil_halt_cpu(wil);

		rc = wil_request_firmware(wil, WIL_FW_NAME);
		if (rc)
			return rc;
		rc = wil_request_firmware(wil, WIL_FW2_NAME);
		if (rc)
			return rc;


		wil_s(wil, RGF_USER_USAGE_6, 1);


		wil6210_clear_irq(wil);


		wil_s(wil, RGF_CAF_ICR + offsetof(struct RGF_ICR, ICR), 0);
		wil_w(wil, RGF_CAF_ICR + offsetof(struct RGF_ICR, IMV), ~0);

		wil_release_cpu(wil);
	}


	wil->pending_connect_cid = -1;
	wil->ap_isolate = 0;
	reinit_completion(&wil->wmi_ready);
	reinit_completion(&wil->wmi_call);

	if (load_fw) {
		wil_configure_interrupt_moderation(wil);
		wil_unmask_irq(wil);


		rc = wil_wait_for_fw_ready(wil);
		if (rc == 0)
			rc = wmi_echo(wil);
	}

	return rc;
}
