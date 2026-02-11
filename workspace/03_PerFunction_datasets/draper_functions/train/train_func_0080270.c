IntrAssRecExpr ( void )
{
    Obj                 record;
    UInt                rnam;
    Obj                 rhs;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }
    if ( IntrCoding    > 0 ) { CodeAssRecExpr(); return; }


    rhs = PopObj();


    rnam = RNamObj( PopObj() );


    record = PopObj();


    ASS_REC( record, rnam, rhs );


    PushObj( rhs );
}
