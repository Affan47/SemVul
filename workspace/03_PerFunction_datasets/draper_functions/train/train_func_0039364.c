hub_get_status_message_log(struct hub_info* hub, enum status_message msg)
{
#define STATUS(MSG) case status_ ## MSG : return #MSG; break
	switch (msg)
	{
		STATUS(msg_hub_full);
		STATUS(msg_hub_disabled);
		STATUS(msg_hub_registered_users_only);
		STATUS(msg_inf_error_nick_missing);
		STATUS(msg_inf_error_nick_multiple);
		STATUS(msg_inf_error_nick_invalid);
		STATUS(msg_inf_error_nick_long);
		STATUS(msg_inf_error_nick_short);
		STATUS(msg_inf_error_nick_spaces);
		STATUS(msg_inf_error_nick_bad_chars);
		STATUS(msg_inf_error_nick_not_utf8);
		STATUS(msg_inf_error_nick_taken);
		STATUS(msg_inf_error_nick_restricted);
		STATUS(msg_inf_error_cid_invalid);
		STATUS(msg_inf_error_cid_missing);
		STATUS(msg_inf_error_cid_taken);
		STATUS(msg_inf_error_pid_missing);
		STATUS(msg_inf_error_pid_invalid);
		STATUS(msg_ban_permanently);
		STATUS(msg_ban_temporarily);
		STATUS(msg_auth_invalid_password);
		STATUS(msg_auth_user_not_found);
		STATUS(msg_error_no_memory);
		STATUS(msg_user_share_size_low);
		STATUS(msg_user_share_size_high);
		STATUS(msg_user_slots_low);
		STATUS(msg_user_slots_high);
		STATUS(msg_user_hub_limit_low);
		STATUS(msg_user_hub_limit_high);
		STATUS(msg_proto_no_common_hash);
		STATUS(msg_proto_obsolete_adc0);
	}
#undef STATUS
	return "unknown";
}
