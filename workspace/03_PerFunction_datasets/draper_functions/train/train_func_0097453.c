mbfl_filt_ident_utf8(int c, mbfl_identify_filter *filter)
{
	if (c < 0x80) {
		if (c < 0) {
			filter->flag = 1;
		} else if (filter->status) {
			filter->flag = 1;
		}
		filter->status = 0;
	} else if (c < 0xc0) {
		switch (filter->status) {
		case 0x20:
		case 0x30:
		case 0x31:
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x50:
		case 0x51:
		case 0x52:
		case 0x53:
			filter->status++;
			break;
		case 0x10:
		case 0x21:
		case 0x32:
		case 0x43:
		case 0x54:
			filter->status = 0;
			break;
		default:
			filter->flag = 1;
			filter->status = 0;
			break;
		}
	} else {
		if (filter->status) {
			filter->flag = 1;
		}
		filter->status = 0;
		if (c < 0xe0) {
			filter->status = 0x10;
		} else if (c < 0xf0) {
			filter->status = 0x20;
		} else if (c < 0xf8) {
			filter->status = 0x30;
		} else if (c < 0xfc) {
			filter->status = 0x40;
		} else if (c < 0xfe) {
			filter->status = 0x50;
		} else {
			filter->flag = 1;
		}
	}

	return c;
}
