GetPeriodicRSSI(unsigned long arg)
{
	struct host_if_drv *hif_drv = (struct host_if_drv *)arg;

	if (!hif_drv)	{
		PRINT_ER("Driver handler is NULL\n");
		return;
	}

	if (hif_drv->enuHostIFstate == HOST_IF_CONNECTED) {
		s32 result = 0;
		struct host_if_msg msg;

		memset(&msg, 0, sizeof(struct host_if_msg));

		msg.id = HOST_IF_MSG_GET_RSSI;
		msg.drv = hif_drv;

		result = wilc_mq_send(&hif_msg_q, &msg, sizeof(struct host_if_msg));
		if (result) {
			PRINT_ER("Failed to send get host channel param's message queue ");
			return;
		}
	}
	periodic_rssi.data = (unsigned long)hif_drv;
	mod_timer(&periodic_rssi, jiffies + msecs_to_jiffies(5000));
}
