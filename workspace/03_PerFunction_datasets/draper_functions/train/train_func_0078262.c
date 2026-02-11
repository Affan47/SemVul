dpm_updpoolfreespace(char *poolname, signed64 incr)
{
	int found = 0;
	int i;
	char tmpbuf0[21];
	char tmpbuf1[21];

	if (Cthread_mutex_lock (&poolconf_mutex) < 0)
		return (-1);

	for (i = 0; i < nbpool; i++) {
		if (strcmp ((pools + i)->poolname, poolname) == 0) {
			found++;
			break;
		}
	}
	if (found) {
		(pools + i)->free += incr;
		dpmlogit ("dpm_updpoolfreespace", "%s incr=%s, poolp->free=%s\n",
		    poolname, i64tostr (incr, tmpbuf0, 0), i64tostr((pools+i)->free, tmpbuf1, 0));
	}
	(void) Cthread_mutex_unlock (&poolconf_mutex);
	return (0);
}
