led_filter_audio (void)
{
	led_filter_on = 0;
	if (led_filter_forced > 0 || (gui_data.powerled && led_filter_forced >= 0))
		led_filter_on = 1;
}
