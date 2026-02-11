list_append(
	LIST	*l,
	LIST	*nl )
{
	if( !nl )
	{

	}
	else if( !l )
	{
	    l = nl;
	}
	else
	{

	    l->tail->next = nl;
	    l->tail = nl->tail;
	}

	return l;
}
