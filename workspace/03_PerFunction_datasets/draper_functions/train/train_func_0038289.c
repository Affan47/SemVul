DoVerboseMutableAttribute (
    Obj                 self,
    Obj                 obj )
{
    Obj                 val;
    Int                 flag2;
    Obj                 kind;
    Obj                 flags;


    flag2 = INT_INTOBJ( FLAG2_FILT( self ) );


    kind  = TYPE_OBJ_FEO( obj );
    flags = FLAGS_TYPE( kind );


    if ( flag2 <= LEN_FLAGS( flags ) && ELM_FLAGS( flags, flag2 ) == True ) {
        return DoVerboseOperation1Args( self, obj );
    }


    val = DoVerboseOperation1Args( self, obj );


    if ( ENABLED_ATTR( self ) == 1 ) {
        switch ( TNUM_OBJ( obj ) ) {
        case T_COMOBJ:
        case T_POSOBJ:
        case T_DATOBJ:
            DoVerboseSetAttribute( SETTR_FILT(self), obj, val );
        }
    }


    return val;
}
