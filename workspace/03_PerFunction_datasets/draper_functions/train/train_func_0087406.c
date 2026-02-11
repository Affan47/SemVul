mbfl_filt_conv_utf16be_wchar(int c, mbfl_convert_filter *filter)
{
	int n;

	switch (filter->status) {
	case 0:
		filter->status = 1;
		n = (c & 0xff) << 8;
		filter->cache |= n;
		break;
	default:
		filter->status = 0;
		n = (filter->cache & 0xff00) | (c & 0xff);
		if (n >= 0xd800 && n < 0xdc00) {
			filter->cache = ((n & 0x3ff) << 16) + 0x400000;
		} else if (n >= 0xdc00 && n < 0xe000) {
			n &= 0x3ff;
			n |= (filter->cache & 0xfff0000) >> 6;
			filter->cache = 0;
			if (n >= MBFL_WCSPLANE_SUPMIN && n < MBFL_WCSPLANE_SUPMAX) {
				CK((*filter->output_function)(n, filter->data));
			} else {
				n &= MBFL_WCSGROUP_MASK;
				n |= MBFL_WCSGROUP_THROUGH;
				CK((*filter->output_function)(n, filter->data));
			}
		} else {
			filter->cache = 0;
			CK((*filter->output_function)(n, filter->data));
		}
		break;
	}

	return c;
}
