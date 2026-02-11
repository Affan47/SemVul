target_name( TARGET * t )
{
    static char buf[ 1000 ];
    if ( t->flags & T_FLAG_INTERNAL )
    {
        sprintf( buf, "%s (internal node)", object_str( t->name ) );
        return buf;
    }
    return object_str( t->name );
}
