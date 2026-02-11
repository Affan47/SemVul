slapi_is_rootdse( const char *dn )
{
    if ( NULL != dn )
    {
	    if ( *dn == '\0' )
	    {
            return 1;
        }
    }
    return 0;
}
