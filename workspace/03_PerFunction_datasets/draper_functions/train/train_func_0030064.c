create(UI_WINDOW *wnd, char *_text, int _x, int _y, int _w, int _h)
{
	if (_text)
		text = vm_strdup(_text);
	else
		text = NULL;

	base_create(wnd, UI_KIND_ICON, _x, _y, _w, _h);
	m_flags = 0;
}
