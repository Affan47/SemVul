Handle_FlushConnect(struct host_if_drv *hif_drv)
{
	s32 result = 0;
	struct wid strWIDList[5];
	u32 u32WidsCount = 0;
	u8 *pu8CurrByte = NULL;

	strWIDList[u32WidsCount].id = WID_INFO_ELEMENT_ASSOCIATE;
	strWIDList[u32WidsCount].type = WID_BIN_DATA;
	strWIDList[u32WidsCount].val = info_element;
	strWIDList[u32WidsCount].size = info_element_size;
	u32WidsCount++;

	strWIDList[u32WidsCount].id = (u16)WID_11I_MODE;
	strWIDList[u32WidsCount].type = WID_CHAR;
	strWIDList[u32WidsCount].size = sizeof(char);
	strWIDList[u32WidsCount].val = (s8 *)(&(mode_11i));
	u32WidsCount++;

	strWIDList[u32WidsCount].id = (u16)WID_AUTH_TYPE;
	strWIDList[u32WidsCount].type = WID_CHAR;
	strWIDList[u32WidsCount].size = sizeof(char);
	strWIDList[u32WidsCount].val = (s8 *)(&auth_type);
	u32WidsCount++;

	strWIDList[u32WidsCount].id = (u16)WID_JOIN_REQ_EXTENDED;
	strWIDList[u32WidsCount].type = WID_STR;
	strWIDList[u32WidsCount].size = join_req_size;
	strWIDList[u32WidsCount].val = (s8 *)join_req;
	pu8CurrByte = strWIDList[u32WidsCount].val;

	pu8CurrByte += FLUSHED_BYTE_POS;
	*(pu8CurrByte) = FLUSHED_JOIN_REQ;

	u32WidsCount++;

	result = send_config_pkt(SET_CFG, strWIDList, u32WidsCount,
				 get_id_from_handler(join_req_drv));
	if (result) {
		PRINT_ER("failed to send config packet\n");
		result = -EINVAL;
	}

	return result;
}
