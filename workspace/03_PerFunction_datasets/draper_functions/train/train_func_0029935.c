read_ps_event(uint8_t *event, uint16_t ocf)
{
	hci_event_hdr *eh;
	uint16_t opcode = htobs(cmd_opcode_pack(HCI_VENDOR_CMD_OGF, ocf));

	event++;

	eh = (void *)event;
	event += HCI_EVENT_HDR_SIZE;

	if (eh->evt == EVT_CMD_COMPLETE) {
		evt_cmd_complete *cc = (void *)event;

		event += EVT_CMD_COMPLETE_SIZE;

		if (cc->opcode == opcode && event[0] == HCI_EV_SUCCESS)
			return 0;
		else
			return -EILSEQ;
	}

	return -EILSEQ;
}
