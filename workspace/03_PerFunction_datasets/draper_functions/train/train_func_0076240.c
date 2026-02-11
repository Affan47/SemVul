logi_dj_raw_event(struct hid_device *hdev,
			     struct hid_report *report, u8 *data,
			     int size)
{
	dbg_hid("%s, size:%d\n", __func__, size);

	switch (data[0]) {
	case REPORT_ID_DJ_SHORT:
		if (size != DJREPORT_SHORT_LENGTH) {
			dev_err(&hdev->dev, "DJ report of bad size (%d)", size);
			return false;
		}
		return logi_dj_dj_event(hdev, report, data, size);
	case REPORT_ID_HIDPP_SHORT:
		if (size != HIDPP_REPORT_SHORT_LENGTH) {
			dev_err(&hdev->dev,
				"Short HID++ report of bad size (%d)", size);
			return false;
		}
		return logi_dj_hidpp_event(hdev, report, data, size);
	case REPORT_ID_HIDPP_LONG:
		if (size != HIDPP_REPORT_LONG_LENGTH) {
			dev_err(&hdev->dev,
				"Long HID++ report of bad size (%d)", size);
			return false;
		}
		return logi_dj_hidpp_event(hdev, report, data, size);
	}

	return false;
}
