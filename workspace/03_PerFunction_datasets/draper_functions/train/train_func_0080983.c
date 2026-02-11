microread_hci_ready(struct nfc_hci_dev *hdev)
{
	int r;
	u8 param[4];

	param[0] = 0x03;
	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_ISO_A,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, param, 1, NULL);
	if (r)
		return r;

	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_ISO_A_3,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, NULL, 0, NULL);
	if (r)
		return r;

	param[0] = 0x00;
	param[1] = 0x03;
	param[2] = 0x00;
	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_ISO_B,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, param, 3, NULL);
	if (r)
		return r;

	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_NFC_T1,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, NULL, 0, NULL);
	if (r)
		return r;

	param[0] = 0xFF;
	param[1] = 0xFF;
	param[2] = 0x00;
	param[3] = 0x00;
	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_NFC_T3,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, param, 4, NULL);

	return r;
}
