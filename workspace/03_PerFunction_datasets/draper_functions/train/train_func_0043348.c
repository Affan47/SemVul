bookmark_keypress_cb(GtkWidget *button, GdkEventKey *event, gpointer data)
{
	BookMarkData *bm = data;

	switch (event->keyval)
		{
		case GDK_F10:
			if (!(event->state & GDK_CONTROL_MASK)) return FALSE;
		case GDK_Menu:
			bookmark_menu_popup(bm, button, 0, event->time, TRUE);
			return TRUE;
			break;
		case GDK_Up:
			if (event->state & GDK_SHIFT_MASK)
				{
				bookmark_move(bm, button, -1);
				return TRUE;
				}
			break;
		case GDK_Down:
			if (event->state & GDK_SHIFT_MASK)
				{
				bookmark_move(bm, button, 1);
				return TRUE;
				}
			break;
		}

	return FALSE;
}
