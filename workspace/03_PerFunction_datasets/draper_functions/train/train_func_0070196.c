ups_is_alive(utype_t *ups)
{
	time_t	now;

	time(&now);
	ups->lastpoll = now;

	if (ups->commstate == 1)
		return;


	if (ups->commstate == 0)
		do_notify(ups, NOTIFY_COMMOK);

	ups->commstate = 1;
}
