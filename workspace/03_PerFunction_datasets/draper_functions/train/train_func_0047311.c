dpm_stop_gc(char *poolname)
{
	int i;

	if (Cthread_mutex_lock (&poolconf_mutex) < 0)
		return (-1);
	for (i = 0; i < maxnbpools; i++) {
		if (strcmp ((gc_entry+i)->poolname, poolname) == 0) break;
	}
	if (i >= maxnbpools) {
		(void) Cthread_mutex_unlock (&poolconf_mutex);
		return (-1);
	}
	(gc_entry+i)->status = 2;
	(void) Cthread_mutex_unlock (&poolconf_mutex);
	return (0);
}
