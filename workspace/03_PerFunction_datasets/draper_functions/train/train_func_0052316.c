bthci_StateStarting(struct rtw_adapter *padapter,
		    enum hci_state_with_cmd StateCmd, u8 EntryNum)
{
	struct bt_30info *pBTInfo = GET_BT_INFO(padapter);
	struct bt_mgnt *pBtMgnt = &pBTInfo->BtMgnt;

	RTPRINT(FIOCTL, IOCTL_STATE, ("[BT state], [Starting], "));
	switch (StateCmd) {
	case STATE_CMD_CONNECT_ACCEPT_TIMEOUT:
		RTPRINT(FIOCTL, IOCTL_STATE, ("STATE_CMD_CONNECT_ACCEPT_TIMEOUT\n"));
		pBTInfo->BtAsocEntry[EntryNum].PhysLinkCompleteStatus = HCI_STATUS_CONNECT_ACCEPT_TIMEOUT;
		pBtMgnt->bNeedNotifyAMPNoCap = true;
		BTHCI_DisconnectPeer(padapter, EntryNum);
		break;
	case STATE_CMD_DISCONNECT_PHY_LINK:
		RTPRINT(FIOCTL, IOCTL_STATE, ("STATE_CMD_DISCONNECT_PHY_LINK\n"));

		bthci_EventDisconnectPhyLinkComplete(padapter,
		HCI_STATUS_SUCCESS,
		pBTInfo->BtAsocEntry[EntryNum].PhyLinkDisconnectReason,
		EntryNum);

		del_timer_sync(&pBTInfo->BTHCIJoinTimeoutTimer);

		pBTInfo->BtAsocEntry[EntryNum].PhysLinkCompleteStatus = HCI_STATUS_UNKNOW_CONNECT_ID;

		BTHCI_DisconnectPeer(padapter, EntryNum);
		break;
	case STATE_CMD_MAC_START_COMPLETE:
		RTPRINT(FIOCTL, IOCTL_STATE, ("STATE_CMD_MAC_START_COMPLETE\n"));
		if (pBTInfo->BtAsocEntry[EntryNum].AMPRole == AMP_BTAP_CREATOR)
			bthci_EventChannelSelected(padapter, EntryNum);
		break;
	default:
		RTPRINT(FIOCTL, IOCTL_STATE, ("State command(%d) is Wrong !!!\n", StateCmd));
		break;
	}
}
