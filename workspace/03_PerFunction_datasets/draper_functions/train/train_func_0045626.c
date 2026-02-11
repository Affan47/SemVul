Handle_Disconnect(struct host_if_drv *hif_drv)
{
	struct wid wid;

	s32 result = 0;
	u16 u16DummyReasonCode = 0;

	wid.id = (u16)WID_DISCONNECT;
	wid.type = WID_CHAR;
	wid.val = (s8 *)&u16DummyReasonCode;
	wid.size = sizeof(char);

	PRINT_D(HOSTINF_DBG, "Sending disconnect request\n");

	g_obtainingIP = false;
	host_int_set_power_mgmt(hif_drv, 0, 0);

	eth_zero_addr(u8ConnectedSSID);

	result = send_config_pkt(SET_CFG, &wid, 1,
				 get_id_from_handler(hif_drv));

	if (result) {
		PRINT_ER("Failed to send dissconect config packet\n");
	} else {
		tstrDisconnectNotifInfo strDisconnectNotifInfo;

		memset(&strDisconnectNotifInfo, 0, sizeof(tstrDisconnectNotifInfo));

		strDisconnectNotifInfo.u16reason = 0;
		strDisconnectNotifInfo.ie = NULL;
		strDisconnectNotifInfo.ie_len = 0;

		if (hif_drv->usr_scan_req.pfUserScanResult) {
			del_timer(&hif_drv->hScanTimer);
			hif_drv->usr_scan_req.pfUserScanResult(SCAN_EVENT_ABORTED, NULL,
							       hif_drv->usr_scan_req.u32UserScanPvoid, NULL);

			hif_drv->usr_scan_req.pfUserScanResult = NULL;
		}

		if (hif_drv->usr_conn_req.pfUserConnectResult) {
			if (hif_drv->enuHostIFstate == HOST_IF_WAITING_CONN_RESP) {
				PRINT_D(HOSTINF_DBG, "Upper layer requested termination of connection\n");
				del_timer(&hif_drv->hConnectTimer);
			}

			hif_drv->usr_conn_req.pfUserConnectResult(CONN_DISCONN_EVENT_DISCONN_NOTIF, NULL,
								  0, &strDisconnectNotifInfo, hif_drv->usr_conn_req.u32UserConnectPvoid);
		} else {
			PRINT_ER("usr_conn_req.pfUserConnectResult = NULL\n");
		}

		scan_while_connected = false;

		hif_drv->enuHostIFstate = HOST_IF_IDLE;

		eth_zero_addr(hif_drv->au8AssociatedBSSID);

		hif_drv->usr_conn_req.ssidLen = 0;
		kfree(hif_drv->usr_conn_req.pu8ssid);
		kfree(hif_drv->usr_conn_req.pu8bssid);
		hif_drv->usr_conn_req.ConnReqIEsLen = 0;
		kfree(hif_drv->usr_conn_req.pu8ConnReqIEs);

		if (join_req && join_req_drv == hif_drv) {
			kfree(join_req);
			join_req = NULL;
		}

		if (info_element && join_req_drv == hif_drv) {
			kfree(info_element);
			info_element = NULL;
		}
	}

	up(&hif_drv->hSemTestDisconnectBlock);
}
