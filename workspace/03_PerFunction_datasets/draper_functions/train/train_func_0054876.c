IntrIsbComObjExpr ( void )
{
    Obj                 isb;
    Obj                 record;
    UInt                rnam;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }
    if ( IntrCoding    > 0 ) { CodeIsbComObjExpr(); return; }


    rnam = RNamObj( PopObj() );


    record = PopObj();


    if ( TNUM_OBJ(record) == T_COMOBJ ) {
        isb = (IsbPRec( record, rnam ) ? True : False);
    }
    else {
        isb = (ISB_REC( record, rnam ) ? True : False);
    }


    PushObj( isb );
}
