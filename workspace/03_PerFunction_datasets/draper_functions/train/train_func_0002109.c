timer_remove(plugin_t *plugin, const char *name)
{
	struct timer *t;
	int removed = 0;

	for (t = timers; t; t = t->next) {
		if (t->plugin == plugin && !xstrcasecmp(name, t->name)) {
			t = timers_removei(t);
			removed++;
		}
	}

	return ((removed) ? 0 : -1);
}
