on_resize(int old_width, int old_height)
{
	CL_Rect rect_decrease;
	CL_Rect rect_increase;
	CL_Rect rect_client;

	if (scrollbar->is_vertical())
	{
		int button_size = scrollbar->get_width();
		rect_decrease = CL_Rect(0, 0, button_size, button_size);
		rect_increase = CL_Rect(0, scrollbar->get_height() - button_size, button_size, scrollbar->get_height());
		rect_client = CL_Rect(0, button_size, button_size, scrollbar->get_height() - button_size);
	}
	else
	{
		int button_size = scrollbar->get_height();
		rect_decrease = CL_Rect(0, 0, button_size, button_size);
		rect_increase = CL_Rect(scrollbar->get_width() - button_size, 0, scrollbar->get_width(), button_size);
		rect_client = CL_Rect(button_size, 0, scrollbar->get_width() - button_size, button_size);
	}

	button_decrease->set_position(rect_decrease);
	button_increase->set_position(rect_increase);
	scrollbar->get_client_area()->set_position(rect_client);
}
