host_int_ScanCompleteReceived(u8 *pu8Buffer, u32 u32Length)
{
	s32 result = 0;
	struct host_if_msg msg;
	int id;
	struct host_if_drv *hif_drv = NULL;

	id = ((pu8Buffer[u32Length - 4]) | (pu8Buffer[u32Length - 3] << 8) | (pu8Buffer[u32Length - 2] << 16) | (pu8Buffer[u32Length - 1] << 24));
	hif_drv = get_handler_from_id(id);

	PRINT_D(GENERIC_DBG, "Scan notification received %p\n", hif_drv);

	if (!hif_drv || hif_drv == terminated_handle)
		return;

	if (hif_drv->usr_scan_req.pfUserScanResult) {
		memset(&msg, 0, sizeof(struct host_if_msg));

		msg.id = HOST_IF_MSG_RCVD_SCAN_COMPLETE;
		msg.drv = hif_drv;

		result = wilc_mq_send(&hif_msg_q, &msg, sizeof(struct host_if_msg));
		if (result)
			PRINT_ER("Error in sending message queue scan complete parameters: Error(%d)\n", result);
	}

	return;
}
