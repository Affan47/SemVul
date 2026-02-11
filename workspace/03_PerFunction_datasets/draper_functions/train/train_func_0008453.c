hub_handle_info_login(struct hub_info* hub, struct hub_user* user, struct adc_message* cmd)
{
	int code = 0;

	INF_CHECK(hub_perform_login_checks, hub, user, cmd);


	adc_msg_remove_named_argument(cmd, ADC_INF_FLAG_PRIVATE_ID);

	code = set_credentials(hub, user, cmd);


	if (check_is_hub_full(hub, user))
	{
		return status_msg_hub_full;
	}

	if (check_registered_users_only(hub, user))
	{
		return status_msg_hub_registered_users_only;
	}

	INF_CHECK(check_limits, hub, user, cmd);


	hub_handle_info_low_bandwidth(hub, user, cmd);


	user_set_info(user, cmd);

	return code;
}
