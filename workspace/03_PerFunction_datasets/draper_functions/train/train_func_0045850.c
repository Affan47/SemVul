free_rewrite_location(rewrite_location_t *list)
{
rewrite_location_t	*next;

    while ( list ) {
	next = list->next;
	regfree(&list->preg);
	if ( list->dst ) free(list->dst);
	free(list);
	list = next;
    }
}
