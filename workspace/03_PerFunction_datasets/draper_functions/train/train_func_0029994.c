mg_handle_drop (GtkWidget *widget, int y, int *pos, int *other_pos)
{
	int height;
	session_gui *gui = current_sess->gui;

	gdk_drawable_get_size (widget->window, NULL, &height);

	if (y < height / 2)
	{
		if (is_child_of (widget, gui->vpane_left))
			*pos = 1;
		else
			*pos = 3;
	}
	else
	{
		if (is_child_of (widget, gui->vpane_left))
			*pos = 2;
		else
			*pos = 4;
	}


	if (*pos == *other_pos)
	{
		switch (*other_pos)
		{
		case 1:
			*other_pos = 2;
			break;
		case 2:
			*other_pos = 1;
			break;
		case 3:
			*other_pos = 4;
			break;
		case 4:
			*other_pos = 3;
			break;
		}
	}

	mg_place_userlist_and_chanview (gui);
}
