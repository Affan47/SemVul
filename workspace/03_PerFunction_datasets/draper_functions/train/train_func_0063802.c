DoFilter (
    Obj                 self,
    Obj                 obj )
{
    Obj                 val;
    Int                 flag1;
    Obj                 kind;
    Obj                 flags;


    flag1 = INT_INTOBJ( FLAG1_FILT( self ) );


    kind  = TYPE_OBJ( obj );
    flags = FLAGS_TYPE( kind );


    if ( flag1 <= LEN_FLAGS( flags ) ) {
        val = ELM_FLAGS( flags, flag1 );
    }
    else {
        val = False;
    }


    return val;
}
