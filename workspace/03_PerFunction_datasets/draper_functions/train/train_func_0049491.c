Handle_SetMulticastFilter(struct host_if_drv *hif_drv,
				      struct set_multicast *strHostIfSetMulti)
{
	s32 result = 0;
	struct wid wid;
	u8 *pu8CurrByte;

	PRINT_D(HOSTINF_DBG, "Setup Multicast Filter\n");

	wid.id = (u16)WID_SETUP_MULTICAST_FILTER;
	wid.type = WID_BIN;
	wid.size = sizeof(struct set_multicast) + ((strHostIfSetMulti->cnt) * ETH_ALEN);
	wid.val = kmalloc(wid.size, GFP_KERNEL);
	if (!wid.val)
		goto ERRORHANDLER;

	pu8CurrByte = wid.val;
	*pu8CurrByte++ = (strHostIfSetMulti->enabled & 0xFF);
	*pu8CurrByte++ = ((strHostIfSetMulti->enabled >> 8) & 0xFF);
	*pu8CurrByte++ = ((strHostIfSetMulti->enabled >> 16) & 0xFF);
	*pu8CurrByte++ = ((strHostIfSetMulti->enabled >> 24) & 0xFF);

	*pu8CurrByte++ = (strHostIfSetMulti->cnt & 0xFF);
	*pu8CurrByte++ = ((strHostIfSetMulti->cnt >> 8) & 0xFF);
	*pu8CurrByte++ = ((strHostIfSetMulti->cnt >> 16) & 0xFF);
	*pu8CurrByte++ = ((strHostIfSetMulti->cnt >> 24) & 0xFF);

	if ((strHostIfSetMulti->cnt) > 0)
		memcpy(pu8CurrByte, gau8MulticastMacAddrList, ((strHostIfSetMulti->cnt) * ETH_ALEN));

	result = send_config_pkt(SET_CFG, &wid, 1,
				 get_id_from_handler(hif_drv));
	if (result)
		PRINT_ER("Failed to send setup multicast config packet\n");

ERRORHANDLER:
	kfree(wid.val);
}
