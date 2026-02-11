cx_bm_list_enter(void)
{
	if (changedir(USTR(bm_list[panel_bm_lst.pd->curs])) == 0)
		next_mode = MODE_SPECIAL_RETURN;
}
