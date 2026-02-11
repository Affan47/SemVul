handleNotificationEntry()
{
	if (!strncmp(_text, "HOST NOTIFICATION: ", 19)
			|| !strncmp(_text, "SERVICE NOTIFICATION: ", 22))
	{
		_logclass = LOGCLASS_NOTIFICATION;
		bool svc = _text[0] == 'S';
		char *scan = _text;
		_text = next_token(&scan, ':');
		scan++;

		_contact_name  = next_token(&scan, ';');
		_host_name     = next_token(&scan, ';');
		if (svc) {
			_svc_desc = next_token(&scan, ';');
			_state_type = save_next_token(&scan, ';');
			_state = serviceStateToInt(_state_type);
		}
		else {
			_state_type = save_next_token(&scan, ';');
			_state = hostStateToInt(_state_type);
		}

		_command_name  = next_token(&scan, ';');
		_check_output  = next_token(&scan, ';');
		return true;
	}

	return false;
}
