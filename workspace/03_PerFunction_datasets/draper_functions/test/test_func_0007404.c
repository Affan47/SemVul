filter_list_active(void)
{
	return !!uc_filter_list ||
		!!(command_line_actions & IUCODE_F_UCSELECT);
}
