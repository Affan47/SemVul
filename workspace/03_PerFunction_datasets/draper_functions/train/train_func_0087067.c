wacom_intuos_general(struct wacom_wac *wacom)
{
	struct wacom_features *features = &wacom->features;
	unsigned char *data = wacom->data;
	struct input_dev *input = wacom->pen_input;
	unsigned int t;


	if ((data[1] & 0xb8) == 0xa0) {
		t = (data[6] << 2) | ((data[7] >> 6) & 3);
		if (features->pressure_max == 2047) {
			t = (t << 1) | (data[1] & 1);
		}
		input_report_abs(input, ABS_PRESSURE, t);
		if (features->type != INTUOSHT2) {
		    input_report_abs(input, ABS_TILT_X,
				 (((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		    input_report_abs(input, ABS_TILT_Y, (data[8] & 0x7f) - 64);
		}
		input_report_key(input, BTN_STYLUS, data[1] & 2);
		input_report_key(input, BTN_STYLUS2, data[1] & 4);
		input_report_key(input, BTN_TOUCH, t > 10);
	}


	if ((data[1] & 0xbc) == 0xb4) {
		input_report_abs(input, ABS_WHEEL,
				(data[6] << 2) | ((data[7] >> 6) & 3));
		input_report_abs(input, ABS_TILT_X,
				 (((data[7] << 1) & 0x7e) | (data[8] >> 7)) - 64);
		input_report_abs(input, ABS_TILT_Y, (data[8] & 0x7f) - 64);
	}
}
