is_rectangle_selection_event (GdkEventKey *event)
{
	return (event->state & GDK_CONTROL_MASK) != 0 &&
		(event->state & GDK_SHIFT_MASK) != 0;
}
