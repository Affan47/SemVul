adsi_status(struct ast_channel *chan, struct vm_state *vms)
{
	unsigned char buf[256] = "";
	char buf1[256] = "", buf2[256] = "";
	int bytes = 0;
	unsigned char keys[8];
	int x;

	char *newm = (vms->newmessages == 1) ? "message" : "messages";
	char *oldm = (vms->oldmessages == 1) ? "message" : "messages";
	if (!ast_adsi_available(chan))
		return;
	if (vms->newmessages) {
		snprintf(buf1, sizeof(buf1), "You have %d new", vms->newmessages);
		if (vms->oldmessages) {
			strncat(buf1, " and", sizeof(buf1) - strlen(buf1) - 1);
			snprintf(buf2, sizeof(buf2), "%d old %s.", vms->oldmessages, oldm);
		} else {
			snprintf(buf2, sizeof(buf2), "%s.", newm);
		}
	} else if (vms->oldmessages) {
		snprintf(buf1, sizeof(buf1), "You have %d old", vms->oldmessages);
		snprintf(buf2, sizeof(buf2), "%s.", oldm);
	} else {
		strcpy(buf1, "You have no messages.");
		buf2[0] = ' ';
		buf2[1] = '\0';
	}
	bytes += ast_adsi_display(buf + bytes, ADSI_COMM_PAGE, 1, ADSI_JUST_LEFT, 0, buf1, "");
	bytes += ast_adsi_display(buf + bytes, ADSI_COMM_PAGE, 2, ADSI_JUST_LEFT, 0, buf2, "");
	bytes += ast_adsi_set_line(buf + bytes, ADSI_COMM_PAGE, 1);

	for (x = 0; x < 6; x++)
		keys[x] = ADSI_KEY_SKT | (ADSI_KEY_APPS + x);
	keys[6] = 0;
	keys[7] = 0;


	if (vms->lastmsg < 0)
		keys[0] = 1;
	bytes += ast_adsi_set_keys(buf + bytes, keys);

	bytes += ast_adsi_voice_mode(buf + bytes, 0);

	ast_adsi_transmit_message(chan, buf, bytes, ADSI_MSG_DISPLAY);
}
