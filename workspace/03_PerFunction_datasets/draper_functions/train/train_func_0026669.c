is_oops_internal_header(struct av *av)
{
    if ( !av || !av->attr ) return(FALSE);
    if ( !strncmp(av->attr, "X-oops-internal", 15) )
	return(TRUE);
    return(FALSE);
}
