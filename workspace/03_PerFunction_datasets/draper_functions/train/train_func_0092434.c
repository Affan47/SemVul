wcn36xx_smd_switch_channel_rsp(void *buf, size_t len)
{
	struct wcn36xx_hal_switch_channel_rsp_msg *rsp;
	int ret = 0;

	ret = wcn36xx_smd_rsp_status_check(buf, len);
	if (ret)
		return ret;
	rsp = (struct wcn36xx_hal_switch_channel_rsp_msg *)buf;
	wcn36xx_dbg(WCN36XX_DBG_HAL, "channel switched to: %d, status: %d\n",
		    rsp->channel_number, rsp->status);
	return ret;
}
