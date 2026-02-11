plantronics_device_type(struct hid_device *hdev)
{
	unsigned i, col_page;
	unsigned long plt_type = hdev->product;


	if (plt_type >= PLT_BT300_MIN && plt_type <= PLT_BT300_MAX)
		goto exit;


	for (i = 0; i < hdev->maxcollection; i++) {
		col_page = hdev->collection[i].usage & HID_USAGE_PAGE;
		if (col_page == PLT_HID_2_0_PAGE) {
			plt_type = hdev->collection[i].usage;
			break;
		}
		if (col_page == PLT_HID_1_0_PAGE)
			plt_type = hdev->collection[i].usage;
	}

exit:
	hid_dbg(hdev, "plt_type decoded as: %08lx\n", plt_type);
	return plt_type;
}
