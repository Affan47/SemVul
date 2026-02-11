cb_status__check_592(const char *p, unsigned int s, void *payload)
{
	GIT_UNUSED(payload);

	if (s != GIT_STATUS_WT_DELETED || (payload != NULL && strcmp(p, (const char *)payload) != 0))
		return -1;

	return 0;
}
