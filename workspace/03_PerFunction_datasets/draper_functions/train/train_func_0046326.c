Handle_GetRssi(struct host_if_drv *hif_drv)
{
	s32 result = 0;
	struct wid wid;

	wid.id = (u16)WID_RSSI;
	wid.type = WID_CHAR;
	wid.val = &rssi;
	wid.size = sizeof(char);

	PRINT_D(HOSTINF_DBG, "Getting RSSI value\n");

	result = send_config_pkt(GET_CFG, &wid, 1,
				 get_id_from_handler(hif_drv));
	if (result) {
		PRINT_ER("Failed to get RSSI value\n");
		result = -EFAULT;
	}

	up(&hif_drv->hSemGetRSSI);
}
