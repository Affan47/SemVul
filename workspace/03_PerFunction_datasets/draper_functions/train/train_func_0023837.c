invalidate(void)
{

    if (is_realized())
    {
	Gdk::Rectangle rect = get_allocation();
	rect.set_x(0);
	rect.set_y(0);


	get_window()->invalidate_rect(rect, false);
    }
}
