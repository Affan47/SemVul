service_set_chanmsg(service_t *service, bool chanmsg)
{
	return_if_fail(service != NULL);

	service->chanmsg = chanmsg;
}
