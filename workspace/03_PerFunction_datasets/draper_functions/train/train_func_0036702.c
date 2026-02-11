skype_status_text(PurpleBuddy *buddy)
{
	char *mood_text;
	PurplePresence *presence;
	PurpleStatus *status;
	PurpleStatusType *type;
	SkypeBuddy *sbuddy = buddy->proto_data;

	if (sbuddy && sbuddy->mood != NULL && strlen(sbuddy->mood))
		return skype_strdup_withhtml(sbuddy->mood);

	if (sbuddy == NULL || sbuddy->mood == NULL)
	{
		if (buddy->name[0] != '+')
			skype_send_message_nowait("GET USER %s MOOD_TEXT", buddy->name);
		return NULL;
	}


	presence = purple_buddy_get_presence(buddy);
	if (presence == NULL)
		return NULL;
	status = purple_presence_get_active_status(presence);
	if (status == NULL)
		return NULL;
	type = purple_status_get_type(status);
	if (type == NULL || g_str_equal(purple_status_type_get_id(type), "ONLINE") ||
		purple_status_type_get_primitive(type) == PURPLE_STATUS_OFFLINE)
			return NULL;
	mood_text = (char *)purple_status_type_get_name(type);
	if (mood_text != NULL && strlen(mood_text))
		return skype_strdup_withhtml(mood_text);

	return NULL;
}
