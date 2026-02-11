ula200_ftdi_write_command(Driver *drvthis, unsigned char *data, int length, bool escape)
{
	PrivateData *p = (PrivateData *) drvthis->private_data;
	int i, err;
	int repeat_count = 0;
	int pos = 0;
	unsigned char buffer[1024];

	if (length > 512) {
		return -EINVAL;
	}


	buffer[pos++] = CH_STX;
	for (i = 0; i < length; i++) {
		if (escape) {
			if (data[i] == CH_STX) {
				buffer[pos++] = CH_ENQ;
				buffer[pos++] = CH_DC2;
			}
			else if (data[i] == CH_ETX) {
				buffer[pos++] = CH_ENQ;
				buffer[pos++] = CH_DC3;
			}
			else if (data[i] == CH_ENQ) {
				buffer[pos++] = CH_ENQ;
				buffer[pos++] = CH_NAK;
			}
			else {
				buffer[pos++] = data[i];
			}
		}
		else {
			buffer[pos++] = data[i];
		}
	}
	buffer[pos++] = CH_ETX;

	do {

		err = ftdi_write_data(&p->ftdic, buffer, pos);
		if (err < 0) {
			report(RPT_WARNING, "%s: ftdi_write_data failed", drvthis->name);
			return -1;
		}
	}
	while (!ula200_ftdi_read_response(drvthis)&&(repeat_count++ < MAX_REPEATS));

	return 0;
}
