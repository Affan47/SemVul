list_print( LIST *l )
{
	for( ; l; l = list_next( l ) )
	    printf( "%s ", l->string );
}
