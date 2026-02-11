sddr55_get_capacity(struct us_data *us) {

	unsigned char uninitialized_var(manufacturerID);
	unsigned char uninitialized_var(deviceID);
	int result;
	struct sddr55_card_info *info = (struct sddr55_card_info *)us->extra;

	usb_stor_dbg(us, "Reading capacity...\n");

	result = sddr55_read_deviceID(us,
		&manufacturerID,
		&deviceID);

	usb_stor_dbg(us, "Result of read_deviceID is %d\n", result);

	if (result != USB_STOR_XFER_GOOD)
		return 0;

	usb_stor_dbg(us, "Device ID = %02X\n", deviceID);
	usb_stor_dbg(us, "Manuf  ID = %02X\n", manufacturerID);

	info->pageshift = 9;
	info->smallpageshift = 0;
	info->blocksize = 16;
	info->blockshift = 4;
	info->blockmask = 15;

	switch (deviceID) {

	case 0x6e:
	case 0xe8:
	case 0xec:
		info->pageshift = 8;
		info->smallpageshift = 1;
		return 0x00100000;

	case 0xea:
	case 0x64:
		info->pageshift = 8;
		info->smallpageshift = 1;
	case 0x5d:
		return 0x00200000;

	case 0xe3:
	case 0xe5:
	case 0x6b:
	case 0xd5:
		return 0x00400000;

	case 0xe6:
	case 0xd6:
		return 0x00800000;

	case 0x73:
		info->blocksize = 32;
		info->blockshift = 5;
		info->blockmask = 31;
		return 0x01000000;

	case 0x75:
		info->blocksize = 32;
		info->blockshift = 5;
		info->blockmask = 31;
		return 0x02000000;

	case 0x76:
		info->blocksize = 32;
		info->blockshift = 5;
		info->blockmask = 31;
		return 0x04000000;

	case 0x79:
		info->blocksize = 32;
		info->blockshift = 5;
		info->blockmask = 31;
		return 0x08000000;

	default:
		return 0;

	}
}
