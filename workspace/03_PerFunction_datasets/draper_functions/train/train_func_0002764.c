seaudit_message_to_misc_string(const seaudit_message_t * msg)
{
	if (msg == NULL) {
		errno = EINVAL;
		return NULL;
	}
	switch (msg->type) {
	case SEAUDIT_MESSAGE_TYPE_AVC:
		return avc_message_to_misc_string(msg->data.avc);
	case SEAUDIT_MESSAGE_TYPE_BOOL:
		return bool_message_to_misc_string(msg->data.boolm);
	case SEAUDIT_MESSAGE_TYPE_LOAD:
		return load_message_to_misc_string(msg->data.load);
	default:
		errno = EINVAL;
		return NULL;
	}
}
