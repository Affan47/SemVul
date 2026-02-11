send_cap_mode_changes(struct Client *client_p, struct Client *source_p,
		      struct Channel *chptr, struct ChModeChange mode_changes[], int mode_count)
{
	static char modebuf[BUFSIZE];
	static char parabuf[BUFSIZE];
	int i, mbl, pbl, nc, mc, preflen, len;
	char *pbuf;
	const char *arg;
	int cap;
	int nocap;
	int dir;
	int arglen;


	mc = 0;
	nc = 0;
	pbl = 0;
	parabuf[0] = 0;
	pbuf = parabuf;
	dir = MODE_QUERY;

	mbl = preflen = rb_sprintf(modebuf, ":%s TMODE %ld %s ",
				   use_id(source_p), (long) chptr->channelts,
				   chptr->chname);


	for (i = 0; i < mode_count; i++)
	{


		if (mode_changes[i].letter == 0)
			continue;

		cap = mode_changes[i].caps;
		nocap = mode_changes[i].nocaps;

		if (!EmptyString(mode_changes[i].id))
			arg = mode_changes[i].id;
		else
			arg = mode_changes[i].arg;

		if(arg)
		{
			arglen = strlen(arg);


			if(arglen > MODEBUFLEN - 5)
				continue;
		}


		if(arg && ((mc == MAXMODEPARAMSSERV) ||
			   ((mbl + pbl + arglen + 4) > (BUFSIZE - 3))))
		{
			if(nc != 0)
				sendto_server(client_p, chptr, cap, nocap,
					      "%s %s", modebuf, parabuf);
			nc = 0;
			mc = 0;

			mbl = preflen;
			pbl = 0;
			pbuf = parabuf;
			parabuf[0] = 0;
			dir = MODE_QUERY;
		}

		if(dir != mode_changes[i].dir)
		{
			modebuf[mbl++] = (mode_changes[i].dir == MODE_ADD) ? '+' : '-';
			dir = mode_changes[i].dir;
		}

		modebuf[mbl++] = mode_changes[i].letter;
		modebuf[mbl] = 0;
		nc++;

		if(arg != NULL)
		{
			len = rb_sprintf(pbuf, "%s ", arg);
			pbuf += len;
			pbl += len;
			mc++;
		}
	}

	if(pbl && parabuf[pbl - 1] == ' ')
		parabuf[pbl - 1] = 0;

	if(nc != 0)
		sendto_server(client_p, chptr, cap, nocap, "%s %s", modebuf, parabuf);
}
