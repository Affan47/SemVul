desc_add(dlist_t **list, const char *name, const char *desc)
{
	dlist_t	*temp;

	for (temp = *list; temp != NULL; temp = temp->next) {
		if (!strcasecmp(temp->name, name)) {
			break;
		}
	}

	if (temp == NULL) {
		temp = xcalloc(1, sizeof(*temp));
		temp->name = xstrdup(name);
		temp->next = *list;
		*list = temp;
	}

	free(temp->desc);
	temp->desc = xstrdup(desc);
}
