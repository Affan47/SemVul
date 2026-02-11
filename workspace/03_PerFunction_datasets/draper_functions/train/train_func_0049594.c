cmdstr_to_hash(char* cmdstr, hash_table *htab) {

	char *str, *saveptr;
	uint8_t byte, cmd_len, cmd_data[CEC_MAX_COMMAND_SIZE];

	str = strtok_r(cmdstr, ",", &saveptr);
	for (cmd_len=0; ((str!=NULL)&&(cmd_len<ARRAY_SIZE(cmd_data))); cmd_len++) {
		if (str_to_byte(str, &byte)) {
			cmd_len = 0;
			break;
		}
		cmd_data[cmd_len] = byte;
		str = strtok_r(NULL, ",", &saveptr);
	}

	return htab_hash(cmd_data, cmd_len, htab, 1);
}
