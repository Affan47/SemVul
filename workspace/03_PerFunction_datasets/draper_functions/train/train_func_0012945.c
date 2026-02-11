ConfigMouseBaud(const char *config)
{
	int baud;

	sscanf(config, "%d", &baud);

	switch (baud) {
	case 9600:
		mouseBaud = B9600;
		break;
	case 4800:
		mouseBaud = B4800;
		break;
	case 2400:
		mouseBaud = B2400;
		break;
	default:
		KonWarn("invalid mouse baud rate %d; set to default (1200)\r\n", baud);
	case 1200:
		mouseBaud = B1200;
		break;
	}
	return SUCCESS;
}
