insert_standard_msg_header(const seaudit_log_t * log, const apol_vector_t * tokens, size_t * position,
				      seaudit_message_t * msg)
{
	int ret = 0;
	if ((ret = insert_time(log, tokens, position, msg)) != 0) {
		return ret;
	}
	if ((ret = insert_hostname(log, tokens, position, msg)) != 0) {
		return ret;
	}
	return ret;
}
