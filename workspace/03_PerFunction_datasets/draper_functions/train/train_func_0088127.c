seaudit_message_get_data(const seaudit_message_t * msg, seaudit_message_type_e * type)
{
	if (type != NULL) {
		*type = SEAUDIT_MESSAGE_TYPE_INVALID;
	}
	if (msg == NULL || type == NULL || msg->type == SEAUDIT_MESSAGE_TYPE_INVALID) {
		errno = EINVAL;
		return NULL;
	}
	switch ((*type = msg->type)) {
	case SEAUDIT_MESSAGE_TYPE_AVC:
		return msg->data.avc;
	case SEAUDIT_MESSAGE_TYPE_BOOL:
		return msg->data.boolm;
	case SEAUDIT_MESSAGE_TYPE_LOAD:
		return msg->data.load;
	default:
		errno = EINVAL;
		return NULL;
	}
}
