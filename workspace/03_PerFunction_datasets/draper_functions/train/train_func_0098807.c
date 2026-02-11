burst_ban(struct Client *client_p)
{
	rb_dlink_node *ptr;
	struct ConfItem *aconf;
	const char *type, *oper;

	char operbuf[NICKLEN + USERLEN + HOSTLEN + HOSTLEN + 5];
	char *p;
	size_t melen;

	melen = strlen(me.name);
	RB_DLINK_FOREACH(ptr, prop_bans.head)
	{
		aconf = ptr->data;


		if(aconf->lifetime < rb_current_time())
			continue;
		switch(aconf->status & ~CONF_ILLEGAL)
		{
			case CONF_KILL: type = "K"; break;
			case CONF_DLINE: type = "D"; break;
			case CONF_XLINE: type = "X"; break;
			case CONF_RESV_NICK: type = "R"; break;
			case CONF_RESV_CHANNEL: type = "R"; break;
			default:
				continue;
		}
		oper = aconf->info.oper;
		if(aconf->flags & CONF_FLAGS_MYOPER)
		{


			rb_strlcpy(operbuf, aconf->info.oper, sizeof buf);
			p = strrchr(operbuf, '{');
			if (p != NULL &&
					operbuf + sizeof operbuf - p > (ptrdiff_t)(melen + 2))
			{
				memcpy(p + 1, me.name, melen);
				p[melen + 1] = '}';
				p[melen + 2] = '\0';
				oper = operbuf;
			}
		}
		sendto_one(client_p, ":%s BAN %s %s %s %lu %d %d %s :%s%s%s",
				me.id,
				type,
				aconf->user ? aconf->user : "*", aconf->host,
				(unsigned long)aconf->created,
				(int)(aconf->hold - aconf->created),
				(int)(aconf->lifetime - aconf->created),
				oper,
				aconf->passwd,
				aconf->spasswd ? "|" : "",
				aconf->spasswd ? aconf->spasswd : "");
	}
}
