enterPopup(gMainWindow *owner)
{
	void *old_owner = _loop_owner;
	int l = _loopLevel;
	GtkWindowGroup *oldGroup;
	GtkWindow *window = GTK_WINDOW(owner->border);

	_in_popup++;

	oldGroup = enterGroup();

	gtk_window_set_modal(window, true);
	gdk_window_set_override_redirect(owner->border->window, true);
	owner->show();

	if (_in_popup == 1)
	{
		_popup_grab_window = owner->border->window;
		gApplication::grabPopup();
	}

	_loopLevel++;
	_loop_owner = owner;

	do
	{
		MAIN_do_iteration(false);
	}
	while (_loopLevel > l);

	gApplication::ungrabPopup();

	_loop_owner = old_owner;

	gdk_window_set_override_redirect(owner->border->window, false);
	gtk_window_set_modal(window, false);
	exitGroup(oldGroup);

	_in_popup--;
}
