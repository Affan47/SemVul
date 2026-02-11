bthci_CommandCompleteHeader(
	u8 *pbuf,
	u16		OGF,
	u16		OCF,
	enum hci_status	status
	)
{
	struct packet_irp_hcievent_data *PPacketIrpEvent = (struct packet_irp_hcievent_data *)pbuf;
	u8 NumHCI_Comm = 0x1;

	PPacketIrpEvent->EventCode = HCI_EVENT_COMMAND_COMPLETE;
	PPacketIrpEvent->Data[0] = NumHCI_Comm;
	PPacketIrpEvent->Data[1] = HCIOPCODELOW(OCF, OGF);
	PPacketIrpEvent->Data[2] = HCIOPCODEHIGHT(OCF, OGF);

	if (OGF == OGF_EXTENSION) {
		if (OCF == HCI_SET_RSSI_VALUE) {
			RTPRINT(FIOCTL, (IOCTL_BT_EVENT_PERIODICAL),
				("[BT event], CommandComplete, Num_HCI_Comm = 0x%x, Opcode = 0x%02x%02x, status = 0x%x, OGF = 0x%x, OCF = 0x%x\n",
				NumHCI_Comm, (HCIOPCODEHIGHT(OCF, OGF)), (HCIOPCODELOW(OCF, OGF)), status, OGF, OCF));
		} else {
			RTPRINT(FIOCTL, (IOCTL_BT_HCICMD_EXT),
				("[BT event], CommandComplete, Num_HCI_Comm = 0x%x, Opcode = 0x%02x%02x, status = 0x%x, OGF = 0x%x, OCF = 0x%x\n",
				NumHCI_Comm, (HCIOPCODEHIGHT(OCF, OGF)), (HCIOPCODELOW(OCF, OGF)), status, OGF, OCF));
		}
	} else {
		RTPRINT(FIOCTL, (IOCTL_BT_EVENT|IOCTL_BT_LOGO),
			("[BT event], CommandComplete, Num_HCI_Comm = 0x%x, Opcode = 0x%02x%02x, status = 0x%x, OGF = 0x%x, OCF = 0x%x\n",
			NumHCI_Comm, (HCIOPCODEHIGHT(OCF, OGF)), (HCIOPCODELOW(OCF, OGF)), status, OGF, OCF));
	}
	return 3;
}
