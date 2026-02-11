update()
{
	ht_listbox::update();
	Cursor_adjust = 0;
	if (widths) {
		for (int i=0; i<keycol; i++) {
			Cursor_adjust+=widths[i]+3;
		}
	}
}
