cmd_execute(char* command) {
	uint32_t packet;


	if (str_to_uint32(command, &packet)) {
		cecd_log("execute: '%s' [NOT IMPLEMENTED YET]\n", command);
		return;
	}

	if (target_fd != NULL) {
		fwrite(&packet, target_packet_size, 1, target_fd);
		if (target_repeat) {
			fwrite(&packet, target_packet_size, 1, target_fd);
		}
		fflush(target_fd);
		cecd_dbg("execute: sent packet 0x%08x\n", packet);
	}
}
