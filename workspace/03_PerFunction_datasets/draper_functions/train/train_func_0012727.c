Cmd_MacroExpandString (const char *text)
{
	int				i, j, count, len;
	qboolean		inquote = false, rescan, badtoken;
	static	char	expanded[MAX_STRING_CHARS];
	char			temporary[MAX_STRING_CHARS], *token;
	const char		*scan, *start;

	scan = text;
	len = strlen(scan);
	if (len >= MAX_STRING_CHARS) {
		Com_Printf ("Cmd_MacroExpandString: Line exceeded %i chars, discarded.\n", MAX_STRING_CHARS);
		return NULL;
	}

	count = 0;

	for (i=0 ; i<len ; i++)
	{
		if (scan[i] == '"')
			inquote ^= 1;
		if (inquote)
			continue;
		if (scan[i] != '$')
			continue;

		start = scan+i+1;


		while (*start && *start <= ' ') {
			start++;
		}

		if (!*start)
			break;

		token = temporary;
		if(*start == '{')
		{
			start++;
			if( *start == '$' )
				start++;

			badtoken = true;
			while( *start > ' ' ) {
				if( *start == '}' ) {
					start++;
					badtoken = false;
					break;
				}
				*token++ = *start++;
			}
			if(badtoken)
				continue;
		}
		else
		{
			while( *start > ' ' ) {
				if( *start == '$' ) {
					start++;
					break;
				}
				*token++ = *start++;
			}
		}
		*token = 0;

		rescan = false;
		if(aliasHack)
		{
			if(*temporary < '1' || *temporary > '9')
				continue;

			if(!temporary[1])
				token = Cmd_Argv(*temporary - '0');
			else if(temporary[1] == '-' && !temporary[2])
				token = Cmd_ArgsFrom(*temporary - '0');
			else
				continue;
		}
		else
		{
			token = Cvar_VariableString ( temporary );
			if(!*token)
				token = Cmd_MacroString( temporary );
			else
				rescan = true;
		}

		j = strlen(token);

		len += j - (start - scan - i);
		if (len >= MAX_STRING_CHARS) {
			Com_Printf ("Expanded line exceeded %i chars, discarded.\n", MAX_STRING_CHARS);
			return NULL;
		}
		if (++count == 100) {
			Com_Printf ("Macro expansion loop, discarded.\n");
			return NULL;
		}

		strncpy (temporary, scan, i);
		strcpy (temporary+i, token);
		strcpy (temporary+i+j, start);

		strcpy (expanded, temporary);
		scan = expanded;
		i--;
		if(!rescan)
			i += j;
	}

	if (inquote) {
		Com_Printf ("Line has unmatched quote, discarded.\n");
		return NULL;
	}

	return scan;
}
