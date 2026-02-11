tmdc_parse_packet(struct tmdc_port *port, unsigned char *data)
{
	int i, k, l;

	if (data[TMDC_BYTE_ID] != port->mode)
		return -1;

	for (i = 0; i < port->absc; i++) {
		if (port->abs[i] < 0)
			return 0;

		input_report_abs(port->dev, port->abs[i], data[tmdc_byte_a[i]]);
	}

	switch (port->mode) {

		case TMDC_MODE_M3DI:

			i = tmdc_byte_d[0];
			input_report_abs(port->dev, ABS_HAT0X, ((data[i] >> 3) & 1) - ((data[i] >> 1) & 1));
			input_report_abs(port->dev, ABS_HAT0Y, ((data[i] >> 2) & 1) - ( data[i]       & 1));
			break;

		case TMDC_MODE_AT:

			i = tmdc_byte_a[3];
			input_report_abs(port->dev, ABS_HAT0X, tmdc_hat_to_axis[(data[i] - 141) / 25].x);
			input_report_abs(port->dev, ABS_HAT0Y, tmdc_hat_to_axis[(data[i] - 141) / 25].y);
			break;

	}

	for (k = l = 0; k < 4; k++) {
		for (i = 0; i < port->btnc[k]; i++)
			input_report_key(port->dev, port->btn[i + l],
				((data[tmdc_byte_d[k]] >> (i + port->btno[k])) & 1));
		l += port->btnc[k];
	}

	input_sync(port->dev);

	return 0;
}
