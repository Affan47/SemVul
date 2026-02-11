compile_local(
	PARSE	*parse,
	LOL	*args,
	int	*jmp )
{
	LIST *l;
	SETTINGS *s = 0;
	LIST	*nt = (*parse->left->func)( parse->left, args, jmp );
	LIST	*ns = (*parse->right->func)( parse->right, args, jmp );
	LIST	*result;

	if( DEBUG_COMPILE )
	{
	    debug_compile( 0, "local" );
	    list_print( nt );
	    printf( " = " );
	    list_print( ns );
	    printf( "\n" );
	}


	for( l = nt; l; l = list_next( l ) )
	    s = addsettings( s, 0, l->string, list_copy( (LIST*)0, ns ) );

	list_free( ns );
	list_free( nt );


	pushsettings( s );
	result = (*parse->third->func)( parse->third, args, jmp );
	popsettings( s );
	freesettings( s );

	return result;
}
