jab_send_raw(jconn j, const char *str)
{
	if (j && j->state != JCONN_STATE_OFF) {
		ext_jabber_write(j, str, strlen(str));
	}
#ifdef JDEBUG
	fprintf(stderr, "rjab<%s %s\n", j->user->user, str);
#endif
}
