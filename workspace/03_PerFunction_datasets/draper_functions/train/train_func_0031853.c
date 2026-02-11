mbfl_filt_conv_wchar_euccn(int c, mbfl_convert_filter *filter)
{
	int c1, c2, s;

	s = 0;
	if (c >= ucs_a1_cp936_table_min && c < ucs_a1_cp936_table_max) {
		s = ucs_a1_cp936_table[c - ucs_a1_cp936_table_min];
	} else if (c >= ucs_a2_cp936_table_min && c < ucs_a2_cp936_table_max) {
		s = ucs_a2_cp936_table[c - ucs_a2_cp936_table_min];
	} else if (c >= ucs_a3_cp936_table_min && c < ucs_a3_cp936_table_max) {
		s = ucs_a3_cp936_table[c - ucs_a3_cp936_table_min];
	} else if (c >= ucs_i_cp936_table_min && c < ucs_i_cp936_table_max) {
		s = ucs_i_cp936_table[c - ucs_i_cp936_table_min];
	} else if (c >= ucs_hff_cp936_table_min && c < ucs_hff_cp936_table_max) {
		s = ucs_hff_cp936_table[c - ucs_hff_cp936_table_min];
	}
	c1 = (s >> 8) & 0xff;
	c2 = s & 0xff;

	if (c1 < 0xa1 || c2 < 0xa1) {
		s = c;
	}

	if (s <= 0) {
		c1 = c & ~MBFL_WCSPLANE_MASK;
		if (c1 == MBFL_WCSPLANE_GB2312) {
			s = c & MBFL_WCSPLANE_MASK;
		}
		if (c == 0) {
			s = 0;
		} else if (s <= 0) {
			s = -1;
		}
	}
	if (s >= 0) {
		if (s < 0x80) {
			CK((*filter->output_function)(s, filter->data));
		} else {
			CK((*filter->output_function)((s >> 8) & 0xff, filter->data));
			CK((*filter->output_function)(s & 0xff, filter->data));
		}
	} else {
		if (filter->illegal_mode != MBFL_OUTPUTFILTER_ILLEGAL_MODE_NONE) {
			CK(mbfl_filt_conv_illegal_output(c, filter));
		}
	}

	return c;
}
