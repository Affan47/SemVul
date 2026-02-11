try_status()
{
	struct message *m;
	manager_action("Status", "");
	m = wait_for_response(10000);
	if (!m) {
		gui_show_message("Status Failed", "Timeout waiting for response");
	} else if (strcasecmp(get_header(m, "Response"), "Success"))  {
		gui_show_message("Status Failed", get_header(m, "Message"));
	}
}
