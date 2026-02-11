cache_maxage( void )
{
    int age = 100;
    LIST * var = var_get( root_module(), constant_HCACHEMAXAGE );
    if ( !list_empty( var ) )
    {
        age = atoi( object_str( list_front( var ) ) );
        if ( age < 0 )
            age = 0;
    }
    return age;
}
