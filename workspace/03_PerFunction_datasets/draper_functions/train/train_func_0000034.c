acl_index_by_name(char *name)
{
named_acl_t	*curr = named_acls;

    if ( !name || !named_acls ) return(0);
    while ( curr ) {
	if ( !strcmp(curr->name, name) ) {
	    return(curr->internal_number);
	}
	curr = curr->next;
    }
    return(0);
}
