SCR_Draw_f( void )
{
    int x, y, i;
    char *s;
    drawobj_t *entry;
    xmacro_t macro;
	cvar_t	*cvar;

	i = Cmd_Argc();
    if( i < 4 ) {
		Com_Printf( "Usage: %s <name> <x> <y> [color [time]]\n", Cmd_Argv( 0 ) );
        return;
    }

    s = Cmd_Argv( 1 );
    x = atoi( Cmd_Argv( 2 ) );
    y = atoi( Cmd_Argv( 3 ) );

    macro = Cmd_FindMacroFunction( s );
	if( macro ) {
		cvar = NULL;
	} else {
		cvar = Cvar_Get( s, "", CVAR_USER_CREATED );
	}

	for(entry = scr_objects; entry; entry = entry->next ) {
		if( entry->macro == macro && entry->cvar == cvar ) {

			if (entry->x == x && entry->y == y)
				break;
		}
	}

	if (!entry) {
		entry = Z_TagMalloc( sizeof( *entry ), TAG_CL_DRAWSTRING );
		entry->next = scr_objects;
		scr_objects = entry;

		entry->cvar = cvar;
		entry->macro = macro;
	}
    entry->x = x;
    entry->y = y;

	entry->startTime = cls.realtime;
	entry->visTime = 0;
	if (i > 4) {
		entry->color = atoi( Cmd_Argv( 4 ) ) & 7;
		if (i > 5)
			entry->visTime = (unsigned)atoi( Cmd_Argv( 5 ) ) * 1000;
	} else {
		entry->color = 7;
	}
}
