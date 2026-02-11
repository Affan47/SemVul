chapms2_check_success(unsigned char *msg, int len, unsigned char *private)
{
	if ((len < MS_AUTH_RESPONSE_LENGTH + 2) ||
	    strncmp((char *)msg, "S=", 2) != 0) {

		error("MS-CHAPv2 Success packet is badly formed.");
		return 0;
	}
	msg += 2;
	len -= 2;
	if (len < MS_AUTH_RESPONSE_LENGTH
	    || memcmp(msg, private, MS_AUTH_RESPONSE_LENGTH)) {

		error("MS-CHAPv2 mutual authentication failed.");
		return 0;
	}

	msg += MS_AUTH_RESPONSE_LENGTH;
	len -= MS_AUTH_RESPONSE_LENGTH;
	if ((len >= 3) && !strncmp((char *)msg, " M=", 3)) {
		msg += 3;
	} else if (len) {

		error("MS-CHAPv2 Success packet is badly formed.");
		return 0;
	}
	return 1;
}
