on_delay_reboot()
{
	if (is_recording)
		on_preview();
	else if (is_running)
		start_play();
	return false;
}
