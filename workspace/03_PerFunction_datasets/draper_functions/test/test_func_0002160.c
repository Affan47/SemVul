avc_msg_insert_access_type(const seaudit_log_t * log, const char *token, seaudit_avc_message_t * avc)
{
	if (strcmp(token, "granted") == 0) {
		avc->msg = SEAUDIT_AVC_GRANTED;
		return 0;
	} else if (strcmp(token, "denied") == 0) {
		avc->msg = SEAUDIT_AVC_DENIED;
		return 0;
	}
	WARN(log, "%s", "No AVC message type found, assuming it was a denial.");
	avc->msg = SEAUDIT_AVC_DENIED;
	return 1;
}
