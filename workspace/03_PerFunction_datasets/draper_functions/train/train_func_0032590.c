get_color(GB_DRAW *d, int col, bool bg)
{
	QWidget *wid = get_widget(d);

	if (col == COLOR_DEFAULT)
	{
		if (wid)
		{
			if (bg)
				col = wid->palette().color(QPalette::Window).rgb() & 0xFFFFFF;
			else
				col = wid->palette().color(QPalette::WindowText).rgb() & 0xFFFFFF;
		}
		else
			col = bg ? 0xFFFFFF : 0x000000;
	}

	return col;
}
