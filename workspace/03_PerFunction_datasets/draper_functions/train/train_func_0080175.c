wxt_cleanup()
{
	std::vector<wxt_window_t>::iterator wxt_iter;

	if (wxt_status == STATUS_UNINITIALIZED)
		return;

	FPRINTF((stderr,"wxt_cleanup: start\n"));


	wxt_status = STATUS_UNINITIALIZED;


	wxt_sigint_init();


	for(wxt_iter = wxt_window_list.begin();
			wxt_iter != wxt_window_list.end(); wxt_iter++)
		wxt_iter->frame->Destroy();

	wxTheApp->OnExit();
	wxUninitialize();


	wxt_sigint_check();
	wxt_sigint_restore();

	FPRINTF((stderr,"wxt_cleanup: finished\n"));
}
