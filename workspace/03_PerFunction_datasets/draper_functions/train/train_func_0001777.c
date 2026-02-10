set_value(int value, bool using_slider)
{
	if(value < min_value) value = min_value;
	if(value > max_value) value = max_value;

	if(cur_value != value)
	{
		cur_value = value;

		if(using_slider)
			sig_slider_moved(cur_value);

		if((using_slider && tracking) || using_slider == false)
			sig_value_changed(cur_value);
	}

	if(using_slider == false)
		calculate_slider();
}
