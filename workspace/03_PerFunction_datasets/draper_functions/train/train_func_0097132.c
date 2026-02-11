ethi_remove_drop_marker (ETableHeaderItem *ethi)
{
	if (ethi->drag_mark == -1)
		return;

	gtk_widget_hide (arrow_up);
	gtk_widget_hide (arrow_down);

	ethi->drag_mark = -1;
}
