saitek_raw_event(struct hid_device *hdev,
		struct hid_report *report, u8 *raw_data, int size)
{
	struct saitek_sc *ssc = hid_get_drvdata(hdev);

	if (ssc->quirks & SAITEK_RELEASE_MODE_RAT7 && size == 7) {

		int mode = -1;
		if (raw_data[1] & 0x01)
			mode = 0;
		else if (raw_data[1] & 0x02)
			mode = 1;
		else if (raw_data[1] & 0x04)
			mode = 2;


		raw_data[1] &= ~0x07;

		if (mode != ssc->mode) {
			hid_dbg(hdev, "entered mode %d\n", mode);
			if (ssc->mode != -1) {

				raw_data[1] |= 0x04;
			}
			ssc->mode = mode;
		}
	} else if (ssc->quirks & SAITEK_RELEASE_MODE_MMO7 && size == 8) {


		int mode = -1;
		if (raw_data[1] & 0x80)
			mode = 0;
		else if (raw_data[2] & 0x01)
			mode = 1;
		else if (raw_data[2] & 0x02)
			mode = 2;


		raw_data[1] &= ~0x80;
		raw_data[2] &= ~0x03;

		if (mode != ssc->mode) {
			hid_dbg(hdev, "entered mode %d\n", mode);
			if (ssc->mode != -1) {


				raw_data[1] |= 0x80;
			}
			ssc->mode = mode;
		}
	}

	return 0;
}
