add_rule_name( void * r_, void * result_ )
{
    RULE * const r = (RULE *)r_;
    LIST * * const result = (LIST * *)result_;
    if ( r->exported )
        *result = list_push_back( *result, object_copy( r->name ) );
}
