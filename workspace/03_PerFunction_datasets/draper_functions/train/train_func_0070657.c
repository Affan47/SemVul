CWINDOW_set_cancel_button(CWINDOW *win, QPushButton *button, bool on)
{

	if (on)
	{
		win->cancelButton = button;
	}
	else
	{
		if (button == win->cancelButton)
			win->cancelButton = 0;
	}
}
