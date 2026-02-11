argument_list_free( struct arg_list * args, int args_count )
{
    int i, j;
    for ( i = 0; i < args_count; ++i )
    {
        for ( j = 0; j < args[ i ].size; ++j )
        {
            if ( args[ i ].args[ j ].type_name  )
                object_free( args[ i ].args[ j ].type_name );
            object_free( args[ i ].args[ j ].arg_name );
        }
        BJAM_FREE( args[ i ].args );
    }
    BJAM_FREE( args );
}
