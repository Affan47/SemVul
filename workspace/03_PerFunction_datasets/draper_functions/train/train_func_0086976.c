read_ath3k_version(int pConfig, uint32_t *rom_version,
					uint32_t *build_version)
{
	uint8_t cmd[3];
	uint8_t *event;
	int err;
	int status;
	hci_command_hdr *ch = (void *)cmd;

	ch->opcode = htobs(cmd_opcode_pack(HCI_VENDOR_CMD_OGF,
						GET_VERSION_OCF));
	ch->plen = 0;

	err = send_hci_cmd_sync(pConfig, cmd, sizeof(cmd), &event);
	if (err < 0)
		return err;

	err = read_ps_event(event, GET_VERSION_OCF);
	if (err < 0)
		goto cleanup;

	status = event[10];
	status = (status << 8) | event[9];
	status = (status << 8) | event[8];
	status = (status << 8) | event[7];
	*rom_version = status;

	status = event[14];
	status = (status << 8) | event[13];
	status = (status << 8) | event[12];
	status = (status << 8) | event[11];
	*build_version = status;

cleanup:
	free(event);

	return err;
}
