timestamp(
	char	*target,
	time_t	*time )
{
	PATHNAME f1, f2;
	BINDING	binding, *b = &binding;
	char buf[ MAXJPATH ];

# ifdef DOWNSHIFT_PATHS
	char path[ MAXJPATH ];
	char *p = path;

	do *p++ = tolower( *target );
	while( *target++ );

	target = path;
# endif

	if( !bindhash )
	    bindhash = hashinit( sizeof( BINDING ), "bindings" );


	b->name = target;
	b->time = b->flags = 0;
	b->progress = BIND_INIT;

	if( hashenter( bindhash, (HASHDATA **)&b ) )
	    b->name = newstr( target );

	if( b->progress != BIND_INIT )
	    goto afterscanning;

	b->progress = BIND_NOENTRY;


	path_parse( target, &f1 );


	{
	    BINDING binding, *b = &binding;

	    f2 = f1;
	    f2.f_grist.len = 0;
	    path_parent( &f2 );
	    path_build( &f2, buf, 0 );

	    b->name = buf;
	    b->time = b->flags = 0;
	    b->progress = BIND_INIT;

	    if( hashenter( bindhash, (HASHDATA **)&b ) )
		b->name = newstr( buf );

	    if( !( b->flags & BIND_SCANNED ) )
	    {
		file_dirscan( buf, time_enter, bindhash );
		b->flags |= BIND_SCANNED;
	    }
	}


	if( f1.f_member.len )
	{
	    BINDING binding, *b = &binding;

	    f2 = f1;
	    f2.f_grist.len = 0;
	    f2.f_member.len = 0;
	    path_build( &f2, buf, 0 );

	    b->name = buf;
	    b->time = b->flags = 0;
	    b->progress = BIND_INIT;

	    if( hashenter( bindhash, (HASHDATA **)&b ) )
		b->name = newstr( buf );

	    if( !( b->flags & BIND_SCANNED ) )
	    {
		file_archscan( buf, time_enter, bindhash );
		b->flags |= BIND_SCANNED;
	    }
	}

    afterscanning:

	if( b->progress == BIND_SPOTTED )
	{
	    if( file_time( b->name, &b->time ) < 0 )
		b->progress = BIND_MISSING;
	    else
		b->progress = BIND_FOUND;
	}

	*time = b->progress == BIND_FOUND ? b->time : 0;
}
