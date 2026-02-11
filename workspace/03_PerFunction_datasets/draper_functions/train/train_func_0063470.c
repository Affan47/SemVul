bthci_CmdWriteLinkSupervisionTimeout(
	struct rtw_adapter *padapter,
	struct packet_irp_hcicmd_data *pHciCmd
	)
{
	enum hci_status	status = HCI_STATUS_SUCCESS;
	struct bt_30info *pBTinfo = GET_BT_INFO(padapter);
	u8 physicalLinkHandle, EntryNum;

	physicalLinkHandle = *((u8 *)pHciCmd->Data);

	EntryNum = bthci_GetCurrentEntryNum(padapter, physicalLinkHandle);

	if (EntryNum == 0xff) {
		RTPRINT(FIOCTL, IOCTL_BT_HCICMD, ("WriteLinkSupervisionTimeout, No such Handle in the Entry\n"));
		status = HCI_STATUS_UNKNOW_CONNECT_ID;
	} else {
		if (pBTinfo->BtAsocEntry[EntryNum].PhyLinkCmdData.BtPhyLinkhandle != physicalLinkHandle) {
			status = HCI_STATUS_UNKNOW_CONNECT_ID;
		} else {
			pBTinfo->BtAsocEntry[EntryNum].PhyLinkCmdData.LinkSuperversionTimeout = *((u16 *)(((u8 *)pHciCmd->Data)+2));
			RTPRINT(FIOCTL, IOCTL_STATE, ("BT Write LinkSuperversionTimeout[%d] = 0x%x\n",
				EntryNum, pBTinfo->BtAsocEntry[EntryNum].PhyLinkCmdData.LinkSuperversionTimeout));
		}
	}

	{
		u8 localBuf[8] = "";
		u8 *pRetPar;
		u8 len = 0;
		struct packet_irp_hcievent_data *PPacketIrpEvent;

		PPacketIrpEvent = (struct packet_irp_hcievent_data *)(&localBuf[0]);

		len += bthci_CommandCompleteHeader(&localBuf[0],
			OGF_SET_EVENT_MASK_COMMAND,
			HCI_WRITE_LINK_SUPERVISION_TIMEOUT,
			status);


		pRetPar = &PPacketIrpEvent->Data[len];
		pRetPar[0] = status;
		pRetPar[1] = pBTinfo->BtAsocEntry[EntryNum].PhyLinkCmdData.BtPhyLinkhandle;
		pRetPar[2] = 0;
		len += 3;
		PPacketIrpEvent->Length = len;

		bthci_IndicateEvent(padapter, PPacketIrpEvent, len+2);
	}

	return status;
}
