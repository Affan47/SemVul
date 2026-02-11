host_int_delBASession(struct host_if_drv *hif_drv, char *pBSSID, char TID)
{
	s32 result = 0;
	struct host_if_msg msg;
	struct ba_session_info *pBASessionInfo = &msg.body.session_info;

	if (!hif_drv) {
		PRINT_ER("driver is null\n");
		return -EFAULT;
	}

	memset(&msg, 0, sizeof(struct host_if_msg));

	msg.id = HOST_IF_MSG_DEL_BA_SESSION;

	memcpy(pBASessionInfo->au8Bssid, pBSSID, ETH_ALEN);
	pBASessionInfo->u8Ted = TID;
	msg.drv = hif_drv;

	result = wilc_mq_send(&hif_msg_q, &msg, sizeof(struct host_if_msg));
	if (result)
		PRINT_ER("wilc_mq_send fail\n");

	down(&hif_sema_wait_response);

	return result;
}
