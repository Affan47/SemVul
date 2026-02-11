Handle_AddBeacon(struct host_if_drv *hif_drv,
			     struct beacon_attr *pstrSetBeaconParam)
{
	s32 result = 0;
	struct wid wid;
	u8 *pu8CurrByte;

	PRINT_D(HOSTINF_DBG, "Adding BEACON\n");

	wid.id = (u16)WID_ADD_BEACON;
	wid.type = WID_BIN;
	wid.size = pstrSetBeaconParam->head_len + pstrSetBeaconParam->tail_len + 16;
	wid.val = kmalloc(wid.size, GFP_KERNEL);
	if (!wid.val)
		goto ERRORHANDLER;

	pu8CurrByte = wid.val;
	*pu8CurrByte++ = (pstrSetBeaconParam->interval & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->interval >> 8) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->interval >> 16) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->interval >> 24) & 0xFF);

	*pu8CurrByte++ = (pstrSetBeaconParam->dtim_period & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->dtim_period >> 8) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->dtim_period >> 16) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->dtim_period >> 24) & 0xFF);

	*pu8CurrByte++ = (pstrSetBeaconParam->head_len & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->head_len >> 8) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->head_len >> 16) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->head_len >> 24) & 0xFF);

	memcpy(pu8CurrByte, pstrSetBeaconParam->head, pstrSetBeaconParam->head_len);
	pu8CurrByte += pstrSetBeaconParam->head_len;

	*pu8CurrByte++ = (pstrSetBeaconParam->tail_len & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->tail_len >> 8) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->tail_len >> 16) & 0xFF);
	*pu8CurrByte++ = ((pstrSetBeaconParam->tail_len >> 24) & 0xFF);

	if (pstrSetBeaconParam->tail > 0)
		memcpy(pu8CurrByte, pstrSetBeaconParam->tail, pstrSetBeaconParam->tail_len);
	pu8CurrByte += pstrSetBeaconParam->tail_len;

	result = send_config_pkt(SET_CFG, &wid, 1,
				 get_id_from_handler(hif_drv));
	if (result)
		PRINT_ER("Failed to send add beacon config packet\n");

ERRORHANDLER:
	kfree(wid.val);
	kfree(pstrSetBeaconParam->head);
	kfree(pstrSetBeaconParam->tail);
}
