msg_channel_flags(int p_or_n, const char *command, struct Client *client_p,
		  struct Client *source_p, struct Channel *chptr, int flags, const char *text)
{
	char text2[BUFSIZE];
	int type;
	char c;

	if(flags & CHFL_VOICE)
	{
		type = ONLY_CHANOPSVOICED;
		c = '+';
	}
	else
	{
		type = ONLY_CHANOPS;
		c = '@';
	}

	if(MyClient(source_p))
	{

		if(p_or_n != NOTICE)
			source_p->localClient->last = rb_current_time();
	}

	if(chptr->mode.mode & MODE_NOCOLOR)
	{
		rb_strlcpy(text2, text, BUFSIZE);
		strip_colour(text2);
		text = text2;
		if (EmptyString(text))
		{


			if(p_or_n != NOTICE)
				sendto_one(source_p, form_str(ERR_NOTEXTTOSEND), me.name, source_p->name);
			return;
		}
	}

	if (p_or_n != NOTICE && *text == '\001' &&
			strncasecmp(text + 1, "ACTION ", 7))
	{
		if (chptr->mode.mode & MODE_NOCTCP)
		{
			sendto_one_numeric(source_p, ERR_CANNOTSENDTOCHAN,
					   form_str(ERR_CANNOTSENDTOCHAN), chptr->chname);
			return;
		}
		else if (rb_dlink_list_length(&chptr->locmembers) > (unsigned)(GlobalSetOptions.floodcount / 2))
		{


			source_p->large_ctcp_sent = rb_current_time();
		}
	}

	sendto_channel_flags(client_p, type, source_p, chptr, "%s %c%s :%s",
			     command, c, chptr->chname, text);
}
