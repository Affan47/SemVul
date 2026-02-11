filter_perm_support(const seaudit_message_t * msg)
{
	return msg->type == SEAUDIT_MESSAGE_TYPE_AVC && msg->data.avc->perms != NULL &&
		apol_vector_get_size(msg->data.avc->perms) >= 1;
}
