cancel_timer(const char *name, const char *cname)
{
	ttype_t	*tmp;

	for (tmp = thead; tmp != NULL; tmp = tmp->next) {
		if (!strcmp(tmp->name, name)) {
			if (verbose)
				upslogx(LOG_INFO, "Cancelling timer: %s", name);
			removetimer(tmp);
			return;
		}
	}


	if (cname && cname[0]) {
		if (verbose)
			upslogx(LOG_INFO, "Cancel %s, event: %s", name, cname);

		exec_cmd(cname);
	}
}
