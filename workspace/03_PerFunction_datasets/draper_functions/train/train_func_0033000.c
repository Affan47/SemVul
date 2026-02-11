show_status_line(void)
{
	int cnt = 0, cksum = 0;


	if (!have_status_msg) {
		cnt = format_edit_status();
		cksum = bufsum(status_buffer, cnt);
	}
	if (have_status_msg || ((cnt > 0 && last_status_cksum != cksum))) {
		last_status_cksum = cksum;
		go_bottom_and_clear_to_eol();
		write1(status_buffer);
		if (have_status_msg) {
			if (((int)strlen(status_buffer) - (have_status_msg - 1)) >
					(columns - 1) ) {
				have_status_msg = 0;
				Hit_Return();
			}
			have_status_msg = 0;
		}
		place_cursor(crow, ccol, FALSE);
	}
	fflush_all();
}
