wxt_set_ruler(int x, int y)
{
	if (wxt_status == STATUS_UNINITIALIZED)
		return;

	wxt_sigint_init();
	wxt_MutexGuiEnter();

	if (x<0) {
		wxt_current_panel->wxt_ruler = false;
		wxt_current_panel->Draw();
	} else {
		wxt_current_panel->wxt_ruler = true;
		wxt_current_panel->wxt_ruler_x = device_x(wxt_current_plot, x);
		wxt_current_panel->wxt_ruler_y = device_y(wxt_current_plot, y);
		wxt_current_panel->Draw();
	}

	wxt_MutexGuiLeave();
	wxt_sigint_check();
	wxt_sigint_restore();
}
