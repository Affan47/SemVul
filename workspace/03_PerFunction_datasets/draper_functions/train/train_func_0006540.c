flags_aton(char *string, uint8_t *flags)
{
	char *p;
	u_int i;

	*flags = 0;

	if (strncmp(string, "0x", 2) == 0) {
		if (sscanf(string, "%i", &i) != 1 || i > 0xff)
			return (-1);
		*flags = i & 0xff;

		return (0);
	}
	for (p = string; *p != '\0'; p++) {
		switch (*p) {
		case 'S':
			*flags |= TH_SYN;
			break;
		case 'A':
			*flags |= TH_ACK;
			break;
		case 'F':
			*flags |= TH_FIN;
			break;
		case 'R':
			*flags |= TH_RST;
			break;
		case 'P':
			*flags |= TH_PUSH;
			break;
		case 'U':
			*flags |= TH_URG;
			break;
		default:
			return (-1);
		}
	}
	return (0);
}
