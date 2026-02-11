on_resize(int old_width, int old_height)
{
	CL_Rect client_rect(3, 24, window->get_width() - 3, window->get_height() - 3);
	window->get_client_area()->set_position(client_rect);

	int xpos = window->get_width() - 20;

	if(button_close)
	{
		CL_Rect close_rect(xpos, 3, xpos + 17, 20);
		button_close->set_position(close_rect);
		xpos -= 18;
	}

	if(button_maximize)
	{
		CL_Rect close_rect(xpos, 3, xpos + 17, 20);
		button_maximize->set_position(close_rect);
		xpos -= 18;
	}

	if(button_minimize)
	{
		CL_Rect close_rect(xpos, 3, xpos + 17, 20);
		button_minimize->set_position(close_rect);
		xpos -= 18;
	}

	if(button_help)
	{
		CL_Rect close_rect(xpos, 3, xpos + 17, 20);
		button_help->set_position(close_rect);
	}

	CL_Rect move_rect(0, 0, window->get_width(), titlebar_height);
	move_handler->set_position(move_rect);

	CL_Rect resize_rect(window->get_width() - 3, window->get_height() - 3, window->get_width(), window->get_height());
	resize_handler->set_position(resize_rect);
}
