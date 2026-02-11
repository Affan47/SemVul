get_x11_title()
{
	XTextProperty	text_prop;

	if (get_x11_windis() == OK)
	{

		if (XGetWMName(x11_display, x11_window, &text_prop))
		{
			if (text_prop.value != NULL)
				oldtitle = strsave((char_u *)text_prop.value);
			XFree((void *)text_prop.value);
		}
	}
	if (oldtitle == NULL)
		oldtitle = (char_u *)"Thanks for flying Vim";
}
