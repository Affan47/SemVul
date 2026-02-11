Cmd_UnAlias_f (void)
{
	char		*s;
	unsigned int hash;
	cmdalias_t	*a, *entry, **back;

	if (Cmd_Argc() == 1) {
		Com_Printf ("Usage: %s <name>\n", Cmd_Argv(0));
		return;
	}

	s = Cmd_Argv(1);
	if (strlen(s) >= MAX_ALIAS_NAME) {
		Com_Printf ("Alias name is too long\n");
		return;
	}

	hash = Com_HashKey(s, ALIAS_HASH_SIZE);
	back = &cmd_aliasHash[hash];
	for(entry = *back; entry; back=&entry->hashNext, entry=entry->hashNext ) {
		if(!Q_stricmp(s, entry->name)) {
			*back = entry->hashNext;
			break;
		}
	}
	if(!entry) {
		Com_Printf ("Cmd_Unalias_f: \"%s\" not added\n", s);
		return;
	}

	back = &cmd_alias;
	for(a = *back; a; back = &a->next, a = a->next) {
		if(a == entry) {
			*back = a->next;
			Z_Free(a->value);
			Z_Free(a);
			Com_Printf ("Alias \"%s\" removed\n", s);
			break;
		}
	}
}
