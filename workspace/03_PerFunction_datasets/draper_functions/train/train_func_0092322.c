mo_info(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(hunt_server(client_p, source_p, ":%s INFO :%s", 1, parc, parv) == HUNTED_ISME)
	{
		info_spy(source_p);
		send_info_text(source_p);

		if(IsOper(source_p))
		{
			send_conf_options(source_p);
			sendto_one_numeric(source_p, RPL_INFO, ":%s",
					rb_lib_version());
		}

		send_birthdate_online_time(source_p);

		sendto_one_numeric(source_p, RPL_ENDOFINFO, form_str(RPL_ENDOFINFO));
	}

	return 0;
}
