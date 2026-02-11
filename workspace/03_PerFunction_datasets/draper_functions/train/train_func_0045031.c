initialize()
{

	Window_height = Max_lines * Line_h;

	active_messages.clear();
	pending_messages = SCP_queue<HUD_message_data>();

	Scroll_needed = false;
	Scroll_in_progress = false;
	Scroll_time_id = 1;

	HudGauge::initialize();
}
