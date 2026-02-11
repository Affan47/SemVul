c2h_evt_read23a(struct rtw_adapter *adapter, u8 *buf)
{
	int ret = _FAIL;
	struct c2h_evt_hdr *c2h_evt;
	int i;
	u8 trigger;

	if (buf == NULL)
		goto exit;

	trigger = rtl8723au_read8(adapter, REG_C2HEVT_CLEAR);

	if (trigger == C2H_EVT_HOST_CLOSE)
		goto exit;
	else if (trigger != C2H_EVT_FW_CLOSE)
		goto clear_evt;

	c2h_evt = (struct c2h_evt_hdr *)buf;

	memset(c2h_evt, 0, 16);

	*buf = rtl8723au_read8(adapter, REG_C2HEVT_MSG_NORMAL);
	*(buf + 1) = rtl8723au_read8(adapter, REG_C2HEVT_MSG_NORMAL + 1);

	RT_PRINT_DATA(_module_hal_init_c_, _drv_info_, "c2h_evt_read23a(): ",
		      &c2h_evt, sizeof(c2h_evt));

	if (0) {
		DBG_8723A("%s id:%u, len:%u, seq:%u, trigger:0x%02x\n",
			  __func__, c2h_evt->id, c2h_evt->plen, c2h_evt->seq,
			  trigger);
	}


	for (i = 0; i < c2h_evt->plen; i++)
		c2h_evt->payload[i] = rtl8723au_read8(adapter,
						REG_C2HEVT_MSG_NORMAL +
						sizeof(*c2h_evt) + i);

	RT_PRINT_DATA(_module_hal_init_c_, _drv_info_,
		      "c2h_evt_read23a(): Command Content:\n", c2h_evt->payload,
		      c2h_evt->plen);

	ret = _SUCCESS;

clear_evt:


	c2h_evt_clear23a(adapter);
exit:
	return ret;
}
