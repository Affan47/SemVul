bthci_RemoveEntryByEntryNum(struct rtw_adapter *padapter, u8 EntryNum)
{
	struct bt_30info *pBTInfo = GET_BT_INFO(padapter);
	struct bt_mgnt *pBtMgnt = &pBTInfo->BtMgnt;

	bthci_ResetEntry(padapter, EntryNum);

	if (pBtMgnt->CurrentBTConnectionCnt > 0)
		pBtMgnt->CurrentBTConnectionCnt--;

	RTPRINT(FIOCTL, IOCTL_STATE, ("[BT Flag], CurrentBTConnectionCnt = %d!!\n",
		pBtMgnt->CurrentBTConnectionCnt));

	if (pBtMgnt->CurrentBTConnectionCnt > 0) {
		pBtMgnt->BtOperationOn = true;
	} else {
		pBtMgnt->BtOperationOn = false;
		RTPRINT(FIOCTL, IOCTL_STATE, ("[BT Flag], Bt Operation OFF!!\n"));
	}

	if (!pBtMgnt->BtOperationOn) {
		del_timer_sync(&pBTInfo->BTHCIDiscardAclDataTimer);
		del_timer_sync(&pBTInfo->BTBeaconTimer);
		pBtMgnt->bStartSendSupervisionPkt = false;
	}
}
