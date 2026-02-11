find_long_option( ARGPARSE_ARGS *arg,
		  ARGPARSE_OPTS *opts, const char *keyword )
{
    int i;
    size_t n;


    if( !*keyword )
	return -1;
    for(i=0; opts[i].short_opt; i++ )
	if( opts[i].long_opt && !strcmp( opts[i].long_opt, keyword) )
	    return i;
#if 0
    {
	ALIAS_DEF a;

	for( a = args->internal.aliases; a; a = a->next ) {
	    if( !strcmp( a->name, keyword) ) {

		args->internal.cur_alias = a;
		return -3;
	    }
	}
    }
#endif


    n = strlen( keyword );
    for(i=0; opts[i].short_opt; i++ ) {
	if( opts[i].long_opt && !strncmp( opts[i].long_opt, keyword, n ) ) {
	    int j;
	    for(j=i+1; opts[j].short_opt; j++ ) {
		if( opts[j].long_opt
		    && !strncmp( opts[j].long_opt, keyword, n ) )
		    return -2;
	    }
	    return i;
	}
    }
    return -1;
}
