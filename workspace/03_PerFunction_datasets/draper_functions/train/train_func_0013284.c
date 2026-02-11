apple_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct apple_sc *asc = hid_get_drvdata(hdev);

	if ((asc->quirks & APPLE_RDESC_JIS) && *rsize >= 60 &&
			rdesc[53] == 0x65 && rdesc[59] == 0x65) {
		hid_info(hdev,
			 "fixing up MacBook JIS keyboard report descriptor\n");
		rdesc[53] = rdesc[59] = 0xe7;
	}
	return rdesc;
}
