win_rest_invalid(wp)
	WIN			*wp;
{
	while (wp)
	{
		wp->w_lsize_valid = 0;
		wp->w_redr_type = NOT_VALID;
		wp->w_redr_status = TRUE;
		wp = wp->w_next;
	}
	redraw_cmdline = TRUE;
}
