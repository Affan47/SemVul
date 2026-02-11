find_contact_in_group_by_nick(const char *nick, grouplist *gl)
{
	LList *l;

	if (nick == NULL || gl == NULL)
		return NULL;

	for (l = gl->members; l; l = l->next) {
		if (!strcasecmp(((struct contact *)l->data)->nick, nick))
			return (struct contact *)l->data;
	}

	return NULL;
}
