IntrRecExprBegin (
    UInt                top )
{
    Obj                 record;
    Obj                 old;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }
    if ( IntrCoding    > 0 ) { CodeRecExprBegin( top ); return; }


    record = NEW_PREC( 0 );


    if ( top ) {
        old = VAL_GVAR( Tilde );
        if ( old != 0 ) { PushObj( old ); }
        else            { PushVoidObj();  }
        AssGVar( Tilde, record );
    }


    PushObj( record );
}
