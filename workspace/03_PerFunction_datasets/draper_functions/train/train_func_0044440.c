sd_int_pkt_scan(struct gspca_dev *gspca_dev, u8 *data, int len)
{
	struct sd *sd = (struct sd *)gspca_dev;
	u8 state;

	if (len != 2)
		return -EINVAL;

	switch (data[0]) {
	case 0:
	case 1:
		state = data[0];
		break;
	default:
		return -EINVAL;
	}
	if (sd->button_state != state) {
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, state);
		input_sync(gspca_dev->input_dev);
		sd->button_state = state;
	}

	return 0;
}
