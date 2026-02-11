set_credentials(struct hub_info* hub, struct hub_user* user, struct adc_message* cmd)
{
	int ret = 0;
	struct auth_info* info = acl_get_access_info(hub, user->id.nick);

	if (info)
	{
		user->credentials = info->credentials;
		ret = 1;
	}
	else
	{
		user->credentials = auth_cred_guest;
	}
	hub_free(info);

	switch (user->credentials)
	{
		case auth_cred_none:
			break;

		case auth_cred_bot:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_BOT);
			break;

		case auth_cred_ubot:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_BOT);
			break;

		case auth_cred_guest:

			break;

		case auth_cred_user:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_REGISTERED_USER);
			break;

		case auth_cred_operator:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_OPERATOR);
			break;

		case auth_cred_opbot:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_HUBBOT);
			break;

		case auth_cred_opubot:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_HUBBOT);
			break;

		case auth_cred_super:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_SUPER_USER);
			break;

		case auth_cred_admin:
			adc_msg_add_argument(cmd, ADC_INF_FLAG_CLIENT_TYPE ADC_CLIENT_TYPE_ADMIN);
			break;

		case auth_cred_link:
			break;
 	}

	return ret;
}
