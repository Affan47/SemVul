adsi_transmit_message_full(struct ast_channel *chan, unsigned char *msg, int msglen, int msgtype, int dowait)
{
	unsigned char *msgs[5] = { NULL, NULL, NULL, NULL, NULL };
	int msglens[5], msgtypes[5], newdatamode = (ast_channel_adsicpe(chan) & ADSI_FLAG_DATAMODE), res, x, waitforswitch = 0;
	struct ast_format writeformat;
	struct ast_format readformat;

	ast_format_copy(&writeformat, ast_channel_writeformat(chan));
	ast_format_copy(&readformat, ast_channel_readformat(chan));

	for (x = 0; x < msglen; x += (msg[x+1]+2)) {
		if (msg[x] == ADSI_SWITCH_TO_DATA) {
			ast_debug(1, "Switch to data is sent!\n");
			waitforswitch++;
			newdatamode = ADSI_FLAG_DATAMODE;
		}

		if (msg[x] == ADSI_SWITCH_TO_VOICE) {
			ast_debug(1, "Switch to voice is sent!\n");
			waitforswitch++;
			newdatamode = 0;
		}
	}
	msgs[0] = msg;

	msglens[0] = msglen;
	msgtypes[0] = msgtype;

	if (msglen > 253) {
		ast_log(LOG_WARNING, "Can't send ADSI message of %d bytes, too large\n", msglen);
		return -1;
	}

	ast_stopstream(chan);

	if (ast_set_write_format_by_id(chan, AST_FORMAT_ULAW)) {
		ast_log(LOG_WARNING, "Unable to set write format to ULAW\n");
		return -1;
	}

	if (ast_set_read_format_by_id(chan, AST_FORMAT_ULAW)) {
		ast_log(LOG_WARNING, "Unable to set read format to ULAW\n");
		if (writeformat.id) {
			if (ast_set_write_format(chan, &writeformat)) {
				ast_log(LOG_WARNING, "Unable to restore write format to %s\n", ast_getformatname(&writeformat));
			}
		}
		return -1;
	}
	res = __adsi_transmit_messages(chan, msgs, msglens, msgtypes);

	if (dowait) {
		ast_debug(1, "Wait for switch is '%d'\n", waitforswitch);
		while (waitforswitch-- && ((res = ast_waitfordigit(chan, 1000)) > 0)) {
			res = 0;
			ast_debug(1, "Waiting for 'B'...\n");
		}
	}

	if (!res) {
		ast_channel_adsicpe_set(chan, (ast_channel_adsicpe(chan) & ~ADSI_FLAG_DATAMODE) | newdatamode);
	}

	if (writeformat.id) {
		ast_set_write_format(chan, &writeformat);
	}
	if (readformat.id) {
		ast_set_read_format(chan, &readformat);
	}

	if (!res) {
		res = ast_safe_sleep(chan, 100 );
	}
	return res;
}
