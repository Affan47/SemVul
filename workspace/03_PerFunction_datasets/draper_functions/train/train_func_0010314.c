CWIDGET_handle_focus(CWIDGET *control, bool on)
{
	if (on == (CWIDGET_active_control == control))
		return;


	CWIDGET_active_control = on ? control : NULL;
	handle_focus_change();
}
