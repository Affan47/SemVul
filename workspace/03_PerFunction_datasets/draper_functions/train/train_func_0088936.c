SendPacket(string text, string in_player, int opt, int id) {
	if (shutdown)
		return 0;


	if (sound_remote->FetchSpawnPid() <= 0) {
		if (SpawnChildProcess() < 0 || globalreg->fatal_condition)
			return -1;
	}

	ipc_packet *pack =
		(ipc_packet *) malloc(sizeof(ipc_packet) +
							  sizeof(soundcontrol_ipc_frame) +
							  text.length() + 1);

	soundcontrol_ipc_frame *frame = (soundcontrol_ipc_frame *) pack->data;

	snprintf(frame->player, 256, "%s", in_player.c_str());
	snprintf(frame->msg, text.length() + 1, "%s", text.c_str());
	frame->opt = opt;
	frame->timestamp = time(0);

	pack->data_len = sizeof(soundcontrol_ipc_frame) + text.length() + 1;
	pack->ipc_cmdnum = id;
	pack->ipc_ack = 0;

	sound_remote->SendIPC(pack);

    return 1;
}
