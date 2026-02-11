join_session(int i, char *password, char *playerName)
{
	SessionDesc *session = (SessionDesc *)current_sessions.get(i);
	if (!session)
		return 0;

	if (!open_port())
	{
		MSG("Unable to get the game socket.\n");
		return 0;
	}

	max_players = MAX_NATION;


	player_pool[0] = new PlayerDesc(0, "", &session->address);


	my_player = new PlayerDesc(playerName);

	joined_session = *session;
	strncpy(joined_session.password, password, MP_SESSION_NAME_LEN);
	joined_session.password[MP_SESSION_NAME_LEN] = 0;

	status = MP_STATUS_CONNECTING;

	return 1;
}
