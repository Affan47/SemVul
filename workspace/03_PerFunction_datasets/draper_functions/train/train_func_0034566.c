bthci_CmdExtensionVersionNotify(
	struct rtw_adapter *padapter,
	struct packet_irp_hcicmd_data *pHciCmd
	)
{
	enum hci_status	status = HCI_STATUS_SUCCESS;
	struct bt_30info *pBTInfo = GET_BT_INFO(padapter);
	struct bt_mgnt *pBtMgnt = &pBTInfo->BtMgnt;
	struct bt_dgb *pBtDbg = &pBTInfo->BtDbg;

	pBtDbg->dbgHciInfo.hciCmdCntExtensionVersionNotify++;
	RTPRINT_DATA(FIOCTL, IOCTL_BT_HCICMD_EXT, "ExtensionVersionNotify, Hex Data :\n",
			&pHciCmd->Data[0], pHciCmd->Length);

	pBtMgnt->ExtConfig.HCIExtensionVer = *((u16 *)&pHciCmd->Data[0]);
	RTPRINT(FIOCTL, IOCTL_BT_HCICMD_EXT, ("HCIExtensionVer = 0x%x\n", pBtMgnt->ExtConfig.HCIExtensionVer));

	{
		u8 localBuf[6] = "";
		u8 *pRetPar;
		u8 len = 0;
		struct packet_irp_hcievent_data *PPacketIrpEvent;

		PPacketIrpEvent = (struct packet_irp_hcievent_data *)(&localBuf[0]);

		len += bthci_CommandCompleteHeader(&localBuf[0],
			OGF_EXTENSION,
			HCI_EXTENSION_VERSION_NOTIFY,
			status);


		pRetPar = &PPacketIrpEvent->Data[len];
		pRetPar[0] = status;

		len += 1;
		PPacketIrpEvent->Length = len;

		bthci_IndicateEvent(padapter, PPacketIrpEvent, len+2);
	}

	return status;
}
