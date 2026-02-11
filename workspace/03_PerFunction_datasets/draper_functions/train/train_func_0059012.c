avc_msg_insert_tclass(seaudit_log_t * log, seaudit_avc_message_t * avc, const char *tmp)
{
	char *tclass;
	if ((tclass = strdup(tmp)) == NULL || apol_bst_insert_and_get(log->classes, (void **)&tclass, NULL) < 0) {
		int error = errno;
		ERR(log, "%s", strerror(error));
		errno = error;
		return -1;
	}
	avc->tclass = tclass;
	return 0;
}
