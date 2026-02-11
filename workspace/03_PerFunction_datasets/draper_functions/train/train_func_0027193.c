copysettings( SETTINGS *from )
{
	SETTINGS *head = 0, *v;

	for( ; from; from = from->next )
	{
	    SETTINGS *v = (SETTINGS *)malloc( sizeof( *v ) );
	    v->symbol = copystr( from->symbol );
	    v->value = list_copy( 0, from->value );
	    v->next = head;
	    head = v;
	}

	return head;
}
