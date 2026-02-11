cue_ball_placed(GtkWidget *widget,
                                           GdkEventButton *event,
								   Application *app)
{
	int x = int(event->x) ; int y = int(event->y);
	std::vector<Ball>::iterator bb;
	bb = find_if(app->balls.begin(), app->balls.end(), pointer_selects(x, y, FALSE));
	if (app->game_name == eight_ball || app->game_name == rotation)
	{
		if(x - BALL_SIZE / 2 > app->table.x &&

		   x + BALL_SIZE / 2 < app->table.x + app->table.width &&
		   y - BALL_SIZE / 2 > app->table.y &&
		   y + BALL_SIZE / 2 < app->table.y + app->table.height)
		{
			app->new_ball(x, y, CUE, other, true);
			update_dirty(x - BALL_SIZE / 2, x + BALL_SIZE / 2, y - BALL_SIZE / 2,
			             y + BALL_SIZE / 2);
			gtk_signal_disconnect(GTK_OBJECT(app->drawing_area), app->qbp_hndlr);
			gtk_signal_handler_unblock(GTK_OBJECT(app->drawing_area),
			                           app->button_press_handler_id);
			gdk_window_set_cursor(app->drawing_area->window, (GdkCursor *)NULL);
		}
	} else
	{
		if(x - BALL_SIZE / 2 > app->table.x &&
		   x + BALL_SIZE / 2 < app->table.x + app->table.width &&
		   y - BALL_SIZE / 2 > app->table.y &&
		   y + BALL_SIZE / 2 < app->table.y + app->table.height)
		{
			app->new_ball(x, y, CUE, other, true);
			update_dirty(x - BALL_SIZE / 2, x + BALL_SIZE / 2, y - BALL_SIZE / 2,
			             y + BALL_SIZE / 2);
			gtk_signal_disconnect(GTK_OBJECT(app->drawing_area), app->qbp_hndlr);
			gtk_signal_handler_unblock(GTK_OBJECT(app->drawing_area),
			                           app->button_press_handler_id);
			gdk_window_set_cursor(app->drawing_area->window, (GdkCursor *)NULL);
		}
	}
	app->placing_cue = false;

	return app->placing_cue;
}
