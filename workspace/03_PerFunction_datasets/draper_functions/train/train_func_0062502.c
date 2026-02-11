Banlist_loadbans()
{
	banlrec	*b, *b_next, *b_tmp;
	char	s[BUFSIZ], ident[BUFSIZ], banlist[256];
	int	line = 0;
	time_t	now = time(NULL);
	FILE	*f;


	sprintf(banlist,"%s/%s",Grufti->botdir,Grufti->banlist);
	f = fopen(banlist,"r");
	if(f == NULL)
	{
		Banlist->flags |= BANLIST_ACTIVE;
		return;
	}


	b_tmp = banlrec_new();


	while(readline(f,s))
	{
		line++;


		split(ident,s);


		switch(ident[0])
		{
		    case 'n':
			if(b_tmp->nick != NULL)
			{
				Banlist_appendban(b_tmp);
				b_tmp = banlrec_new();
			}
			banlrec_setnick(b_tmp,s);
			break;

		    case 'b':
			banlrec_setban(b_tmp,s);
			break;

		    case 't':
			b_tmp->time_set = (time_t)atol(s);
			break;

		    case 'e':
			b_tmp->expires = (time_t)atol(s);
			break;

		    case 'u':
			b_tmp->used = atoi(s);
			break;
		}
	}

	fclose(f);


	if(b_tmp->nick != NULL)
		Banlist_appendban(b_tmp);


	Banlist->flags |= BANLIST_ACTIVE;
	Banlist->flags &= ~BANLIST_NEEDS_WRITE;


	b = Banlist->banlist;
	while(b != NULL)
	{
		b_next = b->next;
		if(b->expires != 0)
		{
			if((b->time_set + b->expires) < now)
			{
				Banlist_deleteban(b);
				Banlist->flags |= BANLIST_NEEDS_WRITE;
			}
		}

		b = b_next;
	}
}
