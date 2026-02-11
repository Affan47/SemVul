get_oper_name(sourceinfo_t *si)
{
	static char result[NICKLEN+USERLEN+HOSTLEN+NICKLEN+10];

	if (si->v != NULL && si->v->get_oper_name != NULL)
		return si->v->get_oper_name(si);

	if (si->su != NULL)
	{
		if (si->smu == NULL)
			snprintf(result, sizeof result, "%s!%s@%s{%s}", si->su->nick,
					si->su->user, si->su->vhost,
					si->su->server->name);
		else if (!irccasecmp(si->su->nick, entity(si->smu)->name))
			snprintf(result, sizeof result, "%s", si->su->nick);
		else
			snprintf(result, sizeof result, "%s (%s)", si->su->nick,
					si->smu ? entity(si->smu)->name : "");
	}
	else if (si->s != NULL)
		snprintf(result, sizeof result, "%s", si->s->name);
	else
	{
		snprintf(result, sizeof result, "<%s>%s", si->v->description,
				si->smu ? entity(si->smu)->name : "");
	}
	return result;
}
