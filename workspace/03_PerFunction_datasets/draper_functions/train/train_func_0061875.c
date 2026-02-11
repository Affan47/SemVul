handle_packet (SESSION * session,
		   int cmd, unsigned char *payload, unsigned short len)
{
	int error = 0;

	switch (cmd) {
	case CMD_SECRETBLK:
		error = handle_secret_block (session, payload, len);
		break;

	case CMD_PING:
		error = handle_ping (session, payload, len);
		break;

	case CMD_CHANNELDATA:
		error = handle_channel (cmd, payload, len);
		break;

	case CMD_CHANNELERR:
		error = handle_channel (cmd, payload, len);
		break;

	case CMD_AESKEY:
		error = handle_aeskey (payload, len);
		break;

    case CMD_AESKEYERR:
        error = handle_aeskeyerr (payload);
        break;

	case CMD_SHAHASH:
		break;

	case CMD_COUNTRYCODE:
		error = handle_countrycode (session, payload, len);
		break;

	case CMD_P2P_INITBLK:
		DSFYDEBUG ("Server said 0x21 (P2P initalization block)\n")
			break;

	case CMD_NOTIFY:

		break;

	case CMD_PRODINFO:

		error = handle_prodinfo (session, payload, len);
		break;

	case CMD_WELCOME:
		error = handle_welcome (session);
		break;

	case CMD_PAUSE:


		break;
	}

	return error;
}
