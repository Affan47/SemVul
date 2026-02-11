IntrAssComObjExpr ( void )
{
    Obj                 record;
    UInt                rnam;
    Obj                 rhs;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }
    if ( IntrCoding    > 0 ) { CodeAssComObjExpr(); return; }


    rhs = PopObj();


    rnam = RNamObj( PopObj() );


    record = PopObj();


    if ( TNUM_OBJ(record) == T_COMOBJ ) {
        AssPRec( record, rnam, rhs );
    }
    else {
        ASS_REC( record, rnam, rhs );
    }


    PushObj( rhs );
}
