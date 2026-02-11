hci_command(uint8_t *data)
{
	hci_command_hdr *ch;
	uint8_t *ptr = data;
	uint16_t ogf, ocf;

	ch = (hci_command_hdr *) ptr;
	ptr += HCI_COMMAND_HDR_SIZE;

	ch->opcode = btohs(ch->opcode);
	ogf = cmd_opcode_ogf(ch->opcode);
	ocf = cmd_opcode_ocf(ch->opcode);

	switch (ogf) {
	case OGF_LINK_CTL:
		hci_link_control(ocf, ch->plen, ptr);
		break;

	case OGF_LINK_POLICY:
		hci_link_policy(ocf, ch->plen, ptr);
		break;

	case OGF_HOST_CTL:
		hci_host_control(ocf, ch->plen, ptr);
		break;

	case OGF_INFO_PARAM:
		hci_info_param(ocf, ch->plen, ptr);
		break;

	case OGF_STATUS_PARAM:
		hci_status_param(ocf, ch->plen, ptr);
		break;

	case OGF_LE_CTL:
		hci_le_control(ocf, ch->plen, ptr);
		break;

	default:
		command_status(ogf, ocf, 0x01);
		break;
	}
}
