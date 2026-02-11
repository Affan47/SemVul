set_mode_normal(P_Buttons *page)
{
	if(page->button != NULL)
		set_button_state(page->button, FALSE);
	page->button = NULL;
	page->mode   = BM_NORMAL;
	reset_widgets(page);
}
