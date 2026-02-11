wxt_update_size(int number)
{
	wxt_window_t *window;

	if (wxt_status != STATUS_OK)
		return;

	wxt_sigint_init();

	wxt_MutexGuiEnter();

	if ((window = wxt_findwindowbyid(number))) {
		FPRINTF((stderr,"wxt : update size of window %d\n",number));
		window->frame->SetClientSize( wxSize(wxt_width, wxt_height) );
	}

	wxt_MutexGuiLeave();

	wxt_sigint_check();
	wxt_sigint_restore();
}
