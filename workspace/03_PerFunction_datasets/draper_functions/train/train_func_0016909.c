initProperties()
{
	#ifndef NO_X_WINDOW
	CWIDGET *_object = CWidget::get(this);

	if (!THIS->toplevel)
		return;

	CWINDOW_change_property(this, X11_atom_net_wm_state_above, THIS->stacking == 1);
	CWINDOW_change_property(this, X11_atom_net_wm_state_stays_on_top, THIS->stacking == 1);
	CWINDOW_change_property(this, X11_atom_net_wm_state_below, THIS->stacking == 2);
	CWINDOW_change_property(this, X11_atom_net_wm_state_skip_taskbar, THIS->skipTaskbar);
	X11_set_window_type(winId(), _type);
	#endif
}
