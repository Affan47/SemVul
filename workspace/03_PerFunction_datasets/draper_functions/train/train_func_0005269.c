IRC_event_general(irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	printf("%s %s", event, origin);
	for (unsigned int i = 0; i < count; ++i) {
		printf(" %s", params[i]);
	}
	printf("\n");
}
