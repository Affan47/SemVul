create(UI_WINDOW *wnd, int _x, int _y, int _w, int _h, int _numitems, char **_list, char *_check_list, int _max_items)
{

	int tw, th, nrows;
	int real_h;

	gr_set_font(wnd->f_id);
	gr_get_string_size(&tw, &th, "*");

	nrows = _h / th;
	real_h = nrows * th;

	base_create( wnd, UI_KIND_LISTBOX, _x, _y, _w, real_h );

   max_items = _max_items;
   list = _list;
	num_items = _numitems;
	check_list = _check_list;
	num_items_displayed = nrows;

	first_item = 0;
	current_item = -1;
	toggled_item = -1;
	last_scrolled = 0;
	textheight = th;
	dragging = 0;
	selected_item = -1;
	key_buffer_count = 0;
	last_typed = timer_get_milliseconds();

	if (_numitems > nrows) {
		scrollbar.create( wnd, _x+_w+3, _y, real_h, 0, _numitems-nrows, 0, nrows );
		scrollbar.set_parent(this);
		has_scrollbar = 1;

	} else {
		has_scrollbar = 0;
	}


	draw_frame = 1;
}
