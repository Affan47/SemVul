huawei_read_operator(const char *cmd)
{
    int bytes, i, pos = 0, copy = 0;
    char *buf;

    buf = huawei_send_receive(cmd);
    bytes = strlen(buf);

    if (strncmp(buf, "+COPS:", 6) == 0) {


	for (i = 6; i <= bytes; i++) {
	    if (buf[i] == '\"' && copy == 0) {
		i++;
		copy = 1;
	    } else if ((buf[i] == '\"') && copy == 1)
		copy = 0;

	    if (copy == 1 && strlen(operator) < sizeof(operator) - 1) {
		operator[pos] = buf[i];
		pos++;
	    }
	}

	if (debug)
	    debug("DEBUG: Operator version string: \'%s\'", operator);
    } else
	error("%s: ERROR: Invalid or empty response: \'%s\' received for: \'%s\'", name, buf, cmd);

    return;
}
