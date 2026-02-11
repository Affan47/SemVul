prepare_at_line(struct cpssp *cpssp, char * cmd_buffer, int cmd_counter)
{
	int i;


	while(cmd_counter) {
		if ((*cmd_buffer == ASC_SPACE) || (*cmd_buffer == ASC_CR)
		 || (*cmd_buffer == ASC_LF)) {
			cmd_counter--;
			cmd_buffer++;
			continue;
		}
		break;
	}


	for (i=cmd_counter; i--; ) {
		cmd_buffer[i] = tolower(cmd_buffer[i]);
	}


	if (! cmd_counter) {
		return;
	}


	if ((2 < cmd_counter) && (cmd_buffer[0] == 'a')
	 && (cmd_buffer[1] == 't')) {

		cmd_buffer += 2;
		cmd_counter -= 2;

		extract_at_cmds(cpssp, cmd_buffer, cmd_counter);
		return;
	}

	if ((cmd_counter == 2)
	 && (cmd_buffer[0] == 'a')
	 && (cmd_buffer[1] == 't')) {

	 	modem_result(cpssp, RESULT_OK);
	} else {


		modem_result(cpssp, RESULT_ERROR);

		cmd_buffer[cmd_counter] = '\0';
		faum_log(FAUM_LOG_DEBUG, "serial-modem", "fsm",
				"got non AT-Command: %s\n.", cmd_buffer);
		return;
	}
}
