find_bounce(aClient *cptr, int class, int fd)
{
	Reg	aConfItem	*aconf;

	if (fd < 0 && cptr == NULL)
	{

		return;
	}

	for (aconf = conf; aconf; aconf = aconf->next)
	{
		if (aconf->status != CONF_BOUNCE)
		{
			continue;
		}

		if (fd >= 0)
		{


			if (*aconf->host == '\0')
			{
				char rpl[BUFSIZE];

				sprintf(rpl, replies[RPL_BOUNCE], ME, "unknown",
					aconf->name, aconf->port);
				strcat(rpl, "\r\n");
#ifdef INET6
				sendto(fd, rpl, strlen(rpl), 0, 0, 0);
#else
				send(fd, rpl, strlen(rpl), 0);
#endif
				return;
			}
			else
			{
				continue;
			}
		}


		if (fd != -2 &&
		    !strchr(aconf->host, '.') &&
			(isdigit(*aconf->host) || *aconf->host == '-'))
		{
			if (class != atoi(aconf->host))
			{
				continue;
			}
		}
		else
		{
			if (strchr(aconf->host, '/'))
			{
				if (match_ipmask(aconf->host, cptr, 1))
					continue;
			}
			else if (match(aconf->host, cptr->sockhost))
			{
				continue;
			}
		}

		sendto_one(cptr, replies[RPL_BOUNCE], ME, BadTo(cptr->name),
			aconf->name, aconf->port);
		return;
	}

}
