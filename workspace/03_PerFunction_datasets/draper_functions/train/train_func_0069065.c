editchar(c, flags)
	int c;
	int flags;
{
	int action;
	int nch;
	char *s;
	char usercmd[MAX_CMDLEN+1];


	if (c == erase_char || c == erase2_char)
		return (EC_BACKSPACE);
	if (c == kill_char)
		return (EC_LINEKILL);


	nch = 0;
	do {
	  	if (nch > 0)
			c = getcc();
		usercmd[nch] = c;
		usercmd[nch+1] = '\0';
		nch++;
		action = ecmd_decode(usercmd, &s);
	} while (action == A_PREFIX);

	if (flags & EC_NORIGHTLEFT)
	{
		switch (action)
		{
		case EC_RIGHT:
		case EC_LEFT:
			action = A_INVALID;
			break;
		}
	}
#if CMD_HISTORY
	if (flags & EC_NOHISTORY)
	{


		switch (action)
		{
		case EC_UP:
		case EC_DOWN:
			action = A_INVALID;
			break;
		}
	}
#endif
#if TAB_COMPLETE_FILENAME
	if (flags & EC_NOCOMPLETE)
	{


		switch (action)
		{
		case EC_F_COMPLETE:
		case EC_B_COMPLETE:
		case EC_EXPAND:
			action = A_INVALID;
			break;
		}
	}
#endif
	if ((flags & EC_PEEK) || action == A_INVALID)
	{


		while (nch > 1)
		{
			ungetcc(usercmd[--nch]);
		}
	} else
	{
		if (s != NULL)
			ungetsc(s);
	}
	return action;
}
