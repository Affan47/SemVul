host_int_del_station(struct host_if_drv *hif_drv, const u8 *pu8MacAddr)
{
	s32 result = 0;
	struct host_if_msg msg;
	struct del_sta *pstrDelStationMsg = &msg.body.del_sta_info;

	if (!hif_drv) {
		PRINT_ER("driver is null\n");
		return -EFAULT;
	}

	memset(&msg, 0, sizeof(struct host_if_msg));

	PRINT_D(HOSTINF_DBG, "Setting deleting station message queue params\n");

	msg.id = HOST_IF_MSG_DEL_STATION;
	msg.drv = hif_drv;

	if (!pu8MacAddr)
		eth_broadcast_addr(pstrDelStationMsg->mac_addr);
	else
		memcpy(pstrDelStationMsg->mac_addr, pu8MacAddr, ETH_ALEN);

	result = wilc_mq_send(&hif_msg_q, &msg, sizeof(struct host_if_msg));
	if (result)
		PRINT_ER("wilc_mq_send fail\n");
	return result;
}
