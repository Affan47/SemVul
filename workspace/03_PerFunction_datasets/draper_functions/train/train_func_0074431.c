addaction(actionlist_t *base, const char *action)
{
	actionlist_t	*tmp, *last = NULL;

	if (!action) {
		return base;
	}

	for (tmp = base; tmp != NULL; tmp = tmp->next) {

		last = tmp;
	}

	tmp = xcalloc(1, sizeof(*tmp));
	tmp->action = xstrdup(action);

	if (last) {
		last->next = tmp;
		return base;
	}

	return tmp;
}
