make1list(
	LIST	*l,
	TARGETS	*targets,
	int	flags )
{
    for( ; targets; targets = targets->next )
    {
	TARGET *t = targets->target;


	if( t->binding == T_BIND_UNBOUND )
	    make1bind( t, !( flags & RULE_EXISTING ) );

	if( ( flags & RULE_EXISTING ) && t->binding != T_BIND_EXISTS )
	    continue;

	if( ( flags & RULE_UPDATED ) && t->fate <= T_FATE_STABLE )
	    continue;


	if( flags & RULE_TOGETHER )
	{
	    LIST *m;

	    for( m = l; m; m = m->next )
		if( !strcmp( m->string, t->boundname ) )
		    break;

	    if( m )
		continue;
	}


	l = list_new( l, t->boundname, 1 );
    }

    return l;
}
