targetchain(
	TARGETS	*chain,
	TARGETS	*targets )
{
	TARGETS *c;

	if( !targets )
	    return chain;
	else if( !chain )
	    return targets;

	chain->tail->next = targets;
	chain->tail = targets->tail;

	return chain;
}
