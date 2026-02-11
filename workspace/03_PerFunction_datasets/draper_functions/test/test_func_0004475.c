gfrm_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *data, int size)
{
	unsigned long hdev_type = (unsigned long) hid_get_drvdata(hdev);
	int ret = 0;

	if (hdev_type != GFRM100)
		return 0;

	if (size < 2 || data[0] != GFRM100_SEARCH_KEY_REPORT_ID)
		return 0;


	switch (data[1]) {
	case GFRM100_SEARCH_KEY_DOWN:
		ret = hid_report_raw_event(hdev, HID_INPUT_REPORT, search_key_dn,
					   sizeof(search_key_dn), 1);
		break;

	case GFRM100_SEARCH_KEY_AUDIO_DATA:
		break;

	case GFRM100_SEARCH_KEY_UP:
		ret = hid_report_raw_event(hdev, HID_INPUT_REPORT, search_key_up,
					   sizeof(search_key_up), 1);
		break;

	default:
		break;
	}

	return (ret < 0) ? ret : -1;
}
